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

#ifndef EDITOR_SCENE_HPP
#define EDITOR_SCENE_HPP

#include "../controls/control.hpp"
#include "../controls/slider.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/String.hpp>
#include <SFML/OpenGL.hpp>
#include <map>
#include <mutex>
#include <thread>

class Scene : public sf::Drawable
{
public:
	Scene();

	sf::String							getBackgroundKey();
	sf::String							getMusic();
	sf::Time							getOffset();
	sf::Vector2f						getBackgroundPosition();
	void								addControl(Control* control);
	void								setBackgroundKey(sf::String key);
	void								setBackground(sf::Texture* texture);
	void								setBackground(sf::Vector2u resolution, sf::Texture* texture);
	void								setMusic(sf::String music);
	void								setAnimations(bool toggle);
	void								setBackgroundMovement(bool enabled, sf::Vector2f min, sf::Vector2f max, sf::Vector2f step);
	void								updateScene(sf::Time offset);
	void								realignScene(float alignment, std::vector<size_t> ignore_id);
	void								onThemeUpdated();
	void								onBackgroundUpdated();
	void								onUpdated();
	void								onWindowEvent(sf::Event window_event);
	void								draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
private:
	std::vector<Control*>				m_ignore_clipping_controls;
	std::vector<Control*>				m_controls;
	std::vector<sf::Vector2f>			m_control_positions;
	sf::Sprite							m_background;
	float								m_scale;
	bool								m_toggle_animations;
	bool								m_bg_movement_enabled;
	sf::Vector2f						m_min;
	sf::Vector2f						m_max;
	sf::Vector2f						m_step;
	bool								m_direction;
	sf::String							m_music;
	sf::Vector2f*						m_background_position;
	sf::Int32*							m_music_offset;
	sf::IntRect							m_clipping_rect;
	sf::String							m_background_key;
	sf::Vector2u						m_resolution;
};

#endif