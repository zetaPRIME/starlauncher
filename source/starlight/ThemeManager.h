#pragma once
#include "starlight/_global.h"

#include <string>
#include <unordered_map>

#include "starlight/gfx/Drawable.h"
#include "starlight/gfx/Font.h"

namespace starlight {
    // forward declare
    namespace gfx {
        template <class T>
        class ThemeRef;
    }

    class ThemeManager {
        template <class T>
        friend class starlight::gfx::ThemeRef;
    private:
        static std::unordered_map<std::string, gfx::ThemeRef<gfx::Drawable>> drawables;
        static std::unordered_map<std::string, gfx::ThemeRef<gfx::Font>> fonts;
    protected:
        static void Fulfill(gfx::ThemeRef<gfx::Drawable>& ref);
        static void Fulfill(gfx::ThemeRef<gfx::Font>& ref);
    public:
        ThemeManager() = delete; // "static" class
        
        static const gfx::ThemeRef<gfx::Drawable>& GetAsset(std::string name);
        static const gfx::ThemeRef<gfx::Font>& GetFont(std::string name);
    };
}

// post-include dependency
#include "starlight/gfx/ThemeRef.h"
