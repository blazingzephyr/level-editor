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

#ifndef EDITOR_COMBO_BOX_HPP
#define EDITOR_COMBO_BOX_HPP

#include "text_control.hpp"
#include "button.hpp"

class ComboBox : public TextControl
{
public:
	ComboBox();
	ComboBox(sf::RenderWindow* window, sf::Vector2u intended_resolution, std::map<sf::String, sf::String>* strings, const ControlTheme* theme, SoundHandler* handler, const TextTheme* text_theme, sf::Vector2f position, sf::Vector2f size,
		const sf::IntRect& bg, const sf::IntRect& bg_focused, float button_offset, sf::Vector2f button_size,
		const sf::IntRect& left_button_bg, const sf::IntRect& left_button_bg_focused, const sf::IntRect& right_button_bg, const sf::IntRect& right_button_bg_focused,
		std::vector<sf::String> items, size_t index, int scroll_time, std::function<void(size_t)> updated, float min_y_position, bool visible = true, bool enabled = true);

	sf::String					getItem() const;
	size_t						getIndex() const;
	void						forceSetIndex(size_t index);
	void						setEnabled(bool enabled);
	void						setIndex(size_t index);
	void						setItems(std::vector<sf::String> items, size_t new_index);
	void						setPosition(sf::Vector2f position) override;
	void onLanguageUpdated() override;
	void						onThemeUpdated() override;
	void						onUpdated() override;
	bool						onWindowEvent(sf::Event data) override;
	void						draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::function<void(size_t)>	m_value_updated;
	sf::Vector2f				m_button_size;
	float						m_button_offset;
	Button*						m_backwards_button;
	Button*						m_forward_button;
	std::vector<sf::String>		m_items;
	size_t						m_items_count;
	size_t						m_index;
	sf::String					m_item;
	sf::Clock					m_clock;
	int							m_scroll_time;
	int							m_elapsed_time;
	bool						m_requires_restarting;
	bool						m_holding;
	bool						m_holding_first_time;
	bool						m_extra_holding_check;

	void						moveIndex(sf::Int8 summand);
};

#endif