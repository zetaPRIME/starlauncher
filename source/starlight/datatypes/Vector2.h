#pragma once

namespace starlight {
    class Vector2 {
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
        
        inline bool operator == (const Vector2 & o) const { return x == o.x && y == o.y; }
        inline bool operator != (const Vector2 & o) const { return x != o.x || y != o.y; }
            
        inline Vector2 operator * (const float scalar) const { return Vector2(x * scalar, y * scalar); }
        inline Vector2 operator / (const float scalar) const { return Vector2(x / scalar, y / scalar); }
        
        inline Vector2 operator + (const Vector2 & o) const { return Vector2(x + o.x, y + o.y); }
        inline Vector2 operator - (const Vector2 & o) const { return Vector2(x - o.x, y - o.y); }
        inline Vector2 operator * (const Vector2 & o) const { return Vector2(x * o.x, y * o.y); }
        //inline Vector2 operator / (const Vector2 & o) { return Vector2(x / o.x, y / o.y); } // not sure if relevant
        
        inline Vector2 & operator *= (const float scalar) { x *= scalar; y *= scalar; return *this; }
        inline Vector2 & operator /= (const float scalar) { x /= scalar; y /= scalar; return *this; } // maybe reciprocate then multiply instead? maybe the compiler does that
        
        inline Vector2 & operator += (const Vector2 & o) { x += o.x; y += o.y; return *this; }
        inline Vector2 & operator -= (const Vector2 & o) { x -= o.x; y -= o.y; return *this; }
        inline Vector2 & operator *= (const Vector2 & o) { x *= o.x; y *= o.y; return *this; }
        
        static const Vector2 zero;
        static const Vector2 one;
        static const Vector2 half;
    };
}
