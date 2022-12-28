#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class SpriteComponent : public sf::Drawable, public sf::Transformable
{
public:
	SpriteComponent(const sf::Vector2f& position, const sf::Texture* texture_pointer, const sf::IntRect& sprite);
	SpriteComponent(const sf::Vector2f& position, const sf::Texture* texture_pointer, const sf::IntRect& sprite_default, const sf::IntRect& sprite_alt = sf::IntRect(), bool use_alt = false);

	void				setUseAlt(bool use_alt);
	void				onTextureUpdated();
	void				draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	const sf::Texture*	m_texture_pointer;
	sf::Sprite*			m_sprite_current;
	sf::Sprite*			m_sprite_default;
	sf::Sprite*			m_sprite_alt;
	bool				m_has_alt;
	bool				m_use_alt;
};

#endif