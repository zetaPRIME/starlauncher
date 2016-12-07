#include "UIElement.h"

using starlight::ui::UIElement;
using starlight::ui::UIContainer;

UIElement::UIElement() { }
UIElement::~UIElement() { }

void UIElement::_Dive(std::function<bool(UIElement*)>& func, bool consumable, bool frontFirst, bool& finished) {
    finished = func(this) && consumable;
}
