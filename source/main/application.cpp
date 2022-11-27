////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#include "application.hpp"
using namespace std::chrono;

using minijson::const_buffer_context;
using minijson::dispatcher;
using sf::Event;
using sf::RenderWindow;
using sf::String;
using sf::VideoMode;
using sf::Texture;
using sf::Uint8;
using std::exception;
using std::find;
using std::get;
using std::ofstream;
using std::make_tuple;
using std::map;
using std::thread;
using std::time;
using std::tuple;
using std::vector;
using std::filesystem::create_directory;
using std::filesystem::directory_iterator;
using std::filesystem::exists;
using std::filesystem::path;
using sf::Image;
using sf::Uint8;
using sf::Uint16;
using sf::Uint32;
using minijson::array_writer;
using minijson::object_writer;
using minijson::writer_configuration;
using namespace sf::Style;

Application::Application() :

	m_mutex(),
	m_loading_mutex(),
	m_terminated(false),
	m_loaded(false),
	m_control_mutex(),
	m_window_sizes(
		new tuple<Uint16, Uint16>[4]
		{
			make_tuple(640, 360),
			make_tuple(854, 480),
			make_tuple(1280, 720),
			make_tuple(1920, 1080)
		}
	),
	m_color_window_sizes(
		new tuple<Uint16, Uint16>[2]
		{
			make_tuple(500, 500),
			make_tuple(1000, 1000)
		}
	)
{
	loadFromFile("Settings.json", settings_dispatcher, m_settings);
	m_current_language = m_settings.language;
	m_current_theme = m_settings.theme;
	m_current_layout = m_settings.layout;

	m_music.setLoop(true);
	m_music.setVolume(m_settings.music_volume);

	auto window_size = m_window_sizes[m_settings.window_size > 3 ? 2 : m_settings.window_size];
	Uint16 width = m_settings.full_screen ? 1920 : get<0>(window_size);
	Uint16 height = m_settings.full_screen ? 1080 : get<1>(window_size);

	m_window = new RenderWindow(
		VideoMode(width, height, 64),
		"",
		m_settings.full_screen ? Fullscreen : Close
	);

	setVSyncOrFps();
	m_window->setActive(false);
	loadFromFile("Themes\\" + m_settings.theme + ".json", theme_dispatcher, m_theme);

	Texture loading = Texture();
	loading.loadFromFile(".\\Data\\Resources\\Textures\\" + m_theme.loading_screen);

	Vector2u size = loading.getSize();
	m_loading_sprite = Sprite(loading);
	m_loading_sprite.setScale(width / static_cast<float>(size.x), height / static_cast<float>(size.y));

	Image icon = Image();
	icon.loadFromFile(".\\Data\\Resources\\Textures\\" + m_theme.icon);

	Vector2u icon_size = icon.getSize();
	m_window->setIcon(icon_size.x, icon_size.y, icon.getPixelsPtr());

	thread renderThread = thread(&Application::renderThreadLoop, this);
	renderThread.detach();

	m_strings = new map<String, String>();
	m_layout = LayoutSettings();

	m_scene_loaded.type = Event::MouseMoved;
	m_scene_loaded.mouseMove.x = 0;
	m_scene_loaded.mouseMove.y = 0;

	m_button_released.type = Event::MouseButtonReleased;
	m_button_released.mouseMove.x = 0;
	m_button_released.mouseMove.y = 0;

	loadFromFile("Strings\\" + m_settings.language + ".json", strings_dispatcher, m_strings);
	m_window->setTitle(m_strings->operator[]("title"));

	m_sound_handler = new SoundHandler(m_theme.sounds, m_settings.sound_volume);

	loadFromFile("Layouts\\" + m_settings.layout + ".json", layout_dispatcher, *this, *m_sound_handler, m_settings, m_theme, *m_window, m_layout, m_strings);
	m_current_scene = m_layout.scenes[m_layout.starter_scene];
	m_music.openFromFile(m_theme.music[m_current_scene.getMusic()]);
	m_music.play();

	time_t now = time(0);
	tm* localtime = new tm();
	localtime_s(localtime, &now);

	char current_time[15];
	strftime(current_time, sizeof current_time, "%Y%m%d%H%M%S", localtime);

	InputControl* filename = dynamic_cast<InputControl*>(m_controls["filename"]);
	filename->setText(string(current_time) + ".json");

	m_loading_mutex.lock();
	m_loaded = true;
	m_loading_mutex.unlock();

	while (!m_terminated)
	{
		m_control_mutex.lock();
		m_current_scene.onUpdated();
		m_control_mutex.unlock();

		Event window_event = Event();
		while (m_window->pollEvent(window_event))
		{
			if (window_event.type == Event::Closed)
			{
				close();
			}
			else if (m_loaded && window_event.type == Event::Resized)
			{
				for (auto& scene : m_layout.scenes)
				{
					m_control_mutex.lock();
					scene.second.onWindowEvent(window_event);
					m_control_mutex.unlock();
				}
			}
			else if (m_loaded)
			{
				m_control_mutex.lock();
				m_current_scene.onWindowEvent(window_event);
				m_control_mutex.unlock();
			}
		}
	}
}

