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
SpriteBasedControl::SpriteBasedControl(const sf::Vector2f& position, const sf::Vector2f& size,
const SpriteBasedControlTheme* theme, const sf::IntRect& spriteDefault, const sf::IntRect& spriteAlt,
bool useAlt, bool enabled) :

Control::Control(position, size, enabled),
m_shader(nullptr),
m_sprite(sf::Vector2f(), theme ? *theme->m_texture : sf::Texture(), spriteDefault, spriteAlt, useAlt)
{
}


////////////////////////////////////////////////////////////
bool SpriteBasedControl::contains(float x, float y) const
{
	sf::FloatRect spriteRect = this->m_sprite.getLocalBounds();
	sf::Transform transform = getParentTransform() * getTransform();
	return transform.transformRect(spriteRect).contains(x, y);
}


////////////////////////////////////////////////////////////
void SpriteBasedControl::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.shader = this->m_shader;
	target.draw(this->m_sprite, states);
}


////////////////////////////////////////////////////////////
void SpriteBasedControl::onClicked(sf::Mouse::Button button, sf::Vector2f worldPos)
{
	printf("SpriteBasedControl::onClicked IS NOT IMPLEMENTED\n");
}


////////////////////////////////////////////////////////////
void SpriteBasedControl::onReleasedControl(sf::Mouse::Button button, sf::Vector2f worldPos)
{
	printf("SpriteBasedControl::onReleasedControl IS NOT IMPLEMENTED\n");
}


////////////////////////////////////////////////////////////
void SpriteBasedControl::onEntered(sf::Vector2f worldPos)
{
	if (this->m_theme)
	{
		this->m_shader = this->m_enabled ? this->m_theme->m_hovering : this->m_theme->m_disabledHovering;
	}
}


////////////////////////////////////////////////////////////
void SpriteBasedControl::onLeft(sf::Vector2f worldPos)
{
	if (this->m_theme)
	{
		this->m_shader = this->m_enabled ? nullptr : this->m_theme->m_disabled;
	}
}

} //namespace le