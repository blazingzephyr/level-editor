////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#include "combo_box.hpp"

using sf::RenderWindow;
using sf::Int8;
using sf::IntRect;
using sf::String;
using sf::Vector2f;
using sf::Vector2u;
using std::function;
using std::map;

ComboBox::ComboBox() :

	TextControl::TextControl(),
	m_backwards_button(nullptr),
	m_forward_button(nullptr),
	m_items(0),
	m_items_count(0),
	m_index(0),
	m_clock(),
	m_elapsed_time(0),
	m_scroll_time(500),
	m_requires_restarting(true),
	m_button_size(),
	m_button_offset(0),
	m_holding_first_time(true)
{

}

ComboBox::ComboBox(RenderWindow* window, Vector2u intended_resolution, map<String, String>* strings, const ControlTheme* theme, SoundHandler* handler, const TextTheme* text_theme, Vector2f position, Vector2f size,
	const IntRect& bg, const IntRect& bg_focused, float button_offset, Vector2f button_size,
	const IntRect& left_button_bg, const IntRect& left_button_bg_focused, const IntRect& right_button_bg, const IntRect& right_button_bg_focused,
	std::vector<String> items, size_t index, int scroll_time, function<void(size_t)> updated, float min_y_position, bool visible, bool enabled) :

	TextControl::TextControl(window, intended_resolution, strings, theme, handler, text_theme, position, size, bg, bg_focused, "", min_y_position, visible, enabled),
	m_items(items),
	m_items_count(m_items.size()),
	m_index(index),
	m_clock(),
	m_elapsed_time(0),
	m_scroll_time(scroll_time),
	m_requires_restarting(true),
	m_button_size(button_size),
	m_button_offset(button_offset),
	m_holding(false),
	m_holding_first_time(true),
	m_value_updated(updated)
{
	auto initialize_button = [&](Button** control, float offset, const IntRect& button_bg, const IntRect& button_bg_focused, char summand = -1)
	{
		*control = new Button(
			window,
			intended_resolution,
			strings,
			theme,
			handler,
			text_theme,
			Vector2f(position.x + offset, position.y + (size.y - button_size.y) / 2),
			button_size,
			button_bg,
			button_bg_focused,
			"",
			[this, summand]()
			{
				if (m_extra_holding_check)
				{
					m_extra_holding_check = false;
				}
				else if (m_holding_first_time)
				{
					m_holding_first_time = false;
					m_extra_holding_check = true;
				}
				else
				{
					if (m_holding)
					{
						m_holding = false;
					}
					else
					{
						m_elapsed_time = 0;
						m_requires_restarting = true;
						moveIndex(summand);
					}
				}
			},
			[this, summand]()
			{
				if (m_extra_holding_check)
				{
					m_extra_holding_check = false;
				}
				if (m_holding_first_time)
				{
					m_holding_first_time = false;
					m_extra_holding_check = true;
					moveIndex(summand);
				}
				else
				{
					m_holding = true;

					if (m_requires_restarting)
					{
						m_requires_restarting = false;
						m_clock.restart();
					}

					m_elapsed_time = m_clock.getElapsedTime().asMilliseconds();
					if (m_elapsed_time >= m_scroll_time)
					{
						m_requires_restarting = true;
						moveIndex(summand);
					}
				}
			},
			0,
			visible,
			enabled
		);
	};

	initialize_button(&m_backwards_button, -button_size.x - button_offset, left_button_bg, left_button_bg_focused);
	initialize_button(&m_forward_button, size.x + button_offset, right_button_bg, right_button_bg_focused, 1);

	forceSetIndex(m_index);
}

String ComboBox::getItem() const
{
	return m_item;
}

size_t ComboBox::getIndex() const
{
	return m_index;
}

void ComboBox::forceSetIndex(size_t index)
{
	m_index = index;
	m_item = m_items[index];
	setText(m_strings->contains(m_item) ? m_strings->operator[](m_item) : m_item);
}

void ComboBox::setEnabled(bool enabled)
{
	TextControl::setEnabled(enabled);
	m_backwards_button->setEnabled(enabled);
	m_forward_button->setEnabled(enabled);
}

void ComboBox::setIndex(size_t index)
{
	forceSetIndex(index);
	m_value_updated(index);
}

void ComboBox::setItems(std::vector<sf::String> items, size_t new_index)
{
	m_items = items;
	m_items_count = m_items.size();
	setIndex(new_index);
}

void ComboBox::setPosition(sf::Vector2f position)
{
	TextControl::setPosition(position);
	m_backwards_button->setPosition(Vector2f(position.x - m_button_size.x - m_button_offset, position.y + (m_size.y - m_button_size.y) / 2));
	m_forward_button->setPosition(Vector2f(position.x + m_size.x + m_button_offset, position.y + (m_size.y - m_button_size.y) / 2));
}

void ComboBox::onLanguageUpdated()
{
	Control::onLanguageUpdated();
	setText(m_strings->contains(m_item) ? m_strings->operator[](m_item) : m_item);
}

void ComboBox::onThemeUpdated()
{
	Control::onThemeUpdated();
	if (m_initialized)
	{
		m_backwards_button->onThemeUpdated();
		m_forward_button->onThemeUpdated();
	}
}

void ComboBox::onUpdated()
{
	if (m_initialized)
	{
		m_backwards_button->onUpdated();
		m_forward_button->onUpdated();
	}
}

inline bool ComboBox::onWindowEvent(sf::Event data)
{
	if (m_initialized)
	{
		m_backwards_button->onWindowEvent(data);
		m_forward_button->onWindowEvent(data);
	}

	return TextControl::onWindowEvent(data);
}

void ComboBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	TextControl::draw(target, states);
	states.shader = m_shader;
	target.draw(*m_backwards_button, states);
	target.draw(*m_forward_button, states);
}

void ComboBox::moveIndex(Int8 summand)
{
	long long new_index = m_index + summand;
	if (new_index < 0)
	{
		new_index = m_items_count - 1;
	}
	else if (new_index == m_items_count)
	{
		new_index = 0;
	}

	setIndex(new_index);
}