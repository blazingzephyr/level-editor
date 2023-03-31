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

#ifndef EDITOR_CONTROL_CONSTRUCTOR_HPP
#define EDITOR_CONTROL_CONSTRUCTOR_HPP

#include "../main/sound_handler.hpp"
#include "../themes/control_theme.hpp"
#include "../themes/text_theme.hpp"
#include "../themes/input_control_theme.hpp"
#include <functional>
#include <string>

struct ControlConstructor
{
	std::string								control_type;
	sf::RenderWindow*						window;
	sf::Vector2u							intended_resolution;
	std::map<sf::String, sf::String>*		strings;
	ControlTheme*							theme;
	sf::Vector2f							position;
	sf::Vector2f							size;
	sf::IntRect								bg_rect;
	sf::IntRect								bg_active_rect;
	bool									visible;
	bool									enabled;
	TextTheme*								text_theme;
	InputControlTheme*						input_control_theme;
	bool									checked;
	sf::String								text;
	std::function<void()>					action_empty;
	std::function<void(bool)>				action_boolean;
	std::function<void(long double)>		action_numeric;
	std::function<void(sf::String)>			action_string;
	sf::Vector2f							button_size;
	sf::IntRect								first_button_bg_rect;
	sf::IntRect								first_button_bg_focused_rect;
	sf::IntRect								second_button_bg_rect;
	sf::IntRect								second_button_bg_focused_rect;
	long double								min;
	long double								max;
	long double								step;
	long double								value;
	float									button_offset;
	std::vector<sf::String>					items;
	size_t									index;
	int										scroll_time;
	sf::Vector2f							thumb_size;
	sf::IntRect								thumb_rect;
	bool									vertical;
	float									scroll_multiplier;
	sf::Vector2f							create_button_position;
	sf::Vector2f							create_button_size;
	sf::IntRect								create_button_bg;
	sf::IntRect								create_button_bg_focused;
	sf::String								create_button_text;
	sf::Vector2f							slider_position;
	sf::Vector2f							slider_size;
	sf::IntRect								slider_bg;
	sf::IntRect								slider_bg_focused;
	sf::Vector2f							slider_thumb_size;
	sf::IntRect								slider_thumb;
	float									row_offset;
	std::vector<ControlConstructor>			row_constructors;
	ControlConstructor*						row_erase_button;
	float									rotation_angle;
	float									min_y_position;
	SoundHandler*							handler;
};

#endif