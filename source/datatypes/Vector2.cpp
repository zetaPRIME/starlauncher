#include <stdlib.h>
#include <math.h>
#include <fastmath.h>

#include "Vector2.h"

Vector2::Vector2() {
    
}

Vector2::~Vector2() {
    
}

Vector2::Vector2(float x, float y) : x(x), y(y) { }

// maths
float Vector2::Length() const { return sqrtf(x * x + y * y); }
Vector2 Vector2::Normalized() const { float m = Length(); return Vector2(x / m, y / m); }

// operators!
//inline Vector2 operator *(const Vector2* vec, const float scalar) { return Vector2(vec.x * scalar, vec.y * scalar); }

// constants
const Vector2 Vector2::zero = Vector2(0.0f, 0.0f);
const Vector2 Vector2::one = Vector2(1.0f, 1.0f);
const Vector2 Vector2::half = Vector2(0.5f, 0.5f);