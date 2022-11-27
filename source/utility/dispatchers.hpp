////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_DISPATCHERS_HPP
#define EDITOR_DISPATCHERS_HPP

#include "control_constructor.hpp"
#include "io.hpp"
#include "../controls/button.hpp"
#include "../controls/check_box.hpp"
#include "../controls/input_control.hpp"
#include "../controls/numeric_up_down.hpp"
#include "../main/sound_handler.hpp"
#include "../utility/layout_settings.hpp"
#include "../utility/construct_control.hpp"
#include "../utility/control_constructor.hpp"
#include <minijson/minijson_reader.hpp>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

const minijson::dispatcher settings_dispatcher
{
	minijson::handlers::handler("windowSize",				[](ApplicationSettings& settings, minijson::value v) { v.to(settings.window_size); }),
	minijson::handlers::handler("isFullscreen",				[](ApplicationSettings& settings, minijson::value v) { v.to(settings.full_screen); }),
	minijson::handlers::handler("enableVSync",				[](ApplicationSettings& settings, minijson::value v) { v.to(settings.enable_vsync); }),
	minijson::handlers::handler("fpsLimit",					[](ApplicationSettings& settings, minijson::value v) { v.to(settings.fps_limit); }),
	minijson::handlers::handler("language",					[](ApplicationSettings& settings, minijson::value v) { settings.language = toWide(v.raw()); }),
	minijson::handlers::handler("theme",					[](ApplicationSettings& settings, minijson::value v) { settings.theme = toWide(v.raw()); }),
	minijson::handlers::handler("layout",					[](ApplicationSettings& settings, minijson::value v) { settings.layout = toWide(v.raw()); }),
	minijson::handlers::handler("musicVolume",				[](ApplicationSettings& settings, minijson::value v) { v.to(settings.music_volume); }),
	minijson::handlers::handler("soundVolume",				[](ApplicationSettings& settings, minijson::value v) { v.to(settings.sound_volume); }),
	minijson::handlers::handler("usePrettyPrinting",		[](ApplicationSettings& settings, minijson::value v) { v.to(settings.use_pretty_printing); }),
	minijson::handlers::handler("useTabs",					[](ApplicationSettings& settings, minijson::value v) { v.to(settings.use_tabs); }),
	minijson::handlers::handler("defaultFileLocation",		[](ApplicationSettings& settings, minijson::value v) { settings.default_file_location = toWide(v.raw()); }),
	minijson::handlers::ignore_any_handler {}
};

const minijson::dispatcher strings_dispatcher
{
	minijson::handlers::any_handler(
		[](std::map<sf::String, sf::String>* dictionary, std::string_view name, minijson::value v)
		{
			sf::String key = toWide(name);
			dictionary->operator[](key) = toWide(v.raw());
			return true;
		}
	)
};

