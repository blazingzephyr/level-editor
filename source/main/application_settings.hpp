////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
//
////////////////////////////////////////////////////////////

#ifndef EDITOR_APPLICATION_SETTINGS_HPP
#define EDITOR_APPLICATION_SETTINGS_HPP

#include <SFML/Config.hpp>
#include <SFML/System/String.hpp>

struct ApplicationSettings
{
	size_t				window_size;
	bool				full_screen;
	bool				enable_vsync;
	sf::Uint8			fps_limit;
	sf::String			language;
	sf::String			theme;
	sf::String			layout;
	float				music_volume;
	float				sound_volume;
	bool				use_pretty_printing;
	bool				use_tabs;
	sf::String			default_file_location;
};

#endif