#pragma once
#include "starlight/_global.h"

#include <string>
#include <unordered_map>
#include <list>
#include <functional>

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
        static std::list<std::function<void()>> tq;
    protected:
        static void Fulfill(gfx::ThemeRef<gfx::Drawable>& ref);
        static void Fulfill_(gfx::ThemeRef<gfx::Drawable>& ref);
        static void Fulfill(gfx::ThemeRef<gfx::Font>& ref);
    public:
        ThemeManager() = delete; // "static" class
        
        static const gfx::ThemeRef<gfx::Drawable>& GetAsset(const std::string& name);
        static const gfx::ThemeRef<gfx::Font>& GetFont(const std::string& name);
        
        static void LoadProc();
        
        static std::string ResolveAssetPath(const std::string& id);
        static std::string ResolveFontPath(const std::string& id);
    };
}

// post-include dependency
#include "starlight/gfx/ThemeRef.h"
