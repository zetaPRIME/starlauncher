#pragma once

#include <experimental/optional>

#include "starlight/datatypes/Vector2.h"
#include "starlight/datatypes/VRect.h"
#include "starlight/datatypes/Color.h"

#include "starlight/datatypes/OptRef.h"

// no way am I typing this much for EVERYTHING
#define opt_ std::experimental::optional

namespace starlight {
    namespace gfx {
        class Drawable {
        public:
            Drawable();
            virtual ~Drawable();
            
            // pattern after:
            // public abstract void Draw(DrawContext context, PxRect rect, PxRect? sampleRect = null, DrawColor? color = null);
            // public abstract void Draw(DrawContext context, FxVector position, FxVector? align = null, PxRect? sampleRect = null, DrawColor? color = null, float rotation = 0, FxVector? scale = null);
            virtual void Draw(const Vector2& position, OptRef<Vector2> hotspot = nullptr, const OptRef<VRect> sampleRect = nullptr, OptRef<starlight::Color> color = nullptr, float rotation = 0, const Vector2& scale = Vector2::one) = 0;
            //virtual void Draw(const Vector2& position, const Vector2* hotspot = nullptr, const VRect* sampleRect = nullptr, starlight::Color* color = nullptr, float rotation = 0, const Vector2& scale = Vector2::one) = 0;
            void test();
        };
    }
}


