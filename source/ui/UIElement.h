#pragma once

#include <memory>
#include <functional>

#include "datatypes/Vector2.h"
#include "datatypes/VRect.h"

// forward declare to uncirclify
class UIContainer;

class UIElement : public std::enable_shared_from_this<UIElement> {
private:
    //
    
protected:
    
    
public:
    std::weak_ptr<UIContainer> parent;
    
    VRect rect;
    
    UIElement();
    ~UIElement();
    
    virtual void Update() { }
    virtual void Draw() { }
    
    // internals... apparently need to be public?
    virtual void _Dive(std::function<bool(UIElement*)>& func, bool consumable, bool frontFirst, bool& finished);
};

// autoinclude after declaration since these two are pretty inextricably linked
#include "UIContainer.h"
