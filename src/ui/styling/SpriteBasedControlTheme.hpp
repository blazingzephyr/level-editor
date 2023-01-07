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

#ifndef LEVEL_EDITOR_SPRITE_BASED_CONTROL_THEME_HPP
#define LEVEL_EDITOR_SPRITE_BASED_CONTROL_THEME_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>
#include <optional>


namespace le
{
////////////////////////////////////////////////////////////
/// \brief Standard layout class representing a collection of shared
/// 	   data mainly intended for GUI customization
///
////////////////////////////////////////////////////////////
struct SpriteBasedControlTheme
{
	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	const sf::Shader*         m_hovering;         //!< Shader applied to a control when it is hovered
	const sf::Shader*         m_disabled;         //!< Shader applied to a control when it is disabled
	const sf::Shader*         m_disabledHovering; //!< Combination of the two other shaders
	const sf::Texture*        m_texture;          //!< Texture applied to all elements of a control
	std::optional<sf::String> m_enterSound;       //!< Sound played when mouse cursor enters a control
	std::optional<sf::String> m_clickSound;       //!< Sound played when a control is clicked
	std::optional<sf::String> m_releaseSound;     //!< Sound played when a control is released
};

} // namespace le

#endif // LEVEL_EDITOR_SPRITE_BASED_CONTROL_THEME_HPP