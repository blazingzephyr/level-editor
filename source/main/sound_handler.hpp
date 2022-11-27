////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

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