const minijson::dispatcher theme_dispatcher
{
	minijson::handlers::handler(
		"loadingScreen",
		[](EditorTheme& theme, minijson::value v)
		{
			theme.loading_screen = toWide(v.raw());
		}
	),

	minijson::handlers::handler(
		"icon",
		[](EditorTheme& theme, minijson::value v)
		{
			theme.icon = toWide(v.raw());
		}
	),

	minijson::handlers::handler(
		"toggleAnimations",
		[](EditorTheme& theme, minijson::value v)
		{
			v.to(theme.toggle_animations);
		}
	),
	
	minijson::handlers::handler(
		"shaders",
		[](EditorTheme& theme, minijson::value, auto& context)
		{
			parse_object(context, [&](std::string_view name, minijson::value, auto& inner_context)
				{
					sf::String key = toWide(name);
					theme.shaders[key] = new sf::Shader();
					shader_dispatcher.run(inner_context, theme.shaders[key]);
				}
			);
		}
	),

	minijson::handlers::handler(
		"fonts",
		[](EditorTheme& theme, minijson::value, auto& context)
		{
			parse_object(context, [&](std::string_view name, minijson::value v, auto& inner_context)
				{
					sf::String key = toWide(name);
					theme.fonts[key] = new sf::Font();
					theme.fonts[key]->loadFromFile("Data\\Resources\\Fonts\\" + std::string(v.raw()));
				}
			);
		}
	),

	minijson::handlers::handler(
		"textures",
		[](EditorTheme& theme, minijson::value, auto& context)
		{
			parse_object(context, [&](std::string_view name, minijson::value v, auto& inner_context)
				{
					sf::String key = toWide(name);
					theme.textures[key] = new sf::Texture();
					theme.textures[key]->loadFromFile("Data\\Resources\\Textures\\" + std::string(v.raw()));
				}
			);
		}
	),

	minijson::handlers::handler(
		"sounds",
		[](EditorTheme& theme, minijson::value, auto& context)
		{
			parse_object(context, [&](std::string_view name, minijson::value v, auto& inner_context)
				{
					sf::String key = toWide(name);
					theme.sounds[key] = new sf::SoundBuffer();
					theme.sounds[key]->loadFromFile("Data\\Resources\\Sounds\\" + std::string(v.raw()));
				}
			);
		}
	),

	minijson::handlers::handler(
		"music",
		[](EditorTheme& theme, minijson::value, auto& context)
		{
			parse_object(context, [&](std::string_view name, minijson::value v, auto& inner_context)
				{
					sf::String key = toWide(name);
					theme.music[key] = "Data\\Resources\\Music\\" + std::string(v.raw());
				}
			);
		}
	),

	minijson::handlers::handler(
		"controlThemes",
		[](EditorTheme& theme, minijson::value, auto& context)
		{
			parse_object(context, [&](std::string_view name, minijson::value, auto& inner_context)
				{
					sf::String key = toWide(name);
					theme.control_themes[key] = ControlTheme();
					control_theme_dispatcher.run(inner_context, theme, theme.control_themes[key]);
				}
			);
		}
	),
	
	minijson::handlers::handler(
		"textThemes",
		[](EditorTheme& theme, minijson::value, auto& context) 
		{
			parse_object(context, [&](std::string_view name, minijson::value, auto& inner_context)
				{
					sf::String key = toWide(name);
					theme.text_themes[key] = TextTheme();
					text_theme_dispatcher.run(inner_context, theme, theme.text_themes[key]);
				}
			);
		}
	),
			
	minijson::handlers::handler(
		"inputControlThemes",
		[](EditorTheme& theme, minijson::value, auto& context)
		{
			parse_object(context, [&](std::string_view name, minijson::value v, auto& ctx)
				{
					sf::String key = toWide(name);
					theme.input_control_themes[key] = InputControlTheme();
					input_control_theme_dispatcher.run(ctx, theme, theme.input_control_themes[key]);
				}
			);
		}
	),

	minijson::handlers::ignore_any_handler {}
};

const minijson::dispatcher shader_dispatcher
{
	minijson::handlers::optional_handler("fragment",	[&](sf::Shader* shader, minijson::value v) { shader->loadFromFile("Data\\Resources\\Shaders\\Fragment\\" + std::string(v.raw()), sf::Shader::Type::Fragment); }),
	minijson::handlers::optional_handler("geometry",	[&](sf::Shader* shader, minijson::value v) { shader->loadFromFile("Data\\Resources\\Shaders\\Geometry\\" + std::string(v.raw()), sf::Shader::Type::Geometry); }),
	minijson::handlers::optional_handler("vertex",		[&](sf::Shader* shader, minijson::value v) { shader->loadFromFile("Data\\Resources\\Shaders\\Vertex\\" + std::string(v.raw()), sf::Shader::Type::Vertex); }),

	minijson::handlers::any_handler(
		[](sf::Shader* shader, std::string_view name, minijson::value, auto& context)
		{
			std::vector<float> array_elements = std::vector<float>();
			minijson::parse_array(context, [&](minijson::value v)
				{
					array_elements.push_back(v.as<float>());
				}
			);

			shader->setUniformArray(name.data(), array_elements.data(), array_elements.size());
			return true;
		}
	)
};

const minijson::dispatcher control_theme_dispatcher
{
	minijson::handlers::handler("texture",							[](EditorTheme& theme, ControlTheme& control_theme, minijson::value v) { control_theme.texture = theme.textures[toWide(v.raw())]; }),
	minijson::handlers::optional_handler("hoveringShader",			[](EditorTheme& theme, ControlTheme& control_theme, minijson::value v) { control_theme.hovering_shader = theme.shaders[toWide(v.raw())]; }),
	minijson::handlers::optional_handler("disabledShader",			[](EditorTheme& theme, ControlTheme& control_theme, minijson::value v) { control_theme.disabled_shader = theme.shaders[toWide(v.raw())]; }),
	minijson::handlers::optional_handler("disabledHoveringShader",	[](EditorTheme& theme, ControlTheme& control_theme, minijson::value v) { control_theme.disabled_hovering_shader = theme.shaders[toWide(v.raw())]; }),
	minijson::handlers::optional_handler("enterSound",				[](EditorTheme& theme, ControlTheme& control_theme, minijson::value v) { control_theme.enter_sound = toWide(v.raw()); }),
	minijson::handlers::optional_handler("clickSound",				[](EditorTheme& theme, ControlTheme& control_theme, minijson::value v) { control_theme.click_sound = toWide(v.raw()); }),
	minijson::handlers::optional_handler("releaseSound",			[](EditorTheme& theme, ControlTheme& control_theme, minijson::value v) { control_theme.release_sound = toWide(v.raw()); }),
	minijson::handlers::ignore_any_handler {}
};

