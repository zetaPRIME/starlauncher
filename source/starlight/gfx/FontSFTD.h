#pragma once
#include "starlight/_global.h"

#include <sftd.h>

#include "starlight/gfx/Font.h"

namespace starlight {
    namespace gfx {
        class FontSFTD : public Font {
        private:
            sftd_font* sfont;
            
        public:
            FontSFTD(sftd_font* sfont) : sfont(sfont) { }
            ~FontSFTD();
            
            Vector2 Measure(std::string& text, int size = defaultSize, int maxWidth = 400) override;
            void Print(Vector2 position, std::string& text, int size = defaultSize, Color color = Color::white, Vector2 justification = Vector2::zero) override;
            void Print(VRect rect, std::string& text, int size = defaultSize, Color color = Color::white, Vector2 justification = Vector2::zero) override;
        };
    }
}