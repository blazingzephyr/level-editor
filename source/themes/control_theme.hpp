////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_CONTROL_THEME_HPP
#define EDITOR_CONTROL_THEME_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

struct ControlTheme
{
	sf::Shader*			hovering_shader = nullptr;
	sf::Shader*			disabled_shader = nullptr;
	sf::Shader*			disabled_hovering_shader = nullptr;
	sf::Texture*		texture = nullptr;
	sf::String			enter_sound = "";
	sf::String			click_sound = "";
	sf::String			release_sound = "";
};

#endif