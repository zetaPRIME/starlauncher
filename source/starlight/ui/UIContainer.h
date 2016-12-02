#pragma once

#include <memory>
#include <list>
#include <functional>

#include "starlight/datatypes/Vector2.h"
#include "starlight/datatypes/VRect.h"

#include "UIElement.h"

// no forward declaration in this header

class UIContainer : public UIElement {
private:
    std::list<std::shared_ptr<UIElement>> children;
    
protected:
    void _Dive(std::function<bool(UIElement*)>& func, bool consumable, bool frontFirst, bool& finished);
    
public:
    UIContainer();
    ~UIContainer();
    
    void Dive(std::function<bool(UIElement*)>, bool consumable = true, bool frontFirst = true);
    //void _Dive(std::function<bool(UIElement*)>& func, bool consumable, bool frontFirst, bool& finished);
    
    void Add(std::shared_ptr<UIElement> elem);
    //void Add(UIElement* elem);
    void Remove(std::shared_ptr<UIElement> elem);
};

