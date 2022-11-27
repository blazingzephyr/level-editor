////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#include "text_control.hpp"

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
using std::map;

TextControl::TextControl() : Control(),
	m_text_theme(nullptr),
	m_text(),
	m_string(),
	m_str_len(0)
{

}

TextControl::TextControl(RenderWindow* window, Vector2u intended_resolution, map<sf::String, sf::String>* strings, const ControlTheme* theme, SoundHandler* handler, const TextTheme* text_theme, Vector2f position, Vector2f size,
	const IntRect& bg, const IntRect& bg_focused, String text, float min_y_position, bool visible, bool enabled) :
	
	Control(window, intended_resolution, strings, theme, handler, position, size, bg, bg_focused, min_y_position, visible, enabled),
	m_text_theme(text_theme),
	m_text(Text(strings->contains(text) ? strings->operator[](text) : text, *text_theme->font, static_cast<sf::Uint32>(text_theme->character_size * m_size_coeff.x))),
	m_text_string(strings->contains(text) ? strings->operator[](text) : text),
	m_string(text),
	m_str_len(m_text_string.getSize()),
	m_current_position(m_global_position),
	m_current_size(m_global_size)
{
	m_text.setLetterSpacing(text_theme->letter_spacing);
	m_text.setLineSpacing(text_theme->line_spacing);
	m_text.setOutlineThickness(text_theme->outline_thickness * m_size_coeff.x);
	m_text.setStyle(text_theme->style);

	setTextColors(false, false);
	setTextOrigin();
	setTextPosition();
}

void TextControl::setEnabled(bool enabled)
{
	Control::setEnabled(enabled);
	if (m_initialized)
	{
		setTextColors(false, false);
	}
}

void TextControl::setPosition(sf::Vector2f position)
{
	Control::setPosition(position);

	m_current_position = Vector2f(position.x * m_original_size_coeff.x, position.y * m_original_size_coeff.y);
	m_current_size = Vector2f(m_size.x * m_original_size_coeff.x, m_size.y * m_original_size_coeff.y);

	setTextOrigin();
	setTextPosition();
}

void TextControl::onLanguageUpdated()
{
	Control::onLanguageUpdated();
	m_text_string = m_strings->operator[](m_string);
	m_str_len = m_text_string.getSize();
	setText(m_text_string);
}

void TextControl::onThemeUpdated()
{
	Control::onThemeUpdated();
	setTextColors(false, false);
}

void TextControl::setText(String string)
{
	if (m_initialized)
	{
		m_text_string = string;
		m_str_len = string.getSize();
		m_text.setString(string);

		setTextOrigin();
		setTextPosition();
	}
}

void TextControl::onResized(Event::SizeEvent data)
{
	Control::onResized(data);

	if (m_initialized)
	{
		m_text_local = m_text.getLocalBounds();
		m_text_global = m_text.getGlobalBounds();
	}
}

void TextControl::draw(RenderTarget& target, RenderStates states) const
{
	Control::draw(target, states);
	if (m_initialized && m_visible)
	{
		try
		{
			glEnable(GL_SCISSOR_TEST);
			glScissor(m_global_position.x, target.getSize().y - m_global_position.y - m_global_size.y, m_global_size.x, m_global_size.y);
			target.draw(m_text);
			glDisable(GL_SCISSOR_TEST);
		}
		catch (const std::exception)
		{

		}
	}
}

void TextControl::setTextOrigin()
{
	try
	{
		m_text_local = m_text.getLocalBounds();
		switch (m_text_theme->horizontal_alignment)
		{
			case TextTheme::TextHorizontalAlignment::Center:
				m_text_origin.x = m_text_local.left + m_text_local.width * 0.5;
				break;

			case TextTheme::TextHorizontalAlignment::Left:
				m_text_origin.x = m_text_local.left + m_text_local.width * 0.02;
				break;

			case TextTheme::TextHorizontalAlignment::Right:
				m_text_origin.x = m_text_local.left + m_text_local.width * 0.98;
				break;
		}

		switch (m_text_theme->vertical_alignment)
		{
			case TextTheme::TextVerticalAlignment::Center:
				m_text_origin.y = m_text_local.top + m_text_local.height * 0.5;
				break;

			case TextTheme::TextVerticalAlignment::Top:
				m_text_origin.y = m_text_local.top + m_text_local.height * 0.02;
				break;

			case TextTheme::TextVerticalAlignment::Bottom:
				m_text_origin.y = m_text_local.top + m_text_local.height * 0.98;
				break;
		}

		m_text.setOrigin(m_text_origin);
		m_text_global = m_text.getGlobalBounds();
	}
	catch (const std::exception)
	{

	}
}

void TextControl::setTextPosition()
{
	switch (m_text_theme->horizontal_alignment)
	{
		case TextTheme::TextHorizontalAlignment::Center:
			m_text_position.x = m_current_size.x * 0.5;
			break;

		case TextTheme::TextHorizontalAlignment::Left:
			m_text_position.x = m_current_size.x * 0.02;
			break;

		case TextTheme::TextHorizontalAlignment::Right:
			m_text_position.x = m_current_size.x * 0.98;
			break;
	}
	
	switch (m_text_theme->vertical_alignment)
	{
		case TextTheme::TextVerticalAlignment::Center:
			m_text_position.y = m_current_size.y * 0.5;
			break;

		case TextTheme::TextVerticalAlignment::Top:
			m_text_position.y = m_current_size.y * 0.02;
			break;

		case TextTheme::TextVerticalAlignment::Bottom:
			m_text_position.y = m_current_size.y * 0.98;
			break;
	}

	m_text_position.x += m_current_position.x;
	m_text_position.y += m_current_position.y;
	m_text.setPosition(m_text_position);
}

void TextControl::setTextColors(bool holding, bool hovering)
{
	m_text.setFillColor(!m_enabled ? m_text_theme->fill_disabled_color : holding ? m_text_theme->fill_holding_color : hovering ? m_text_theme->fill_hovering_color : m_text_theme->fill_default_color);
	m_text.setOutlineColor(!m_enabled ? m_text_theme->outline_disabled_color : holding ? m_text_theme->outline_holding_color : hovering ? m_text_theme->outline_hovering_color : m_text_theme->outline_default_color);
}

void TextControl::onMouseMoved(sf::Event::MouseMoveEvent data)
{
	if (m_initialized && m_input_valid && m_enabled)
	{
		bool current_hovering = m_hovering;
		Control::onMouseMoved(data);

		if (current_hovering != m_hovering)
		{
			setTextColors(m_hovering ? m_holding : false, m_hovering);
		}
	}
}

void TextControl::onMouseButtonPressed(Event::MouseButtonEvent data)
{
	Control::onMouseButtonPressed(data);
	if (m_initialized && m_input_valid && m_enabled)
	{
		if (m_holding || m_holding_wheel)
		{
			setTextColors(true, false);
		}
	}
}

void TextControl::onMouseButtonReleased(Event::MouseButtonEvent data)
{
	Control::onMouseButtonReleased(data);
	if (m_initialized && m_input_valid && m_enabled && m_holding_current && m_hovering)
	{
		setTextColors(false, m_hovering);
	}
}