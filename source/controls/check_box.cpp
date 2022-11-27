////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#include "check_box.hpp"

using minijson::value;
using minijson::value_type;
using sf::Event;
using sf::IntRect;
using sf::String;
using sf::RenderWindow;
using sf::Vector2f;
using sf::Vector2u;
using std::function;
using std::map;

CheckBox::CheckBox() : 
	
	Control::Control(),
	m_checked_changed(),
	m_checked(false)
{

}

CheckBox::CheckBox(RenderWindow* window, Vector2u intended_resolution, map<String, String>* strings, const ControlTheme* theme, SoundHandler* handler, Vector2f position, Vector2f size, const IntRect& bg_unchecked, const IntRect& bg_checked,
	function<void(bool)> listener, bool checked, float min_y_position, bool visible, bool enabled) :

	Control(window, intended_resolution, strings, theme, handler, position, size, bg_unchecked, bg_checked, min_y_position, visible, enabled),
	m_checked_changed(listener),
	m_checked(checked)
{
	m_drawable = checked ? m_bg_active : m_bg;
}

bool CheckBox::getChecked() const
{
	return m_checked;
}

void CheckBox::forceSetChecked(bool value)
{
	m_checked = value;
	m_drawable = value ? m_bg_active : m_bg;
}

void CheckBox::setChecked(bool value)
{
	forceSetChecked(value);
	m_checked_changed(value);
}

void CheckBox::onMouseEntered(Event::MouseMoveEvent data)
{
	Control::onMouseEntered(data);
	setDrawable();
}

void CheckBox::onMouseLeft(Event::MouseMoveEvent data)
{
	setDrawable(true);
}

void CheckBox::onClicked(Event::MouseButtonEvent data)
{
	Control::onClicked(data);
	setDrawable();
}

void CheckBox::onReleased(Event::MouseButtonEvent data)
{
	Control::onReleased(data);
	setChecked(!m_checked);
}

void CheckBox::onScrolled(Event::MouseWheelScrollEvent data)
{
	setDrawable();
	setChecked(!m_checked);
}

void CheckBox::setDrawable(bool swap)
{
	if (m_enabled && m_holding)
	{
		m_drawable = !m_checked != !swap ? m_bg : m_bg_active;
	}
}