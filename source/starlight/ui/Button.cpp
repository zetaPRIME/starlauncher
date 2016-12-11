#include "starlight/ThemeManager.h"

#include "Button.h"

using starlight::ThemeManager;

using starlight::ui::Button;

void Button::Draw() {
    static auto drw = ThemeManager::GetAsset("whatever");
    
    drw->Draw(rect, nullptr, starlight::Color(1,1,1));
    drw->Draw(rect.Expand(Vector2::one * -0.5f, Vector2::one), nullptr, starlight::Color(0.5f,0.5f,0.5f));
    drw->Draw(rect.Expand(Vector2::one * -1), nullptr, starlight::Color(0.75f,0.75f,0.75f));
}

