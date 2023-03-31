// MIT License
// 
// Copyright (c) 2022 ZaBlazzingZephyr
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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