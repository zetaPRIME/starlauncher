#pragma once

#include "Vector2.h"

class VRect
{
private:
    //
    
public:
    Vector2 pos;
    Vector2 size;
    
    VRect();
    VRect(float x, float y, float w, float h);
    VRect(Vector2 pos, Vector2 size);
    ~VRect();
    
    Vector2 Center();
    
    VRect Intersect(const VRect & o);
    
    inline VRect operator + (const Vector2 & vec) { return VRect(pos + vec, size); }
    inline VRect operator - (const Vector2 & vec) { return VRect(pos - vec, size); }

};

