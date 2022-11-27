////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_SLIDER_INL
#define EDITOR_SLIDER_INL

#include "slider.hpp"

using sf::FloatRect;
using sf::IntRect;
using sf::RenderWindow;
using sf::String;
using sf::Vector2f;
using sf::Vector2u;
using std::function;
using std::map;

template<typename T>
	requires arithmetic<T>
Slider<T>::Slider() :

	Control::Control(),
	m_slider_rect(),
	m_thumb(),
	m_thumb_position(),
	m_thumb_size(),
	m_vertical(false),
	m_min(0),
	m_max(0),
	m_range(0),
	m_value(0),
	m_scroll_multiplier(0),
	m_value_updated()
{

}

template<typename T>
	requires arithmetic<T>
Slider<T>::Slider(RenderWindow* window, Vector2u intended_resolution, map<String, String>* strings, const ControlTheme* theme, SoundHandler* handler, Vector2f position, Vector2f size,
	const IntRect& bg, const IntRect& bg_focused, Vector2f thumb_size, const IntRect& thumb, T min, T max, T value, float scroll_multiplier,
	function<void(T)> updated, bool vertical, float min_y_position, bool visible, bool enabled) :

	Control::Control(window, intended_resolution, strings, theme, handler, position, size, bg, bg_focused, min_y_position, visible, enabled),
	m_slider_rect(position, size),
	m_thumb(*m_theme->texture, thumb),
	m_thumb_size(thumb_size),
	m_vertical(vertical),
	m_min(min),
	m_max(max),
	m_range(max - min),
	m_scroll_multiplier(scroll_multiplier),
	m_value_updated(updated)
{
	m_thumb.setScale(m_original_size_coeff.x, m_original_size_coeff.y);
	m_thumb.setOrigin(m_thumb_size.x / 2, m_thumb_size.y / 2);
	forceSetValue(value);
}

template<typename T>
	requires arithmetic<T>
T Slider<T>::getValue() const
{
	return m_value;
}

template<typename T>
	requires arithmetic<T>
void Slider<T>::setPercent(float percentage)
{
	if (m_initialized && percentage >= 0. && percentage <= 1)
	{
		m_percentage = percentage;
		m_value = m_min + static_cast<T>(percentage * m_range);

		updateThumbPosition(percentage);
		m_value_updated(m_value);
	}
}

template<typename T>
	requires arithmetic<T>
void Slider<T>::forceSetValue(T value)
{
	if (m_initialized && value >= m_min && value <= m_max)
	{
		m_percentage = (value - m_min) / static_cast<float>(m_range);
		m_value = value;
		updateThumbPosition(m_percentage);
	}
}

template<typename T>
	requires arithmetic<T>
void Slider<T>::setValue(T value)
{
	forceSetValue(value);
	if (m_initialized && value >= m_min && value <= m_max)
	{
		m_value_updated(value);
	}
}

template<typename T>
	requires arithmetic<T>
inline void Slider<T>::setMax(float max)
{
	m_max = max;
	m_range = max - m_min;
	m_percentage = (m_value - m_min) / static_cast<float>(m_range);
	updateThumbPosition(m_percentage);
}

template<typename T>
	requires arithmetic<T>
inline void Slider<T>::setPosition(sf::Vector2f position)
{
	Control::setPosition(position);
	m_slider_rect = FloatRect(position, m_size);
	updateThumbPosition(m_percentage);
}

template<typename T>
	requires arithmetic<T>
void Slider<T>::onMouseMoved(sf::Event::MouseMoveEvent data)
{
	Control::onMouseMoved(data);
	if (m_initialized && m_holding)
	{
		moveThumb(data.x, data.y);
	}
}

template<typename T>
	requires arithmetic<T>
void Slider<T>::onMouseButtonPressed(sf::Event::MouseButtonEvent data)
{
	Control::onMouseButtonPressed(data);
	if (m_initialized)
	{
		m_scrolled = false;
	}
}

template<typename T>
	requires arithmetic<T>
inline void Slider<T>::onMouseButtonReleased(sf::Event::MouseButtonEvent data)
{
	if (m_initialized)
	{
		m_drawable = m_bg;
		if (!m_scrolled)
		{
			moveThumb(data.x, data.y, m_holding);
		}
	}

	Control::onMouseButtonReleased(data);
}

template<typename T>
	requires arithmetic<T>
inline void Slider<T>::onThemeUpdated()
{
	Control::onThemeUpdated();
	if (m_initialized)
	{
		m_thumb.setTexture(*m_theme->texture);
	}
}

template<typename T>
	requires arithmetic<T>
void Slider<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Control::draw(target, states);
	if (m_initialized && m_visible)
	{
		target.draw(m_thumb, states);
	}
}

template<typename T>
	requires arithmetic<T>
inline void Slider<T>::onClicked(sf::Event::MouseButtonEvent data)
{
	m_drawable = m_bg_active;
}

template<typename T>
	requires arithmetic<T>
inline void Slider<T>::onScrolled(sf::Event::MouseWheelScrollEvent data)
{
	m_scrolled = true;
	setPercent(m_percentage - data.delta / 100 * m_scroll_multiplier);
}

template<typename T>
	requires arithmetic<T>
inline void Slider<T>::moveThumb(float x, float y, bool is_hovering)
{
	if (is_hovering)
	{
		FloatRect thumb_rect = FloatRect(m_thumb.getPosition(), m_thumb_size);
		bool contains_thumb = thumb_rect.contains(x, y);
		bool contains_slider = m_vertical ? m_global_position.y <= y <= m_global_position.y + m_global_position.y + m_global_size.y 
			: m_global_position.x <= x <= m_global_position.x + m_global_position.x + m_global_size.x;

		x /= m_size_coeff.x;
		y /= m_size_coeff.y;

		if (contains_slider)
		{
			setPercent(m_vertical ? (y - m_position.y) / m_size.y : (x - m_position.x) / m_size.x);
		}

		else if (contains_thumb)
		{
			setValue(m_vertical ? y <= m_position.y : x <= m_position.x ? m_min : m_max);
		}
	}
}

template<typename T>
	requires arithmetic<T>
inline void Slider<T>::updateThumbPosition(float percentage)
{
	m_thumb.setPosition((m_position.x + (m_vertical ? m_size.x / 2 : percentage * m_size.x)) * m_original_size_coeff.x, 
		(m_position.y + (m_vertical ? percentage * m_size.y : m_size.y / 2)) * m_original_size_coeff.y);
}

#endif