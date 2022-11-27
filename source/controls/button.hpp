////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_BUTTON_HPP
#define EDITOR_BUTTON_HPP

#include "text_control.hpp"
#include <functional>

class Button : public TextControl
{
public:
	Button();
	Button(sf::RenderWindow* window, sf::Vector2u intended_resolution, std::map<sf::String, sf::String>* strings, const ControlTheme* theme, SoundHandler* handler, const TextTheme* text_theme, sf::Vector2f position, sf::Vector2f size,
		const sf::IntRect& bg, const sf::IntRect& bg_active, sf::String text, const std::function<void()>& on_clicked, const std::function<void()>& on_hold,
		float min_y_position, bool visible = true, bool enabled = true);

	void					onClicked(sf::Event::MouseButtonEvent data) override;

private:
	std::function<void()>	m_on_clicked;
	std::function<void()>	m_on_hold;
	
	void					onHold() override;
	void					onMouseEntered(sf::Event::MouseMoveEvent data) override;
	void					onMouseLeft(sf::Event::MouseMoveEvent data) override;
	void					onReleased(sf::Event::MouseButtonEvent data) override;
};

#endif