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
const sf::Transform& Control::getParentTransform() const
{
	sf::Transform combinedTransform = sf::Transform::Identity;
	std::function<void(const Control*)> getParentTransform = [&](const Control* parent)
	{
		if (parent != nullptr)
		{
			combinedTransform *= parent->getTransform();
			getParentTransform(parent->m_parent);
		}
	};

	getParentTransform(this->m_parent);
	return combinedTransform;
}


////////////////////////////////////////////////////////////
bool Control::contains(float x, float y) const
{
	sf::Vector2f position = getPosition();
	sf::FloatRect rect = sf::FloatRect(position.x, position.y, this->m_size.x, this->m_size.y);
	return getParentTransform().transformRect(rect).contains(x, y);
}


////////////////////////////////////////////////////////////
void Control::setEnabled(bool enabled)
{
	this->m_enabled = enabled;
}


////////////////////////////////////////////////////////////
void Control::setParent(Control* parent)
{
	this->m_parent = parent;
}


////////////////////////////////////////////////////////////
void Control::update()
{
	if (this->m_enabled && this->m_hovering && this->m_holding)
	{
		onHold();
	}
}


bool Control::onWindowEvent(sf::RenderWindow& window, sf::Event event)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

	bool isAccepted = true;
	this->m_window = &window;

	switch (event.type)
	{
		case sf::Event::TextEntered:
			onTextEntered(event.text.unicode);
			break;

		case sf::Event::KeyPressed:
			onKeyPressed(event.key);
			break;

		case sf::Event::KeyReleased:
			onKeyReleased(event.key);
			break;

		case sf::Event::MouseWheelScrolled:
			onMouseWheelScrolled(event.mouseWheelScroll);
			break;

		case sf::Event::MouseButtonPressed:
			onMouseButtonPressed(event.mouseButton.button, worldPos);
			break;

		case sf::Event::MouseButtonReleased:
			onMouseButtonReleased(event.mouseButton.button, worldPos);
			break;

		case sf::Event::MouseMoved:
			onMouseMoved(worldPos);
			break;

		default:
			isAccepted = false;
			break;
	}

	return isAccepted;
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
void Control::onMouseButtonPressed(sf::Mouse::Button button, sf::Vector2f worldPos)
{
	if (this->m_hovering)
	{
		this->m_holding = button == sf::Mouse::Left || button == sf::Mouse::Right;
	}

	if (this->m_enabled)
	{
		onPressed(button, worldPos);

		if (this->m_holding)
		{
			onClicked(button, worldPos);
		}
		else
		{
			onUnclicked(button, worldPos);
		}
	}
}


////////////////////////////////////////////////////////////
void Control::onMouseButtonReleased(sf::Mouse::Button button, sf::Vector2f worldPos)
{
	if (this->m_enabled)
	{
		this->m_wasHolding = this->m_holding;
		this->m_holding = false;

		if (this->m_wasHolding)
		{
			onReleased(button, worldPos);
			
			if (this->m_hovering)
			{
				onReleasedControl(button, worldPos);
			}
		}
	}
}


////////////////////////////////////////////////////////////
void Control::onMouseMoved(sf::Vector2f worldPos)
{
	if (this->m_enabled)
	{
		bool hovering = contains(worldPos.x, worldPos.y);
		if (this->m_hovering != hovering)
		{
			this->m_hovering = hovering;

			if (hovering)
			{
				onEntered(worldPos);
			}
			else
			{
				onLeft(worldPos);
			}
		}

		if (this->m_holding)
		{
			onMovedControl(worldPos);
		}
	}
}

} //namespace le