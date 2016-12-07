#include <stdlib.h>
#include <math.h>
#include <fastmath.h>
#include <algorithm>

#include "VRect.h"

using starlight::Vector2;
using starlight::VRect;

VRect::VRect() : pos(Vector2()), size(Vector2()) { }

VRect::~VRect() { }

VRect::VRect(float x, float y, float w, float h) : pos(x, y), size(w, h) { }
VRect::VRect(Vector2 pos, Vector2 size) : pos(pos), size(size) { }

Vector2 VRect::Center() const { return pos + (size * 0.5f); }
Vector2 VRect::TopLeft() const { return pos; }
Vector2 VRect::TopRight() const { return Vector2(pos.x + size.x, pos.y); }
Vector2 VRect::BottomLeft() const { return Vector2(pos.x, pos.y + size.y); }
Vector2 VRect::BottomRight() const { return pos + size; }

bool VRect::Overlaps(const VRect & o) const {
    Vector2 c = Center();
    Vector2 oc = o.Center();
    return fabsf(c.x - oc.x) * 2.0f < size.x + o.size.x && fabsf(c.y - oc.y) * 2.0f < size.y + o.size.y;
}
bool VRect::Contains(const Vector2 & vec) const {
    Vector2 c = Center();
    return fabsf(c.x - vec.x) < size.x * 0.5f && fabsf(c.y - vec.y) < size.y * 0.5f;
}

VRect VRect::Intersect(const VRect & o) const {
    Vector2 tl ( std::max(pos.x, o.pos.x), std::max(pos.y, o.pos.y) );
    Vector2 br ( std::min(pos.x + size.x, o.pos.x + o.size.x), std::min(pos.y + size.y, o.pos.y + o.size.y) );
    VRect res (tl, br - tl);
    if (res.size.x <= 0.0f || res.size.y <= 0.0f) return VRect(); // invalid area represented as a zero-rect
    return res;
}

// constants
const VRect VRect::zero = VRect(); // should initialize to 0,0,0,0