Control* Application::getControl(String key)
{
	return m_controls[key];
}

void Application::addControl(String key, Control* control)
{
	m_controls[key] = control;
}

void Application::loadScene(String scene, bool restart_music, bool play_from_start)
{
	m_current_scene.updateScene(m_music.getPlayingOffset());
	m_current_scene = m_layout.scenes[scene];
	m_current_scene.onUpdated();
	m_current_scene.onWindowEvent(m_scene_loaded);

	if (restart_music)
	{
		m_music.stop();
		m_music.openFromFile(m_theme.music[m_current_scene.getMusic()]);
		m_music.setPlayingOffset(play_from_start ? sf::Time() : m_current_scene.getOffset());
		m_music.setLoop(true);
		m_music.play();
	}
}

void Application::loadSettings(vector<String> arguments)
{
	tuple<String, String, String>* load_info = new tuple<String, String, String>[4]
	{
		make_tuple("Strings", arguments[2], m_settings.language),
		make_tuple("Themes", arguments[3], m_settings.theme),
		make_tuple("Layouts", arguments[5], m_settings.layout)
	};

	for (size_t i = 0; i < 4; i++)
	{
		auto& tuple = load_info[i];
		String combo = get<1>(tuple);
		ComboBox* combo_box = dynamic_cast<ComboBox*>(m_controls[combo]);

		if (combo_box)
		{
			string subdirectory = get<0>(load_info[i]);
			vector<String> items = vector<String>();

			for (const auto& entry : directory_iterator("Data\\Plugins\\" + subdirectory))
			{
				path path = entry.path();
				if (path.extension() == ".json")
				{
					string filename = path.filename().replace_extension().string();
					items.push_back(filename);
				}
			}

			auto it = find(items.begin(), items.end(), get<2>(tuple));
			combo_box->setItems(items, it == items.end() ? 0 : it - items.begin());
		}
	}

	ComboBox* window_size = dynamic_cast<ComboBox*>(m_controls[arguments[6]]);
	if (window_size)
	{
		size_t i = 0;
		bool found = false;

		for (; i < 4; i++)
		{
			auto& screen_size = m_window_sizes[i];
			if (screen_size == m_window_sizes[m_settings.window_size > 3 ? 2 : m_settings.window_size])
			{
				found = true;
				break;
			}
		}

		window_size->forceSetIndex(found ? i : 2);
	}

	CheckBox* fullscreen = dynamic_cast<CheckBox*>(m_controls[arguments[7]]);
	if (fullscreen)
	{
		fullscreen->forceSetChecked(m_settings.full_screen);
	}

	CheckBox* enable_vsync = dynamic_cast<CheckBox*>(m_controls[arguments[8]]);
	if (enable_vsync)
	{
		enable_vsync->forceSetChecked(m_settings.enable_vsync);
	}

	UintNumeric* fps_limit = dynamic_cast<UintNumeric*>(m_controls[arguments[9]]);
	if (fps_limit)
	{
		fps_limit->forceSetValue(m_settings.fps_limit);
	}

	FloatSlider* music_volume = dynamic_cast<FloatSlider*>(m_controls[arguments[13]]);
	if (music_volume)
	{
		music_volume->forceSetValue(m_settings.music_volume);
	}

	FloatSlider* sound_volume = dynamic_cast<FloatSlider*>(m_controls[arguments[14]]);
	if (sound_volume)
	{
		sound_volume->forceSetValue(m_settings.sound_volume);
	}

	CheckBox* pretty_printing = dynamic_cast<CheckBox*>(m_controls[arguments[15]]);
	if (pretty_printing)
	{
		pretty_printing->forceSetChecked(m_settings.use_pretty_printing);
	}

	CheckBox* use_tabs = dynamic_cast<CheckBox*>(m_controls[arguments[16]]);
	if (use_tabs)
	{
		use_tabs->forceSetChecked(m_settings.use_tabs);
	}

	InputControl* default_file_location = dynamic_cast<InputControl*>(m_controls[arguments[17]]);
	if (default_file_location)
	{
		default_file_location->setText(m_settings.default_file_location);
	}
}

