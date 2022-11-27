////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
//
////////////////////////////////////////////////////////////

#ifndef EDITOR_HSV_HPP
#define EDITOR_HSV_HPP

#include "math.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics/Color.hpp>
#include <tuple>

typedef std::tuple<float, float, float, float> RGBA;

struct Hsv
{
	sf::Uint16		h;
	sf::Uint8		s;
	sf::Uint8		v;
	sf::Uint8		a;

	Hsv(float r, float g, float b, float a = 255.);

	RGBA toRGB();
};

#endif