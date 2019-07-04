/*
 * Rudy Castan
 * Math Library
 * CS230
 */
#pragma once

#include <CS230/math/vector2.hpp>

namespace CS230
{
    struct [[nodiscard]] rectangle
    {
        vector2 min{};
        vector2 max{};

        void    ExtendBy(vector2 point) noexcept;
        bool    DoesContainPoint(vector2 point) const noexcept;
        bool    DoesIntersectWith(rectangle other) const noexcept;
        vector2 CalculateCenter() const noexcept;
        float   CalculateWidth() const noexcept;
        float   CalculateHeight() const noexcept;
    };
}