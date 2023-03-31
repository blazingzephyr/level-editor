// MIT License
// 
// Copyright (c) 2022 ZaBlazzingZephyr
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

#ifndef EDITOR_THEME_HPP
#define EDITOR_THEME_HPP

#include "control_theme.hpp"
#include "text_theme.hpp"
#include "input_control_theme.hpp"
#include <SFML/System/String.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <map>

struct EditorTheme
{
	sf::String								loading_screen;
	sf::String								icon;
	bool									toggle_animations;
	std::map<sf::String, sf::Shader*>		shaders;
	std::map<sf::String, sf::Font*>			fonts;
	std::map<sf::String, sf::Texture*>		textures;
	std::map<sf::String, sf::SoundBuffer*>	sounds;
	std::map<sf::String, sf::String>		music;
	std::map<sf::String, ControlTheme>		control_themes;
	std::map<sf::String, TextTheme>			text_themes;
	std::map<sf::String, InputControlTheme>	input_control_themes;
};

#endif