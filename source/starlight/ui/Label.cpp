#include "Label.h"

#include "starlight/GFXManager.h"

using starlight::GFXManager;

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
    
    dl = gfx::DisplayList();
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
    auto rect = (this->rect + GFXManager::GetOffset()).IntSnap();
    if (!dl.Valid()) {
        (*font)->PrintDisplayList(&dl, rect, text, 1, color, justification, borderColor);
    }
    //(*font)->Print(rect, text, 1, color, justification, borderColor);
    dl.Run(rect.pos);
}

