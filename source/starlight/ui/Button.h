#pragma once
#include "starlight/_global.h"

#include "starlight/ui/UIElement.h"

namespace starlight {
    namespace ui {
        class Button : public UIElement {
        private:
            //
            
        public:
            Button(VRect rect) { this->rect = rect; }
            ~Button() { }
            
            void Draw() override;
            
            // events
            void OnTouchOn() override;
            
            void OnDragStart() override;
            void OnDragRelease() override;
            void OnDragHold() override;
            
        };
    }
}

