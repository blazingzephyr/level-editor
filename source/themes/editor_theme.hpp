////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_THEME_HPP
#define EDITOR_THEME_HPP

#include "control_theme.hpp"
#include "text_theme.hpp"
#include "input_control_theme.hpp"
#include <SFML/System/String.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <map>

struct EditorTheme
{
	sf::String								loading_screen;
	sf::String								icon;
	bool									toggle_animations;
	std::map<sf::String, sf::Shader*>		shaders;
	std::map<sf::String, sf::Font*>			fonts;
	std::map<sf::String, sf::Texture*>		textures;
	std::map<sf::String, sf::SoundBuffer*>	sounds;
	std::map<sf::String, sf::String>		music;
	std::map<sf::String, ControlTheme>		control_themes;
	std::map<sf::String, TextTheme>			text_themes;
	std::map<sf::String, InputControlTheme>	input_control_themes;
};

#endif