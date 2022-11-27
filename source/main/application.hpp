////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_APPLICATION_HPP
#define EDITOR_APPLICATION_HPP

#include "application_settings.hpp"
#include "scene.hpp"
#include "../themes/editor_theme.hpp"
#include "../utility/io.hpp"
#include "../utility/layout_settings.hpp"
#include <minijson/minijson_reader.hpp>
#include <minijson/minijson_writer.hpp>
#include <SFML/Audio/Music.hpp>
#include <filesystem>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

class Application
{
public:
	Application();

	Control*								getControl(sf::String key);
	void									addControl(sf::String key, Control* control);
	void									loadScene(sf::String scene, bool restart_music = true, bool play_from_start = false);
	void									loadSettings(std::vector<sf::String> arguments);
	void									updateIfDirty();
	void									setWindowSize(size_t index);
	void									setFullscreen(bool fullscreen);
	void									setVsync(bool enable_vsync);
	void									setFramerateLimit(sf::Uint8 fps_limit);
	void									setLanguage(sf::String control);
	void									setTheme(sf::String control);
	void									setLayout(sf::String control);

	void									setMusicVolume(float volume);
	void									setSoundVolume(float volume);
	void									setPrettyPrinting(bool pretty_printing);
	void									setTabs(bool use_tabs);
	void									setDefaultFileLocation(sf::String default_file_location);
	void									saveJson();
	void									close();

private:
	sf::RenderWindow*						m_window;
	ApplicationSettings						m_settings;
	std::map<sf::String, sf::String>*		m_strings;
	EditorTheme								m_theme;
	LayoutSettings							m_layout;
	std::map<sf::String, Control*>			m_controls;
	Scene									m_current_scene;
	sf::Music								m_music;
	SoundHandler*							m_sound_handler;
	sf::Event								m_scene_loaded;
	sf::Event								m_button_released;
	std::mutex								m_mutex;
	std::mutex								m_loading_mutex;
	bool									m_terminated;
	sf::Sprite								m_loading_sprite;
	bool									m_loaded;
	std::mutex								m_control_mutex;
	std::tuple<sf::Uint16, sf::Uint16>*		m_window_sizes;
	std::tuple<sf::Uint16, sf::Uint16>*		m_color_window_sizes;
	bool									m_current_window_fullscreen;
	sf::String								m_current_language;
	sf::String								m_current_theme;
	sf::String								m_current_layout;
	bool									m_settings_changed;

	template<typename ...Handler, typename ...Target>
	void loadFromFile(sf::String path, minijson::dispatcher<Handler...> dispatcher, Target&... target);
	void renderThreadLoop();
	void									setVSyncOrFps();

	template <typename T, typename U>
	U										getControlValue(sf::String id);
	std::string								getLevelModule(sf::String id);
	void									saveProperty(minijson::object_writer& writer, sf::String id, const char* property_id, bool is_module = false, sf::String compare = "");

	bool									isTableEmpty(sf::String id);
	void									writeTable(const char* field_name, sf::String id, minijson::object_writer& object_writer, const char** field_names);
};

#include "../utility/dispatchers.hpp"
#endif

template <typename T, typename U>
U Application::getControlValue(sf::String id)
{
	if constexpr (is_same_v<T, CheckBox>)
	{
		CheckBox* control = dynamic_cast<CheckBox*>(m_controls[id]);
		return control->getChecked();
	}
	else if constexpr (is_same_v<T, ComboBox>)
	{
		ComboBox* control = dynamic_cast<ComboBox*>(m_controls[id]);
		if constexpr (is_same_v<U, std::string>)
		{
			return control->getItem();
		}
		else if constexpr (is_same_v<U, size_t>)
		{
			return control->getIndex();
		}
	}
	else if constexpr (is_same_v<T, InputControl>)
	{
		InputControl* control = dynamic_cast<InputControl*>(m_controls[id]);
		return control->getText();
	}
	else if constexpr (is_same_v<T, FloatNumeric>)
	{
		FloatNumeric* control = dynamic_cast<FloatNumeric*>(m_controls[id]);
		return control->getNumber();
	}
	else if constexpr (is_same_v<T, UintNumeric>)
	{
		UintNumeric* control = dynamic_cast<UintNumeric*>(m_controls[id]);
		return control->getNumber();
	}
	else return U();
}