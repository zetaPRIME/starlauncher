#pragma once
#include "starlight/_global.h"

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
            virtual void _Dive(std::function<bool(UIElement*)>& check, std::function<bool(UIElement*)>& func, bool consumable, bool frontFirst, bool& finished);
            virtual void _Dive(std::function<bool(UIElement*)>& func, bool consumable, bool frontFirst, bool& finished);
            
        public:
            std::weak_ptr<UIContainer> parent;
            
            VRect rect;
            virtual VRect ViewRect();
            virtual VRect ScreenRect();
            
            UIElement();
            virtual ~UIElement();
            
            virtual void Update() { }
            virtual void PreDraw() { }
            virtual void Draw() { }
            
            // events
            virtual void OnTouchOn() { }
            virtual void OnTouchOff() { }
            virtual void OnTouchHold() { }
            
            virtual void OnProcessTouchEvent() { } // name?
            
            virtual bool InterceptsTouch(Vector2 where) { return false; }
            
            virtual bool OnDragPassed() { return false; }
            virtual void OnDragStart() { }
            virtual void OnDragRelease() { }
            virtual void OnDragHold() { }
            
        };
    }
}

// autoinclude after declaration since these two are pretty inextricably linked
#include "UIContainer.h"
