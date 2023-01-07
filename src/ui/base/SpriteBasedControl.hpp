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

#ifndef LEVEL_EDITOR_SPRITE_BASED_CONTROL_HPP
#define LEVEL_EDITOR_SPRITE_BASED_CONTROL_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Control.hpp"
#include "../components/SpriteComponent.hpp"
#include "../styling/SpriteBasedControlTheme.hpp"
#include <SFML/Graphics/Shader.hpp>


namespace le
{
////////////////////////////////////////////////////////////
/// \brief Abstract class, representing a user control with SpriteComponent
///
////////////////////////////////////////////////////////////
class SpriteBasedControl : public Control 
{
public:

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// This constructor creates an invalid sprite-based control
	/// 
	////////////////////////////////////////////////////////////
	SpriteBasedControl();

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// \param position      Position set to control
	/// \param size          Size of control
	/// \param texture       Source texture
	/// \param spriteDefault Sub-rectangle of the texture to assign to the default sprite
	/// \param spriteAlt     Sub-rectangle of the texture to assign to the alternative sprite
	/// \param useAlt        Use alternative sprite instead of the default one
	/// \param enable        Enable this control
	/// 
	////////////////////////////////////////////////////////////
	SpriteBasedControl(const sf::Vector2f& position, const sf::Vector2f& size, const SpriteBasedControlTheme* theme,
	const sf::IntRect& spriteDefault, const sf::IntRect& spriteAlt, bool useAlt, bool enabled);

	////////////////////////////////////////////////////////////
	/// \brief Virtual destructor
	///
	////////////////////////////////////////////////////////////
	virtual ~SpriteBasedControl() {}

	////////////////////////////////////////////////////////////
	/// \brief Checks whether a point intersects the control
	///
	/// \param x X coord
	/// \param y Y coord
	/// 
	////////////////////////////////////////////////////////////
	bool contains(float x, float y) const override;

	////////////////////////////////////////////////////////////
	/// \brief Draw this sprite-based control to a render target.
	///
	/// \param target Render target to draw to
	/// \param states Current render states
	///
	////////////////////////////////////////////////////////////
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is pressed while hovering
	///
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onClicked(sf::Mouse::Button button, sf::Vector2f worldPos) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is released pressed while hovering
	///
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onReleasedControl(sf::Mouse::Button button, sf::Vector2f worldPos) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse cursor enters the area of the control
	///
	/// \param mouseMove Mouse move event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onEntered(sf::Vector2f worldPos) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse cursor leaves the area of the control
	///
	/// \param mouseMove Mouse move event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onLeft(sf::Vector2f worldPos) override;

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	SpriteComponent m_sprite;                //!< Sprite drawn in SpriteBasedControl::draw
	const SpriteBasedControlTheme* m_theme;  //!< Set of read-only parameters shared between controls
	const sf::Shader* m_shader;              //!< Shader applied to sprite in SpriteBasedControl::draw
};

} //namespace le


#endif // LEVEL_EDITOR_SPRITE_BASED_CONTROL_HPP