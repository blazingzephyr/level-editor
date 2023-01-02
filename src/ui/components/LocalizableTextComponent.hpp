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

#ifndef LEVEL_EDITOR_LOCALIZABLE_TEXT_COMPONENT_HPP
#define LEVEL_EDITOR_LOCALIZABLE_TEXT_COMPONENT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "TextComponent.hpp"
#include "../../utility/Config.hpp"


namespace le
{
////////////////////////////////////////////////////////////
/// \brief Text component, which can be localized
///
////////////////////////////////////////////////////////////
class LocalizableTextComponent : public TextComponent
{
public:

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// This constructor creates an invalid LocalizableTextComponent
	///
	////////////////////////////////////////////////////////////
	LocalizableTextComponent();

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// \param position   Position of the text component
	/// \param size       Size of the text component
	/// \param style      Style to use. Has to remain valid the entire lifetime of the text component.
	/// \param strings    List of strings 
	/// \param string     Key of string assigned to the text
	/// \param textOffset Offset of the text towards the render texture
	///
	////////////////////////////////////////////////////////////
	LocalizableTextComponent(const sf::Vector2f& position, const sf::Vector2u& size, const TextStyle* style,
	const Strings& strings, const sf::String& string, const sf::Vector2f& textOffset = sf::Vector2f());

	////////////////////////////////////////////////////////////
	/// \brief Copy constructor
	///
	////////////////////////////////////////////////////////////
	LocalizableTextComponent(const LocalizableTextComponent&);

	////////////////////////////////////////////////////////////
	/// \brief Set the text's string
	///
    /// \param string Key of string assigned to the text
	/// 
	////////////////////////////////////////////////////////////
	void setString(const sf::String& string) override;

	////////////////////////////////////////////////////////////
	/// \brief Apply changes made to the text
	///
	/// Text component stores a reference to the strings that were passed in the constructor.
	/// In order for this to work the reference has to remain valid.
	///
	////////////////////////////////////////////////////////////
	void applyTextChanges();

private:

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	sf::String     m_string;  //!< String key
	const Strings& m_strings; //!< Reference to the strings
};

} //namespace le


#endif // LEVEL_EDITOR_LOCALIZABLE_TEXT_COMPONENT_HPP