#pragma once

#include <memory>

#include "datatypes/Vector2.h"
#include "datatypes/VRect.h"

// forward declare to uncirclify
class UIContainer;

class UIElement {
public:
    std::weak_ptr<UIContainer> parent;
    
    VRect rect;
    
    UIElement();
    ~UIElement();
    
    virtual void Update() { }
    virtual void Draw() { }
    
};

// autoinclude after declaration since these two are pretty inextricably linked
#include "UIContainer.h"
