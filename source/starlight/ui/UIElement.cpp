#include "UIElement.h"

using starlight::Vector2;
using starlight::VRect;
using starlight::ui::UIElement;
using starlight::ui::UIContainer;

UIElement::UIElement() { }
UIElement::~UIElement() { }

void UIElement::_Dive(std::function<bool(UIElement*)>& func, bool consumable, bool frontFirst, bool& finished) {
    finished = func(this) && consumable;
}

VRect UIElement::ViewRect() {
    if (auto p = parent.lock()) {
        return rect + p->scrollOffset;
    }
    return rect;
}

VRect UIElement::ScreenRect() {
    if (auto p = parent.lock()) {
        return ViewRect() + p->ScreenRect().pos;
    }
    return rect;
}