////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#include "math.hpp"

using sf::Vector3;
using std::clamp;
using std::lerp;
using std::make_pair;
using std::max;
using std::min;
using std::pair;

float saturate(float a)
{
	return clamp(a, 0.f, 1.f);
}

float3 lerp(float3 a, float3 b, float3 c)
{
	return float3(
		lerp(a.x, b.x, c.x),
		lerp(a.y, b.y, c.y),
		lerp(a.z, b.z, c.z)
	);
}

float3 lerp(float3 a, float3 b, float c)
{
	return float3(
		lerp(a.x, b.x, c),
		lerp(a.y, b.y, c),
		lerp(a.z, b.z, c)
	);
}

float3 zxy(float3 a)
{
	return float3(a.z, a.x, a.y);
}

float3 yzx(float3 a)
{
	return float3(a.y, a.z, a.x);
}