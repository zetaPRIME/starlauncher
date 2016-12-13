#include <sf2d.h>
#include <sftd.h>

#include "ThemeManager.h"
#include "starlight/gfx/ThemeRef.h"

#include "starlight/gfx/DrawableTest.h"
#include "starlight/gfx/FontSFTD.h"

using starlight::ThemeManager;
using starlight::gfx::Drawable;
using starlight::gfx::Font;
using starlight::gfx::ThemeRef;

std::unordered_map<std::string, ThemeRef<Drawable>> ThemeManager::drawables;
std::unordered_map<std::string, ThemeRef<Font>> ThemeManager::fonts;

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
    static auto test = new starlight::gfx::DrawableTest();
    ref.ptr = test;
}

void ThemeManager::Fulfill(ThemeRef<Font>& ref) {
    sftd_font* f = sftd_load_font_file("romfs:/Arcon-Regular.otf");
    auto test = new starlight::gfx::FontSFTD(f);
    ref.ptr = test;
}

