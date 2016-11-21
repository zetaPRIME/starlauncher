#pragma once

#include <memory>
#include <list>
#include <functional>

#include "datatypes/Vector2.h"
#include "datatypes/VRect.h"

#include "UIElement.h"

// no forward declaration in this header

class UIContainer : public UIElement {
private:
    std::list<std::shared_ptr<UIElement>> children;
    
    void _Dive(std::function<bool(UIElement&)> func, bool& consumable, bool& frontFirst);
    
public:
    UIContainer();
    ~UIContainer();
    
    void Dive(std::function<bool(UIElement&)>, bool consumable = true, bool frontFirst = true);
};

