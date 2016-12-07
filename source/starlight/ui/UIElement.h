#pragma once

#include <memory>
#include <functional>

#include "starlight/datatypes/Vector2.h"
#include "starlight/datatypes/VRect.h"

namespace starlight {
    namespace ui {
        // forward declare to uncirclify
        class UIContainer;

        class UIElement : public std::enable_shared_from_this<UIElement> {
            friend class UIContainer;
        private:
            //
            
        protected:
            virtual void _Dive(std::function<bool(UIElement*)>& func, bool consumable, bool frontFirst, bool& finished);
            
        public:
            std::weak_ptr<UIContainer> parent;
            
            VRect rect;
            
            UIElement();
            virtual ~UIElement();
            
            virtual void Update() { }
            virtual void Draw() { }
            
        };
    }
}

// autoinclude after declaration since these two are pretty inextricably linked
#include "UIContainer.h"
