#pragma once

#include <string>
#include <unordered_map>

#include "starlight/gfx/drawable.h"

namespace starlight {
    // forward declare
    namespace gfx {
        template <class T>
        class ThemeRef;
    }

    class ThemeManager {
        template <class T>
        friend class ThemeRef;
    private:
        static std::unordered_map<std::string, gfx::ThemeRef<gfx::Drawable>> drawables;
        //static std::unordered_map<std::string, ThemeRef<Font>> fonts;
    public:
        ThemeManager() = delete; // "static" class
        
        static const gfx::ThemeRef<gfx::Drawable>& GetAsset(std::string name);
    };
}