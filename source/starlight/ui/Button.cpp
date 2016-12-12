#include "starlight/InputManager.h"
#include "starlight/GFXManager.h"
#include "starlight/ThemeManager.h"

#include "Button.h"

using starlight::InputManager;
using starlight::GFXManager;
using starlight::ThemeManager;

using starlight::ui::Button;

void Button::Draw() {
    static auto drw = ThemeManager::GetAsset("whatever");
    
    auto rect = this->rect + GFXManager::GetOffset();
    
    if (InputManager::GetDragHandle().valid()) {
        drw->Draw(rect, nullptr, starlight::Color(0.32f,0.32f,0.32f));
        drw->Draw(rect.Expand(Vector2::one * -0.5f, Vector2::one), nullptr, starlight::Color(0.75f,0.75f,0.75f));
        drw->Draw(rect.Expand(Vector2::one * -1), nullptr, starlight::Color(0.5f,0.5f,0.5f));
    } else {
        drw->Draw(rect, nullptr, starlight::Color(1,1,1));
        drw->Draw(rect.Expand(Vector2::one * -0.5f, Vector2::one), nullptr, starlight::Color(0.5f,0.5f,0.5f));
        drw->Draw(rect.Expand(Vector2::one * -1), nullptr, starlight::Color(0.75f,0.75f,0.75f));
    }
}

void Button::OnTouchOn() {
    if (InputManager::Pressed(KEY_TOUCH)) {
        InputManager::GetDragHandle().Grab(this);
    }
    rect.pos += Vector2::one * 2;
}

void Button::OnDragStart() {
    rect.pos.x += 2;
}

void Button::OnDragHold() {
    if (InputManager::TouchDragDist().Length() > InputManager::dragThreshold) {
        //InputManager::GetDragHandle().PassUp(true);
        rect.pos.y += 1;
    }
}

#define err(nth, wat) *((unsigned int*)0x00100000+(nth))=wat;
#define ded(wat) err(0,wat)
#define die() ded(0xDEADBEEF);

void Button::OnDragRelease() {
    //if (this == static_cast<UIElement*>(nullptr)) { ded(0x1337BEEF); }
    if (!InputManager::GetDragHandle().released) { rect.pos.x = 88; }
    if (InputManager::Released(KEY_TOUCH)) {
        rect.size = Vector2::one * 64;
        rect.pos.y += 5;
    }
}
