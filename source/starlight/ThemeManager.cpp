#include <cstdlib>
#include <string>
#include <fstream>
#include <sys/stat.h>

#include <citro3d.h>
#include <sf2d.h>
#include <sftd.h>

#include "starlight/_incLib/lodepng.h"
#include "starlight/_incLib/json.hpp"

#include "ThemeManager.h"
#include "starlight/gfx/ThemeRef.h"

#include "starlight/gfx/DrawableImage.h"
#include "starlight/gfx/DrawableTest.h"
#include "starlight/gfx/FontSFTD.h"

#include "starlight/gfx/RenderCore.h"

using std::string;

using nlohmann::json;

using starlight::Vector2;

using starlight::ThemeManager;
using starlight::gfx::Drawable;
using starlight::gfx::Font;
using starlight::gfx::ThemeRef;

using starlight::gfx::DrawableImage;

using starlight::gfx::RenderCore;
using starlight::gfx::CTexture;

namespace {
    inline int NextPow2(unsigned int x) {
        --x;
        x |= x >> 1;
        x |= x >> 2;
        x |= x >> 4;
        x |= x >> 8;
        x |= x >> 16;
        return ++x >= 64 ? x : 64; // min size to keep gpu from locking
    }
    
    inline string FindExtension(const string& path) {
        auto idot = path.rfind('.');
        if (idot == string::npos || idot == 0) return string(); // no dot found, or .hiddenfile? return empty
        auto idir = path.rfind('/');
        if (idir != string::npos && idir >= idot-1) return string(); // last dot in containing directory, or dir/.hiddenfile? return empty
        return path.substr(idot+1); // return extension without dot
    }
    
    CTexture* LoadPNG(const std::string& path, bool isPremult = false) {
        unsigned char* imgbuf;
        unsigned width, height;
        lodepng_decode32_file(&imgbuf, &width, &height, path.c_str());
        
        unsigned bw = NextPow2(width), bh = NextPow2(height);
        
        u8* gpubuf = static_cast<u8*>(linearAlloc(bw*bh*4));
        
        u8* src = static_cast<u8*>(imgbuf); u8* dst = static_cast<u8*>(gpubuf);
        
        if (isPremult) {
            // just convert endianness
            for(unsigned iy = 0; iy<height; iy++) {
                for (unsigned ix = 0; ix < height; ix++) {
                    int r = *src++;
                    int g = *src++;
                    int b = *src++;
                    int a = *src++;
                    
                    *dst++ = a;
                    *dst++ = b;
                    *dst++ = g;
                    *dst++ = r;
                }
                dst += (bw - width) * 4; // skip the difference
            }
        } else {
            // convert and premultiply
            for(unsigned iy = 0; iy<height; iy++) {
                for (unsigned ix = 0; ix < height; ix++) {
                    int r = *src++;
                    int g = *src++;
                    int b = *src++;
                    int a = *src++;
                    
                    float aa = (1.0f / 255.0f) * a;
                    
                    *dst++ = a;
                    *dst++ = b*aa;
                    *dst++ = g*aa;
                    *dst++ = r*aa;
                }
                dst += (bw - width) * 4; // skip the difference
            }
        }
        // completely skipping over the difference instead of erasing might eventually lead to garbage outside of frame,
        // but meh; that'll only be visible if you intentionally push the UVs outside the image proper
        
        CTexture* tx = RenderCore::LoadTexture(static_cast<void*>(gpubuf), bw, bh);
        tx->size = Vector2(width, height); // and for now just fix the size after the fact
        
        std::free(imgbuf);
        linearFree(gpubuf);
        
        return tx;
    }
}

std::unordered_map<std::string, ThemeRef<Drawable>> ThemeManager::drawables;
std::unordered_map<std::string, ThemeRef<Font>> ThemeManager::fonts;
std::list<std::function<void()>> ThemeManager::tq;

const ThemeRef<Drawable>& ThemeManager::GetAsset(std::string name) {
    auto const& itr = drawables.find(name);
    if (itr == drawables.end()) {
        return drawables.insert(std::make_pair(name, ThemeRef<Drawable>(name))).first->second;
    } else return itr->second;
}

const ThemeRef<Font>& ThemeManager::GetFont(std::string name) {
    auto const& itr = fonts.find(name);
    if (itr == fonts.end()) {
        return fonts.insert(std::make_pair(name, ThemeRef<Font>(name))).first->second;
    } else return itr->second;
}

void ThemeManager::Fulfill(ThemeRef<Drawable>& ref) {
    ref.ptr = new starlight::gfx::DrawableTest(); // todo: nil drawable
    /*tq.push_back([&ref](){
       ThemeManager::Fulfill_(ref);
    });*/
    Fulfill_(ref);
}

void ThemeManager::Fulfill_(ThemeRef<Drawable>& ref) {
    string path = ResolveAssetPath(ref.name);
    string ext = FindExtension(path);
    printf("load: %s (%s)\n", path.c_str(), ext.c_str());
    /**/ if (ext == "png") {
        ref.ptr = new DrawableImage(LoadPNG(path));
    }
    else if (ext == "json") {
        json j;
        { // using:
            std::ifstream fs(path);
            fs >> j;
        }
        auto st = j.dump();
        printf("file contents: %s\n", st.c_str());
        ref.ptr = new starlight::gfx::DrawableTest();
    }
    else ref.ptr = new starlight::gfx::DrawableTest();
}

void ThemeManager::Fulfill(ThemeRef<Font>& ref) {
    sftd_font* f = sftd_load_font_file("romfs:/Arcon-Regular.otf");
    auto test = new starlight::gfx::FontSFTD(f);
    ref.ptr = test;
}

void ThemeManager::LoadProc() {
    while (!tq.empty()) {
        tq.front()();
        tq.pop_front();
    }
}

string ThemeManager::ResolveAssetPath(const string& id) {
    struct stat buf;
    string path(id.length() + 64, ' '); // preallocate buffer space
    path.clear(); path.append("romfs:/"); path.append(id); path.append(".json");
    printf("attempt: %s\n", path.c_str());
    if (stat(path.c_str(), &buf) == 0) return path;
    path.erase(path.end()-5, path.end()); path.append(".png");
    printf("attempt: %s\n", path.c_str());
    if (stat(path.c_str(), &buf) == 0) return path;
    
    return string();
}

