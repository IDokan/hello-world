/*******************************************************************************
1. sinil.gang
2. Math Programming Assignment
3. CS230
4. Spring 2019

*******************************************************************************/


#include <CS230\math\vector2.hpp>
#include <cassert>		// for assert()
#include <limits>

#include <cmath>		// for std::abs(), std::cos(), std::sin(), std::sqrt(), std::acos()

namespace CS230
{
    vector2::vector2() noexcept :x(0), y(0)
    {
    }

    vector2::vector2(float repeated_float) noexcept : x(repeated_float), y(repeated_float)
    {
    }

    vector2::vector2(float fx, float fy) noexcept :x(fx), y(fy)
    {
    }

    void operator+=(vector2& v, const vector2& adding_vector) noexcept { v = v + adding_vector; }

    void operator-=(vector2& v, const vector2& subtracting_vector) noexcept { v = v - subtracting_vector; }

    void operator*=(vector2& v, float scale) noexcept { v = v * scale; }

    void operator/=(vector2& v, float divisor) noexcept { v = v / divisor; }

    vector2 operator-(const vector2& v) noexcept 
    {
        return vector2(-v.x, -v.y); 
    }


    vector2 operator+(const vector2& v1, const vector2& v2) noexcept 
    {
        return vector2(v1.x + v2.x, v1.y + v2.y); 
    }


    vector2 operator-(const vector2& v1, const vector2& v2) noexcept 
    {
	return vector2(v1.x - v2.x, v1.y - v2.y); 
    }

    vector2 operator*(const vector2& v, float scale) noexcept 
    {
        return vector2(v.x*scale, v.y*scale); 
    }

    vector2 operator*(float scale, const vector2& v) noexcept { return v * scale; }

    vector2 operator/(const vector2& v, float divisor) noexcept 
    {
        // Check for divide by zero
        assert(divisor != 0);
        return vector2(v.x/divisor, v.y/divisor); 
    }

    bool operator==(const vector2& v1, const vector2& v2) noexcept 
    {
        // use epsilon for float equality checks
        return (
            std::abs(v1.x - v2.x) <= std::numeric_limits<float>::epsilon() &&
            std::abs(v1.y - v2.y) <= std::numeric_limits<float>::epsilon());
    }

    bool operator!=(const vector2& v1, const vector2& v2) noexcept { return !(v1 == v2); }

    float dot(vector2 a, vector2 b) noexcept 
    { 	
        return a.x * b.x + a.y *b.y; 
    }

    vector2 perpendicular_to(vector2 a) noexcept 
    {
        return vector2(-a.y, a.x);
    }

    float magnitude_squared(vector2 a) noexcept 
    { 
        return dot(a, a); 
    }

    float magnitude(vector2 a) noexcept 
    { 
        return std::sqrt(magnitude_squared(a)); 
    }

    vector2 normalize(vector2 a) noexcept 
    { 
        return a/magnitude(a); 
    }

    float distance_between_squared(vector2 a, vector2 b) noexcept 
    {
        return magnitude_squared(a - b);
    }

    float distance_between(vector2 a, vector2 b) noexcept 
    { 
        return std::sqrt(distance_between_squared(a,b)); 
    }

    float angle_between(vector2 a, vector2 b) noexcept 
    { 
        const float magnitudeOfA = magnitude(a);
        assert(magnitudeOfA);
        const float magnitudeOfB = magnitude(b);
        assert(magnitudeOfB);

        // Use Dot Product Theorem
        return std::acos(dot(a, b) / magnitudeOfA / magnitudeOfB); 
    }

    vector2 rotate_by(float angle_in_radians, vector2 v) noexcept 
    { 
        const float cos = std::cos(angle_in_radians);
        const float sin = std::sin(angle_in_radians);
        return vector2(
            cos*v.x - sin*v.y,
            sin*v.x + cos*v.y); 
    }

}
