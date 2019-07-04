/*******************************************************************************
1. sinil.gang
2. Math Programming Assignment
3. CS230
4. Spring 2019

*******************************************************************************/

#include "vector3.hpp"
#include <cassert>		// for assert()
#include <limits>

#include <cmath>		// for std::sqrt(), std::abs(), and std::acos()

    vector3::vector3() noexcept 
    : x(0), y(0), z(0) 
    {
    }

    vector3::vector3(float repeated_float) noexcept 
    : x(repeated_float), y(repeated_float), z(repeated_float)
    {
    }

    vector3::vector3(float fx, float fy, float fz) noexcept 
    :x(fx), y(fy), z(fz) 
    {
    }

    void operator+=(vector3& v, const vector3& adding_vector) noexcept 
    { 
    	v = v + adding_vector;
    }

    void operator-=(vector3& v, const vector3& subtracting_vector) noexcept 
    { 
        v = v - subtracting_vector;
    }

    void operator*=(vector3& v, float scale) noexcept 
    { 
        v = v * scale;
    }

    void operator/=(vector3& v, float divisor) noexcept 
    { 
        v = v / divisor;
    }

    vector3 operator-(const vector3& v) noexcept { return vector3(-v.x, -v.y, -v.z); }

    vector3 operator+(const vector3& v1, const vector3& v2) noexcept 
    { 
        return vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z); 
    }

    vector3 operator-(const vector3& v1, const vector3& v2) noexcept 
    { 
        return vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    }

    vector3 operator*(const vector3& v, float scale) noexcept 
    { 
        return vector3(v.x*scale, v.y*scale, v.z*scale);
    }

    vector3 operator*(float scale, const vector3& v) noexcept 
    { 
        return v * scale; 
    }

    vector3 operator/(const vector3& v, float divisor) noexcept 
    {
        // Check for divide by zero
        assert(divisor != 0);
        return vector3(v.x/divisor, v.y/divisor, v.z/divisor); 
    }

    bool operator==(const vector3& v1, const vector3& v2) noexcept 
    { 
        // use epsilon for float equality checks
        return (
            std::abs(v1.x - v2.x) <= std::numeric_limits<float>::epsilon() && 
            std::abs(v1.y - v2.y) <= std::numeric_limits<float>::epsilon()  &&
            std::abs(v1.z - v2.z) <= std::numeric_limits<float>::epsilon());
    }

    bool operator!=(const vector3& v1, const vector3& v2) noexcept 
    { 
        return !(v1 == v2); 
    }

    float dot(vector3 a, vector3 b) noexcept 
    { 
        return a.x * b.x + a.y * b.y + a.z * b.z; 
    }

    vector3 cross(vector3 a, vector3 b) noexcept 
    {
        return vector3(a.y * b.z - a.z * b.y, -(a.x * b.z - a.z * b.x), a.x * b.y - a.y * b.x);
    }

    float magnitude_squared(vector3 a) noexcept 
    { 
        return dot(a, a);
    }

    float magnitude(vector3 a) noexcept 
    { 
        return std::sqrt(magnitude_squared(a)); 
    }

    vector3 normalize(vector3 a) noexcept 
    { 
        return vector3(a)/magnitude(a);
    }

    float distance_between_squared(vector3 a, vector3 b) noexcept 
    {
        return magnitude_squared(a - b);
    }

    float distance_between(vector3 a, vector3 b) noexcept 
    { 
        return std::sqrt(distance_between_squared(a, b)); 
    }

    float angle_between(vector3 a, vector3 b) noexcept 
    {
        const float magnitudeOfA = magnitude(a);
        assert(magnitudeOfA);
        const float magnitudeOfB = magnitude(b);
        assert(magnitudeOfB);

        // Use Dot Product Theorem
        return std::acos(dot(a, b) / magnitudeOfA / magnitudeOfB);
    }
