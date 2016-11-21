#pragma once

#include "Vector2.h"

class VRect {
private:
    //
    
public:
    Vector2 pos;
    Vector2 size;
    
    VRect();
    VRect(float x, float y, float w, float h);
    VRect(Vector2 pos, Vector2 size);
    ~VRect();
    
    Vector2 Center() const;
    
    bool Overlaps(const VRect & o) const;
    bool Contains(const Vector2 & vec) const;
    
    VRect Intersect(const VRect & o) const;
    
    inline bool operator == (const VRect & o) const { return pos == o.pos && size == o.size; }
    inline bool operator != (const VRect & o) const { return pos != o.pos || size != o.size; }
    
    inline VRect operator + (const Vector2 & vec) const { return VRect(pos + vec, size); }
    inline VRect operator - (const Vector2 & vec) const { return VRect(pos - vec, size); }
    
    inline VRect & operator += (const Vector2 & vec) { pos += vec; return *this; }
    inline VRect & operator -= (const Vector2 & vec) { pos -= vec; return *this; }
    
    static const VRect zero;
};

