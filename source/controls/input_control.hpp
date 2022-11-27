////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_TEXT_BOX_HPP
#define EDITOR_TEXT_BOX_HPP

#include "text_control.hpp"
#include "../themes/input_control_theme.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Clipboard.hpp>
#include <SFML/Window/Keyboard.hpp>

class InputControl : public TextControl
{
public:
	InputControl();
	InputControl(sf::RenderWindow* window, sf::Vector2u intended_resolution, std::map<sf::String, sf::String>* strings, const ControlTheme* theme, SoundHandler* handler, const TextTheme* text_theme, const InputControlTheme* input_control_theme,
		sf::Vector2f position, sf::Vector2f size, const sf::IntRect& bg, const sf::IntRect& bg_focused, sf::String text, std::function<void(sf::String)> updated, float min_y_position, bool visible = true, bool enabled = true);

	sf::String						getText() const;
	virtual void					setCursor(size_t position);
	virtual void					onKeyPressed(sf::Event::KeyEvent data) override;
	virtual void					onTextEntered(sf::Event::TextEvent data) override;
	void							onResized(sf::Event::SizeEvent data) override;
	virtual void					draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	enum struct ValidationResult : char
	{
		Invalid = -1,
		Static = 0,
		Valid = 1
	};

	const InputControlTheme*		m_input_theme;
	std::function<void(sf::String)>	m_text_updated;
	sf::RectangleShape				m_cursor;
	sf::RectangleShape				m_selection;
	bool							m_focused;
	bool							m_overwrite;
	size_t							m_cursor_position;
	bool							m_selected;
	float							m_selection_offset;
	std::pair<size_t, size_t>		m_selection_range;

	sf::FloatRect					m_control_rect;
	sf::FloatRect					m_text_bounds;

	virtual void					onMouseEntered(sf::Event::MouseMoveEvent data) override;
	virtual void					onMouseLeft(sf::Event::MouseMoveEvent data) override;
	virtual void					onClicked(sf::Event::MouseButtonEvent data) override;
	virtual void					onUnclicked(sf::Event::MouseButtonEvent data) override;
	virtual void					onMoved(sf::Event::MouseMoveEvent data) override;
	virtual ValidationResult		validateText(sf::String& buffer);

private:
	void							updatePosition(bool condition, size_t selection_position, long long offset);
	void							eraseText(bool condition, size_t last, long long offset);
	void							inputText(sf::String characters);
	void							updateText(size_t offset, sf::String buffer);
	void							disableSelection();
};

#endif