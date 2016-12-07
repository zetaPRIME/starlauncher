#pragma once

#include <forward_list>

#include "starlight/gfx/DrawContext.h"

namespace starlight {
    class GFXManager {
    private:
        static std::forward_list<gfx::DrawContext*> ctxStack;
    public:
        GFXManager() = delete;
        
        static void PushContext(gfx::DrawContext* context);
        static gfx::DrawContext* PopContext();
        static gfx::DrawContext* GetContext();
        
        static bool PrepareForDrawing();
    };
}
