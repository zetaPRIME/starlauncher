#include "starlight/InputManager.h"
#include "starlight/GFXManager.h"
#include "starlight/ThemeManager.h"

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

namespace {
    VRect brah;
    Vector2 tpos;
    bool bt = true;
}

TouchScreenCanvas::TouchScreenCanvas() {
    rect = VRect(0, 0, 320, 240);
    drawContext = std::make_unique<DrawContextTouchscreen>();
}

void TouchScreenCanvas::Update() {
    // input test
    if (InputManager::Pressed(KEY_TOUCH)) {
        tpos = InputManager::TouchPos();
        bt = true;
        Dive(
            [&tpos, &brah, &bt, this](UIElement* e){
                //brah = e->ScreenRect();
                return e->ScreenRect().Contains(tpos);
            },
            [&tpos, &brah, &bt](UIElement* e){
                e->OnTap();
                if (bt) {
                    brah = e->ScreenRect();
                    bt = false;
                }
                return true;
            }, true, true);
    }
    
    // and update children
    this->UIContainer::Update();
}

void TouchScreenCanvas::PreDraw() {
    this->UIContainer::PreDraw();
}

void TouchScreenCanvas::Draw() {
    static auto blah = ThemeManager::GetAsset("");
    GFXManager::PushContext(drawContext.get());
    this->UIContainer::Draw();
    blah->Draw(brah, nullptr, Color(0,0,1,0.25f));
    blah->Draw(VRect(tpos, Vector2::one).Expand(Vector2::one), nullptr, Color(0,1,0));
    GFXManager::PopContext();
}
