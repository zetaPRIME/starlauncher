#pragma once

#include "starlight/datatypes/Vector2.h"

namespace starlight {
    class InputManager {
    public:
        static void Update();
        
        static Vector2 CirclePad();
        static Vector2 CStick();
        
        static bool Held(u32 mask);
        static bool Pressed(u32 mask);
        static bool Released(u32 mask);
        
        static Vector2 TouchPos();
        static Vector2 TouchDelta();
        static Vector2 TouchStart();
        static Vector2 TouchDragDist();
        
    private:
        InputManager() {}
    };
}
