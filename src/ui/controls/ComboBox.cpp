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
#include "ComboBox.hpp"


namespace le
{
////////////////////////////////////////////////////////////
ComboBox::ComboBox() :
Control::Control(),
m_text(),
m_onItemChanged(),
m_buttonLeft(),
m_buttonRight(),
m_items(),
m_item(),
m_index(0),
m_secondaryButtons()
{
}


////////////////////////////////////////////////////////////
ComboBox::ComboBox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& buttonSize, const sf::Texture& texture,
const sf::IntRect& spriteDefault, const sf::IntRect& spriteActive, const TextStyle* style, const TextTheme* theme,
const Strings* strings, const Items& items, size_t index, int scrollTime, Event1<ComboBox, size_t> onItemChanged, bool enabled) :

Control::Control(position, size, enabled),

m_text(sf::Vector2f(), sf::Vector2u(size), style, strings, items[index]),
m_onItemChanged(onItemChanged),
m_items(items),
m_secondaryButtons(
	&m_buttonLeft, &m_buttonRight, sf::Vector2f(buttonSize.x, size.y / 2), sf::Vector2f(size.x - buttonSize.x, size.y / 2),
	buttonSize, texture, spriteDefault, spriteActive, theme, enabled, scrollTime, [this](int8_t summand) { moveIndex(summand); }
)
{
	this->m_buttonLeft.setOrigin(0, buttonSize.y / 2);
	this->m_buttonLeft.setScale(-1, 1);
	this->m_buttonLeft.setParent(this);

	this->m_buttonRight.setOrigin(0, buttonSize.y / 2);
	this->m_buttonRight.setParent(this);

	setIndex(index, false);
}


////////////////////////////////////////////////////////////
sf::String ComboBox::getItem() const
{
	return this->m_item;
}


////////////////////////////////////////////////////////////
bool ComboBox::getIndex() const
{
	return this->m_index;
}


////////////////////////////////////////////////////////////
void ComboBox::setItems(Items items, size_t new_index, bool raiseEvent)
{
	this->m_items = items;
	setIndex(new_index, raiseEvent);
}


////////////////////////////////////////////////////////////
void ComboBox::setIndex(size_t index, bool raiseEvent)
{
	if (index < this->m_items.size())
	{
		this->m_index = index;
		this->m_item = this->m_items[index];
		this->m_text.setString(this->m_item);

		if (raiseEvent)
		{
			this->m_onItemChanged(*this, index);
		}
	}
}


////////////////////////////////////////////////////////////
void ComboBox::setEnabled(bool enabled)
{
	Control::setEnabled(enabled);
	this->m_buttonLeft.setEnabled(enabled);
	this->m_buttonRight.setEnabled(enabled);
}


////////////////////////////////////////////////////////////
void ComboBox::update()
{
	Control::update();
	this->m_buttonLeft.update();
	this->m_buttonRight.update();
}


////////////////////////////////////////////////////////////
bool ComboBox::onWindowEvent(sf::RenderWindow& window, sf::Event event)
{
	bool isAccepted = Control::onWindowEvent(window, event);
	if (isAccepted)
	{
		this->m_buttonLeft.onWindowEvent(window, event);
		this->m_buttonRight.onWindowEvent(window, event);
	}

	return isAccepted;
}


////////////////////////////////////////////////////////////
void ComboBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(this->m_text, states);
	target.draw(this->m_buttonLeft, states);
	target.draw(this->m_buttonRight, states);
}


////////////////////////////////////////////////////////////
void ComboBox::moveIndex(int8_t summand)
{
	long long new_index = this->m_index + summand;
	if (new_index < 0)
	{
		new_index = m_items.size() - 1;
	}
	else if (new_index == m_items.size())
	{
		new_index = 0;
	}

	setIndex(new_index);
}

} //namespace le