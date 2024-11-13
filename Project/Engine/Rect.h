#pragma once
#include <algorithm> //min, max
#include "vec3.h" //Vec2 variables

struct [[nodiscard]] rect3
{
	vec3 point1{ 1.0f, 1.0f, 1.0f };
	vec3 point2{ 1.0f, 1.0f, 1.0f };

	constexpr vec3 Size() const noexcept { return { Right() - Left(), Top() - Bottom(), 1.f }; }
	constexpr float Left() const noexcept { return std::min(point1.x, point2.x); }     // if the rect was flipped, then bottomLeft.x > topRight.x
	constexpr float Right() const noexcept { return std::max(point1.x, point2.x); }    // if the rect was flipped, then bottomLeft.x > topRight.x
	constexpr float Top() const noexcept { return std::max(point1.y, point2.y); }   // if the rect uses top left as {0, 0} or was flipped in the y direction
	constexpr float Bottom() const noexcept { return std::min(point1.y, point2.y); }   // if the rect uses top left as {0, 0} or was flipped in the y direction
};
//struct [[nodiscard]] rect2
//{
//    vec2 point1{ 0.0, 0.0 };
//    vec2 point2{ 0.0, 0.0 };
//
//    constexpr vec2 Size() const noexcept { return { Right() - Left(), Top() - Bottom() }; }
//    constexpr double Left() const noexcept { return std::min(point1.x, point2.x); }     // if the rect was flipped, then bottomLeft.x > topRight.x
//    constexpr double Right() const noexcept { return std::max(point1.x, point2.x); }    // if the rect was flipped, then bottomLeft.x > topRight.x
//    constexpr double Top() const noexcept { return std::max(point1.y, point2.y); }   // if the rect uses top left as {0, 0} or was flipped in the y direction
//    constexpr double Bottom() const noexcept { return std::min(point1.y, point2.y); }   // if the rect uses top left as {0, 0} or was flipped in the y direction
//};