void Application::updateIfDirty()
{
	m_loading_mutex.lock();
	m_loaded = false;
	m_loading_mutex.unlock();

	if (m_settings.theme != m_current_theme)
	{
		m_settings.theme = m_current_theme;
		m_settings_changed = true;

		loadFromFile("Themes\\" + m_settings.theme + ".json", theme_dispatcher, m_theme);
		m_sound_handler->setSounds(m_theme.sounds);

		Image icon = Image();
		icon.loadFromFile(".\\Data\\Resources\\Textures\\" + m_theme.icon);

		Vector2u icon_size = icon.getSize();
		m_window->setIcon(icon_size.x, icon_size.y, icon.getPixelsPtr());

		for (auto& scene_ref : m_layout.scenes)
		{
			Scene& scene = scene_ref.second;
			scene.onThemeUpdated();
			scene.setAnimations(m_theme.toggle_animations);
			scene.updateScene(sf::Time());
			scene.setBackground(m_theme.textures[scene.getBackgroundKey()]);
		}
	}

	if (m_settings.language != m_current_language)
	{ 
		m_settings.language = m_current_language;
		m_settings_changed = true;

		loadFromFile("Strings\\" + m_settings.language + ".json", strings_dispatcher, m_strings);
		m_window->setTitle(m_strings->operator[]("title"));

		for (auto& control : m_controls)
		{
			bool is_valid = control.second != nullptr && dynamic_cast<InputControl*>(control.second) == nullptr;
			if (is_valid)
			{
				control.second->onLanguageUpdated();
			}
		}
	}

	if (m_settings.layout != m_current_layout)
	{
		m_settings.layout = m_current_layout;
		m_settings_changed = true;
		loadFromFile("Layouts\\" + m_settings.layout + ".json", layout_dispatcher, *this, *m_sound_handler, m_settings, m_theme, *m_window, m_layout, m_strings);
	}

	m_loading_mutex.lock();
	m_loaded = true;
	m_loading_mutex.unlock();
}

void Application::setWindowSize(size_t index)
{
	auto& size_tuple = m_window_sizes[index];
	m_settings.window_size = index;
	m_settings_changed = true;

	if (!m_settings.full_screen)
	{
		float width = get<0>(size_tuple);
		float height = get<1>(size_tuple);
		m_window->setSize(Vector2u(width, height));

		Event size_event = Event();
		size_event.type = Event::Resized;
		size_event.size = Event::SizeEvent();
		size_event.size.width = width;
		size_event.size.height = height;

		for (auto& scene : m_layout.scenes)
		{
			scene.second.onWindowEvent(size_event);
		}

		m_current_scene.onWindowEvent(m_button_released);
		m_current_scene.onWindowEvent(size_event);
	}
}

void Application::setFullscreen(bool fullscreen)
{
	m_current_window_fullscreen = fullscreen;
	m_settings_changed = true;
}

