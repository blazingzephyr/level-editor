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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Control.hpp"


namespace le
{
////////////////////////////////////////////////////////////
Control::Control() :
m_enabled(false),
m_size(),
m_hovering(false),
m_holding(false),
m_wasHolding(false)
{
}


////////////////////////////////////////////////////////////
Control::Control(sf::Vector2f position, sf::Vector2f size, bool enabled) :
m_enabled(enabled),
m_size(size),
m_hovering(false),
m_holding(false),
m_wasHolding(false)
{
	setPosition(position);
}


////////////////////////////////////////////////////////////
bool Control::contains(float x, float y) const
{
	sf::Vector2f position = getPosition();
	return x >= position.x
		&& x <= position.x + this->m_size.x
		&& y >= position.y
		&& y <= position.y + this->m_size.y;
}


////////////////////////////////////////////////////////////
void Control::update()
{
	if (this->m_enabled && this->m_hovering && this->m_holding)
	{
		onHold();
	}
}


////////////////////////////////////////////////////////////
void Control::onMouseWheelScrolled(sf::Event::MouseWheelScrollEvent mouseWheelScroll)
{
	if (this->m_enabled && this->m_hovering)
	{
		onScrolledControl(mouseWheelScroll);
	}
}


////////////////////////////////////////////////////////////
void Control::onMouseButtonPressed(sf::Event::MouseButtonEvent mouseButton)
{
	if (this->m_hovering)
	{
		this->m_holding = mouseButton.button == sf::Mouse::Left || mouseButton.button == sf::Mouse::Right;
	}

	if (this->m_enabled)
	{
		onPressed(mouseButton);

		if (this->m_holding)
		{
			onClicked(mouseButton);
		}
		else
		{
			onUnclicked(mouseButton);
		}
	}
}


////////////////////////////////////////////////////////////
void Control::onMouseButtonReleased(sf::Event::MouseButtonEvent mouseButton)
{
	if (this->m_enabled)
	{
		this->m_wasHolding = this->m_holding;
		this->m_holding = false;

		if (this->m_hovering && this->m_wasHolding)
		{
			onReleased(mouseButton);
		}
	}
}


////////////////////////////////////////////////////////////
void Control::onMouseMoved(sf::Event::MouseMoveEvent mouseMove)
{
	if (this->m_enabled)
	{
		bool hovering = contains(static_cast<float>(mouseMove.x), static_cast<float>(mouseMove.y));
		if (this->m_hovering != hovering)
		{
			this->m_hovering = hovering;

			if (hovering)
			{
				onEntered(mouseMove);
			}
			else
			{
				onLeft(mouseMove);
			}
		}

		if (this->m_holding)
		{
			onMovedControl(mouseMove);
		}
	}
}

} //namespace le