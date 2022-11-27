////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#include "label.hpp"

using sf::IntRect;
using sf::RenderStates;
using sf::RenderTarget;
using sf::RenderWindow;
using sf::String;
using sf::Vector2f;

Label::Label() :

	TextControl::TextControl()
{

}

Label::Label(RenderWindow* window, sf::Vector2u intended_resolution, std::map<String, String>* strings, const ControlTheme* theme, SoundHandler* handler, const TextTheme* text_theme,
	Vector2f position, Vector2f size, String text, float rotation_angle, bool enabled) :

	TextControl::TextControl(window, intended_resolution, strings, theme, handler, text_theme, 
		position, size, IntRect(0, 0, 0, 0), IntRect(0, 0, 0, 0), text, -1, true, enabled)
{
	m_text.setRotation(rotation_angle);
}

void Label::draw(RenderTarget& target, RenderStates states) const
{
	Control::draw(target, states);
	target.draw(m_text, states);
}