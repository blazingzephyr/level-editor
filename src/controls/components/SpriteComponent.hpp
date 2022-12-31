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

#ifndef LEVEL_EDITOR_SPRITE_COMPONENT_HPP
#define LEVEL_EDITOR_SPRITE_COMPONENT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <memory>
#include <optional>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace le
{
////////////////////////////////////////////////////////////
/// \brief Sprite component representing a rich sf::Sprite wrapper
///
////////////////////////////////////////////////////////////
class SpriteComponent : public sf::Drawable, public sf::Transformable
{
public:

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// Constructs an empty SpriteComponent
	/// 
	////////////////////////////////////////////////////////////
	SpriteComponent();

	////////////////////////////////////////////////////////////
	/// \brief SpriteComponent without the alternative sprite
	///
    /// \param position  Position set to sprite
	/// \param texture   Source texture
	/// \param rectangle Sub-rectangle of the texture to assign to the sprite
	/// 
	////////////////////////////////////////////////////////////
	SpriteComponent(const sf::Vector2f& position, const sf::Texture& texture, const sf::IntRect& sprite);

	////////////////////////////////////////////////////////////
	/// \brief SpriteComponent with both sprites
	/// 
	/// \param position      Position set to sprite
	/// \param texture       Source texture
	/// \param spriteDefault Sub-rectangle of the texture to assign to the default sprite
	/// \param spriteAlt     Optional sub-rectangle of the texture to assign to the alternative sprite
	/// \param useAlt        Use alternative sprite instead of the default one
	/// 
	////////////////////////////////////////////////////////////
	SpriteComponent(const sf::Vector2f& position, const sf::Texture& texture, const sf::IntRect& spriteDefault, std::optional<const sf::IntRect> spriteAlt, bool useAlt = false);

	////////////////////////////////////////////////////////////
	/// \brief Switch between the default and the alternative sprites.
	///
	/// If the alternative sprite was not provided, SpriteComponent uses the default sprite regardless of the provided value.
	///
	/// \param useAlt true to use the alternative sprite, false to use the default one.
	///
	////////////////////////////////////////////////////////////
	void setUseAlt(bool useAlt);

	////////////////////////////////////////////////////////////
	/// \brief Draw this SpriteComponent to a render target.
	///
	/// \param target Render target to draw to
	/// \param states Current render states
	///
	////////////////////////////////////////////////////////////
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	const sf::Sprite*         m_spriteCurrent; //!< Pointer to the currenly used sprite. The object pointed by this shall not be modified.
	sf::Sprite                m_spriteDefault; //!< Default sprite
	std::optional<sf::Sprite> m_spriteAlt;     //!< Optional alternative sprite. Is initialized only if the corresponding sf::IntRect was provided
	bool                      m_useAlt;        //!< Indicates whether to use the alternative sprite or not
};

} //namespace le


#endif // LEVEL_EDITOR_SPRITE_COMPONENT_HPP