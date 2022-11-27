////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_TEXT_CONTROL_HPP
#define EDITOR_TEXT_CONTROL_HPP

#include "control.hpp"
#include "../themes/text_theme.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/OpenGL.hpp>
#include <string>

class TextControl : public Control
{
public:
	TextControl();
	TextControl(sf::RenderWindow* window, sf::Vector2u intended_resolution, std::map<sf::String, sf::String>* strings, const ControlTheme* theme, SoundHandler* handler, const TextTheme* text_theme, sf::Vector2f position, sf::Vector2f size,
		const sf::IntRect& bg, const sf::IntRect& bg_focused, sf::String text, float min_y_position, bool visible = true, bool enabled = true);

	void					setEnabled(bool enabled) override;
	void					setPosition(sf::Vector2f position) override;
	void					onLanguageUpdated() override;
	void					onThemeUpdated() override;
	virtual void			setText(sf::String string);
	void					onResized(sf::Event::SizeEvent data) override;
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void			onMouseMoved(sf::Event::MouseMoveEvent data) override;
	virtual void			onMouseButtonPressed(sf::Event::MouseButtonEvent data) override;
	virtual void			onMouseButtonReleased(sf::Event::MouseButtonEvent data) override;

protected:
	const TextTheme*		m_text_theme;
	sf::Text				m_text;
	sf::FloatRect			m_text_local;
	sf::FloatRect			m_text_global;
	sf::String				m_text_string;
	sf::String				m_string;
	size_t					m_str_len;
	sf::Vector2f			m_text_origin;
	sf::Vector2f			m_text_position;
	sf::Vector2f			m_current_position;
	sf::Vector2f			m_current_size;
	
	void					setTextOrigin();
	void					setTextPosition();
	void					setTextColors(bool holding, bool hovering);

};

#endif