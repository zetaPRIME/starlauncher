#include <algorithm>

#include "UIContainer.h"

UIContainer::UIContainer() {
    
}

UIContainer::~UIContainer() {
    
}

void UIContainer::Dive(std::function<bool(UIElement&)> func, bool consumable, bool frontFirst) {
    bool finished = false;
    _Dive(func, consumable, frontFirst, finished);
}

void UIContainer::_Dive(std::function<bool(UIElement&)>& func, bool consumable, bool frontFirst, bool& finished) {
    if (frontFirst) for (auto itr = children.rbegin(); itr != children.rend(); ++itr) {
        (*itr)->_Dive(func, consumable, frontFirst, finished);
        if (finished) return;
    } else for (auto itr = children.begin(); itr != children.end(); ++itr) {
        (*itr)->_Dive(func, consumable, frontFirst, finished);
        if (finished) return;
    }
    // same thing as plain UIElement's version
    finished = func(*this) && consumable;
}


