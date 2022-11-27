////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_NUMERIC_UP_DOWN_INL
#define EDITOR_NUMERIC_UP_DOWN_INL

#include "numeric_up_down.hpp"

using sf::Event;
using sf::IntRect;
using sf::Mouse;
using sf::RenderStates;
using sf::RenderTarget;
using sf::RenderWindow;
using sf::Shader;
using sf::Sprite;
using sf::String;
using sf::Text;
using sf::Vector2f;
using sf::Vector2u;
using std::floating_point;
using std::function;
using std::integral;
using std::is_same_v;
using std::map;
using std::out_of_range;
using std::regex_match;
using std::stod;
using std::stof;
using std::stoi;
using std::stol;
using std::stold;
using std::stoll;
using std::stoul;
using std::stoull;
using std::to_string;
using std::unsigned_integral;
using std::regex;
using std::string;

template<typename T>
	requires arithmetic<T>
inline NumericUpDown<T>::NumericUpDown() :

	InputControl(),
	m_value_updated(),
	m_first_condition(),
	m_second_condition(),
	m_last_valid(),
	m_value(0),
	m_min(0),
	m_max(0),
	m_step(0),
	m_top_button()
{

}

template<typename T>
	requires arithmetic<T>
inline NumericUpDown<T>::NumericUpDown(RenderWindow* window, Vector2u intended_resolution, map<String, String>* strings, const ControlTheme* theme, SoundHandler* handler, const TextTheme* text_theme, const InputControlTheme* input_control_theme,
	Vector2f field_position, Vector2f field_size, const IntRect& bg, const IntRect& bg_focused, Vector2f button_size,
	const IntRect& top_button_bg, const sf::IntRect& top_button_bg_focused, const IntRect& bottom_button_bg, const IntRect& bottom_button_bg_focused,
	T min, T max, T step, T value, function<void(T)> updated, int scroll_time, float min_y_position, bool visible, bool enabled) :

	InputControl::InputControl(window, intended_resolution, strings, theme, handler, text_theme, input_control_theme, field_position, field_size, bg, bg_focused, to_string(value), [](sf::String) {}, min_y_position, visible, enabled),
	m_button_size(button_size),
	m_value_updated(updated),
	m_first_condition(unsigned_integral<T> ? "^[+]?\\d+$" : integral<T> ? "^[+-]?\\d+$" : "^[0-9.+-]+$"),
	m_second_condition("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)$"),
	m_last_valid(to_string(value)),
	m_value(value),
	m_min(min),
	m_max(max),
	m_step(step),
	m_scroll_time(scroll_time),
	m_holding_first_time(true)
{
	auto initialize_button = [&](Button** control, const IntRect& button_bg, const IntRect& button_bg_focused, float y_shift = 0.f, float multiplier = 1.f)
	{
		*control = new Button(
			window,
			intended_resolution,
			strings,
			theme,
			handler,
			text_theme,
			Vector2f(field_position.x + field_size.x, field_position.y + y_shift),
			button_size,
			button_bg,
			button_bg_focused,
			"",
			[&, this, multiplier]()
			{
				if (m_holding)
				{
					m_holding = false;
				}
				else
				{
					m_elapsed_time = 0;
					m_requires_restarting = true;
					setValue(m_value + multiplier * m_step);
				}
			},
			[&, this, multiplier]()
			{
				if (m_holding_first_time)
				{
					m_holding_first_time = false;
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
						setValue(m_value + multiplier * m_step);
					}
				}
			},
			0,
			visible,
			enabled
		);
	};

	initialize_button(&m_top_button, top_button_bg, top_button_bg_focused);
	initialize_button(&m_bottom_button, bottom_button_bg, bottom_button_bg_focused, button_size.y, -1.f);

	updateText();
};

template<typename T>
	requires arithmetic<T>
inline void NumericUpDown<T>::setEnabled(bool enabled)
{
	InputControl::setEnabled(enabled);
	m_top_button->setEnabled(enabled);
	m_bottom_button->setEnabled(enabled);
}

template<typename T>
	requires arithmetic<T>
inline void NumericUpDown<T>::setPosition(sf::Vector2f position)
{
	TextControl::setPosition(position);
	auto& t = m_text;
	m_top_button->setPosition(Vector2f(position.x + m_size.x, position.y));
	m_bottom_button->setPosition(Vector2f(position.x + m_size.x, position.y + m_button_size.y));
}

