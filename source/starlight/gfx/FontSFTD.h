#pragma once
#include "starlight/_global.h"

#include <sftd.h>

#include "starlight/gfx/Font.h"

namespace starlight {
    namespace gfx {
        class FontSFTD : public Font {
        private:
            sftd_font* sfont;
            
            void PrintOp(Vector2 position, std::string& text, int size, const Color& color, Vector2 justification, OptRef<Color> borderColor, int maxWidth, Vector2* measure);
            
        public:
            FontSFTD(sftd_font* sfont) : sfont(sfont) { }
            ~FontSFTD();
            
            Vector2 Measure(std::string& text, int size = defaultSize, int maxWidth = 400) override;
            void Print(Vector2 position, std::string& text, int size = defaultSize, Color color = Color::white, Vector2 justification = Vector2::zero, OptRef<Color> borderColor = nullptr) override;
            void Print(VRect rect, std::string& text, int size = defaultSize, Color color = Color::white, Vector2 justification = Vector2::zero, OptRef<Color> borderColor = nullptr) override;
        };
    }
}