const minijson::dispatcher text_theme_dispatcher
{
	minijson::handlers::handler(
		"horizontalAlignment", 
		[](EditorTheme&, TextTheme& textTheme, minijson::value v)
		{
			static std::unordered_map<std::string, TextTheme::TextHorizontalAlignment> const table
				=	{ 
						{ "Center", TextTheme::TextHorizontalAlignment::Center },
						{ "Left", TextTheme::TextHorizontalAlignment::Left },
						{ "Right", TextTheme::TextHorizontalAlignment::Right }
					};

			auto it = table.find(v.raw().data());
			textTheme.horizontal_alignment = it != table.end() ? it->second : TextTheme::TextHorizontalAlignment::Center;
		}
	),

	minijson::handlers::handler(
		"verticalAlignment",
		[](EditorTheme&, TextTheme& textTheme, minijson::value v)
		{
			static std::unordered_map<std::string, TextTheme::TextVerticalAlignment> const table
				=	{
						{ "Center", TextTheme::TextVerticalAlignment::Center },
						{ "Top", TextTheme::TextVerticalAlignment::Top },
						{ "Bottom", TextTheme::TextVerticalAlignment::Bottom }
					};

			auto it = table.find(v.raw().data());
			textTheme.vertical_alignment = it != table.end() ? it->second : TextTheme::TextVerticalAlignment::Center;
		}
	),

	minijson::handlers::handler("font",						[](EditorTheme& theme, TextTheme& textTheme, minijson::value v)			{ textTheme.font = theme.fonts[toWide(v.raw())]; }),
	minijson::handlers::handler("fillDefaultColor",			[](EditorTheme&, TextTheme& textTheme, minijson::value v, auto& ctx)	{ color_dispatcher.run(ctx, textTheme.fill_default_color); }),
	minijson::handlers::handler("fillHoveringColor",		[](EditorTheme&, TextTheme& textTheme, minijson::value v, auto& ctx)	{ color_dispatcher.run(ctx, textTheme.fill_hovering_color); }),
	minijson::handlers::handler("fillHoldingColor",			[](EditorTheme&, TextTheme& textTheme, minijson::value v, auto& ctx)	{ color_dispatcher.run(ctx, textTheme.fill_holding_color); }),
	minijson::handlers::handler("fillDisabledColor",		[](EditorTheme&, TextTheme& textTheme, minijson::value v, auto& ctx)	{ color_dispatcher.run(ctx, textTheme.fill_disabled_color); }),
	minijson::handlers::handler("outlineDefaultColor",		[](EditorTheme&, TextTheme& textTheme, minijson::value v, auto& ctx)	{ color_dispatcher.run(ctx, textTheme.outline_default_color); }),
	minijson::handlers::handler("outlineHoveringColor",		[](EditorTheme&, TextTheme& textTheme, minijson::value v, auto& ctx)	{ color_dispatcher.run(ctx, textTheme.outline_hovering_color); }),
	minijson::handlers::handler("outlineHoldingColor",		[](EditorTheme&, TextTheme& textTheme, minijson::value v, auto& ctx)	{ color_dispatcher.run(ctx, textTheme.outline_holding_color); }),
	minijson::handlers::handler("outlineDisabledColor",		[](EditorTheme&, TextTheme& textTheme, minijson::value v, auto& ctx)	{ color_dispatcher.run(ctx, textTheme.outline_disabled_color); }),
	minijson::handlers::handler("characterSize",			[](EditorTheme&, TextTheme& textTheme, minijson::value v)				{ v.to(textTheme.character_size); }),
	minijson::handlers::handler("letterSpacing",			[](EditorTheme&, TextTheme& textTheme, minijson::value v)				{ v.to(textTheme.letter_spacing); }),
	minijson::handlers::handler("lineSpacing",				[](EditorTheme&, TextTheme& textTheme, minijson::value v)				{ v.to(textTheme.line_spacing); }),
	minijson::handlers::handler("outlineThickness",			[](EditorTheme&, TextTheme& textTheme, minijson::value v)				{ v.to(textTheme.outline_thickness); }),
	minijson::handlers::handler("style",					[](EditorTheme&, TextTheme& textTheme, minijson::value v)				{ v.to(textTheme.style); }),
	minijson::handlers::ignore_any_handler {}
};

