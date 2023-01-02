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

#ifndef LEVEL_EDITOR_BUTTON_HPP
#define LEVEL_EDITOR_BUTTON_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "../interfaces/TextBasedControl.hpp"
#include "../../utility/Config.hpp"


namespace le
{
////////////////////////////////////////////////////////////
/// \brief Clickable button control
///
////////////////////////////////////////////////////////////
class Button : public TextBasedControl
{
public:

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// Constructs an empty button
	/// 
	////////////////////////////////////////////////////////////
	Button();

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// \param position      Position set to button
	/// \param size          Size of button
	/// \param texture       Source texture
	/// \param spriteDefault Sub-rectangle of the texture to assign to the default sprite
	/// \param spriteActive  Sub-rectangle of the texture to assign to the active sprite
	/// \param textTheme     Text theme
	/// \param strings       List of strings
	/// \param string        String key
	/// \param onReleasedControl    Event raised when this button is released
	/// \param onHold        Event raised when this button is held
	/// \param enable        Enable this button
	/// 
	////////////////////////////////////////////////////////////
	Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Texture& texture, const sf::IntRect& spriteDefault,
	const sf::IntRect& spriteActive, const TextTheme* textTheme, const Strings* strings, const sf::String& string,
	Event0<Button> onReleasedControl = Event0<Button>(), Event0<Button> onHold = Event0<Button>(), bool enabled = true);

private:

	////////////////////////////////////////////////////////////
	/// \brief Event continuously triggered when the mouse button is held
	///
	////////////////////////////////////////////////////////////
	void onHold() override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is pressed
	///        while the button is being hovered
	/// 
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	void onClicked(sf::Event::MouseButtonEvent mouseButton) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is released
	///        while the button is being hovered
	/// 
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	void onReleasedControl(sf::Event::MouseButtonEvent mouseButton) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse cursor enters the area of the button
	///
	/// \param mouseMove Mouse move event parameters
	///
	////////////////////////////////////////////////////////////
	void onEntered(sf::Event::MouseMoveEvent mouseMove) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse cursor leaves the area of the button
	///
	/// \param mouseMove Mouse move event parameters
	///
	////////////////////////////////////////////////////////////
	void onLeft(sf::Event::MouseMoveEvent mouseMove) override;

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	Event0<Button> m_onReleased; //!< Event raised when this button is released
	Event0<Button> m_onHold;     //!< Event raised when this button is held
};

} //namespace le


#endif // LEVEL_EDITOR_BUTTON_HPP