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

#include "label.hpp"

using sf::IntRect;
using sf::RenderStates;
using sf::RenderTarget;
using sf::RenderWindow;
using sf::String;
using sf::Vector2f;

Label::Label() :

	TextControl::TextControl()
{

}

Label::Label(RenderWindow* window, sf::Vector2u intended_resolution, std::map<String, String>* strings, const ControlTheme* theme, SoundHandler* handler, const TextTheme* text_theme,
	Vector2f position, Vector2f size, String text, float rotation_angle, bool enabled) :

	TextControl::TextControl(window, intended_resolution, strings, theme, handler, text_theme, 
		position, size, IntRect(0, 0, 0, 0), IntRect(0, 0, 0, 0), text, -1, true, enabled)
{
	m_text.setRotation(rotation_angle);
}

void Label::draw(RenderTarget& target, RenderStates states) const
{
	Control::draw(target, states);
	target.draw(m_text, states);
}