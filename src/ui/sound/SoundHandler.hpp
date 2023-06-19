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

#ifndef LEVEL_EDITOR_SPRITE_BASED_CONTROL_HPP
#define LEVEL_EDITOR_SPRITE_BASED_CONTROL_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <map>
#include <SFML/Audio/Sound.hpp>
#include <SFML/System/String.hpp>


namespace le
{
////////////////////////////////////////////////////////////
/// \brief Abstract class, representing a user control with SpriteComponent
///
////////////////////////////////////////////////////////////
class SoundHandler 
{
public:

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// This constructor creates an empty SoundHandler
	/// 
	////////////////////////////////////////////////////////////
	SoundHandler();

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// \param position      Position set to control
	/// \param size          Size of control
	/// \param texture       Source texture
	/// \param spriteDefault Sub-rectangle of the texture to assign to the default sprite
	/// \param spriteAlt     Sub-rectangle of the texture to assign to the alternative sprite
	/// \param useAlt        Use alternative sprite instead of the default one
	/// \param enable        Enable this control
	/// 
	////////////////////////////////////////////////////////////
	SoundHandler();


	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	std::map<sf::String, sf::SoundBuffer*> m_soundBuffers;
	sf::Sound*                             m_source;

		//!< Sprite drawn in SpriteBasedControl::draw
};

} //namespace le


#endif // LEVEL_EDITOR_SPRITE_BASED_CONTROL_HPP