////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

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