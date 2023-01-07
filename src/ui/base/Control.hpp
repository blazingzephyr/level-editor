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

#ifndef LEVEL_EDITOR_CONTROL_HPP
#define LEVEL_EDITOR_CONTROL_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Updatable.hpp"
#include <functional>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


namespace le
{
////////////////////////////////////////////////////////////
/// \brief Abstract class, representing a user control
///
////////////////////////////////////////////////////////////
class Control : public Updatable, public sf::Drawable, public sf::Transformable 
{
public:

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// This constructor creates an empty control
	/// 
	////////////////////////////////////////////////////////////
	Control();

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// \param position  Position set to control
	/// \param size      Size of control
	/// \param enable    Enable input validation
	/// 
	////////////////////////////////////////////////////////////
	Control(sf::Vector2f position, sf::Vector2f size, bool enabled = true);

    ////////////////////////////////////////////////////////////
    /// \brief Virtual destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual ~Control() {}

	////////////////////////////////////////////////////////////
	/// \brief Get the parent transform of the control
	/// 
	////////////////////////////////////////////////////////////
	const sf::Transform& getParentTransform() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the combined transform
	/// 
	////////////////////////////////////////////////////////////
	const sf::Transform& getCombinedTransform() const;

	////////////////////////////////////////////////////////////
	/// \brief Checks whether a point intersects the control
	///
	/// \param x X coord
	/// \param y Y coord
	/// 
	////////////////////////////////////////////////////////////
	virtual bool contains(float x, float y) const;

	////////////////////////////////////////////////////////////
	/// \brief Enables or disabled the control
	///
	/// \param enabled Enable
	/// 
	////////////////////////////////////////////////////////////
	virtual void setEnabled(bool enabled);

	////////////////////////////////////////////////////////////
	/// \brief Sets parent control.
	///
	/// \param parent Parent control
	/// 
	////////////////////////////////////////////////////////////
	void setParent(Control* parent);

	////////////////////////////////////////////////////////////
	/// \brief Updates the control within the application's main thread loop
	///
	////////////////////////////////////////////////////////////
	virtual void update() override;

	////////////////////////////////////////////////////////////
	/// \brief Process sf::Event within the control
	///
	/// \param window Respective window
	/// \param event  Event that was triggered
	///
	////////////////////////////////////////////////////////////
	virtual bool onWindowEvent(sf::RenderWindow& window, sf::Event event);

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
	virtual void onMouseWheelScrolled(sf::Event::MouseWheelScrollEvent mouseWheelScroll);

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is pressed
	///
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onMouseButtonPressed(sf::Mouse::Button button, sf::Vector2f worldPos);

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is released
	///
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onMouseButtonReleased(sf::Mouse::Button button, sf::Vector2f worldPos);

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse cursor moves
	///
	/// \param mouseMove Mouse move event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onMouseMoved(sf::Vector2f worldPos);

	////////////////////////////////////////////////////////////
	/// \brief Draw the control to a render target
	///
    /// This is a pure virtual function that has to be implemented
    /// by the derived class to define how the control should be
    /// drawn.
    ///
	/// \param target Render target to draw to
	/// \param states Current render states
	///
	////////////////////////////////////////////////////////////
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}

protected:

	////////////////////////////////////////////////////////////
	/// \brief Event continuously triggered when the mouse button is held
	///
	////////////////////////////////////////////////////////////
	virtual void onHold() {}

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse wheel is scrolled 
	///        while the control is being hovered
	/// 
	/// \param mouseWheelScroll Mouse wheel event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onScrolledControl(sf::Event::MouseWheelScrollEvent mouseWheelScroll) {}

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is pressed
	///
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onPressed(sf::Mouse::Button button, sf::Vector2f worldPos) {}

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is pressed
	///        while the control is being hovered
	/// 
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onClicked(sf::Mouse::Button button, sf::Vector2f worldPos) {}

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is pressed
	///        somewhere not within the control
	/// 
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onUnclicked(sf::Mouse::Button button, sf::Vector2f worldPos) {}

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is released
	/// 
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onReleased(sf::Mouse::Button button, sf::Vector2f worldPos) {}

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is released
	///        while the control is being hovered
	/// 
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onReleasedControl(sf::Mouse::Button button, sf::Vector2f worldPos) {}

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse cursor moves
	///        while the control is being hovered
	/// 
	/// \param mouseMove Mouse move event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onMovedControl(sf::Vector2f worldPos) {}

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse cursor enters the area of the control
	///
	/// \param mouseMove Mouse move event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onEntered(sf::Vector2f worldPos) {}

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse cursor leaves the area of the control
	///
	/// \param mouseMove Mouse move event parameters
	///
	////////////////////////////////////////////////////////////
	virtual void onLeft(sf::Vector2f worldPos) {}

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	sf::Window*    m_window;     //!< Last window this control has been draw on
	Control*       m_parent;     //!< Parent control
	bool           m_enabled;    //!< Enable input validation
	sf::Vector2f   m_size;       //!< Size of this control's bounds
	bool           m_hovering;   //!< Mouse hovering over this control
	bool           m_holding;    //!< Mouse is being held over this control
	bool           m_wasHolding; //!< Previous mouse holding state
};

} //namespace le


#endif // LEVEL_EDITOR_CONTROL_HPP