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

#ifndef LEVEL_EDITOR_NUMERIC_UP_DOWN_INL
#define LEVEL_EDITOR_NUMERIC_UP_DOWN_INL

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "NumericUpDown.hpp"


namespace le
{
////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline NumericUpDown<T>::NumericUpDown() :

InputControl::InputControl(),
m_buttonUp        (),
m_buttonDown      (),
m_onValueChanged  ([](NumericUpDown<T>&, T) {}),
m_firstExpression (),
m_secondExpression(),
m_previous        (),
m_min             (0),
m_max             (0),
m_value           (0),
m_diff            (0),
m_secondaryButtons()
{
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline NumericUpDown<T>::NumericUpDown(const sf::Vector2f& position, const sf::Vector3f& buttonOffsets, const sf::Vector2f& size,
const sf::Vector2f& buttonSize,
const sf::Texture& texture, const sf::IntRect& spriteDefault, const sf::IntRect& spriteFocused,
const sf::IntRect& buttonSpriteDefault, const sf::IntRect& buttonSpriteActive, const TextTheme* textTheme, 
const InputTextStyle* inputStyle, T min, T max, T value, T diff, int scrollTime,
Event1<NumericUpDown<T>, T> onValueUpdated,
Event1<InputControl, sf::String> onTextUpdated, bool enabled) :

InputControl::InputControl(position, size, texture, spriteDefault, spriteFocused,
textTheme, inputStyle, onTextUpdated, std::to_wstring(value), enabled),

m_onValueChanged  (onValueUpdated),
m_firstExpression (std::unsigned_integral<T> ? L"^[+]?\\d+$" : std::integral<T> ? L"^[+-]?\\d+$" : L"^[0-9.+-]+$"),
m_secondExpression(L"^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)$"),
m_previous        (std::to_wstring(value)),
m_min             (min),
m_max             (max),
m_value           (value),
m_diff            (diff),

m_secondaryButtons(
	&m_buttonDown, &m_buttonUp, sf::Vector2f(size.x + buttonOffsets.x, buttonOffsets.z),
	sf::Vector2f(size.x + buttonOffsets.x, buttonSize.y + buttonOffsets.y), buttonSize,
	texture, buttonSpriteDefault, buttonSpriteActive, textTheme, enabled, scrollTime,
	[this](int8_t summand) { setValue(this->m_value + summand * this->m_diff); }
)
{
	this->m_buttonUp.setScale(1, -1);
	this->m_buttonUp.setParent(this);
	this->m_buttonDown.setParent(this);
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline T NumericUpDown<T>::getValue() const
{
	return this->m_value;
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline void NumericUpDown<T>::setValue(T value, bool raiseEvent)
{
	if (value >= this->m_min && value <= this->m_max)
	{
		this->m_value = value;
		updateText();
		
		if (raiseEvent)
		{
			this->m_onValueChanged(*this, value);
		}
	}
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline void NumericUpDown<T>::update()
{
	Control::update();
	this->m_buttonUp.update();
	this->m_buttonDown.update();
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline bool NumericUpDown<T>::onWindowEvent(sf::RenderWindow& window, sf::Event event)
{
	bool isAccepted = Control::onWindowEvent(window, event);
	if (isAccepted)
	{
		this->m_buttonUp.onWindowEvent(window, event);
		this->m_buttonDown.onWindowEvent(window, event);
	}

	return isAccepted;
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline void NumericUpDown<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	InputControl::draw(target, states);
	states.transform *= getTransform();
	target.draw(this->m_buttonUp, states);
	target.draw(this->m_buttonDown, states);
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline InputControl::ValidationResult NumericUpDown<T>::validateText(sf::String& buffer)
{
	bool cursorStatic = false;
	if (std::integral<T> && buffer.getSize() > 1 && buffer.toUtf8().starts_with('0'))
	{
		buffer = buffer.substring(1);
		cursorStatic = true;
	}

	std::wstring newBuffer = buffer;
	if (newBuffer == L"")
		newBuffer = L"0";

	bool firstPass = std::regex_match(newBuffer, this->m_firstExpression);
	if (firstPass)
	{
		if (std::floating_point<T>)
		{
			bool floatPass = std::regex_match(newBuffer, this->m_secondExpression);
			if (!floatPass)
			{
				newBuffer = this->m_previous;
			}
		}

		try
		{
			T valueBuffer = T();
			if constexpr (std::is_same_v<T, int>)
			{
				valueBuffer = std::stoi(newBuffer);
			}
			else if constexpr (std::is_same_v<T, long>)
			{
				valueBuffer = std::stol(newBuffer);
			}
			else if constexpr (std::is_same_v<T, long long>)
			{
				valueBuffer = std::stoll(newBuffer);
			}
			else if constexpr (std::is_same_v<T, unsigned> || std::is_same_v<T, unsigned long>)
			{
				valueBuffer = std::stoul(newBuffer);
			}
			else if constexpr (std::is_same_v<T, unsigned long long>)
			{
				valueBuffer = std::stoull(newBuffer);
			}
			else if constexpr (std::is_same_v<T, float>)
			{
				valueBuffer = std::stof(newBuffer);
			}
			else if constexpr (std::is_same_v<T, double>)
			{
				valueBuffer = std::stod(newBuffer);
			}
			else if constexpr (std::is_same_v<T, long double>)
			{
				valueBuffer = std::stold(newBuffer);
			}
			else
			{
				valueBuffer = std::stoi(newBuffer);
			}

			if (valueBuffer < this->m_min)
			{
				valueBuffer = this->m_min;
			}
			else if (valueBuffer > this->m_max)
			{
				valueBuffer = this->m_max;
			}

			this->m_value = valueBuffer;
			this->m_onValueChanged(*this, valueBuffer);
			this->m_previous = newBuffer;
		}
		catch (...)
		{

		}
	}

	return	cursorStatic ? InputControl::ValidationResult::Static :
			firstPass	 ? InputControl::ValidationResult::Valid  : InputControl::ValidationResult::Invalid;
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline void NumericUpDown<T>::onUnclicked(sf::Mouse::Button button, sf::Vector2f worldPos)
{
	InputControl::onUnclicked(button, worldPos);
	updateText();
}


////////////////////////////////////////////////////////////
template<typename T>
requires std::is_arithmetic_v<T>
inline void NumericUpDown<T>::updateText()
{
	std::wstring string = std::to_wstring(this->m_value);
	if (std::floating_point<T>)
		string.erase(string.find_last_not_of('0') + 1, std::wstring::npos);

	setString(string);
}

} //namespace le


#endif // LEVEL_EDITOR_NUMERIC_UP_DOWN_INL