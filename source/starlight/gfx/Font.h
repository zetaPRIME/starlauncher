#pragma once
#include "starlight/_global.h"

#include <string>

#include "starlight/datatypes/Vector2.h"
#include "starlight/datatypes/VRect.h"
#include "starlight/datatypes/Color.h"
#include "starlight/datatypes/OptRef.h"

namespace starlight {
    namespace gfx {
        class Font {
        public:
            static constexpr const int defaultSize = 16;
            
            Font() { }
            virtual ~Font() { }
            
            virtual Vector2 Measure(std::string& text, int size = defaultSize, int maxWidth = 400) = 0;
            virtual void Print(Vector2 position, std::string& text, int size = defaultSize, Color color = Color::white, Vector2 justification = Vector2::zero) = 0;
            virtual void Print(VRect rect, std::string& text, int size = defaultSize, Color color = Color::white, Vector2 justification = Vector2::zero) = 0;
        };
        
    }
}

