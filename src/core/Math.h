#pragma once

#define MATH_PI 3.14159265359f

inline float degToRad(float degrees) { return degrees * (MATH_PI / 180.f); }
inline float radToDeg(float radians) { return radians * (180.f / MATH_PI); }