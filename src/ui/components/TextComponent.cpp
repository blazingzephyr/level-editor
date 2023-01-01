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
#include "TextComponent.hpp"


namespace le
{
////////////////////////////////////////////////////////////
TextComponent::TextComponent() :
m_size(),
m_sprite(),
m_renderTexture(),
m_clearColor(),
m_text(),
m_textOffset(),
m_style(nullptr)
{
}


////////////////////////////////////////////////////////////
TextComponent::TextComponent(const sf::Vector2f& position, const sf::Vector2u& size, const TextStyle* style,
const sf::String& string, const sf::Vector2f& textOffset) :
m_size(size),
m_sprite(sf::Texture(), sf::IntRect(0, 0, size.x, size.y)),
m_renderTexture(),
m_clearColor(sf::Color::Transparent),
m_text(string, *style->m_font),
m_textOffset(textOffset)
{
	this->m_renderTexture.create(size.x, size.y);
	setStyle(style);
	setPosition(position);
}


////////////////////////////////////////////////////////////
void TextComponent::setString(const sf::String& string)
{
	this->m_text.setString(string);
	alignText();
}


////////////////////////////////////////////////////////////
void TextComponent::setTextOffset(const sf::Vector2f& offset)
{
	this->m_textOffset = offset;
	alignText();
}


////////////////////////////////////////////////////////////
void TextComponent::setClearColor(const sf::Color& color)
{
	this->m_clearColor = color;
	displayRenderTexture();
}


////////////////////////////////////////////////////////////
void TextComponent::setStyle(const TextStyle* style)
{
	this->m_style = style;
	applyStyleChanges();
}


////////////////////////////////////////////////////////////
void TextComponent::applyStyleChanges()
{
	if (this->m_style)
	{
		this->m_text.setFont(*this->m_style->m_font);
		this->m_text.setCharacterSize(this->m_style->m_characterSize);
		this->m_text.setLetterSpacing(this->m_style->m_letterSpacingFactor);
		this->m_text.setLineSpacing(this->m_style->m_lineSpacingFactor);
		this->m_text.setStyle(this->m_style->m_style);
		this->m_text.setFillColor(this->m_style->m_fillColor);
		this->m_text.setOutlineColor(this->m_style->m_outlineColor);
		this->m_text.setOutlineThickness(this->m_style->m_outlineThickness);
		alignText();
	}
}


////////////////////////////////////////////////////////////
void TextComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(this->m_sprite, states);
}


////////////////////////////////////////////////////////////
void TextComponent::alignText()
{
	sf::FloatRect bounds = this->m_text.getLocalBounds();
	sf::Vector2f origin = sf::Vector2f();
	sf::Vector2f position = sf::Vector2f();

	switch (this->m_style->m_horizontal_align)
	{
		case le::TextStyle::HorizontalAlignment::Center:
			origin.x = bounds.left + bounds.width * 0.5f;
			position.x = this->m_size.x * 0.5f;
			break;

		case le::TextStyle::HorizontalAlignment::Left:
			origin.x = bounds.left + bounds.width * 0.075f;
			position.x = this->m_size.x * 0.075f;
			break;

		case le::TextStyle::HorizontalAlignment::Right:
			origin.x = bounds.left + bounds.width * 0.925f;
			position.x = this->m_size.x * 0.925f;
			break;
	}

	switch (this->m_style->m_vertical_align)
	{
		case le::TextStyle::VerticalAlignment::Center:
			origin.y = bounds.top + bounds.height * 0.5f;
			position.y = this->m_size.y * 0.5f;
			break;

		case le::TextStyle::VerticalAlignment::Top:
			origin.y = bounds.top + bounds.height * 0.075f;
			position.y = this->m_size.y * 0.075f;
			break;

		case le::TextStyle::VerticalAlignment::Bottom:
			origin.y = bounds.top + bounds.height * 0.925f;
			position.y = this->m_size.y * 0.925f;
			break;
	}

	m_text.setOrigin(origin);
	m_text.setPosition(position + this->m_textOffset);
	displayRenderTexture();
}


////////////////////////////////////////////////////////////
void TextComponent::displayRenderTexture()
{
	this->m_renderTexture.clear(this->m_clearColor);
	this->m_renderTexture.draw(this->m_text);
	this->m_renderTexture.display();
	this->m_sprite.setTexture(this->m_renderTexture.getTexture());
}

} // namespace le