#include <cmath>
#include <sf2d.h>

#include "starlight/datatypes/Color.h"
#include "starlight/GFXManager.h"

#include "DrawContextCanvas.h"

using starlight::Vector2;
using starlight::VRect;
using starlight::Color;
using starlight::GFXManager;
using starlight::gfx::DrawContextCanvas;

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
    //constexpr const int tile = 1;//32;
    int w = nextpwt(rect.size.x);//std::ceil(rect.size.x / tile) * tile;
    int h = nextpwt(rect.size.x);//std::ceil(rect.size.y / tile) * tile;
    target = sf2d_create_rendertarget(h, w); // axes inverted
    
    // fix projection, whee~
    //Mtx_Ortho(&(target->projection), w, 0.0f, h, 0.0f, 0.0f, 1.0f, true); // upside down
    Mtx_Ortho(&(target->projection), 0.0f, w, 0.0f, h, 0.0f, 1.0f, true); // axes also inverted here
    
    // and we have to manually construct a sf2d_texture in-place...
    texture = new sf2d_texture();
    texture->tiled = 1;
    texture->width = rect.size.x;
    texture->height = rect.size.y;
    texture->tex = target->target->renderBuf.colorBuf; // wheeee
    //sf2d_texture_tile32(texture); // watch this derp things up royally :D
}

DrawContextCanvas::DrawContextCanvas(Vector2 size) : DrawContextCanvas(VRect(Vector2::zero, size)) { }

DrawContextCanvas::~DrawContextCanvas() {
    delete texture; // manual flat delete due to manual construction
    sf2d_free_target(target);
}

// drawcontext stuff
void DrawContextCanvas::Open() { }

void DrawContextCanvas::Close() {
    sf2d_end_frame();
    drawReady = false;
}

bool DrawContextCanvas::Prepare() {
    if (drawReady) return true;
    drawReady = true;
    sf2d_start_frame_target(target);
    return true;
}

void DrawContextCanvas::Clear(Color color) {
    sf2d_clear_target(target, color);
}
void DrawContextCanvas::Clear() { sf2d_clear_target(target, 0); }

// drawable stuff
void DrawContextCanvas::Draw(const Vector2& position, OptRef<Vector2> hotspot, OptRef<VRect> sampleRect, OptRef<Color> color, float rotation, const Vector2& scale) {
    if (GFXManager::PrepareForDrawing()) {
        const VRect& sr = sampleRect ? sampleRect.get() : rect;//VRect(0, 0, texture->width, texture->height);
        sf2d_draw_texture_part_rotate_scale_blend(texture, position.x, position.y, rotation, sr.pos.x, sr.pos.y, sr.size.x, sr.size.y, scale.x, scale.y, color ? color.get() : Color(1,1,1,1));
        // todo: figure out hotspot...
    }
}

void DrawContextCanvas::Draw(const VRect& rect, OptRef<VRect> sampleRect, OptRef<Color> color) {
    if (GFXManager::PrepareForDrawing()) {
        const VRect& sr = sampleRect ? sampleRect.get() : this->rect;
        sf2d_draw_texture_part_scale_blend(texture, rect.pos.x, rect.pos.y, sr.pos.x, sr.pos.y, sr.size.x, sr.size.y, rect.size.x / sr.size.x, rect.size.y / sr.size.y, color ? color.get() : Color(1,1,1,1));
    }
}