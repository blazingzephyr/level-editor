#include "sprite_component.hpp"

const sf::IntRect& Empty = sf::IntRect();

SpriteComponent::SpriteComponent(const sf::Vector2f& position, const sf::Texture* texture_pointer, const sf::IntRect& sprite) :
	
	SpriteComponent(position, texture_pointer, sprite, Empty, false)
{

}

SpriteComponent::SpriteComponent(const sf::Vector2f& position, const sf::Texture* texture_pointer, const sf::IntRect& sprite_default, const sf::IntRect& sprite_alt, bool use_alt) :

	m_texture_pointer(texture_pointer),
	m_sprite_default(new sf::Sprite(*texture_pointer, sprite_default)),
	m_sprite_alt(sprite_alt == Empty ? nullptr : new sf::Sprite(*texture_pointer, sprite_alt)),
	m_has_alt(sprite_alt != Empty)
{
	onTextureUpdated();
	setPosition(position);
	setUseAlt(use_alt);

	this->m_sprite_default->setTextureRect(sprite_default);

	if (this->m_has_alt)
	{
		this->m_sprite_alt->setTextureRect(sprite_alt);
	}
}

void SpriteComponent::setUseAlt(bool use_alt)
{
	this->m_use_alt = this->m_has_alt && use_alt;
	this->m_sprite_current = this->m_has_alt && use_alt ? this->m_sprite_alt : this->m_sprite_default;
}

void SpriteComponent::onTextureUpdated()
{
	this->m_sprite_default->setTexture(*this->m_texture_pointer, false);

	if (this->m_has_alt)
	{
		this->m_sprite_alt->setTexture(*this->m_texture_pointer, false);
	}
}

void SpriteComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(*this->m_sprite_current, states);
}