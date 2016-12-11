#include "starlight/GFXManager.h"

#include "starlight/gfx/DrawContextCanvas.h"

#include "UICanvas.h"

using starlight::gfx::Drawable;
using starlight::gfx::DrawContext;
using starlight::gfx::DrawContextCanvas;

using starlight::ui::UIElement;
using starlight::ui::UIContainer;
using starlight::ui::UICanvas;

UICanvas::UICanvas(VRect rect) {
    this->rect = rect;
    drawContext = std::make_unique<starlight::gfx::DrawContextCanvas>(rect.size);
}

void UICanvas::PreDraw() {
    drawContext->Clear();
    GFXManager::PushContext(drawContext.get());
    
    // both passes here so as not to mix things; one rendertarget at a time, please
    for (auto it = children.begin(); it != children.end(); it++) { (*it)->PreDraw(); }
    for (auto it = children.begin(); it != children.end(); it++) { (*it)->Draw(); }
    
    GFXManager::PopContext();
}

void UICanvas::Draw() {
    static_cast<DrawContextCanvas*>(drawContext.get())->Draw(rect + GFXManager::GetOffset());
}

