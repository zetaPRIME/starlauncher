#include <algorithm>

#include "UIContainer.h"

UIContainer::UIContainer() {
    
}

UIContainer::~UIContainer() {
    
}

void UIContainer::Dive(std::function<bool(UIElement&)> func, bool consumable, bool frontFirst) {
    _Dive(func, consumable, frontFirst);
}
void UIContainer::_Dive(std::function<bool(UIElement&)> func, bool& consumable, bool& frontFirst) {
    static const auto loop = [&] (std::shared_ptr<UIElement> elem) {
        if (auto cont = std::dynamic_pointer_cast<UIContainer>(elem)) {
            cont->_Dive(func, consumable, frontFirst);
        } else func(*(elem.get()));
    };
    
    // iterate last-to-first if *visually* front
    if (frontFirst) for_each(children.rbegin(), children.rend(), loop);
    else for_each(children.begin(), children.end(), loop);
    
    func(*this);
}








