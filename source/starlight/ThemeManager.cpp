#include "ThemeManager.h"
#include "starlight/gfx/ThemeRef.h"

#include "starlight/gfx/DrawableTest.h"

using starlight::ThemeManager;
using starlight::gfx::Drawable;
using starlight::gfx::ThemeRef;

std::unordered_map<std::string, ThemeRef<Drawable>> ThemeManager::drawables;

const ThemeRef<Drawable>& ThemeManager::GetAsset(std::string name) {
    auto itr = drawables.find(name);
    if (itr == drawables.end()) {
        return drawables.insert(std::make_pair(name, ThemeRef<Drawable>(name))).first->second;
    } else return itr->second;
}

void ThemeManager::Fulfill(ThemeRef<Drawable>& ref) {
    static auto test = new starlight::gfx::DrawableTest();
    ref.ptr = test;
}

