////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
//
////////////////////////////////////////////////////////////

#ifndef EDITOR_MATH_HPP
#define EDITOR_MATH_HPP

#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Color.hpp>
#include <algorithm>
#include <cmath>

typedef sf::Vector3<float> float3;

float	saturate(float a);
float3	lerp(float3 a, float3 b, float3 c);
float3	lerp(float3 a, float3 b, float c);
float3	zxy(float3 a);
float3	yzx(float3 a);

#endif