////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright (c) 2023 ZaBlazzingZeif
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
//
////////////////////////////////////////////////////////////

#ifndef LEVEL_EDITOR_SLIDER_INL
#define LEVEL_EDITOR_SLIDER_INL

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Slider.hpp"


namespace le
{
////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline Slider<T>::Slider() :

SpriteBasedControl::SpriteBasedControl(),
m_onValueChanged(),
m_onMaxValueChanged(),
m_thumb(),
m_thumbSize(0.f, 0.f),
m_isVertical(false),
m_min(0),
m_max(0),
m_range(0),
m_value(0),
m_percentage(0),
m_scrollMultiplier(0.f),
m_isScrolling(false)
{
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline Slider<T>::Slider(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& thumbSize, const sf::Texture& texture, const sf::IntRect& spriteDefault,
const sf::IntRect& spriteActive, const sf::IntRect& thumb, bool isVertical, T min, T max, T value, float scrollMultiplier,
Event1<Slider<T>, T> onValueChanged, Event1<Slider<T>, T> onMaxValueChanged, 
bool enabled) :

SpriteBasedControl::SpriteBasedControl(position, size, texture, spriteDefault, spriteActive, false, enabled),
m_onValueChanged(onValueChanged),
m_onMaxValueChanged(onMaxValueChanged),
m_thumb(sf::Vector2f(), texture, thumb),
m_thumbSize(thumbSize),
m_isVertical(isVertical),
m_min(min),
m_max(max),
m_range(max - min),
m_value(value),
m_percentage((value - min) / static_cast<float>(max - min)),
m_scrollMultiplier(scrollMultiplier),
m_isScrolling(false)
{
	this->m_thumb.setOrigin(thumbSize.x / 2.f, thumbSize.x / 2.f);
	updateThumbPosition();
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline T Slider<T>::getValue() const
{
	return this->m_value;
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline void Slider<T>::setPercentage(float percentage, bool raiseEvent)
{
	if (percentage >= 0.f && percentage <= 1.f)
	{
		this->m_percentage = percentage;
		this->m_value = this->m_min;
		
		float value = this->m_range * percentage;
		this->m_value += std::is_integral_v<T> ? std::round(value) : value;
		updateThumbPosition();

		if (raiseEvent)
		{
			this->m_onValueChanged(*this, this->m_value);
		}
	}
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline void Slider<T>::setValue(T value, bool raiseEvent)
{
	if (value >= this->m_min && value <= this->m_max)
	{
		this->m_value = value;
		this->m_percentage = (value - this->m_min) / static_cast<float>(this->m_range);
		updateThumbPosition();

		if (raiseEvent)
		{
			this->m_onValueChanged(*this, this->m_value);
		}
	}
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline void Slider<T>::setMax(T max, bool raiseEvent)
{
	this->m_max = max;
	this->m_range = max - this->m_min;
	this->m_percentage = (this->m_value - this->m_min) / static_cast<float>(this->m_range);
	updateThumbPosition(m_percentage);

	if (raiseEvent)
	{
		this->m_onMaxValueChanged(*this, this->m_max);
	}
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline void Slider<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	SpriteBasedControl::draw(target, states);
	states.transform *= getTransform();
	target.draw(this->m_thumb, states);
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline void Slider<T>::moveThumb(float x, float y)
{
	sf::Vector2f sliderPosition = this->getPosition();
	sf::Vector2f thumbPosition = this->m_thumb.getPosition();

	bool containsSlider = m_isVertical ?
		sliderPosition.y <= y <= sliderPosition.y + this->m_size.y :
		sliderPosition.x <= x <= sliderPosition.x + this->m_size.x;

	bool containsThumb = x >= thumbPosition.x &&
		                 x <= thumbPosition.x + this->m_size.x &&
		                 y >= thumbPosition.y &&
		                 y <= thumbPosition.y + this->m_size.y;

	if (containsSlider)
	{
		setPercentage(this->m_isVertical ?
			(y - sliderPosition.y) / this->m_size.y :
			(x - sliderPosition.x) / this->m_size.x
		);
	}
	else if (containsThumb)
	{
		setValue(this->m_isVertical ?
			y <= sliderPosition.y :
			x <= sliderPosition.x ?
				this->m_min : this->m_max
		);
	}
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline void Slider<T>::updateThumbPosition()
{
	float x = this->m_isVertical ? 0.5f : this->m_percentage;
	float y = this->m_isVertical ? this->m_percentage : 0.5f;
	this->m_thumb.setPosition(this->m_size.x * x, this->m_size.y * y);
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline void Slider<T>::onScrolledControl(sf::Event::MouseWheelScrollEvent mouseWheelScroll)
{
	setPercentage(this->m_percentage - mouseWheelScroll.delta / 100 * this->m_scrollMultiplier);
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline void Slider<T>::onPressed(sf::Mouse::Button button, sf::Vector2f worldPos)
{
	this->m_isScrolling = false;
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline void Slider<T>::onClicked(sf::Mouse::Button button, sf::Vector2f worldPos)
{
	this->m_sprite.setUseAlt(true);
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline void Slider<T>::onReleased(sf::Mouse::Button button, sf::Vector2f worldPos)
{
	this->m_sprite.setUseAlt(false);

	if (!this->m_isScrolling)
	{
		moveThumb(mouseButton.x, mouseButton.y);
	}
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline void Slider<T>::onMovedControl(sf::Event::MouseMoveEvent mouseMove)
{
	moveThumb(mouseMove.x, mouseMove.y);
}

} //namespace le


#endif // LEVEL_EDITOR_SLIDER_INL