void Application::setVsync(bool enable_vsync)
{
	m_settings.enable_vsync = enable_vsync;
	m_settings_changed = true;
	setVSyncOrFps();
}

void Application::setFramerateLimit(Uint8 fps_limit)
{
	m_settings.fps_limit = fps_limit;
	m_settings_changed = true;
	setVSyncOrFps();
}

void Application::setLanguage(sf::String control)
{
	ComboBox* combo_box = dynamic_cast<ComboBox*>(m_controls[control]);
	if (combo_box)
	{
		m_current_language = combo_box->getItem();
	}
}

void Application::setTheme(sf::String control)
{
	ComboBox* combo_box = dynamic_cast<ComboBox*>(m_controls[control]);
	if (combo_box)
	{
		m_current_theme = combo_box->getItem();
	}
}

void Application::setLayout(sf::String control)
{
	ComboBox* combo_box = dynamic_cast<ComboBox*>(m_controls[control]);
	if (combo_box)
	{
		m_current_layout = combo_box->getItem();
	}
}

void Application::setMusicVolume(float volume)
{
	m_settings.music_volume = volume;
	m_settings_changed = true;
	m_music.setVolume(volume);
}

void Application::setSoundVolume(float volume)
{
	m_settings.sound_volume = volume;
	m_settings_changed = true;
	m_sound_handler->setVolume(volume);
}

void Application::setPrettyPrinting(bool pretty_printing)
{
	m_settings.use_pretty_printing = pretty_printing;
	m_settings_changed = true;
}

void Application::setTabs(bool use_tabs)
{
	m_settings.use_tabs = use_tabs;
	m_settings_changed = true;
}

void Application::setDefaultFileLocation(String default_file_location)
{
	m_settings.default_file_location = default_file_location;
	m_settings_changed = true;
}

void Application::close()
{
	if (m_settings_changed)
	{
		ofstream file = ofstream("Data\\Plugins\\Settings.json");
		object_writer writer = object_writer(file, writer_configuration().pretty_printing(m_settings.use_pretty_printing).use_tabs(m_settings.use_tabs));
		
		writer.write("windowSize", m_settings.window_size);
		writer.write("isFullscreen", m_current_window_fullscreen);
		writer.write("enableVSync", m_settings.enable_vsync);
		writer.write("fpsLimit", m_settings.fps_limit);
		writer.write("language", toAnsi(m_settings.language));
		writer.write("theme", toAnsi(m_settings.theme));
		writer.write("layout", toAnsi(m_settings.layout));
		writer.write("musicVolume", m_settings.music_volume);
		writer.write("soundVolume", m_settings.sound_volume);
		writer.write("usePrettyPrinting", m_settings.use_pretty_printing);
		writer.write("useTabs", m_settings.use_tabs);
		writer.write("defaultFileLocation", toAnsi(m_settings.default_file_location));
		
		writer.close();
		file.close();
	}

	m_mutex.lock();
	m_terminated = true;
	m_mutex.unlock();
	m_window->close();
}

template<typename ...Handler, typename ...Target>
inline void Application::loadFromFile(String path, minijson::dispatcher<Handler...> dispatcher, Target&... target)
{
	std::string buffer = readFile(".\\Data\\Plugins\\" + path);
	const_buffer_context context = const_buffer_context(buffer.data(), buffer.length());
	dispatcher.run(context, target...);
}

#include <future>

void Application::renderThreadLoop()
{
	while (!m_terminated)
	{
		m_window->clear();

		bool loaded = false;
		m_loading_mutex.lock();
		loaded = m_loaded;
		m_loading_mutex.unlock();

		if (loaded)
		{
			m_current_scene.onBackgroundUpdated();
			m_control_mutex.lock();
			m_window->draw(m_current_scene);
			m_control_mutex.unlock();
		}
		else
		{
			m_window->draw(m_loading_sprite);
		}

		m_window->display();
	}
}

void Application::setVSyncOrFps()
{
	if (m_settings.enable_vsync)
	{
		m_window->setVerticalSyncEnabled(true);
	}
	else
	{
		m_window->setFramerateLimit(m_settings.fps_limit);
	}
}

