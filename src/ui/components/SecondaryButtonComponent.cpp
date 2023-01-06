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

///////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SecondaryButtonComponent.hpp"


namespace le
{
////////////////////////////////////////////////////////////
SecondaryButtonComponent::SecondaryButtonComponent() :
m_onHold    ([](int8_t) {}),
m_clock     (),
m_restart   (false),
m_elapsed   (0),
m_scrollTime(0)
{
}

SecondaryButtonComponent::SecondaryButtonComponent(Button* first, Button* second, const sf::Vector2f& firstButtonPos,
const sf::Vector2f& secondButtonPos, const sf::Vector2f& size, const sf::Texture& texture, const sf::IntRect& spriteDefault, 
const sf::IntRect& spriteActive, const TextTheme* textTheme, bool enabled, int scrollTime, std::function<void(int8_t)> onHold) :
	
m_onHold    (onHold),
m_clock     (),
m_restart   (false),
m_elapsed   (0),
m_scrollTime(scrollTime)
{
	auto initializeButton = [&](Button* button, const sf::Vector2f& position, int8_t summand)
	{
		*button = Button
		(
			position,
			size,
			texture,
			spriteDefault,
			spriteActive,
			textTheme,
			nullptr,
			L"",
			[=, this](Button&)
			{
				onHoldButton(summand);
			},
			[=, this](Button&)
			{
				onHoldButton(summand);
			},
			enabled
		);
	};

	initializeButton(first, firstButtonPos, -1);
	initializeButton(second, secondButtonPos, 1);
}


////////////////////////////////////////////////////////////
void SecondaryButtonComponent::onHoldButton(int8_t summand)
{
	this->m_elapsed = m_clock.getElapsedTime().asMilliseconds();
	if (this->m_elapsed >= this->m_scrollTime)
	{
		this->m_clock.restart();
		this->m_onHold(summand);
	}
}

} //namespace le