#pragma once

#include "starlight/ui/UIElement.h"

namespace starlight {
    namespace ui {
        class Button : public UIElement {
        public:
            Button(VRect rect) { this->rect = rect; }
            ~Button() { }
            
            void Draw() override;
            
            // events
            void OnTap() override;
            
        };
    }
}

