////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_LAYOUT_SETTINGS_HPP
#define EDITOR_LAYOUT_SETTINGS_HPP

#include "../main/scene.hpp"
#include <SFML/System/String.hpp>
#include <map>

struct LayoutSettings
{
	sf::Vector2u				intended_resolution;
	sf::String					starter_scene;
	std::map<sf::String, Scene>	scenes;
};

#endif