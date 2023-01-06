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

#ifndef LEVEL_EDITOR_SECONDARY_BUTTON_COMPONENT_HPP
#define LEVEL_EDITOR_SECONDARY_BUTTON_COMPONENT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "../controls/Button.hpp"


namespace le
{
////////////////////////////////////////////////////////////
/// \brief Component for unifying additional buttons logic (used in ComboBox and NumericUpDown)
///
////////////////////////////////////////////////////////////
class SecondaryButtonComponent
{
public:

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Constructs an empty SecondaryButtonsComponent
	/// 
	////////////////////////////////////////////////////////////
	SecondaryButtonComponent();

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// \param first           The first button that should be initialized
	/// \param second          The second button that should be initialized
	/// \param firstButtonPos  Position set to the first button
	/// \param secondButtonPos Position set to the second button
	/// \param size            Size of a button
	/// \param texture         Source texture
	/// \param spriteDefault   Sub-rectangle of the texture to assign to the default sprite
	/// \param spriteActive    Sub-rectangle of the texture to assign to the active sprite
	/// \param textTheme       Text theme assigned to the button (Can be empty)
	/// \param enabled         Enable this button
	/// \param scrollTime      Amount of time required to scroll through the combo box
	/// \param onItemChanged   Event raised when a button is held
	/// 
	////////////////////////////////////////////////////////////
	SecondaryButtonComponent(Button* first, Button* second, const sf::Vector2f& firstButtonPos, const sf::Vector2f& secondButtonPos,
	const sf::Vector2f& size, const sf::Texture& texture, const sf::IntRect& spriteDefault,
	const sf::IntRect& spriteActive, const TextTheme* textTheme, bool enabled, int scrollTime, std::function<void(int8_t)> onHold);

	////////////////////////////////////////////////////////////
	/// \brief Event raised when a child button is pressed or held
	/// 
	/// \param summand 1 to move right, -1 to move left
	/// 
	////////////////////////////////////////////////////////////
	void onHoldButton(int8_t summand);

private:

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	std::function<void(int8_t)> m_onHold;     //!< Event raised when a button is held
	sf::Clock                   m_clock;      //!< Internal clock for validating holding
	bool                        m_restart;    //!< Determines if the clock should be restarted
	int                         m_elapsed;    //!< Elapsed time of the clock;
	int                         m_scrollTime; //!< Amount of time required to scroll through the items
};

} //namespace le


#endif // LEVEL_EDITOR_SECONDARY_BUTTON_COMPONENT_HPP