template<typename T>
	requires arithmetic<T>
inline T NumericUpDown<T>::getNumber() const
{
	return m_value;
}

template<typename T>
	requires arithmetic<T>
inline void NumericUpDown<T>::setValue(T value)
{
	if (m_initialized && value >= m_min && value <= m_max)
	{
		m_value = value;
		updateText();
		m_value_updated(value);
	}
}

template<typename T>
	requires arithmetic<T>
inline void NumericUpDown<T>::forceSetValue(T value)
{
	if (m_initialized && value >= m_min && value <= m_max)
	{
		m_value = value;
		updateText();
	}
}

template<typename T>
	requires arithmetic<T>
inline void NumericUpDown<T>::draw(RenderTarget& target, RenderStates states) const
{
	InputControl::draw(target, states);
	if (m_initialized)
	{
		target.draw(*m_top_button);
		target.draw(*m_bottom_button);
	}
}

template<typename T>
	requires arithmetic<T>
inline void NumericUpDown<T>::onUpdated()
{
	if (m_initialized)
	{
		m_top_button->onUpdated();
		m_bottom_button->onUpdated();
	}
}

template<typename T>
	requires arithmetic<T>
inline bool NumericUpDown<T>::onWindowEvent(sf::Event data)
{
	if (m_initialized)
	{
		m_top_button->onWindowEvent(data);
		m_bottom_button->onWindowEvent(data);
	}

	return InputControl::onWindowEvent(data);
}

template<typename T>
	requires arithmetic<T>
inline void NumericUpDown<T>::onUnclicked(Event::MouseButtonEvent data)
{
	InputControl::onUnclicked(data);
	if (m_initialized)
	{
		updateText();
	}
}

template<typename T>
	requires arithmetic<T>
inline InputControl::ValidationResult NumericUpDown<T>::validateText(String& buffer)
{
	bool cursor_static = false;
	if (integral<T> && buffer.getSize() > 1 && buffer.toUtf8().starts_with('0'))
	{
		buffer = buffer.substring(1);
		cursor_static = true;
	}

	string new_buffer = buffer;
	if (new_buffer == "")
		new_buffer = "0";

	bool first_check = regex_match(new_buffer, m_first_condition);
	if (first_check)
	{
		if (floating_point<T>)
		{
			bool second_check = regex_match(new_buffer, m_second_condition);
			if (!second_check)
			{
				new_buffer = m_last_valid;
			}
		}

		try
		{
			T value_buffer = T();
			if constexpr (is_same_v<T, int>)
			{
				value_buffer = stoi(new_buffer);
			}
			else if constexpr (is_same_v<T, long>)
			{
				value_buffer = stol(new_buffer);
			}
			else if constexpr (is_same_v<T, long long>)
			{
				value_buffer = stoll(new_buffer);
			}
			else if constexpr (is_same_v<T, unsigned> || is_same_v<T, unsigned long>)
			{
				value_buffer = stoul(new_buffer);
			}
			else if constexpr (is_same_v<T, unsigned long long>)
			{
				value_buffer = stoull(new_buffer);
			}
			else if constexpr (is_same_v<T, float>)
			{
				value_buffer = stof(new_buffer);
			}
			else if constexpr (is_same_v<T, double>)
			{
				value_buffer = stod(new_buffer);
			}
			else if constexpr (is_same_v<T, long double>)
			{
				value_buffer = stold(new_buffer);
			}
			else
			{
				value_buffer = stoi(new_buffer);
			}

			if (value_buffer < m_min)
			{
				value_buffer = m_min;
			}
			else if (value_buffer > m_max)
			{
				value_buffer = m_max;
			}

			m_value = value_buffer;
			m_value_updated(value_buffer);
			m_last_valid = new_buffer;
		}
		catch (...)
		{

		}
	}

	return	cursor_static	? InputControl::ValidationResult::Static	:
			first_check		? InputControl::ValidationResult::Valid		: InputControl::ValidationResult::Invalid;
}

template<typename T>
	requires arithmetic<T>
inline void NumericUpDown<T>::updateText()
{
	string string = to_string(m_value);
	if (floating_point<T>)
		string.erase(string.find_last_not_of('0') + 1, string::npos);

	setText(string);
	setCursor(m_str_len);
}

#endif