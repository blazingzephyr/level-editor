////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_CHECK_BOX_HPP
#define EDITOR_CHECK_BOX_HPP

#include "control.hpp"
#include <functional>

class CheckBox : public Control
{
public:
	CheckBox();
	CheckBox(sf::RenderWindow* window, sf::Vector2u intended_resolution, std::map<sf::String, sf::String>* strings, const ControlTheme* theme, SoundHandler* handler, sf::Vector2f position, sf::Vector2f size, const sf::IntRect& bg_unchecked, const sf::IntRect& bg_checked,
		std::function<void(bool)> checked_changed, bool checked, float min_y_position, bool visible = true, bool enabled = true);

	bool						getChecked() const;
	void						forceSetChecked(bool value);
	void						setChecked(bool value);

private:
	std::function<void(bool)>	m_checked_changed;
	bool						m_checked;

	void						onMouseEntered(sf::Event::MouseMoveEvent data) override;
	void						onMouseLeft(sf::Event::MouseMoveEvent data) override;
	void						onClicked(sf::Event::MouseButtonEvent data) override;
	void						onReleased(sf::Event::MouseButtonEvent data) override;
	void						onScrolled(sf::Event::MouseWheelScrollEvent data) override;

	void						setDrawable(bool swap = false);
};

#endif