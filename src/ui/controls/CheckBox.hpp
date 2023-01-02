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

#ifndef LEVEL_EDITOR_CHECK_BOX_HPP
#define LEVEL_EDITOR_CHECK_BOX_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "../interfaces/SpriteBasedControl.hpp"
#include "../../utility/Config.hpp"


namespace le
{
////////////////////////////////////////////////////////////
/// \brief Check box control
///
////////////////////////////////////////////////////////////
class CheckBox : public SpriteBasedControl
{
public:

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// Constructs an empty check box
	/// 
	////////////////////////////////////////////////////////////
	CheckBox();

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// \param position        Position set to check box
	/// \param size            Size of check box
	/// \param texture         Source texture
	/// \param spriteUnchecked Sub-rectangle of the texture to assign to the unchecked sprite
	/// \param spriteChecked   Sub-rectangle of the texture to assign to the checked sprite
	/// \param isChecked       Is check box checked
	/// \param enable          Enable this check box
	/// 
	////////////////////////////////////////////////////////////
	CheckBox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Texture& texture, const sf::IntRect& spriteUnchecked,
	const sf::IntRect& spriteChecked, Event1<CheckBox, bool> onCheckedChanged = Event1<CheckBox, bool>(), bool isChecked = false, bool enabled = true);

	////////////////////////////////////////////////////////////
	/// \brief Check state of the box
	/// 
	////////////////////////////////////////////////////////////
	bool getChecked() const;

	////////////////////////////////////////////////////////////
	/// \brief Sets check state of the box
	///
	/// \param checked    New check state
	/// \param raiseEvent Raise OnCheckedChanged event
	/// 
	////////////////////////////////////////////////////////////
	void setChecked(bool checked, bool raiseEvent = true);

private:

	////////////////////////////////////////////////////////////
	/// \brief Sets default or alternate sprite for use
	///
	/// \param swap Swap the sprite
	///
	////////////////////////////////////////////////////////////
	void setSprite(bool swap);

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse wheel is scrolled 
	///        while the check box is being hovered
	/// 
	/// \param mouseWheelScroll Mouse wheel event parameters
	///
	////////////////////////////////////////////////////////////
	void onScrolledControl(sf::Event::MouseWheelScrollEvent mouseWheelScroll) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is pressed
	///        while the check box is being hovered
	/// 
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	void onClicked(sf::Event::MouseButtonEvent mouseButton) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is released
	///        while the check box is being hovered
	/// 
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	void onReleasedControl(sf::Event::MouseButtonEvent mouseButton) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse cursor enters the area of the check box
	///
	/// \param mouseMove Mouse move event parameters
	///
	////////////////////////////////////////////////////////////
	void onEntered(sf::Event::MouseMoveEvent mouseMove) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse cursor leaves the area of the check box
	///
	/// \param mouseMove Mouse move event parameters
	///
	////////////////////////////////////////////////////////////
	void onLeft(sf::Event::MouseMoveEvent mouseMove) override;

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	Event1<CheckBox, bool> m_onCheckedChanged; //!< Event raised whenever m_isChecked changes
	bool                   m_isChecked;        //!< Check state of the box

};

} //namespace le


#endif // LEVEL_EDITOR_CHECK_BOX_HPP