////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#include "scene.hpp"

using sf::Event;
using sf::IntRect;
using sf::RenderTarget;
using sf::RenderStates;
using sf::String;
using sf::Texture;
using sf::Vector2f;
using sf::Vector2u;
using std::find;
using std::vector;
using std::mutex;

Scene::Scene() :

	m_background(),
	m_scale(1.f),
	m_background_position(nullptr),
	m_toggle_animations(false),
	m_bg_movement_enabled(false),
	m_direction(false)
{
	m_music_offset = new sf::Int32();
}

sf::String Scene::getBackgroundKey()
{
	return m_background_key;
}

sf::String Scene::getMusic()
{
	return m_music;
}

void Scene::setMusic(sf::String music)
{
	m_music = music;
}

sf::Time Scene::getOffset()
{
	return sf::milliseconds(*m_music_offset);
}

sf::Vector2f Scene::getBackgroundPosition()
{
	return *m_background_position;
}

void Scene::updateScene(sf::Time offset)
{
	*m_music_offset = offset.asMilliseconds();
}

void Scene::realignScene(float alignment, vector<size_t> ignore_id)
{
	Vector2f offset = Vector2f(0, alignment);
	for (size_t i = 0; i < m_controls.size(); ++i)
	{
		if (find(ignore_id.begin(), ignore_id.end(), i) == ignore_id.end())
		{
			m_controls[i]->setPosition(m_control_positions[i] + offset);
		}
	}
}

void Scene::addControl(Control* control)
{
	m_controls.push_back(control);
	m_control_positions.push_back(control->getPosition());
}

void Scene::setBackgroundKey(String key)
{
	m_background_key = key;
}

void Scene::setBackground(Texture* texture)
{
	Vector2f background_size = Vector2f(texture->getSize());
	m_background.setTexture(*texture, true);

	m_scale = m_resolution.y / background_size.y;
	m_background.setScale(m_scale, m_scale);
	m_background.setPosition(0, 0);
}

void Scene::setBackground(Vector2u resolution, Texture* texture)
{
	m_resolution = resolution;
	setBackground(texture);
}

void Scene::setAnimations(bool toggle)
{
	m_toggle_animations = toggle;
	if (toggle && m_bg_movement_enabled)
	{
		m_background_position = new sf::Vector2f(m_min.x + (m_max.x - m_min.x) / 2, m_min.y + (m_max.y - m_min.y) / 2);
		m_background.setPosition(*m_background_position * m_scale);
	}
}

void Scene::setBackgroundMovement(bool enabled, Vector2f min, Vector2f max, Vector2f step)
{
	m_bg_movement_enabled = enabled;
	m_direction = true;
	m_min = min;
	m_max = max;
	m_step = step;
}

void Scene::onThemeUpdated()
{
	for (auto& control : m_controls)
	{
		control->onThemeUpdated();
	}
}

void Scene::onBackgroundUpdated()
{
	if (m_toggle_animations && m_bg_movement_enabled)
	{
		*m_background_position += (m_direction ? 1.f : -1.f) * m_step;

		if (m_background_position->x >= m_max.x || m_background_position->y >= m_max.y && m_direction)
		{
			m_direction = false;
		}
		else if (m_background_position->x <= m_min.x || m_background_position->y <= m_min.y && !m_direction)
		{
			m_direction = true;
		}

		m_background.setPosition(*m_background_position * m_scale);
	}
}

void Scene::onUpdated()
{
	for (size_t i = 0; i < m_controls.size(); ++i)
	{
		m_controls[i]->onUpdated();
	}
}

void Scene::onWindowEvent(Event window_event)
{
	bool valid_event = true;
	for (size_t i = 0; i < m_controls.size() && valid_event; ++i)
	{
		valid_event = m_controls[i]->onWindowEvent(window_event);
	}
}

void Scene::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_background);

	for (auto& control : m_controls)
	{
		target.draw(*control);
	}
}