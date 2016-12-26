#include "Label.h"

using starlight::ui::Label;

Label::Label(VRect rect) {
    this->rect = rect;
    font = const_cast<gfx::ThemeRef<gfx::Font>*>(&(ThemeManager::GetFont("default.12")));
}

void Label::AutoSize() {
    if (autoSizeV) {
        float h = (*font)->Measure(text, 1, rect.size.x).y;
        Resize(rect.size.x, h);
    }
    
    MarkForRedraw();
}

void Label::SetText(const std::string& text) {
    this->text = text;
    AutoSize();
}

void Label::SetFont(const std::string& fontName) {
    font = const_cast<gfx::ThemeRef<gfx::Font>*>(&(ThemeManager::GetFont(fontName)));
    AutoSize();
}

void Label::Draw() {
    (*font)->Print(rect, text, 1, color, justification, borderColor);
}

