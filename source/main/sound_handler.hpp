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

#ifndef EDITOR_SOUND_HANDLER_HPP
#define EDITOR_SOUND_HANDLER_HPP

#include <SFML/Audio/Sound.hpp>
#include <SFML/System/String.hpp>
#include <map>

class SoundHandler
{
public:
	SoundHandler();
	SoundHandler(std::map<sf::String, sf::SoundBuffer*> sounds, float volume);

	void							setVolume(float volume);
	void							setSounds(std::map<sf::String, sf::SoundBuffer*> sounds);
	void							playSound(sf::String string);

private:
	std::map<sf::String, sf::Sound>	m_sounds;
};

#endif