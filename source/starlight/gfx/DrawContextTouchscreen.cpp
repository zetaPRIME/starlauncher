#include <sf2d.h>

#include "DrawContextTouchscreen.h"

using starlight::gfx::DrawContextTouchscreen;

void DrawContextTouchscreen::Open() {
    // let's only do this when we're ready to draw
    //sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
}

void DrawContextTouchscreen::Close() {
    sf2d_end_frame();
    drawReady = false;
}

bool DrawContextTouchscreen::Prepare() {
    if (drawReady) return true;
    drawReady = true;
    sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
    return true;
}