void Application::saveJson()
{
	string directory = toAnsi(m_settings.default_file_location);
	string filename = getControlValue<InputControl, string>("filename");

	if (!exists(directory))
		create_directory(directory);

	string path = directory + "/" + filename;
	FILE* file = nullptr;
	fopen_s(&file, path.data(), "w");

	ofstream stream = ofstream(file);
	object_writer writer = object_writer(stream, writer_configuration().pretty_printing(m_settings.use_pretty_printing).use_tabs(m_settings.use_tabs));

	writer.write("#comment", "Level created by TenaciousKirikot's Level Editor v2.0 tool.");

	array_writer objects_writer = writer.nested_array("objects");
	object_writer level_definition_writer = objects_writer.nested_object();
	level_definition_writer.write("objclass", "LevelDefinition");

	object_writer level_definition_data_writer = level_definition_writer.nested_object("objdata");
	level_definition_data_writer.write("Name", getControlValue<InputControl, std::string>("name"));
	level_definition_data_writer.write("Description", getControlValue<InputControl, string>("description"));
	level_definition_data_writer.write("LevelNumber", getControlValue<UintNumeric, Uint32>("level_number"));
	level_definition_data_writer.write("Loot", getLevelModule("loot"));

	size_t music_type = getControlValue<ComboBox, size_t>("music_type");
	switch (music_type)
	{
		case 2:
			level_definition_data_writer.write("MusicType", "MiniGame_B");
			break;

		case 3:
			level_definition_data_writer.write("LoadDefaultMusic", false);

		case 1:
			level_definition_data_writer.write("MusicType", "MiniGame_A");
			break;
	}

	level_definition_data_writer.write("NormalPresentTable", getControlValue<InputControl, string>("normal_present_table"));
	level_definition_data_writer.write("ShinyPresentTable", getControlValue<InputControl, string>("shiny_present_table"));

	saveProperty(level_definition_data_writer, "outro", "VictoryModule", true, "VictoryOutro");
	saveProperty(level_definition_data_writer, "completion_achievement", "CompletionAchievement");
	saveProperty(level_definition_data_writer, "first_intro", "FirstIntroNarrative");
	saveProperty(level_definition_data_writer, "repeat_intro", "RepeatIntroNarrative");
	saveProperty(level_definition_data_writer, "first_outro", "FirstOutroNarrative");
	saveProperty(level_definition_data_writer, "repeat_outro", "RepeatOutroNarrative");

	level_definition_data_writer.write("ForceToWorldMap", getControlValue<CheckBox, bool>("force_world_map"));
	level_definition_data_writer.write("RepeatPlayForceToWorldMap", getControlValue<CheckBox, bool>("repeat_force_world_map"));
	level_definition_data_writer.write("ForceWarpTunnel", getControlValue<CheckBox, bool>("force_warp"));
	level_definition_data_writer.write("DisableRestart", getControlValue<CheckBox, bool>("disable_restart"));
	level_definition_data_writer.write("FirstRewardType", getControlValue<ComboBox, std::string>("first_reward_type"));
	level_definition_data_writer.write("FirstRewardParam", getControlValue<InputControl, std::string>("first_reward_param"));
	level_definition_data_writer.write("ReplayRewardType", getControlValue<ComboBox, std::string>("repeat_reward_type"));
	level_definition_data_writer.write("ReplayRewardParam", getControlValue<InputControl, std::string>("repeat_reward_param"));
	level_definition_data_writer.write("PlantLevel", getControlValue<UintNumeric, sf::Uint32>("plant_level"));
	level_definition_data_writer.write("ZombieLevel", getControlValue<UintNumeric, sf::Uint32>("zombie_level"));
	level_definition_data_writer.write("GridItemLevel", getControlValue<UintNumeric, sf::Uint32>("grid_item_level"));
	level_definition_data_writer.write("StartingSun", getControlValue<UintNumeric, Uint32>("starting_sun"));
	level_definition_data_writer.write("AddBonusStartingSun", getControlValue<CheckBox, bool>("add_bonus_starting_sun"));
	level_definition_data_writer.write("StageModule", "RTID(" + getControlValue<ComboBox, std::string>("stage") + "@LevelModules)");

	Table* game_features_table = dynamic_cast<Table*>(m_controls["game_features_list"]);
	vector<string> game_features = vector<string>();

	for (size_t i = 0; i < game_features_table->getCount(); i++)
	{
		InputControl* input_control = dynamic_cast<InputControl*>(game_features_table->getControlAt(i, 0));
		game_features.push_back(input_control->getText());
	}

	level_definition_data_writer.write_array("GameFeaturesToUnlock", game_features.begin(), game_features.end());
	saveProperty(level_definition_data_writer, "force_next_level", "ForceNextLevel");

	array_writer level_definition_data_modules_writer = level_definition_data_writer.nested_array("Modules");
	level_definition_data_modules_writer.write(getLevelModule("intro"));

	auto write_level_definition_module = [this, &level_definition_data_modules_writer](bool enable, string module_type, string end)
	{
		if (enable)
		{
			level_definition_data_modules_writer.write("RTID(" + module_type + "@" + end + ")");
		}
	};

	auto write_level_definition_module_checkbox = [this, &write_level_definition_module](string checkbox_name, string module_type, string end = "CurrentLevel")
	{
		bool enable = getControlValue<CheckBox, bool>(checkbox_name);
		write_level_definition_module(enable, module_type, end);
	};

	auto write_level_definition_module_table = [this, &write_level_definition_module](string table_name, string module_type, string end = "CurrentLevel")
	{
		bool enable = !isTableEmpty(table_name);
		write_level_definition_module(enable, module_type, end);
	};

	ComboBox* mowers = dynamic_cast<ComboBox*>(m_controls["lawnmowers"]);
	if (mowers->getIndex() > 0)
	{
		write_level_definition_module(true, mowers->getItem(), "LevelModules");
	}

	write_level_definition_module_checkbox("seed_bank", "SeedBank");
	write_level_definition_module_checkbox("conveyor_belt", "ConveyorBelt");
	write_level_definition_module_checkbox("gravestones", "Gravestones");
	write_level_definition_module_table("initial_plants_table", "InitialPlants");
	write_level_definition_module_table("initial_zombies_table", "InitialZombies");
	write_level_definition_module_table("initial_grid_items_table", "InitialGridItems");
	write_level_definition_module_table("initial_powertiles_list", "PowerTiles");
	write_level_definition_module_checkbox("sun_dropper", getControlValue<ComboBox, string>("sun_dropper_type") + "SunDropper", "LevelModules");
	write_level_definition_module_checkbox("last_stand", "LastStand");

	level_definition_data_modules_writer.write("RTID(ZombiesDeadWinCon@LevelModules)");
	level_definition_data_modules_writer.write("RTID(DefaultZombieWinCondition@LevelModules)");
	level_definition_data_modules_writer.write("RTID(NewWaves@CurrentLevel)");
	level_definition_data_modules_writer.close();

	level_definition_data_writer.close();
	level_definition_writer.close();

	auto write_module = [&, this](bool enable, string alias, string properties, function<void(object_writer&)> func)
	{
		if (enable)
		{
			auto aliases = { alias };
			object_writer writer = objects_writer.nested_object();
			writer.write("objclass", properties);
			writer.write_array("aliases", aliases.begin(), aliases.end());

			object_writer data_writer = writer.nested_object("objdata");
			func(data_writer);

			data_writer.close();
			writer.close();
		}
	};
	write_module(
		getControlValue<CheckBox, bool>("seed_bank"),
		"SeedBank",
		"SeedBankProperties",
		[this](object_writer& writer)
		{
			writer.write("SelectionMethod", getControlValue<ComboBox, string>("seed_selection_type"));
			writeTable("PresetPlantList", "preset_plants_list", writer, new const char* [2]{ "PlantType", "Level" });
		}
	);

	write_module(
		getControlValue<CheckBox, bool>("conveyor_belt"),
		"ConveyorBelt",
		"ConveyorSeedBankProperties",
		[this](object_writer& writer)
		{
			writer.write("ConveyorSpeed", getControlValue<UintNumeric, Uint32>("conveyor_speed"));
			writer.write("MaxPackets", getControlValue<UintNumeric, Uint32>("max_packets"));
			writeTable("InitialPlantList", "initial_plant_list", writer, new const char* [8]{ "MaxCount", "MaxCountCooldownSeconds", "MaxWeightFactor", "MinCount", "MinWeightFactor", "PlantType", "Weight", "ForceBoosted" });
			writeTable("DropDelayConditions", "drop_delay_conditions_table", writer, new const char* [2]{ "Delay", "MaxPackets" });
		}
	);

	write_module(
		getControlValue<CheckBox, bool>("gravestones"),
		"Gravestones",
		"GravestoneProperties",
		[this](object_writer& writer)
		{
			writer.write("GravestoneCount", getControlValue<UintNumeric, Uint32>("gravestone_count"));
			writer.write("SpawnColumnStart", getControlValue<UintNumeric, Uint32>("grave_spawn_column_start"));
			writer.write("SpawnColumnEnd", getControlValue<UintNumeric, Uint32>("grave_spawn_column_end"));
			writeTable("ForceSpawnData", "force_spawn_list", writer, new const char* [3]{ "GridX", "GridY", "TypeName" });
		}
	);

	write_module(
		!isTableEmpty("initial_plants_table"),
		"InitialPlants",
		"InitialPlantProperties",
		[this](object_writer& writer)
		{
			writeTable("InitialPlantPlacements", "initial_plants_table", writer, new const char* [4]{ "GridX", "GridY", "TypeName", "Condition" });
		}
	);

	write_module(
		!isTableEmpty("initial_zombies_table"),
		"InitialZombies",
		"InitialZombieProperties",
		[this](object_writer& writer)
		{
			writeTable("InitialZombiePlacements", "initial_zombies_table", writer, new const char* [4]{ "GridX", "GridY", "TypeName", "Condition" });
		}
	);

	write_module(
		!isTableEmpty("initial_grid_items_table"),
		"InitialPlants",
		"InitialPlantProperties",
		[this](object_writer& writer)
		{
			writeTable("InitialZombiePlacements", "initial_zombies_table", writer, new const char* [4]{ "GridX", "GridY", "TypeName", "Condition" });
		}
	);

	write_module(
		!isTableEmpty("initial_powertiles_list"),
		"PowerTiles",
		"PowerTileProperties",
		[this](object_writer& writer)
		{
			array_writer linked_tiles = writer.nested_array("LinkedTiles");
			Table* powertiles_table = dynamic_cast<Table*>(m_controls["initial_powertiles_list"]);

			for (size_t i = 0; i < powertiles_table->getCount(); i++)
			{
				object_writer inner_tile = linked_tiles.nested_object();
				ComboBox* group = dynamic_cast<ComboBox*>(powertiles_table->getControlAt(i, 0));
				UintNumeric* x = dynamic_cast<UintNumeric*>(powertiles_table->getControlAt(i, 1));
				UintNumeric* y = dynamic_cast<UintNumeric*>(powertiles_table->getControlAt(i, 2));
				FloatNumeric* propagation_delay = dynamic_cast<FloatNumeric*>(powertiles_table->getControlAt(i, 3));

				inner_tile.write("Group", toAnsi(group->getItem()));
				inner_tile.write("PropagationDelay", propagation_delay->getNumber());

				object_writer location = inner_tile.nested_object("Location");
				location.write("mX", x->getNumber());
				location.write("mY", y->getNumber());

				location.close();
				inner_tile.close();
			}

			linked_tiles.close();
		}
	);

	bool is_last_stand = getControlValue<CheckBox, bool>("last_stand");
	write_module(
		is_last_stand,
		"LastStand",
		"LastStandMinigameProperties",
		[this](object_writer& writer)
		{
			writer.write("StartingPlantfood", getControlValue<UintNumeric, Uint32>("starting_plantfood"));
			writer.write("StartingSun", getControlValue<UintNumeric, Uint32>("starting_laststand_sun"));
		}
	);

	write_module(
		true,
		"NewWaves",
		"WaveManagerModuleProperties",
		[&, this](object_writer& writer)
		{
			if (is_last_stand)
			{
				writer.write("ManualStartup", true);
			}

			writer.write("WaveManagerProps", "RTID(WaveManagerProps@CurrentLevel)");
		}
	);

	Table* table = dynamic_cast<Table*>(m_controls["waves"]);
	size_t waves_count = table->getCount();

	write_module(
		true,
		"WaveManagerProps",
		"WaveManagerProperties",
		[&, this](object_writer& writer)
		{
			writer.write("SupressFlagZombie", getControlValue<CheckBox, bool>("supress_flag_zombie"));
			writer.write("FlagWaveInterval", getControlValue<UintNumeric, Uint32>("flag_wave_interval"));
			writer.write("MinNextWaveHealthPercentage", getControlValue<FloatNumeric, float>("nwmihp"));
			writer.write("MaxNextWaveHealthPercentage", getControlValue<FloatNumeric, float>("nwmahp"));
			writer.write("WaveSpendingPoints", getControlValue<UintNumeric, Uint32>("wave_spending_points"));
			writer.write("WaveSpendingPointIncrement", getControlValue<UintNumeric, Uint32>("wave_spending_points_increment"));
			writer.write("WavesAlwaysRandomized", getControlValue<CheckBox, bool>("waves_always_randomized"));
			writer.write("LevelJam", getControlValue<ComboBox, string>("level_jam"));

			writer.write("WaveCount", waves_count);

			array_writer waves = writer.nested_array("Waves");
			for (size_t i = 0; i < waves_count; i++)
			{
				array_writer inner_waves = waves.nested_array();
				inner_waves.write("RTID(Wave" + to_string(i) + "@CurrentLevel)");
				inner_waves.close();
			}

			waves.close();
		}
	);

	for (size_t i = 0; i < waves_count; i++)
	{
		write_module(
			true,
			"Wave" + to_string(i),
			"SpawnZombiesJitteredWaveActionProps",
			[&, this](object_writer& writer)
			{
				UintNumeric* additional_plantfood = dynamic_cast<UintNumeric*>(table->getControlAt(i, 1));
				writer.write("AdditionalPlantfood", additional_plantfood->getNumber());

				array_writer array_writer = writer.nested_array("Zombies");
				Table* inner_table = dynamic_cast<Table*>(table->getControlAt(i, 0));

				for (size_t i = 0; i < inner_table->getCount(); i++)
				{
					InputControl* type = dynamic_cast<InputControl*>(inner_table->getControlAt(i, 0));
					IntNumeric* row_numeric = dynamic_cast<IntNumeric*>(inner_table->getControlAt(i, 1));
					int row = row_numeric->getNumber();

					object_writer object_writer = array_writer.nested_object();
					object_writer.write("Type", "RTID(" + type->getText().toAnsiString() + "@ZombieTypes)");

					if (row != -1)
					{
						object_writer.write("Row", row);
					}

					object_writer.close();
				}

				array_writer.close();
			}
		);
	}

	objects_writer.close();
	writer.write("version", 1);
	writer.close();
	stream.close();
}

inline std::string Application::getLevelModule(sf::String id)
{
	return "RTID(" + getControlValue<InputControl, std::string>(id) + "@LevelModules)";
}

inline void Application::saveProperty(minijson::object_writer& writer, sf::String id, const char* property_id, bool is_module, sf::String compare)
{
	std::string string = getControlValue<InputControl, std::string>(id);
	if (string != compare)
	{
		writer.write(property_id, is_module ? getLevelModule(id) : string);
	}
}

inline bool Application::isTableEmpty(sf::String id)
{
	Table* table = dynamic_cast<Table*>(getControl(id));
	return table->getCount() == 0;
}

inline void Application::writeTable(const char* field_name, sf::String id, minijson::object_writer& object_writer, const char** field_names)
{
	minijson::array_writer writer = object_writer.nested_array(field_name);
	Table* table = dynamic_cast<Table*>(getControl(id));
	table->writeToJson(writer, field_names);
}