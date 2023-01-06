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
#include "SpriteComponent.hpp"


namespace le
{
////////////////////////////////////////////////////////////
SpriteComponent::SpriteComponent() :
m_spriteDefault(),
m_spriteAlt    (std::nullopt),
m_useAlt       (false)
{
}


////////////////////////////////////////////////////////////
SpriteComponent::SpriteComponent(const sf::Vector2f& position, const sf::Texture& texture, const sf::IntRect& sprite) :
m_spriteDefault(texture, sprite),
m_spriteAlt    (std::nullopt),
m_useAlt       (false)
{
	setPosition(position);
}


////////////////////////////////////////////////////////////
SpriteComponent::SpriteComponent(const sf::Vector2f& position, const sf::Texture& texture,
const sf::IntRect& spriteDefault, std::optional<const sf::IntRect> spriteAlt, bool useAlt) :
m_spriteDefault(texture, spriteDefault),
m_spriteAlt    (spriteAlt ? std::make_optional<sf::Sprite>(texture, *spriteAlt) : std::nullopt),
m_useAlt       (useAlt)
{
	setPosition(position);
}


////////////////////////////////////////////////////////////
const sf::Sprite& SpriteComponent::getCurrent() const
{
	return this->m_useAlt ? *this->m_spriteAlt : this->m_spriteDefault;
}


////////////////////////////////////////////////////////////
sf::FloatRect SpriteComponent::getLocalBounds() const
{
	return getCurrent().getLocalBounds();
}


////////////////////////////////////////////////////////////
sf::FloatRect SpriteComponent::getGlobalBounds() const
{
	sf::FloatRect bounds = getCurrent().getLocalBounds();
	return getTransform().transformRect(bounds);
}


////////////////////////////////////////////////////////////
void SpriteComponent::setUseAlt(bool useAlt)
{
	this->m_useAlt = this->m_spriteAlt && useAlt;
}


////////////////////////////////////////////////////////////
void SpriteComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(getCurrent(), states);
}

} //namespace le