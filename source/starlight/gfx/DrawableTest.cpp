#include <sf2d.h>

#include "starlight/datatypes/Color.h"
#include "starlight/GFXManager.h"

#include "DrawableTest.h"

using starlight::Color;
using starlight::GFXManager;
using starlight::gfx::DrawableTest;

void DrawableTest::Draw(const Vector2& position, OptRef<Vector2> hotspot, const OptRef<VRect> sampleRect, OptRef<Color> color, float rotation, const Vector2& scale) {
    if (GFXManager::PrepareForDrawing()) {
        static u32 col = Color(0, 0.5f, 1);
        sf2d_draw_rectangle_rotate(position.x, position.y, 16, 16, col, rotation);
    }
}

