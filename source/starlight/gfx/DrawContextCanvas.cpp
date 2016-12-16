#include <cmath>
#include <sf2d.h>
#include <citro3d.h>

#include "starlight/datatypes/Color.h"
#include "starlight/GFXManager.h"

#include "DrawContextCanvas.h"

using starlight::Vector2;
using starlight::VRect;
using starlight::Color;
using starlight::GFXManager;
using starlight::gfx::DrawContextCanvas;

using starlight::gfx::RenderCore;
using starlight::gfx::CRenderTarget;

namespace {
    inline int nextpwt(int x) {
        if (x < 0) return 0;
        --x;
        x |= x >> 1;
        x |= x >> 2;
        x |= x >> 4;
        x |= x >> 8;
        x |= x >> 16;
        return x+1;
    }
}

DrawContextCanvas::DrawContextCanvas(VRect rect) : DrawContext(rect) {
    target = std::make_unique<CRenderTarget>(rect.size.x, rect.size.y);
}

DrawContextCanvas::DrawContextCanvas(Vector2 size) : DrawContextCanvas(VRect(Vector2::zero, size)) { }

DrawContextCanvas::~DrawContextCanvas() {
    // hmm. don't think we need to do anything here anymore
}

// drawcontext stuff
void DrawContextCanvas::Open() { }

void DrawContextCanvas::Close() {
    drawReady = false;
}

bool DrawContextCanvas::Prepare() {
    if (drawReady) return true;
    drawReady = true;
    target->BindTarget();
    return true;
}

void DrawContextCanvas::Clear(Color color) {
    target->Clear(color);
}
void DrawContextCanvas::Clear() { Clear(Color(0,0,0,0)); }
//void DrawContextCanvas::Clear() { Clear(Color(0,0.5,0,0.5)); }
//void DrawContextCanvas::Clear() { Clear(Color(0.5,0.5,0.5,0.5)); }

// drawable stuff
void DrawContextCanvas::Draw(const Vector2& position, OptRef<Vector2> hotspot, OptRef<VRect> sampleRect, OptRef<Color> color, float rotation, const Vector2& scale) {
    if (GFXManager::PrepareForDrawing()) {
        //const VRect& sr = sampleRect ? sampleRect.get() : rect;//VRect(0, 0, texture->width, texture->height);
        //sf2d_draw_texture_part_rotate_scale_blend(texture, position.x, position.y, rotation, sr.pos.x, sr.pos.y, sr.size.x, sr.size.y, scale.x, scale.y, color ? color.get() : Color(1,1,1,1));
        // todo: figure out hotspot...
    }
}

void DrawContextCanvas::Draw(const VRect& rect, OptRef<VRect> sampleRect, OptRef<Color> color) {
    if (GFXManager::PrepareForDrawing()) {
        const VRect& sr = sampleRect ? sampleRect.get() : this->rect;
        //sf2d_draw_texture_part_scale_blend(texture, rect.pos.x, rect.pos.y, sr.pos.x, sr.pos.y, sr.size.x, sr.size.y, rect.size.x / sr.size.x, rect.size.y / sr.size.y, color ? color.get() : Color(1,1,1,1));
        target->Bind(color ? color.get() : Color(1,1,1,1));
        RenderCore::DrawQuad(rect, VRect(sr.pos / target->txSize, sr.size / target->txSize));
    }
}