const minijson::dispatcher color_dispatcher
{
	minijson::handlers::handler("r",			[](sf::Color& color, minijson::value v) { v.to(color.r); }),
	minijson::handlers::handler("g",			[](sf::Color& color, minijson::value v) { v.to(color.g); }),
	minijson::handlers::handler("b",			[](sf::Color& color, minijson::value v) { v.to(color.b); }),
	minijson::handlers::optional_handler("a",	[](sf::Color& color, minijson::value v) { v.to(color.a); }),
	minijson::handlers::ignore_any_handler {}
};

inline void setCursor(sf::Cursor* cursor, minijson::value v)
{
	std::unordered_map<std::string, sf::Cursor::Type> table
		= {
				{ "Arrow",					sf::Cursor::Arrow },
				{ "ArrowWait",				sf::Cursor::ArrowWait },
				{ "Cross",					sf::Cursor::Cross },
				{ "Hand",					sf::Cursor::Hand },
				{ "Help",					sf::Cursor::Help },
				{ "NotAllowed",				sf::Cursor::NotAllowed },
				{ "SizeAll",				sf::Cursor::SizeAll },
				{ "SizeBottomLeftTopRight",	sf::Cursor::SizeBottomLeftTopRight },
				{ "SizeHorizontal",			sf::Cursor::SizeHorizontal },
				{ "SizeTopLeftBottomRight", sf::Cursor::SizeTopLeftBottomRight },
				{ "SizeVertical",			sf::Cursor::SizeVertical },
				{ "Text",					sf::Cursor::Text },
				{ "Wait",					sf::Cursor::Wait }
	};

	auto it = table.find(v.raw().data());
	cursor->loadFromSystem(it != table.end() ? it->second : sf::Cursor::Arrow);
};

const minijson::dispatcher input_control_theme_dispatcher
{
	minijson::handlers::handler("mouseCursorDefault",	[](EditorTheme&, InputControlTheme& input_control_theme, minijson::value v)				{ setCursor(input_control_theme.mouse_cursor_default, v); }),
	minijson::handlers::handler("mouseCursorText",		[](EditorTheme&, InputControlTheme& input_control_theme, minijson::value v)				{ setCursor(input_control_theme.mouse_cursor_text, v); }),
	minijson::handlers::handler("cursorWidth",			[](EditorTheme&, InputControlTheme& input_control_theme, minijson::value v)				{ v.to(input_control_theme.cursor_width); }),
	minijson::handlers::handler("cursorColor",			[](EditorTheme&, InputControlTheme& input_control_theme, minijson::value, auto& ctx)	{ color_dispatcher.run(ctx, input_control_theme.cursor_color); }),
	minijson::handlers::handler("selectionColor",		[](EditorTheme&, InputControlTheme& input_control_theme, minijson::value, auto& ctx)	{ color_dispatcher.run(ctx, input_control_theme.selection_color); }),
	minijson::handlers::optional_handler("inputSound",	[](EditorTheme& theme, InputControlTheme& input_control_theme, minijson::value v)		{ input_control_theme.input_sound = toWide(v.raw()); }),
	minijson::handlers::ignore_any_handler {}
};

const minijson::dispatcher layout_dispatcher
{
	minijson::handlers::handler(
		"intendedResolution",
		[](Application&, SoundHandler&, ApplicationSettings&, EditorTheme&, sf::RenderWindow&, LayoutSettings& layout, std::map<sf::String, sf::String>*, minijson::value, auto& context)
		{
			vector2u_dispatcher.run(context, layout.intended_resolution);
		}
	),

	minijson::handlers::handler(
		"starterScene",
		[](Application&, SoundHandler&, ApplicationSettings&, EditorTheme&, sf::RenderWindow&, LayoutSettings& layout, std::map<sf::String, sf::String>*, minijson::value v)
		{
			layout.starter_scene = toWide(v.raw());
		}
	),

	minijson::handlers::handler(
		"scenes",
		[](Application& application, SoundHandler& handler, ApplicationSettings& settings, EditorTheme& theme, sf::RenderWindow& window, LayoutSettings& layout, std::map<sf::String, sf::String>* strings, minijson::value, auto& context)
		{
			parse_object(context, [&](std::string_view name, minijson::value, auto& inner_context)
				{
					sf::String key = toWide(name);
					layout.scenes[key] = Scene();

					scene_dispatcher.run(inner_context, application, handler, settings, theme, window, layout.intended_resolution, layout.scenes[key], strings);
					layout.scenes[key].setAnimations(theme.toggle_animations);
				}
			);
		}
	),
	minijson::handlers::ignore_any_handler {}
};

