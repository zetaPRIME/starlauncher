#pragma once

#include <memory>
#include <list>
#include <functional>

#include "starlight/datatypes/Vector2.h"
#include "starlight/datatypes/VRect.h"

#include "starlight/ui/UIElement.h"

// no forward declaration in this header

namespace starlight {
    namespace ui {
        class UIContainer : public UIElement {
        private:
            
        protected:
            std::list<std::shared_ptr<UIElement>> children;
            void _Dive(std::function<bool(UIElement*)>& func, bool consumable, bool frontFirst, bool& finished);
            
        public:
            Vector2 scrollOffset;
            
            VRect ViewportRect() { return VRect(scrollOffset, rect.size); }
            
            UIContainer();
            ~UIContainer();
            
            void Dive(std::function<bool(UIElement*)>, bool consumable = true, bool frontFirst = true);
            
            void Add(std::shared_ptr<UIElement> elem);
            //void Add(UIElement* elem);
            void Remove(std::shared_ptr<UIElement> elem);
            
            void Update() override;
            void PreDraw() override;
            void Draw() override;
        };
    }
}
