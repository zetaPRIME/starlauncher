#include "starlight/GFXManager.h"

#include "starlight/gfx/DrawContextTouchscreen.h"

#include "TouchScreenCanvas.h"

using starlight::Vector2;
using starlight::VRect;

//using starlight::gfx::Drawable;
using starlight::gfx::DrawContext;
using starlight::gfx::DrawContextTouchscreen;

using starlight::ui::UIElement;
using starlight::ui::UIContainer;
using starlight::ui::UICanvas;
using starlight::ui::TouchScreenCanvas;

TouchScreenCanvas::TouchScreenCanvas() {
    rect = VRect(0, 0, 320, 240);
    drawContext = std::make_unique<DrawContextTouchscreen>();
}

void TouchScreenCanvas::PreDraw() {
    this->UIContainer::PreDraw();
}

void TouchScreenCanvas::Draw() {
    this->UIContainer::Draw();
}
