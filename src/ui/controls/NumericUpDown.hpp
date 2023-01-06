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

#ifndef LEVEL_EDITOR_NUMERIC_UP_DOWN_HPP
#define LEVEL_EDITOR_NUMERIC_UP_DOWN_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Button.hpp"
#include "InputControl.hpp"
#include "../components/SecondaryButtonComponent.hpp"
#include <concepts>
#include <regex>


namespace le
{
////////////////////////////////////////////////////////////
/// \brief Input control, accepting numeric input
///
////////////////////////////////////////////////////////////
template <typename T>
requires std::is_arithmetic_v<T>
class NumericUpDown : public InputControl
{
public:

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// Constructs an empty numeric input control
	/// 
	////////////////////////////////////////////////////////////
	NumericUpDown();

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// \param position            Position set to control
	/// \param buttonOffsets       sf::Vector3 representing button offsets. X is X offset of both buttons,
	///                            Y is Y offset of top button and Z is Y offset of bottom button
	/// \param size                Size of control
	/// \param buttonSize          Size of the buttons
	/// \param texture             Source texture
	/// \param spriteDefault       Sub-rectangle of the texture to assign to the default sprite
	/// \param spriteFocused       Sub-rectangle of the texture to assign to the focused sprite
	/// \param buttonSpriteDefault Sub-rectangle of the texture to assign to the default sprites of buttons
	/// \param buttonSpriteActive  Sub-rectangle of the texture to assign to the active sprites of buttons
	/// \param textTheme           Text theme
	/// \param inputStyle          Input style
	/// \param min                 Minimal accepted value
	/// \param max                 Maximum accepted value
	/// \param value               Value assigned to the numeric input
	/// \param diff                Common difference
	/// \param scrollTime          Amount of time required to scroll through the numeric input
	/// \param onValueUpdated      Event raised when the value changes
	/// \param onTextUpdated       Event raised when the input string changes
	/// \param enable              Enable this control
	///
	////////////////////////////////////////////////////////////
	NumericUpDown(const sf::Vector2f& position, const sf::Vector3f& buttonOffsets, const sf::Vector2f& size, 
	const sf::Vector2f& buttonSize, const sf::Texture& texture, const sf::IntRect& spriteDefault,
	const sf::IntRect& spriteFocused, const sf::IntRect& buttonSpriteDefault,
	const sf::IntRect& buttonSpriteActive, const TextTheme* textTheme, const InputTextStyle* inputStyle,
	T min, T max, T value, T diff, int scrollTime,
	Event1<NumericUpDown<T>, T> onValueUpdated = [](NumericUpDown<T>&, T) {}, 
	Event1<InputControl, sf::String> onTextUpdated = [](InputControl&, sf::String) {},
	bool enabled = true);

	////////////////////////////////////////////////////////////
	/// \brief Get value of the numeric
	///
	////////////////////////////////////////////////////////////
	T getValue() const;

	////////////////////////////////////////////////////////////
	/// \brief Set value of the numeric
	///
	/// \param value      Value to assign
	/// \param raiseEvent Raise OnValueChanged event
	/// 
	////////////////////////////////////////////////////////////
	void setValue(T value, bool raiseEvent = true);

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

protected:

	////////////////////////////////////////////////////////////
	/// \brief Validate the text
	/// 
	/// \param buffer Input string to assign
	///
	////////////////////////////////////////////////////////////
	InputControl::ValidationResult validateText(sf::String& buffer) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is pressed
	///        somewhere not within the control
	/// 
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	void onUnclicked(sf::Mouse::Button button, sf::Vector2f worldPos) override;

private:

	////////////////////////////////////////////////////////////
	/// \brief Update the text
	///
	////////////////////////////////////////////////////////////
	void updateText();

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	Button                      m_buttonUp;         //!< Leftmost button of the combo box
	Button                      m_buttonDown;       //!< Rightmost button of the combo box
	Event1<NumericUpDown<T>, T> m_onValueChanged;   //!< Event raised when value changes
	std::wregex                 m_firstExpression;  //!< Regular expression used to evaluate input
	std::wregex                 m_secondExpression; //!< Regular expression used to evaluate specifically float input
	sf::String					m_previous;         //!< Last valid input
	T                           m_min;              //!< Minimal accepted value
	T                           m_max;              //!< Maximum accepted value
	T                           m_value;            //!< Current value
	T                           m_diff;             //!< Common difference
	SecondaryButtonComponent    m_secondaryButtons; //!< Initialization logic of the additional numeric's buttons
};

using ByteNumeric = NumericUpDown<uint8_t>;
using ShortNumeric = NumericUpDown<uint16_t>;
using UintNumeric = NumericUpDown<uint32_t>;
using IntNumeric = NumericUpDown<int32_t>;
using FloatNumeric = NumericUpDown<float_t>;

} //namespace le


#include "NumericUpDown.inl"
#endif // LEVEL_EDITOR_NUMERIC_UP_DOWN_HPP