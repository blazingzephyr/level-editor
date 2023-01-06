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

#ifndef LEVEL_EDITOR_COMBOBOX_HPP
#define LEVEL_EDITOR_COMBOBOX_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Button.hpp"
#include <SFML/System/Clock.hpp>


namespace le
{
////////////////////////////////////////////////////////////
/// \brief Combo box control
///
////////////////////////////////////////////////////////////
using Items = std::vector<sf::String>;
class ComboBox : public Control
{
public:

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// Constructs an empty combo box
	/// 
	////////////////////////////////////////////////////////////
	ComboBox();

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// \param position      Position set to button
	/// \param size          Size of combo box area
	/// \param buttonSize    Size of button
	/// \param texture       Source texture
	/// \param spriteDefault Sub-rectangle of the texture to assign to the default sprite
	/// \param spriteActive  Sub-rectangle of the texture to assign to the active sprite
	/// \param style         Style, used for the text
	/// \param theme         Text theme assigned to the button (Can be empty)
	/// \param strings       List of strings
	/// \param items         Combo box items
	/// \param index         Selected item index
	/// \param scrollTime    Amount of time required to scroll through the combo box
	/// \param onItemChanged Event raised when another item is selected
	/// \param enabled       Enable this button
	/// 
	////////////////////////////////////////////////////////////
	ComboBox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& buttonSize, const sf::Texture& texture,
	const sf::IntRect& spriteDefault, const sf::IntRect& spriteActive, const TextStyle* style, const TextTheme* theme,
	const Strings* strings, const Items& items, size_t index, int scrollTime,
	Event1<ComboBox, size_t> onItemChanged = [](ComboBox&, size_t) {}, bool enabled = true);

	////////////////////////////////////////////////////////////
	/// \brief Selected item
	/// 
	////////////////////////////////////////////////////////////
	sf::String getItem() const;

	////////////////////////////////////////////////////////////
	/// \brief Index of the selected item
	/// 
	////////////////////////////////////////////////////////////
	bool getIndex() const;

	////////////////////////////////////////////////////////////
	/// \brief Sets items
	///
	/// \param items      List of items to assign to this combo box
	/// \param newIndex   New index
	/// \param raiseEvent Raise OnCheckedChanged event
	/// 
	////////////////////////////////////////////////////////////
	void setItems(Items items, size_t newIndex, bool raiseEvent);

	////////////////////////////////////////////////////////////
	/// \brief Sets index
	///
	/// \param index      New index
	/// \param raiseEvent Raise OnCheckedChanged event
	/// 
	////////////////////////////////////////////////////////////
	void setIndex(size_t index, bool raiseEvent = true);

	////////////////////////////////////////////////////////////
	/// \brief Enables or disabled the combo box
	///
	/// \param enabled Enable
	/// 
	////////////////////////////////////////////////////////////
	void setEnabled(bool enabled) override;

	////////////////////////////////////////////////////////////
	/// \brief Updates the control within the application's main thread loop
	///
	////////////////////////////////////////////////////////////
	void update() override;

	////////////////////////////////////////////////////////////
	/// \brief Process sf::Event within the control
	///
	/// \param window Respective window
	/// \param event  Event that was triggered
	///
	////////////////////////////////////////////////////////////
	bool onWindowEvent(sf::RenderWindow& window, sf::Event event) override;

	////////////////////////////////////////////////////////////
	/// \brief Draw the control to a render target
	///
	/// \param target Render target to draw to
	/// \param states Current render states
	///
	////////////////////////////////////////////////////////////
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	////////////////////////////////////////////////////////////
	/// \brief Event raised when a child button is released
	///
	/// \param summand 1 to move right, -1 to move left
	/// 
	////////////////////////////////////////////////////////////
	void onReleasedButton(uint8_t summand);

	////////////////////////////////////////////////////////////
	/// \brief Event raised when a child button is held
	/// 
	/// \param summand 1 to move right, -1 to move left
	/// 
	////////////////////////////////////////////////////////////
	void onHoldButton(uint8_t summand);

	////////////////////////////////////////////////////////////
	/// \brief Moves index left or right
	/// 
	/// \param summand 1 to move right, -1 to move left
	///
	////////////////////////////////////////////////////////////
	void moveIndex(int8_t summand);

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	LocalizableTextComponent m_text;          //!< Text component
	Event1<ComboBox, size_t> m_onItemChanged; //!< Event raised when another item is selected
	Button                   m_buttonLeft;    //!< Leftmost button of the combo box
	Button                   m_buttonRight;   //!< Rightmost button of the combo box
	Items                    m_items;         //!< Combo box items
	sf::String               m_item;          //!< Selected item of the combo box
	size_t                   m_index;         //!< Index of the selected item
	sf::Clock                m_clock;         //!< Internal clock for validating holding
	bool                     m_restart;       //!< Determines if the clock should be restarted
	int                      m_elapsed;       //!< Elapsed time of the clock;
	int                      m_scrollTime;    //!< Amount of time required to scroll through the items
	bool                     m_holdingButton; //!< Determines if a button was held
};

} //namespace le


#endif // LEVEL_EDITOR_COMBOBOX_HPP