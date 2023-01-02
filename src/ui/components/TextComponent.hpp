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

#ifndef LEVEL_EDITOR_TEXT_COMPONENT_HPP
#define LEVEL_EDITOR_TEXT_COMPONENT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "../styling/TextStyle.hpp"
#include <optional>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTexture.hpp>


namespace le
{
////////////////////////////////////////////////////////////
/// \brief Text component representing a rich sf::Text wrapper
///
////////////////////////////////////////////////////////////
class TextComponent : public sf::Drawable, public sf::Transformable
{
public:

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// This constructor creates an empty TextComponent
	///
	////////////////////////////////////////////////////////////
	TextComponent();

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// \param position   Position of the text component
	/// \param size       Size of the text component
	/// \param style      Style to use. Has to remain valid the entire lifetime of the text component
	/// \param string     String assigned to the text 
	/// \param textOffset Offset of the text towards the render texture
	///
	////////////////////////////////////////////////////////////
	TextComponent(const sf::Vector2f& position, const sf::Vector2u& size, const TextStyle* style,
	const sf::String& string = sf::String(), const sf::Vector2f& textOffset = sf::Vector2f());

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
    ///
    /// \param string New string
    ///
    ////////////////////////////////////////////////////////////
	virtual void setString(const sf::String& string);

	////////////////////////////////////////////////////////////
	/// \brief Change the offset of the text
	/// 
	/// \param string New offset
	///
	////////////////////////////////////////////////////////////
	void setTextOffset(const sf::Vector2f& offset);

	////////////////////////////////////////////////////////////
	/// \brief Set the render texture's clear color
	///
	/// \param color New clear color
	/// 
	////////////////////////////////////////////////////////////
	void setClearColor(const sf::Color& color);

	////////////////////////////////////////////////////////////
	/// \brief Set text style
	///
	/// \param style New style
	/// 
	////////////////////////////////////////////////////////////
	void setStyle(const TextStyle* style);

	////////////////////////////////////////////////////////////
	/// \brief Apply changes made to the style to the text
	///
	/// Text component stores a reference to a style that was passed in the constructor or setStyle.
	/// In order for this to work the reference has to remain valid.
	///
	////////////////////////////////////////////////////////////
	void applyStyleChanges();

	////////////////////////////////////////////////////////////
	/// \brief Draw this TextComponent to a render target
	///
	/// \param target Render target to draw to
	/// \param states Current render states
	///
	////////////////////////////////////////////////////////////
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:

	////////////////////////////////////////////////////////////
	/// \brief Align the text towards render texture
	///
	////////////////////////////////////////////////////////////
	void alignText();

	////////////////////////////////////////////////////////////
	/// \brief Display the render texture and update the sprite's texture
	///
	////////////////////////////////////////////////////////////
	void displayRenderTexture();

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	sf::Vector2u                       m_size;          //!< Size of this text component
	sf::Sprite                         m_sprite;        //!< Sprite drawn in draw(sf::RenderTarget& target, sf::RenderStates states)
	std::shared_ptr<sf::RenderTexture> m_renderTexture; //!< RenderTexture that is applied to m_sprite
	sf::Color                          m_clearColor;    //!< Color used to clear m_renderTexture
	sf::Text                           m_text;          //!< Text drawn to m_renderTexture
	sf::Vector2f                       m_textOffset;    //!< Offset of the text towards m_renderTexture
	const TextStyle*                   m_style;         //!< Text style
};

} //namespace le


#endif // LEVEL_EDITOR_TEXT_COMPONENT_HPP