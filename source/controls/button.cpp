////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#include "button.hpp"

using sf::Event;
using sf::IntRect;
using sf::Mouse;
using sf::RenderStates;
using sf::RenderTarget;
using sf::RenderWindow;
using sf::Shader;
using sf::Sprite;
using sf::String;
using sf::Vector2f;
using sf::Vector2u;
using sf::Text;
using std::function;
using std::map;

Button::Button() :

	TextControl(),
	m_on_clicked()
{

}

Button::Button(RenderWindow* window, Vector2u intended_resolution, map<String, String>* strings, const ControlTheme* theme, SoundHandler* handler, const TextTheme* text_theme, Vector2f position, Vector2f size,
	const IntRect& bg, const IntRect& bg_active, String text, const function<void()>& on_clicked, const function<void()>& on_hold, float min_y_position, bool visible, bool enabled) :

	TextControl::TextControl(window, intended_resolution, strings, theme, handler, text_theme, position, size, bg, bg_active, text, min_y_position, visible, enabled),
	m_on_clicked(on_clicked),
	m_on_hold(on_hold)
{

}

void Button::onHold()
{
	m_on_hold();
}

void Button::onMouseEntered(Event::MouseMoveEvent data)
{
	TextControl::onMouseEntered(data);
	m_drawable = m_holding ? m_bg_active : m_bg;
}

void Button::onMouseLeft(Event::MouseMoveEvent data)
{
	TextControl::onMouseLeft(data);
	m_drawable = m_bg;
}

void Button::onClicked(Event::MouseButtonEvent data)
{
	TextControl::onClicked(data);
	m_drawable = m_bg_active;
}

void Button::onReleased(Event::MouseButtonEvent data)
{
	TextControl::onReleased(data);
	m_drawable = m_bg;
	m_on_clicked();
}