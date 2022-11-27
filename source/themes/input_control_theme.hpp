////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_INPUT_CONTROL_THEME_HPP
#define EDITOR_INPUT_CONTROL_THEME_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Audio/Sound.hpp>

struct InputControlTheme
{
	sf::Cursor*			mouse_cursor_default = new sf::Cursor();
	sf::Cursor*			mouse_cursor_text = new sf::Cursor();
	float				cursor_width;
	sf::Color			cursor_color;
	sf::Color			selection_color;
	sf::String			input_sound = "";
};

#endif