const minijson::dispatcher scene_dispatcher
{
	minijson::handlers::handler(
		"background",	
		[](Application&, SoundHandler&, ApplicationSettings&, EditorTheme& theme, sf::RenderWindow& window, sf::Vector2u, Scene& scene, std::map<sf::String, sf::String>*, minijson::value v)
		{
			sf::String key = toWide(v.raw());
			scene.setBackgroundKey(key);
			scene.setBackground(window.getSize(), theme.textures[key]);
		}
	),

	minijson::handlers::handler(
		"backgroundMovement",
		[](Application&, SoundHandler&, ApplicationSettings&, EditorTheme&, sf::RenderWindow&, sf::Vector2u, Scene& scene, std::map<sf::String, sf::String>*, minijson::value, auto& context)
		{
			bool enabled = false;
			sf::Vector2f min = sf::Vector2f(0, 0);
			sf::Vector2f max = sf::Vector2f(0, 0);
			sf::Vector2f step = sf::Vector2f(0, 0);

			background_movement_dispatcher.run(context, enabled, min, max, step);
			scene.setBackgroundMovement(enabled, min, max, step);
		}
	),

	minijson::handlers::handler(
		"music",
		[](Application&, SoundHandler&, ApplicationSettings&, EditorTheme& theme, sf::RenderWindow& window, sf::Vector2u, Scene& scene, std::map<sf::String, sf::String>*, minijson::value v)
		{
			sf::String key = toWide(v.raw());
			scene.setMusic(key);
		}
	),

	minijson::handlers::handler(
		"controls",
		[](Application& application, SoundHandler& handler, ApplicationSettings& settings, EditorTheme& theme, sf::RenderWindow& window, sf::Vector2u intended_resolution, Scene& scene, std::map<sf::String, sf::String>* strings, minijson::value, auto& context)
		{
			parse_object(context, [&](std::string_view name, minijson::value, auto& inner_context)
				{
					sf::String key = toWide(name);
					ControlConstructor constructor = ControlConstructor 
					{
						.window = &window,
						.intended_resolution = intended_resolution,
						.strings = strings,
						.handler = &handler
					};

					control_dispatcher.run(inner_context, application, theme, window, scene, strings, constructor);
					Control* control = constructControl(constructor);

					scene.addControl(control);
					application.addControl(key, control);
				}
			);
		}
	),

	minijson::handlers::ignore_any_handler {}
};

const minijson::dispatcher background_movement_dispatcher
{
	minijson::handlers::handler("enabled",			[](bool& enabled, sf::Vector2f&, sf::Vector2f&, sf::Vector2f&, minijson::value v)			{ v.to(enabled); }),
	minijson::handlers::optional_handler("min",		[](bool&, sf::Vector2f& min, sf::Vector2f&, sf::Vector2f&, minijson::value, auto& context)	{ vector2f_dispatcher.run(context, min); }),
	minijson::handlers::optional_handler("max",		[](bool&, sf::Vector2f&, sf::Vector2f& max, sf::Vector2f&, minijson::value, auto& context)	{ vector2f_dispatcher.run(context, max); }),
	minijson::handlers::optional_handler("step",	[](bool&, sf::Vector2f&, sf::Vector2f&, sf::Vector2f& step, minijson::value, auto& context) { vector2f_dispatcher.run(context, step); }),
	minijson::handlers::ignore_any_handler {}
};

