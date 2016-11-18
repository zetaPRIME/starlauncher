#include <stdlib.h>
#include <math.h>
#include <fastmath.h>
#include <algorithm>

#include "VRect.h"

VRect::VRect() {
    
}

VRect::~VRect() {
    
}

VRect::VRect(float x, float y, float w, float h) : pos(x, y), size(w, h) { }
VRect::VRect(Vector2 pos, Vector2 size) : pos(pos), size(size) { }

Vector2 VRect::Center() { return pos + (size * 0.5f); }

VRect VRect::Intersect(const VRect & o) {
    Vector2 tl ( std::max(pos.x, o.pos.x), std::max(pos.y, o.pos.y) );
    Vector2 br ( std::min(pos.x + size.x, o.pos.x + o.size.x), std::min(pos.y + size.y, o.pos.y + o.size.y) );
    VRect res (tl, br - tl);
    if (res.size.x <= 0 || res.size.y <= 0) return VRect();
    return res;
}