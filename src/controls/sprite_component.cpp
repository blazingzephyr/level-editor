////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright (c) 2022 ZaBlazzingZeif
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
#include "sprite_component.hpp"


namespace le
{
////////////////////////////////////////////////////////////
SpriteComponent::SpriteComponent(const sf::Vector2f& position, const sf::Texture& texture_pointer, const sf::IntRect& sprite) :
m_sprite_current(&this->m_sprite_default),
m_sprite_default(texture_pointer, sprite),
m_sprite_alt    (std::nullopt),
m_use_alt       (false)
{
	setPosition(position);
}


////////////////////////////////////////////////////////////
SpriteComponent::SpriteComponent(const sf::Vector2f& position, const sf::Texture& texture_pointer, const sf::IntRect& sprite_default, std::optional<const sf::IntRect> sprite_alt, bool use_alt) :
m_sprite_current(nullptr),
m_sprite_default(texture_pointer, sprite_default),
m_sprite_alt    (sprite_alt ? std::make_optional<sf::Sprite>(texture_pointer, *sprite_alt) : std::nullopt),
m_use_alt       (false)
{
	setPosition(position);
	setUseAlt(use_alt);
}


////////////////////////////////////////////////////////////
void SpriteComponent::setUseAlt(bool use_alt)
{
	this->m_use_alt = this->m_sprite_alt && use_alt;
	this->m_sprite_current = std::shared_ptr<const sf::Sprite>(this->m_use_alt ? std::to_address(this->m_sprite_alt) : &this->m_sprite_default);
}


////////////////////////////////////////////////////////////
void SpriteComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(*this->m_sprite_current, states);
}

} //namespace le