const minijson::dispatcher control_dispatcher
{
	minijson::handlers::handler("controlType",							[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)				{ constructor.control_type = v.raw().data(); }),
	minijson::handlers::handler("theme",								[](Application&, EditorTheme& theme, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)			{ constructor.theme = &theme.control_themes[toWide(v.raw())]; }),
	minijson::handlers::handler("position",								[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ vector2f_dispatcher.run(context, constructor.position); }),
	minijson::handlers::handler("size",									[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ vector2f_dispatcher.run(context, constructor.size); }),
	minijson::handlers::optional_handler("visible",						[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)				{ v.to(constructor.visible); }),
	minijson::handlers::optional_handler("enabled",						[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)				{ v.to(constructor.enabled); }),
	minijson::handlers::optional_handler("bgRect",						[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ intrect_dispatcher.run(context, constructor.bg_rect); }),
	minijson::handlers::optional_handler("bgActiveRect",				[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ intrect_dispatcher.run(context, constructor.bg_active_rect); }),
	minijson::handlers::optional_handler("textTheme",					[](Application&, EditorTheme& theme, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)			{ constructor.text_theme = &theme.text_themes[toWide(v.raw())]; }),
	minijson::handlers::optional_handler("inputControlTheme",			[](Application&, EditorTheme& theme, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)			{ constructor.input_control_theme = &theme.input_control_themes[toWide(v.raw())]; }),
	minijson::handlers::optional_handler("checked",						[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)				{ v.to(constructor.checked); }),
	minijson::handlers::optional_handler("text",						[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)				{ constructor.text = v.raw().data(); }),
	minijson::handlers::optional_handler("buttonSize",					[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ vector2f_dispatcher.run(context, constructor.button_size); }),
	minijson::handlers::optional_handler("firstButtonBgRect",			[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ intrect_dispatcher.run(context, constructor.first_button_bg_rect); }),
	minijson::handlers::optional_handler("firstButtonBgFocusedRect",	[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ intrect_dispatcher.run(context, constructor.first_button_bg_focused_rect); }),
	minijson::handlers::optional_handler("secondButtonBgRect",			[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ intrect_dispatcher.run(context, constructor.second_button_bg_rect); }),
	minijson::handlers::optional_handler("secondButtonBgFocusedRect",	[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ intrect_dispatcher.run(context, constructor.second_button_bg_focused_rect); }),
	minijson::handlers::optional_handler("min",							[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)				{ v.to(constructor.min); }),
	minijson::handlers::optional_handler("max",							[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)				{ v.to(constructor.max); }),
	minijson::handlers::optional_handler("step",						[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)				{ v.to(constructor.step); }),
	minijson::handlers::optional_handler("value",						[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)				{ v.to(constructor.value); }),
	minijson::handlers::optional_handler("buttonOffset",				[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)				{ v.to(constructor.button_offset); }),
	minijson::handlers::optional_handler("index",						[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)				{ v.to(constructor.index); }),
	minijson::handlers::optional_handler("scrollTime",					[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)				{ v.to(constructor.scroll_time); }),
	minijson::handlers::optional_handler("thumbSize",					[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ vector2f_dispatcher.run(context, constructor.thumb_size); }),
	minijson::handlers::optional_handler("thumbRect",					[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>* ,ControlConstructor& constructor, minijson::value, auto& context)	{ intrect_dispatcher.run(context, constructor.thumb_rect); }),
	minijson::handlers::optional_handler("vertical",					[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)				{ v.to(constructor.vertical); }),
	minijson::handlers::optional_handler("scrollMultiplier",			[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)				{ v.to(constructor.scroll_multiplier); }),
	minijson::handlers::optional_handler("createButtonPosition",		[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ vector2f_dispatcher.run(context, constructor.create_button_position); }),
	minijson::handlers::optional_handler("createButtonSize",			[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ vector2f_dispatcher.run(context, constructor.create_button_size); }),
	minijson::handlers::optional_handler("createButtonBgRect",			[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ intrect_dispatcher.run(context, constructor.create_button_bg); }),
	minijson::handlers::optional_handler("createButtonBgFocusedRect",	[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ intrect_dispatcher.run(context, constructor.create_button_bg_focused); }),
	minijson::handlers::optional_handler("createButtonText",			[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)				{ constructor.create_button_text = v.raw().data(); }),
	minijson::handlers::optional_handler("sliderPosition",				[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ vector2f_dispatcher.run(context, constructor.slider_position); }),
	minijson::handlers::optional_handler("sliderSize",					[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ vector2f_dispatcher.run(context, constructor.slider_size); }),
	minijson::handlers::optional_handler("sliderBgRect",				[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ intrect_dispatcher.run(context, constructor.slider_bg); }),
	minijson::handlers::optional_handler("sliderBgFocusedRect",			[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ intrect_dispatcher.run(context, constructor.slider_bg_focused); }),
	minijson::handlers::optional_handler("sliderThumbSize",				[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ vector2f_dispatcher.run(context, constructor.slider_thumb_size); }),
	minijson::handlers::optional_handler("sliderThumb",					[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)	{ intrect_dispatcher.run(context, constructor.slider_thumb); }),
	minijson::handlers::optional_handler("rowOffset",					[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)				{ v.to(constructor.row_offset); }),
	minijson::handlers::optional_handler("rotationAngle",				[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)				{ v.to(constructor.rotation_angle); }),
	minijson::handlers::optional_handler("minYPosition",				[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value v)				{ v.to(constructor.min_y_position); }),
	
	minijson::handlers::optional_handler(
		"rowConstructors",
		[](Application& application, EditorTheme& theme, sf::RenderWindow& window, Scene& scene, std::map<sf::String, sf::String>* strings, ControlConstructor& constructor, minijson::value, auto& context)
		{
			std::vector<ControlConstructor> array_elements = std::vector<ControlConstructor>();
			minijson::parse_array(context, [&](minijson::value, auto& context)
				{
					ControlConstructor constructor = ControlConstructor { .window = &window, .strings = strings };
					control_dispatcher.run(context, application, theme, window, scene, strings, constructor);
					array_elements.push_back(constructor);
				}
			);

			constructor.row_constructors = array_elements;
			return true;
		}
	),

	minijson::handlers::optional_handler(
		"rowEraseButton",
		[](Application& application, EditorTheme& theme, sf::RenderWindow& window, Scene& scene, std::map<sf::String, sf::String>* strings, ControlConstructor& constructor, minijson::value, auto& context)
		{
			constructor.row_erase_button = new ControlConstructor {.window = &window, .strings = strings };
			control_dispatcher.run(context, application, theme, window, scene, strings, *constructor.row_erase_button);
		}
	),
	
	minijson::handlers::optional_handler(
		"items",
		[](Application&, EditorTheme&, sf::RenderWindow&, Scene&, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)
		{
			std::vector<sf::String> array_elements = std::vector<sf::String>();
			minijson::parse_array(context, [&](minijson::value v)
				{
					array_elements.push_back(toWide(v.raw()));
				}
			);

			constructor.items = array_elements;
			return true;
		}
	),

	minijson::handlers::optional_handler(
		"action",
		[](Application& application, EditorTheme&, sf::RenderWindow&, Scene& scene, std::map<sf::String, sf::String>*, ControlConstructor& constructor, minijson::value, auto& context)
		{ 
			sf::String action_type;
			std::vector<sf::String> arguments;
			action_dispatcher.run(context, action_type, arguments);

			if (action_type == "close")
			{
				constructor.action_empty = [&application]()
				{
					application.close();
				};
			}
			else if (action_type == "changeScene")
			{
				constructor.action_empty = [&application, arguments]()
				{
					bool restart_music = true;
					bool play_from_start = false;

					if (arguments.size() == 18 && arguments[1] == "load_settings")
					{
						application.loadSettings(arguments);
					}
					else 
					{
						auto it = std::find(arguments.begin(), arguments.end(), "update_window");
						if (it != arguments.end())
						{
							application.updateIfDirty();
						}
						
						it = std::find(arguments.begin(), arguments.end(), "open_level");
						if (it != arguments.end())
						{

						}

						it = std::find(arguments.begin(), arguments.end(), "not_restart_music");
						if (it != arguments.end())
						{
							restart_music = false;
						}

						it = std::find(arguments.begin(), arguments.end(), "play_from_start");
						if (it != arguments.end())
						{
							play_from_start = true;
						}
					}

					application.loadScene(arguments[0], restart_music, play_from_start);
				};
			}
			else if (action_type == "openUrl")
			{
				constructor.action_empty = [=]()
				{
					sf::String path = "start " + arguments[0];
					std::system(path.toAnsiString().data());
				};
			}
			else if (action_type == "moveControl")
			{
				std::vector<size_t> ids = std::vector<size_t>();
				for (std::string argument : arguments)
				{
					ids.push_back(std::stoll(argument));
				}

				constructor.action_numeric = [=, &application, &scene](float value)
				{
					scene.realignScene(-value, ids);
				};
			}
			else if (action_type == "setWindowSize")
			{
				constructor.action_numeric = [=, &application, &constructor](size_t value)
				{
					application.setWindowSize(value);
				};
			}
			else if (action_type == "setFullscreen")
			{
				constructor.action_boolean = [=, &application](bool value)
				{
					application.setFullscreen(value);
				};
			}
			else if (action_type == "setVsync")
			{
				constructor.action_boolean = [=, &application](bool value)
				{
					application.setVsync(value);
				};
			}
			else if (action_type == "setFramerateLimit")
			{
				constructor.action_numeric = [=, &application](float value)
				{
					application.setFramerateLimit(value);
				};
			}
			else if (action_type == "setLanguage")
			{
				constructor.action_numeric = [&application, arguments](size_t index)
				{
					application.setLanguage(arguments[0]);
				};
			}
			else if (action_type == "setTheme")
			{
				constructor.action_numeric = [&application, arguments](size_t index)
				{
					application.setTheme(arguments[0]);
				};
			}
			else if (action_type == "setLayout")
			{
				constructor.action_numeric = [&application, arguments](size_t index)
				{
					application.setLayout(arguments[0]);
				};
			}
			else if (action_type == "setMusicVolume")
			{
				constructor.action_numeric = [=, &application](float value)
				{
					application.setMusicVolume(value);
				};
			}
			else if (action_type == "setSoundVolume")
			{
				constructor.action_numeric = [=, &application](float value)
				{
					application.setSoundVolume(value);
				};
			}
			else if (action_type == "setPrettyPrinting")
			{
				constructor.action_boolean = [=, &application](bool value)
				{
					application.setPrettyPrinting(value);
				};
			}
			else if (action_type == "setTabs")
			{
				constructor.action_boolean = [=, &application](bool value)
				{
					application.setTabs(value);
				};
			}
			else if (action_type == "setDefaultFileLocation")
			{
				constructor.action_string = [=, &application](sf::String value)
				{
					application.setDefaultFileLocation(value);
				};
			}
			else if (action_type == "setEnabled")
			{
				constructor.action_empty = [&application, arguments]()
				{
					Control* control = application.getControl(arguments[0]);
					bool enabled = control->getEnabled();
					control->setEnabled(!enabled);
				};
				constructor.action_numeric = [&application, arguments](long double v) { application.getControl(arguments[0])->setEnabled(v > 1); };
				constructor.action_boolean = [&application, arguments](bool v) 
				{
					for (std::string argument : arguments)
					{
						application.getControl(argument)->setEnabled(v);
					}
				};
			}
			else if (action_type == "setVisible")
			{
				constructor.action_empty = [&application, arguments]()
				{
					Control* control = application.getControl(arguments[0]);
					bool visible = control->getVisible();
					control->setVisible(!visible);
				};
				constructor.action_numeric = [&application, arguments](long double v) { application.getControl(arguments[0])->setVisible(v > 1); };
				constructor.action_boolean = [&application, arguments](bool v) { application.getControl(arguments[0])->setVisible(v); };
			}
			else if (action_type == "saveJson")
			{
				constructor.action_empty = [&application]()
				{
					application.saveJson();
				};
			}
			else
			{
				constructor.action_empty = [&]() {};
				constructor.action_numeric = [&](long double) {};
				constructor.action_boolean = [&](bool) {};
				constructor.action_string = [&](sf::String) {};
			}
		}
	),

	minijson::handlers::ignore_any_handler {}
};

