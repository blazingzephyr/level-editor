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

#ifndef EDITOR_BUTTON_HPP
#define EDITOR_BUTTON_HPP

#include "text_control.hpp"
#include <functional>

class Button : public TextControl
{
public:
	Button();
	Button(sf::RenderWindow* window, sf::Vector2u intended_resolution, std::map<sf::String, sf::String>* strings, const ControlTheme* theme, SoundHandler* handler, const TextTheme* text_theme, sf::Vector2f position, sf::Vector2f size,
		const sf::IntRect& bg, const sf::IntRect& bg_active, sf::String text, const std::function<void()>& on_clicked, const std::function<void()>& on_hold,
		float min_y_position, bool visible = true, bool enabled = true);

	void					onClicked(sf::Event::MouseButtonEvent data) override;

private:
	std::function<void()>	m_on_clicked;
	std::function<void()>	m_on_hold;
	
	void					onHold() override;
	void					onMouseEntered(sf::Event::MouseMoveEvent data) override;
	void					onMouseLeft(sf::Event::MouseMoveEvent data) override;
	void					onReleased(sf::Event::MouseButtonEvent data) override;
};

#endif