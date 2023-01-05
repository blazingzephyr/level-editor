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
#include "TextBasedControl.hpp"


namespace le
{
////////////////////////////////////////////////////////////
TextBasedControl::TextBasedControl() :
SpriteBasedControl::SpriteBasedControl(),
m_text (),
m_theme(new TextTheme())
{
}


////////////////////////////////////////////////////////////
TextBasedControl::TextBasedControl(const sf::Vector2f& position, const sf::Vector2f& textPosition, const sf::Vector2f& size, const sf::Texture& texture,
const sf::IntRect& spriteDefault, const sf::IntRect& spriteAlt, const TextTheme* textTheme, bool useAlt, bool enabled) :

SpriteBasedControl::SpriteBasedControl(position, size, texture, spriteDefault, spriteAlt, useAlt, enabled),
m_text(),
m_theme        (textTheme)
{
}


////////////////////////////////////////////////////////////
void TextBasedControl::applyTextChanges()
{
    LocalizableTextComponent* localizable = dynamic_cast<LocalizableTextComponent*>(&this->m_text);
    if (localizable)
    {
        localizable->applyTextChanges();
    }
}


////////////////////////////////////////////////////////////
void TextBasedControl::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    SpriteBasedControl::draw(target, states);
    states.transform *= getTransform();
    target.draw(this->m_text, states);
}


////////////////////////////////////////////////////////////
void TextBasedControl::setTextStyle(bool forceDefault)
{
    const TextStyle* style = (forceDefault)     ? this->m_theme->m_default  :
                             (!this->m_enabled) ? this->m_theme->m_disabled :
                             (this->m_holding)  ? this->m_theme->m_held     :
                             (this->m_hovering) ? this->m_theme->m_hovered  :
                                                  this->m_theme->m_default;

    this->m_text.setStyle(style);
}


////////////////////////////////////////////////////////////
void TextBasedControl::onClicked(sf::Mouse::Button button, sf::Vector2f worldPos)
{
    setTextStyle();
}


////////////////////////////////////////////////////////////
void TextBasedControl::onReleasedControl(sf::Mouse::Button button, sf::Vector2f worldPos)
{
    setTextStyle();
}


////////////////////////////////////////////////////////////
void TextBasedControl::onEntered(sf::Vector2f worldPos)
{
    setTextStyle();
}


////////////////////////////////////////////////////////////
void TextBasedControl::onLeft(sf::Vector2f worldPos)
{
    setTextStyle(true);
}

} //namespace le