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
#include "Button.hpp"


namespace le
{
////////////////////////////////////////////////////////////
Button::Button() :
TextBasedControl::TextBasedControl(),
m_onReleased(),
m_onHold()
{
};


Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Texture& texture, 
const sf::IntRect& spriteDefault, const sf::IntRect& spriteActive, const TextTheme* textTheme, const Strings* strings,
const sf::String& string, Event0<Button> onReleased, Event0<Button> onHold, bool enabled) :

TextBasedControl::TextBasedControl(position, sf::Vector2f(0, 0), size, texture, spriteDefault,
spriteActive, textTheme, false, enabled),
m_onReleased(onReleased),
m_onHold(onHold)
{
	this->m_text = LocalizableTextComponent(sf::Vector2f(), sf::Vector2u(size), textTheme->m_default, strings, string);
}

////////////////////////////////////////////////////////////
void Button::onHold()
{
	this->m_onHold(*this);
}


////////////////////////////////////////////////////////////
void Button::onClicked(sf::Event::MouseButtonEvent mouseButton)
{
	TextBasedControl::onClicked(mouseButton);
	this->m_sprite.setUseAlt(true);
}


////////////////////////////////////////////////////////////
void Button::onReleased(sf::Event::MouseButtonEvent mouseButton)
{
	TextBasedControl::onReleased(mouseButton);
	this->m_sprite.setUseAlt(false);
	this->m_onReleased(*this);
}


////////////////////////////////////////////////////////////
void Button::onEntered(sf::Event::MouseMoveEvent mouseMove)
{
	TextBasedControl::onEntered(mouseMove);
	this->m_sprite.setUseAlt(this->m_holding);
}


////////////////////////////////////////////////////////////
void Button::onLeft(sf::Event::MouseMoveEvent mouseMove)
{
	TextBasedControl::onLeft(mouseMove);
	this->m_sprite.setUseAlt(false);
}

} //namespace le