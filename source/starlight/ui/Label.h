#pragma once
#include "starlight/_global.h"

#include <string>

#include "starlight/ThemeManager.h"
#include "starlight/gfx/ThemeRef.h"

#include "starlight/ui/UIElement.h"

namespace starlight {
    namespace ui {
        class Label : public UIElement {
        private:
            void AutoSize();
            
        public:
            std::string text = "";
            gfx::ThemeRef<gfx::Font>* font;
            
            Color color = Color::white;
            Color borderColor = Color::transparent;
            
            bool autoSizeV = false;
            Vector2 justification = Vector2::half;
            
            Label(VRect rect);
            ~Label() override { }
            
            void SetText(const std::string& text);
            void SetFont(const std::string& fontName);
            
            void Draw() override;
        };
    }
}
