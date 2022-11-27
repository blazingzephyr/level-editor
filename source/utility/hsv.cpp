////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#include "hsv.hpp"

using sf::Uint8;
using sf::Uint16;
using sf::Color;
using std::min;
using std::max;

Hsv::Hsv(float r, float g, float b, float a)
{
    r /= 255.f;
    g /= 255.f;
    b /= 255.f;

    float3 hsv = float3();
    double rgb_min = 0,
        rgb_max = 0;

    auto result = [this, &hsv, &a]()
    {
        h = static_cast<uint16_t>(hsv.x);
        s = static_cast<uint8_t>(hsv.y);
        v = static_cast<uint8_t>(hsv.z);
        this->a = a;
    };

    rgb_min = min({ r, g, b });
    rgb_max = max({ r, g, b });
    hsv.z = rgb_max;

    if (hsv.z == 0)
    {
        hsv.x = hsv.y = 0;
        hsv.y *= 100;
        hsv.z *= 100;

        result();
        return;
    }

    r /= hsv.z;
    g /= hsv.z;
    b /= hsv.z;

    rgb_min = min({ r, g, b });
    rgb_max = max({ r, g, b });
    hsv.y = rgb_max - rgb_min;

    if (hsv.y == 0)
    {
        hsv.x = 0;
        hsv.y *= 100;
        hsv.z *= 100;

        result();
        return;
    }

    r = (r - rgb_min) / (rgb_max - rgb_min);
    g = (g - rgb_min) / (rgb_max - rgb_min);
    b = (b - rgb_min) / (rgb_max - rgb_min);

    rgb_min = min({ r, g, b });
    rgb_max = max({ r, g, b });

    if (rgb_max == r)
    {
        hsv.x = 0.0 + 60 * (g - b);
        if (hsv.x < 0.0)
        {
            hsv.x += 360.0;
        }
    }
    else if (rgb_max == g)
    {
        hsv.x = 120 + 60 * (b - r);
    }
    else
    {
        hsv.x = 240 + 60 * (r - g);
    }

    hsv.y *= 100;
    hsv.z *= 100;

    result();
}

RGBA Hsv::toRGB()
{
    float buffer_h = h / 360.f;
    float buffer_s = s / 100.f;
    float buffer_v = v / 100.f;

    float   HueSlice = 6.0 * buffer_h;
    float   HueSliceInteger = floor(HueSlice);
    float   HueSliceInterpolant = HueSlice - HueSliceInteger;

    float3  TempRGB = float3(buffer_v * (1.0 - buffer_s),
        buffer_v * (1.0 - buffer_s * HueSliceInterpolant),
        buffer_v * (1.0 - buffer_s * (1.0 - HueSliceInterpolant)));

    float   IsOddSlice = fmod(HueSliceInteger, 2.f);
    float   ThreeSliceSelector = 0.5f * (HueSliceInteger - IsOddSlice);

    float3  ScrollingRGBForEvenSlices = float3(buffer_v, TempRGB.z, TempRGB.x);
    float3  ScrollingRGBForOddSlices = float3(TempRGB.y, buffer_v, TempRGB.x);
    float3  ScrollingRGB = lerp(ScrollingRGBForEvenSlices, ScrollingRGBForOddSlices, IsOddSlice);

    float   IsNotFirstSlice = saturate(ThreeSliceSelector);
    float   IsNotSecondSlice = saturate(ThreeSliceSelector - 1.f);

    float3 result = lerp(ScrollingRGB, lerp(zxy(ScrollingRGB), yzx(ScrollingRGB), IsNotSecondSlice), IsNotFirstSlice);
    return RGBA(
        result.x * 255,
        result.y * 255,
        result.z * 255,
        a
    );
}