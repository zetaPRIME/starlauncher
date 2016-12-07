#pragma once

#include "starlight/datatypes/VRect.h"

namespace starlight {
    class GFXManager;
    namespace gfx {
        class DrawContext {
            friend class starlight::GFXManager;
        protected:
            virtual void Open() = 0;
            virtual void Close() = 0;
            virtual bool Prepare() = 0;
            bool drawReady = false;
        public:
            const VRect rect;
            DrawContext() : rect(VRect(0,0,1,1)) { }
            DrawContext(VRect rect) : rect(rect) { }
            virtual ~DrawContext() { }
            
        };
    }
}

