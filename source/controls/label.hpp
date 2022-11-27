////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_LABEL_HPP
#define EDITOR_LABEL_HPP

#include "text_control.hpp"

class Label : public TextControl
{
public:
	Label();
	Label(sf::RenderWindow* window, sf::Vector2u intended_resolution, std::map<sf::String, sf::String>* strings, const ControlTheme* theme, SoundHandler* handler, const TextTheme* text_theme,
		sf::Vector2f position, sf::Vector2f size, sf::String text, float rotation_angle, bool enabled);
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif