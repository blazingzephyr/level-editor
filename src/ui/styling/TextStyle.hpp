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

#ifndef LEVEL_EDITOR_TEXT_STYLE_HPP
#define LEVEL_EDITOR_TEXT_STYLE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <memory>
#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>


namespace le
{
////////////////////////////////////////////////////////////
/// \brief Standard layout class representing collection of styling options for sf::Text and le::TextComponent
///
////////////////////////////////////////////////////////////
struct TextStyle
{
	////////////////////////////////////////////////////////////
	/// \brief Horizontal alignment of sf::Text in relation to le::TextComponent
	///
	////////////////////////////////////////////////////////////
	enum struct HorizontalAlignment : sf::Int8
	{
		Left   = -1, //!< Leftmost of the le::TextComponent
		Center = 0,  //!< Center of the le::TextComponent
		Right  = 1   //!< Rightmost of the le::TextComponent
	};

	////////////////////////////////////////////////////////////
	/// \brief Vertical alignment of sf::Text in relation to le::TextComponent
	///
	////////////////////////////////////////////////////////////
	enum struct VerticalAlignment : sf::Int8
	{
		Top    = -1, //!< Top of the le::TextComponent
		Center = 0,  //!< Center of the le::TextComponent
		Bottom = 1   //!< Bottom of the le::TextComponent
	};

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	HorizontalAlignment       m_horizontal_align;     //!< Horizontal alignment
	VerticalAlignment         m_vertical_align;       //!< Vertical alignment
	const sf::Font*           m_font;                 //!< Shared pointer to a font used to display the string.
	unsigned int              m_characterSize;        //!< Base size of characters, in pixels
	float                     m_letterSpacingFactor;  //!< Spacing factor between letters
	float                     m_lineSpacingFactor;    //!< Spacing factor between lines
	sf::Uint32                m_style;                //!< Text style (see Style enum)
	sf::Color                 m_fillColor;            //!< Text fill color
	sf::Color                 m_outlineColor;         //!< Text outline color
	float                     m_outlineThickness;     //!< Thickness of the text's outline
};

} // namespace le

#endif // LEVEL_EDITOR_TEXT_STYLE_HPP