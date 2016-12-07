#pragma once

#include "starlight/gfx/Drawable.h"

namespace starlight {
    namespace gfx {
        class DrawableTest : public Drawable {
        public:
            DrawableTest() { }
            ~DrawableTest() override { }
            
            void Draw(const Vector2& position, OptRef<Vector2> hotspot = nullptr, const OptRef<VRect> sampleRect = nullptr, OptRef<Color> color = nullptr, float rotation = 0, const Vector2& scale = Vector2::one) override;
            
        };
    }
}

