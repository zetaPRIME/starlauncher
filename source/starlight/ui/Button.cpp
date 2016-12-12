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
    
    if (InputManager::GetDragHandle() == this) {
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
}

void Button::OnDragStart() {
    //
}

void Button::OnDragHold() {
    if (InputManager::TouchDragDist().Length() > InputManager::dragThreshold) {
        InputManager::GetDragHandle().PassUp(true);
    }
}

#define err(nth, wat) *((unsigned int*)0x00100000+(nth))=wat;
#define ded(wat) err(0,wat)
#define die() ded(0xDEADBEEF);

void Button::OnDragRelease() {
    if (InputManager::Released(KEY_TOUCH)) {
        //
    }
}
