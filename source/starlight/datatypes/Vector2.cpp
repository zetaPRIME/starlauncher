#include <stdlib.h>
#include <math.h>
#include <fastmath.h>

#include "Vector2.h"

using starlight::Vector2;

Vector2::Vector2() : x(0.0f), y(0.0f) { }

Vector2::~Vector2() { }

Vector2::Vector2(float x, float y) : x(x), y(y) { }

// maths
float Vector2::Length() const { return sqrtf(x * x + y * y); }
Vector2 Vector2::Normalized() const { float m = Length(); return m == 0.0f ? Vector2::zero : Vector2(x / m, y / m); }

Vector2 Vector2::Reciprocal() const { return Vector2(y, x); }

Vector2 Vector2::CardinalAxis() const {
    if (fabsf(x) > fabsf(y)) return h;
    return v;
}
Vector2 Vector2::Cardinal() const { return *this * CardinalAxis(); }

// operators!
//inline Vector2 operator *(const Vector2* vec, const float scalar) { return Vector2(vec.x * scalar, vec.y * scalar); }

// constants
const Vector2 Vector2::zero = Vector2(0.0f, 0.0f);
const Vector2 Vector2::one = Vector2(1.0f, 1.0f);
const Vector2 Vector2::half = Vector2(0.5f, 0.5f);

const Vector2 Vector2::h = Vector2(1, 0);
const Vector2 Vector2::v = Vector2(0, 1);