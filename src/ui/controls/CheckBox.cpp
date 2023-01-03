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
#include "CheckBox.hpp"


namespace le
{
////////////////////////////////////////////////////////////
CheckBox::CheckBox() :
SpriteBasedControl::SpriteBasedControl(),
m_onCheckedChanged(),
m_isChecked(false)
{
};


////////////////////////////////////////////////////////////
CheckBox::CheckBox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Texture& texture, const sf::IntRect& spriteUnchecked,
const sf::IntRect& spriteChecked, Event1<CheckBox, bool> onCheckedChanged, bool isChecked, bool enabled) :

SpriteBasedControl::SpriteBasedControl(position, size, texture, spriteUnchecked, spriteChecked, false, enabled),
m_onCheckedChanged(onCheckedChanged)
{
	setPosition(position);
	setChecked(isChecked, false);
}


////////////////////////////////////////////////////////////
bool CheckBox::getChecked() const
{
	return this->m_isChecked;
}


////////////////////////////////////////////////////////////
void CheckBox::setChecked(bool checked, bool raiseEvent)
{
	if (this->m_isChecked != checked)
	{
		this->m_isChecked = checked;
		this->m_sprite.setUseAlt(checked);

		if (raiseEvent)
		{
			this->m_onCheckedChanged(*this, checked);
		}
	}
}


////////////////////////////////////////////////////////////
void CheckBox::setSprite(bool swap)
{
	if (this->m_enabled && this->m_holding)
	{
		this->m_sprite.setUseAlt(this->m_isChecked == swap);
	}
}


////////////////////////////////////////////////////////////
void CheckBox::onScrolledControl(sf::Event::MouseWheelScrollEvent mouseWheelScroll)
{
	setChecked(!this->m_isChecked);
}


////////////////////////////////////////////////////////////
void CheckBox::onClicked(sf::Mouse::Button button, sf::Vector2f worldPos)
{
	SpriteBasedControl::onClicked(button, worldPos);
	setSprite(false);
}


////////////////////////////////////////////////////////////
void CheckBox::onReleasedControl(sf::Mouse::Button button, sf::Vector2f worldPos)
{
	SpriteBasedControl::onReleasedControl(button, worldPos);
	setChecked(!this->m_isChecked);
}


////////////////////////////////////////////////////////////
void CheckBox::onEntered(sf::Vector2f worldPos)
{
	SpriteBasedControl::onEntered(worldPos);
	setSprite(false);
}


////////////////////////////////////////////////////////////
void CheckBox::onLeft(sf::Vector2f worldPos)
{
	SpriteBasedControl::onLeft(worldPos);
	setSprite(true);
}

} //namespace le