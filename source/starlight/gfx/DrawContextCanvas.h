#pragma once

#include <sf2d.h>

#include "starlight/gfx/Drawable.h"
#include "starlight/gfx/DrawContext.h"

namespace starlight {
    namespace gfx {
        class DrawContextCanvas : public DrawContext, public Drawable {
        private:
            sf2d_rendertarget* target;
            sf2d_texture* texture;
            
        protected:
            void Open() override;
            void Close() override;
            bool Prepare() override;
        public:
            DrawContextCanvas(VRect rect);
            DrawContextCanvas(Vector2 size);
            ~DrawContextCanvas();
            
            void Draw(const Vector2& position, OptRef<Vector2> hotspot = nullptr, OptRef<VRect> sampleRect = nullptr, OptRef<Color> color = nullptr, float rotation = 0, const Vector2& scale = Vector2::one) override;
            void Draw(const VRect& rect, OptRef<VRect> sampleRect = nullptr, OptRef<Color> color = nullptr) override;
            
            void Clear(Color color) override;
            void Clear() override;
        };
    }
}