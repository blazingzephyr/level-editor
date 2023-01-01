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

#ifndef LEVEL_EDITOR_TEXT_BASED_CONTROL_HPP
#define LEVEL_EDITOR_TEXT_BASED_CONTROL_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SpriteBasedControl.hpp"
#include "../components/TextComponent.hpp"
#include "../styling/TextTheme.hpp"


namespace le
{
////////////////////////////////////////////////////////////
/// \brief Abstract class, representing a user control with TextComponent and SpriteComponent
///
////////////////////////////////////////////////////////////
class TextBasedControl : public SpriteBasedControl 
{
public:

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// This constructor creates an invalid text-based control
	/// 
	////////////////////////////////////////////////////////////
	TextBasedControl();

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// \param position      Position set to control
	/// \param textPosition  Position of the text component
	/// \param size          Size of control
	/// \param texture       Source texture
	/// \param spriteDefault Sub-rectangle of the texture to assign to the default sprite
	/// \param spriteAlt     Sub-rectangle of the texture to assign to the alternative sprite
	/// \param theme         Text theme
	/// \param string        String assigned to the text
	/// \param textOffset    Offset of the text towards the render texture
	/// \param useAlt        Use alternative sprite instead of the default one
	/// \param enable        Enable this control
	/// 
	////////////////////////////////////////////////////////////
	TextBasedControl(sf::Vector2f position, sf::Vector2f textPosition, sf::Vector2f size, const sf::Texture& texture, const sf::IntRect& spriteDefault,
		const sf::IntRect& spriteAlt, const TextTheme& textTheme, const sf::String& string = sf::String(),
		const sf::Vector2f& textOffset = sf::Vector2f(), bool useAlt = false, bool enabled = true);

	////////////////////////////////////////////////////////////
	/// \brief Virtual destructor
	///
	////////////////////////////////////////////////////////////
	virtual ~TextBasedControl() {}

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
	/// \brief Sets text style
	///
	/// \param forceDefault Skips validation and sets style to default
	///
	////////////////////////////////////////////////////////////
	void setTextStyle(bool forceDefault = false);

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is pressed
	///        while the control is being hovered
	/// 
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onClicked(sf::Event::MouseButtonEvent mouseButton) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is released pressed while hovering
	///
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onReleased(sf::Event::MouseButtonEvent mouseButton) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse cursor enters the area of the control
	///
	/// \param mouseMove Mouse move event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onEntered(sf::Event::MouseMoveEvent mouseMove) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse cursor leaves the area of the control
	///
	/// \param mouseMove Mouse move event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onLeft(sf::Event::MouseMoveEvent mouseMove) override;

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	TextComponent    m_text;  //!< Text drawn in TextBasedControl::draw
	const TextTheme& m_theme; //!< Collection of styles passed into m_text
};

} //namespace le


#endif // LEVEL_EDITOR_TEXT_BASED_CONTROL_HPP