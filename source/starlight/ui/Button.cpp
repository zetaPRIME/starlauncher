#include "starlight/InputManager.h"
#include "starlight/GFXManager.h"
#include "starlight/ThemeManager.h"

#include "Button.h"

using starlight::Vector2;
using starlight::Color;

using starlight::gfx::Font;

using starlight::InputManager;
using starlight::GFXManager;
using starlight::ThemeManager;

using starlight::ui::Button;

void Button::Draw() {
    static auto& drw = ThemeManager::GetAsset("whatever");
    static auto& font = ThemeManager::GetFont("default");
    
    static auto& idle = ThemeManager::GetAsset("button.idle");
    static auto& press = ThemeManager::GetAsset("button.press");
    
    auto rect = this->rect + GFXManager::GetOffset();
    
    if (InputManager::GetDragHandle() == this) {
        /*drw->Draw(rect, nullptr, Color(0.32f,0.32f,0.32f));
        drw->Draw(rect.Expand(Vector2::one * -0.5f, Vector2::one), nullptr, Color(0.75f,0.75f,0.75f));
        drw->Draw(rect.Expand(Vector2::one * -1), nullptr, Color(0.5f,0.5f,0.5f));*/
        press->Draw(rect);
    } else {
        /*drw->Draw(rect, nullptr, Color(1,1,1));
        drw->Draw(rect.Expand(Vector2::one * -0.5f, Vector2::one), nullptr, Color(0.5f,0.5f,0.5f));
        drw->Draw(rect.Expand(Vector2::one * -1), nullptr, Color(0.75f,0.75f,0.75f));*/
        idle->Draw(rect);
    }
    
    static std::string label = "Button!\nI'm a grand bananaphone from the planet of the borpletydoos. :D";
    /*Vector2 c = rect.Center();
    font->Print(c-Vector2::h, label, Font::defaultSize, Color(0,0,0,0.25f), Vector2::half);
    font->Print(c+Vector2::h, label, Font::defaultSize, Color(0,0,0,0.25f), Vector2::half);
    font->Print(c-Vector2::v, label, Font::defaultSize, Color(0,0,0,0.25f), Vector2::half);
    font->Print(c+Vector2::v, label, Font::defaultSize, Color(0,0,0,0.25f), Vector2::half);
    
    font->Print(c, label, Font::defaultSize, Color(1,1,1), Vector2::half);*/
    font->Print(rect, label, Font::defaultSize, Color(0,1,1), Vector2(0.25f, 0.5f), Color(1,1,1,0.5f));
}

void Button::OnTouchOn() {
    if (InputManager::Pressed(KEY_TOUCH)) {
        InputManager::GetDragHandle().Grab(this);
    }
}

void Button::OnTouchOff() {
    auto& drag = InputManager::GetDragHandle();
    if (drag == this) drag.Release();
    
    rect.size = Vector2(32, 32); // test!
}

void Button::OnDragStart() {
    //
}

void Button::OnDragHold() {
    if (InputManager::TouchDragDist().Length() > InputManager::dragThreshold) {
        InputManager::GetDragHandle().PassUp();
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
