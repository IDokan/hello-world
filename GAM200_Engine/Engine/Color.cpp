/*
 *  1. sinil.gang
 *  2. Shader Programming / 3
 *  3. CS230
 *  4. Spring 2019
 */

#include "Color4f.hpp"
#include "Color4ub.hpp"

     Color4ub::Color4ub(unsigned_byte grey, unsigned_byte alpha) noexcept
        : red(grey), green(grey), blue(grey), alpha(alpha)
    {
    }

     Color4ub::Color4ub(unsigned_byte red, unsigned_byte green, unsigned_byte blue, unsigned_byte alpha) noexcept
        : red(red), green(green), blue(blue), alpha(alpha)
    {
    }

     Color4ub to_color4ub(const Color4f& float_colors)
    {
        // Clamping each values..
        float red = float_colors.red;

        if (red <= 0.f)
        {
            red = 0.f;
        }
        else if (red >= 1.f)
        {
            red = 1.f;
        }

        float green = float_colors.green;

        if (green <= 0.f)
        {
            green = 0.f;
        }
        else if (green >= 1.f)
        {
            green = 1.f;
        }

        float blue = float_colors.blue;

        if (blue <= 0.f)
        {
            blue = 0.f;
        }
        else if (blue >= 1.f)
        {
            blue = 1.f;
        }

        float alpha = float_colors.alpha;

        if (alpha <= 0.f)
        {
            alpha = 0.f;
        }
        else if (alpha >= 1.f)
        {
            alpha = 1.f;
        }

	// Rounding and type conversion
        return Color4ub(static_cast< Color4ub::unsigned_byte>((red * 255.f) + 0.5f),
			static_cast< Color4ub::unsigned_byte>((green * 255.f) + 0.5f),
                        static_cast< Color4ub::unsigned_byte>((blue * 255.f) + 0.5f),
			static_cast< Color4ub::unsigned_byte>((alpha * 255.f) + 0.5f)
		);
    }

     Color4f::Color4f(float grey, float alpha) noexcept : red(grey), green(grey), blue(grey), alpha(alpha) {}

     Color4f::Color4f(float red, float green, float blue, float alpha) noexcept
        : red(red), green(green), blue(blue), alpha(alpha)
    {
    }

     Color4f to_color4f(const Color4ub& eight_bit_color)
    {
        return Color4f(
            static_cast<float>(eight_bit_color.red) / 255.f, static_cast<float>(eight_bit_color.green) / 255.f,
            static_cast<float>(eight_bit_color.blue) / 255.f, static_cast<float>(eight_bit_color.alpha) / 255.f);
    }