const minijson::dispatcher vector2f_dispatcher
{
	minijson::handlers::handler("x",	[](sf::Vector2f& vector, minijson::value v) { v.to(vector.x); }),
	minijson::handlers::handler("y",	[](sf::Vector2f& vector, minijson::value v) { v.to(vector.y); }),
	minijson::handlers::ignore_any_handler {}
};

const minijson::dispatcher vector2u_dispatcher
{
	minijson::handlers::handler("x",	[](sf::Vector2u& vector, minijson::value v) { v.to(vector.x); }),
	minijson::handlers::handler("y",	[](sf::Vector2u& vector, minijson::value v) { v.to(vector.y); }),
	minijson::handlers::ignore_any_handler {}
};

const minijson::dispatcher intrect_dispatcher
{
	minijson::handlers::handler("left",		[](sf::IntRect& rect, minijson::value v) { v.to(rect.left); }),
	minijson::handlers::handler("top",		[](sf::IntRect& rect, minijson::value v) { v.to(rect.top); }),
	minijson::handlers::handler("width",	[](sf::IntRect& rect, minijson::value v) { v.to(rect.width); }),
	minijson::handlers::handler("height",	[](sf::IntRect& rect, minijson::value v) { v.to(rect.height); }),
	minijson::handlers::ignore_any_handler {}
};

const minijson::dispatcher vertex_dispatcher
{
	minijson::handlers::handler("x",		[](sf::Vector2f& position, int&, minijson::value v) { v.to(position.x); }),
	minijson::handlers::handler("y",		[](sf::Vector2f& position, int&, minijson::value v) { v.to(position.y); }),
	minijson::handlers::handler("scale",	[](sf::Vector2f&, int& scale, minijson::value v) { v.to(scale); }),
	minijson::handlers::ignore_any_handler {}
};

const minijson::dispatcher action_dispatcher
{
	minijson::handlers::handler("actionType",	[](sf::String& action_type, std::vector<sf::String>&, minijson::value v)	{ action_type = v.raw().data(); }),

	minijson::handlers::handler(
		"arguments",
		[](sf::String&, std::vector<sf::String>& arguments, minijson::value, auto& context)
		{
			std::vector<sf::String> array_elements = std::vector<sf::String>();
			minijson::parse_array(context, [&](minijson::value v)
				{
					array_elements.push_back(toWide(v.raw()));
				}
			);

			arguments = array_elements;
		}
	),

	minijson::handlers::ignore_any_handler {}
};

#endif