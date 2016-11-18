#pragma once

class Vector2
{
private:
    //
    
public:
    float x = 0.0f;
    float y = 0.0f;
    
    Vector2();
    Vector2(float x, float y);
    ~Vector2();

    float Length() const;
    Vector2 Normalized() const;
        
    inline Vector2 operator * (const float scalar) { return Vector2(x * scalar, y * scalar); }
    inline Vector2 operator / (const float scalar) { return Vector2(x / scalar, y / scalar); }
    
    inline Vector2 operator + (const Vector2 & o) { return Vector2(x + o.x, y + o.y); }
    inline Vector2 operator - (const Vector2 & o) { return Vector2(x - o.x, y - o.y); }
    inline Vector2 operator * (const Vector2 & o) { return Vector2(x * o.x, y * o.y); }
    //inline Vector2 operator / (const Vector2 & o) { return Vector2(x / o.x, y / o.y); } // not sure if relevant
    
    static const Vector2 zero;
    static const Vector2 one;
    static const Vector2 half;
};

//Vector2 operator *(const Vector2* vec, const float scalar);

