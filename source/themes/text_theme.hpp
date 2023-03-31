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