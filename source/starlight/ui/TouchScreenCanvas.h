#pragma once

#include "starlight/ui/UICanvas.h"

namespace starlight {
    namespace ui {
        class TouchScreenCanvas : public UICanvas {
        public:
            TouchScreenCanvas();
            ~TouchScreenCanvas() { }
            
            void Update() override;
            void PreDraw() override;
            void Draw() override;
        };
    }
}

