#include <stdlib.h>
#include <math.h>
#include <fastmath.h>

#include "VRect.h"

VRect::VRect() {
    
}

VRect::~VRect() {
    
}

VRect::VRect(float x, float y, float w, float h) : pos(x, y), size(w, h) { }
VRect::VRect(Vector2 pos, Vector2 size) : pos(pos), size(size) { }

Vector2 VRect::Center() { return pos + (size * 0.5f); }