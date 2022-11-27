////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#include "sound_handler.hpp"

using sf::Sound;
using std::make_pair;

SoundHandler::SoundHandler()
{

}

SoundHandler::SoundHandler(std::map<sf::String, sf::SoundBuffer*> sounds, float volume)
{
	setSounds(sounds);
	setVolume(volume);
}

void SoundHandler::setVolume(float volume)
{
	for (auto& pair : m_sounds)
	{
		pair.second.setVolume(volume);
	}
}

void SoundHandler::setSounds(std::map<sf::String, sf::SoundBuffer*> sounds)
{
	m_sounds.clear();
	for (auto& pair : sounds)
	{
		m_sounds.emplace(make_pair(pair.first, sf::Sound(*pair.second)));
	}
}

void SoundHandler::playSound(sf::String string)
{
	try 
	{
		bool contains = m_sounds.contains(string);
		if (contains)
		{
			m_sounds[string].play();
		}
	}
	catch (std::exception&)
	{

	}
}