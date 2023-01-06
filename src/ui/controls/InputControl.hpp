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

#ifndef LEVEL_EDITOR_INPUT_CONTROL_HPP
#define LEVEL_EDITOR_INPUT_CONTROL_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "../interfaces/TextBasedControl.hpp"
#include "../styling/InputTextStyle.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Clipboard.hpp>


namespace le
{
////////////////////////////////////////////////////////////
/// \brief Text input control
///
////////////////////////////////////////////////////////////
class InputControl : public TextBasedControl
{
public:

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// Constructs an empty text input control
	/// 
	////////////////////////////////////////////////////////////
	InputControl();

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// \param position      Position set to control
	/// \param size          Size of control
	/// \param texture       Source texture
	/// \param spriteDefault Sub-rectangle of the texture to assign to the default sprite
	/// \param spriteFocused Sub-rectangle of the texture to assign to the focused sprite
	/// \param textTheme     Text theme
	/// \param inputStyle    Input style
	/// \param string        String to assign to the text
	/// \param enable        Enable this control
	/// 
	////////////////////////////////////////////////////////////
	InputControl(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Texture& texture,
	const sf::IntRect& spriteDefault, const sf::IntRect& spriteFocused, const TextTheme* textTheme, 
	const InputTextStyle* inputStyle, Event1<InputControl, sf::String> onTextUpdated = [](InputControl&, sf::String) {},
	const sf::String& string = sf::String(), bool enabled = true);

	////////////////////////////////////////////////////////////
	/// \brief Get the inputs's string
	///
	/// The returned string is a sf::String, which can automatically
	/// be converted to standard string types. So, the following
	/// lines of code are all valid:
	/// \code
	/// sf::String   s1 = text.getString();
	/// std::string  s2 = text.getString();
	/// std::wstring s3 = text.getString();
	/// \endcode
	///
	/// \return Text's string
	///
	/// \see setString
	///
	////////////////////////////////////////////////////////////
	const sf::String& getText() const;

	////////////////////////////////////////////////////////////
	/// \brief Set the text's string
	///
	/// The \a string argument is a sf::String, which can
	/// automatically be constructed from standard string types.
	/// So, the following calls are all valid:
	/// \code
	/// text.setString("hello");
	/// text.setString(L"hello");
	/// text.setString(std::string("hello"));
	/// text.setString(std::wstring(L"hello"));
	/// \endcode
	/// A text's string is empty by default.
	///
	/// \param string     New string
	/// \param raiseEvent Raise OnTextUpdated event
	///
	/// \see getString
	///
	////////////////////////////////////////////////////////////
	void setString(const sf::String& string, bool raiseEvent = true);

	////////////////////////////////////////////////////////////
	/// \brief Set the cursor
	///
	/// \param index New cursor position
	///
	////////////////////////////////////////////////////////////
	void setCursor(size_t index);

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a character is entered
	///
	/// \param unicode UTF-32 Unicode value of the character
	///
	////////////////////////////////////////////////////////////
	void onTextEntered(sf::Uint32 unicode) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a key is pressed
	///
	/// \param key Key event parameters
	///
	////////////////////////////////////////////////////////////
	void onKeyPressed(sf::Event::KeyEvent key) override;

	////////////////////////////////////////////////////////////
	/// \brief Draw the input control to a render target
	///
	/// \param target Render target to draw to
	/// \param states Current render states
	///
	////////////////////////////////////////////////////////////
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:

	////////////////////////////////////////////////////////////
	/// \brief Value returned by validateText
	///
	////////////////////////////////////////////////////////////
	enum struct ValidationResult : int8_t
	{
		Invalid = -1,
		Static  = 0,
		Valid   = 1
	};

	////////////////////////////////////////////////////////////
	/// \brief Validate the text
	/// 
	/// \param buffer Input string to assign
	///
	////////////////////////////////////////////////////////////
	virtual ValidationResult validateText(sf::String& buffer);

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is pressed
	///        while the control is being hovered
	/// 
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	void onClicked(sf::Mouse::Button button, sf::Vector2f worldPos) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is pressed
	///        somewhere not within the control
	/// 
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	void onUnclicked(sf::Mouse::Button button, sf::Vector2f worldPos) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse cursor moves
	///        while the control is being hovered
	/// 
	/// \param mouseMove Mouse move event parameters
	///
	////////////////////////////////////////////////////////////
	void onMovedControl(sf::Vector2f worldPos) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse cursor enters the area of the control
	///
	/// \param mouseMove Mouse move event parameters
	///
	////////////////////////////////////////////////////////////
	void onEntered(sf::Vector2f worldPos) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse cursor leaves the area of the control
	///
	/// \param mouseMove Mouse move event parameters
	///
	////////////////////////////////////////////////////////////
	void onLeft(sf::Vector2f worldPos) override;

private:

	////////////////////////////////////////////////////////////
	/// \brief Move the cursor
	///
	/// \param condition         Move if true
	/// \param selectionPosition Index to move the cursor to if selected
	/// \param offset            Offset of the cursor to move to
	///
	////////////////////////////////////////////////////////////
	void updatePosition(bool condition, size_t selectionPosition, long long offset);

	////////////////////////////////////////////////////////////
	/// \brief Input symbols into the text
	///
	/// \param characters Characters to put into the ending of the text
	///
	////////////////////////////////////////////////////////////
	void inputText(sf::String characters);

	////////////////////////////////////////////////////////////
	/// \brief Erase symbols from the text
	///
	/// \param condition Erase the text if true
	/// \param last      Last selected symbol
	/// \param offset    Offset of the cursor to start erasing from
	///
	////////////////////////////////////////////////////////////
	void eraseText(bool condition, size_t last, size_t offset);

	////////////////////////////////////////////////////////////
	/// \brief Update the text
	///
	/// \param offset     Offset of the cursor
	/// \param buffer     New string to assign to the text
	/// \param raiseEvent Raise OnTextUpdated event
	///
	////////////////////////////////////////////////////////////
	void updateText(size_t offset, sf::String buffer, bool raiseEvent = true);

	////////////////////////////////////////////////////////////
	/// \brief Clear the selection
	///
	////////////////////////////////////////////////////////////
	void clearSelection();

	////////////////////////////////////////////////////////////
	/// \brief Get a character's position
	///
	/// \param index Index of the character
	/// 
	/// \return X position of the index-th character
	///
	////////////////////////////////////////////////////////////
	float characterPos(size_t index);

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	bool                             m_focused;         //!< Is input control focused
	const InputTextStyle*            m_inputStyle;      //!< Input style
	sf::String                       m_string;          //!< Input string
	size_t                           m_strLen;          //!< String length
	Event1<InputControl, sf::String> m_onTextUpdated;   //!< Event raised when input string changes
	bool                             m_selected;        //!< Is selected
	sf::RectangleShape               m_selection;       //!< Selection rectangle
	float                            m_selectionOffset; //!< Selection rectangle position
	std::pair<size_t, size_t>        m_selectionRange;  //!< Selection range
	sf::RectangleShape               m_cursor;          //!< Cursor rectangle
	size_t                           m_cursorPosition;  //!< Cursor position - index-th symbol
	bool                             m_overwrite;       //!< Determines whether to overwrite symbols
};

} //namespace le


#endif // LEVEL_EDITOR_INPUT_CONTROL_HPP