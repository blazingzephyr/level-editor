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

#ifndef LEVEL_EDITOR_EVENT_RECEIVER_HPP
#define LEVEL_EDITOR_EVENT_RECEIVER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Window/Event.hpp>


namespace le
{
////////////////////////////////////////////////////////////
/// \brief Abstract class, representing an object that can receive *some* SFML window events
///
////////////////////////////////////////////////////////////
class EventReceiver
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Virtual destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual ~EventReceiver() {}

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a character is entered
	///
	/// \param unicode UTF-32 Unicode value of the character
	///
	////////////////////////////////////////////////////////////
	virtual void onTextEntered(sf::Uint32 unicode) {}

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a key is pressed
	///
	/// \param key Key event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onKeyPressed(sf::Event::KeyEvent key) {}

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a key is released
	///
	/// \param key Key event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onKeyReleased(sf::Event::KeyEvent key) {}

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse wheel is scrolled
	///
	/// \param mouseWheelScroll Mouse wheel event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onMouseWheelScrolled(sf::Event::MouseWheelScrollEvent mouseWheelScroll) {}

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is pressed
	///
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onMouseButtonPressed(sf::Event::MouseButtonEvent mouseButton) {}

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is released
	///
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onMouseButtonReleased(sf::Event::MouseButtonEvent mouseButton) {}

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse cursor moves
	///
	/// \param mouseMove Mouse move event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onMouseMoved(sf::Event::MouseMoveEvent mouseMove) {}
};

} //namespace le


#endif // LEVEL_EDITOR_EVENT_RECEIVER_HPP