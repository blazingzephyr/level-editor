////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_TEXT_THEME_HPP
#define EDITOR_TEXT_THEME_HPP

#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>

struct TextTheme
{
	enum struct TextHorizontalAlignment : sf::Int8
	{
		Left = -1,
		Center = 0,
		Right = 1
	};

	enum struct TextVerticalAlignment : sf::Int8
	{
		Top = -1,
		Center = 0,
		Bottom = 1
	};

	TextHorizontalAlignment	horizontal_alignment;
	TextVerticalAlignment	vertical_alignment;
	sf::Font*				font = new sf::Font();
	sf::Color				fill_default_color;
	sf::Color				fill_disabled_color;
	sf::Color				fill_hovering_color;
	sf::Color				fill_holding_color;
	sf::Color				outline_default_color;
	sf::Color				outline_disabled_color;
	sf::Color				outline_hovering_color;
	sf::Color				outline_holding_color;
	sf::Uint32				character_size;
	float					letter_spacing;
	float					line_spacing;
	float					outline_thickness;
	sf::Uint32				style;
};

#endif