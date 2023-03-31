// MIT License
// 
// Copyright (c) 2022 ZaBlazzingZephyr
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef EDITOR_SLIDER_HPP
#define EDITOR_SLIDER_HPP

#include "control.hpp"
#include "../utility/arithmetic.hpp"
#include <functional>

template<typename T>
	requires arithmetic<T>
class Slider : public Control
{
public:
	Slider();
	Slider(sf::RenderWindow* window, sf::Vector2u intended_resolution, std::map<sf::String, sf::String>* strings, const ControlTheme* theme, SoundHandler* handler, sf::Vector2f position, sf::Vector2f size, const sf::IntRect& bg, const sf::IntRect& bg_focused,
		sf::Vector2f thumb_size, const sf::IntRect& thumb, T min, T max, T value, float scroll_multiplier, std::function<void(T)> updated, bool vertical, float min_y_position, bool visible = true, bool enabled = true);

	T						getValue() const;
	void					setPercent(float percentage);
	void					forceSetValue(T value);
	void					setValue(T value);
	void					setMax(float max);

	void					setPosition(sf::Vector2f position) override;
	void					onMouseMoved(sf::Event::MouseMoveEvent data) override;
	void					onMouseButtonPressed(sf::Event::MouseButtonEvent data) override;
	void					onMouseButtonReleased(sf::Event::MouseButtonEvent data) override;

	void					onThemeUpdated() override;
	void					draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	void					onClicked(sf::Event::MouseButtonEvent data) override;
	void					onScrolled(sf::Event::MouseWheelScrollEvent data) override;

private:
	std::function<void(T)>	m_value_updated;
	sf::FloatRect			m_slider_rect;
	sf::Sprite				m_thumb;
	sf::Vector2f			m_thumb_position;
	sf::Vector2f			m_thumb_size;
	bool					m_vertical;
	T						m_min;
	T						m_max;
	T						m_range;
	T						m_value;
	float					m_percentage;
	bool					m_scrolled;
	float					m_scroll_multiplier;

	void					moveThumb(float x, float y, bool is_hovering = true);
	void					updateThumbPosition(float percentage);
};

typedef Slider<sf::Uint8>	ByteSlider;
typedef Slider<sf::Uint16>	UshortSlider;
typedef Slider<sf::Uint32>	UintSlider;
typedef Slider<int>			IntSlider;
typedef Slider<float>		FloatSlider;
typedef Slider<double>		DoubleSlider;

#include "slider.inl"
#endif