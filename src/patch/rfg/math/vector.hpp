#pragma once

#include <cmath>

namespace rfg {
struct vector {
    vector() = default;
    vector(const vector& copy) : x(copy.x), y(copy.y), z(copy.z) {}
    vector(float value) : x(value), y(value), z(value) {}
    vector(float x, float y, float z) : x(x), y(y), z(z) {}

    vector operator+(const vector& b) { return vector(x + b.x, y + b.y, z + b.z); }
    vector operator-(const vector& b) { return vector(x - b.x, y - b.y, z - b.z); }
    float operator*(const vector& b) { return (x * b.x) + (y * b.y) + (z * b.z); }
    vector operator*(const float b) { return this->scale(b); }
    vector operator/(const float b) { return this->scale(1.0f / b); }
    vector& operator+=(const vector& b) {
        x += b.x;
        y += b.y;
        z += b.z;
        return *this;
    }
    bool operator==(const vector& b) { return (x == b.x && y == b.y && z == b.z); }
    bool operator!=(const vector& b) { return !(*this == b); }
    vector& operator=(const vector& b) {
        x = b.x;
        y = b.y;
        z = b.z;
        return *this;
    }

    vector cross(const vector& original_vector) {
        vector new_vector;
        new_vector.x = (y * original_vector.z) - (original_vector.y * z);
        new_vector.y = (original_vector.x * z) - (y * original_vector.z);
        new_vector.z = (x * original_vector.y) - (original_vector.x * y);
        return new_vector;
    }

    float magnitude() { return sqrtf((x * x) + (y * y) + (z * z)); }

    vector scale(const float& multiplier) {
        x *= multiplier;
        y *= multiplier;
        z *= multiplier;
        return *this;
    }

    vector unit_vector() {
        vector unit_vector = *this;
        float magnitude = this->magnitude();
        unit_vector.scale(1.0f / magnitude);
        return unit_vector;
    }

    float x{0.0f};
    float y{0.0f};
    float z{0.0f};
};

struct vector2 {
    vector2() = default;
    vector2(const vector2& copy) : x(copy.x), y(copy.y) {}
    vector2(float value) : x(value), y(value) {}
    vector2(float x, float y) : x(x), y(y) {}

    vector2 scale(const float& multiplier) {
        x *= multiplier;
        y *= multiplier;
        return *this;
    }

    float x{0.0f};
    float y{0.0f};
};

struct vector4 {
    float x;
    float y;
    float z;
    float w;
};

struct bbox {
    vector min;
    vector max;
};

struct plane {
    vector normal;
    float offset;
};

struct cubic_bezier_spline {
    vector* knots;
    vector* incoming_handles;
    vector* outgoing_handles;
    int num_knots;
};

struct short_quaternion {
    __int16 x;
    __int16 y;
    __int16 z;
    __int16 w;
};

} // namespace rfg
