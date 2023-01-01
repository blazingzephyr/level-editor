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
#include "SpriteBasedControl.hpp"


namespace le
{
////////////////////////////////////////////////////////////
SpriteBasedControl::SpriteBasedControl() :
Control::Control(),
m_shader(nullptr),
m_sprite()
{
}


////////////////////////////////////////////////////////////
SpriteBasedControl::SpriteBasedControl(sf::Vector2f position, sf::Vector2f size, const sf::Texture& texture, 
const sf::IntRect& spriteDefault, const sf::IntRect& spriteAlt, bool useAlt, bool enabled) :
Control::Control(position, size, enabled),
m_shader(nullptr),
m_sprite(sf::Vector2f(), texture, spriteDefault, spriteAlt, useAlt)
{
}


////////////////////////////////////////////////////////////
void SpriteBasedControl::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.shader = this->m_shader;
	target.draw(this->m_sprite, states);
}


////////////////////////////////////////////////////////////
void SpriteBasedControl::onClicked(sf::Event::MouseButtonEvent mouseButton)
{
	printf("SpriteBasedControl::onClicked IS NOT IMPLEMENTED\n");
}


////////////////////////////////////////////////////////////
void SpriteBasedControl::onReleased(sf::Event::MouseButtonEvent mouseButton)
{
	printf("SpriteBasedControl::onReleased IS NOT IMPLEMENTED\n");
}


////////////////////////////////////////////////////////////
void SpriteBasedControl::onEntered(sf::Event::MouseMoveEvent mouseMove)
{
	this->m_shader = this->m_enabled ? nullptr_t() : nullptr_t();
	printf("SpriteBasedControl::onEntered IS NOT IMPLEMENTED\n");
}


////////////////////////////////////////////////////////////
void SpriteBasedControl::onLeft(sf::Event::MouseMoveEvent mouseMove)
{
	this->m_shader = this->m_enabled ? nullptr : nullptr_t();
	printf("SpriteBasedControl::onLeft IS NOT IMPLEMENTED\n");
}

} //namespace le