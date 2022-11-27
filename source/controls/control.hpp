////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_CONTROL_HPP
#define EDITOR_CONTROL_HPP

#include "../main/sound_handler.hpp"
#include "../themes/control_theme.hpp"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Window/Event.hpp>
#include <map>
#include <minijson/minijson_reader.hpp>

class Control : public sf::Drawable
{
public:
	Control();
	Control(sf::RenderWindow* window, sf::Vector2u intended_resolution, std::map<sf::String, sf::String>* strings, const ControlTheme* theme, SoundHandler* handler, sf::Vector2f position, sf::Vector2f size,
		const sf::IntRect& bg, const sf::IntRect& bg_active, float min_y_position, bool visible = true, bool enabled = true);

	~Control();

	bool									getEnabled() const;
	bool									getVisible() const;
	virtual void							setEnabled(bool enabled);
	virtual void							setVisible(bool visible);
	sf::Vector2f							getPosition() const;
	virtual void							setPosition(sf::Vector2f position);
	virtual void							onLanguageUpdated();
	virtual void							onThemeUpdated();
	virtual void							onUpdated();
	virtual bool							onWindowEvent(sf::Event data);
	virtual void							onResized(sf::Event::SizeEvent data);
	virtual void							onMouseMoved(sf::Event::MouseMoveEvent data);
	virtual void							onMouseButtonPressed(sf::Event::MouseButtonEvent data);
	virtual void							onMouseButtonReleased(sf::Event::MouseButtonEvent data);
	virtual void							onMouseWheelScrolled(sf::Event::MouseWheelScrollEvent data);
	virtual void							onKeyPressed(sf::Event::KeyEvent data);
	virtual void							onKeyReleased(sf::Event::KeyEvent data);
	virtual void							onTextEntered(sf::Event::TextEvent data);
	virtual void							draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	sf::RenderWindow*						m_window;
	std::map<sf::String, sf::String>*		m_strings;
	const ControlTheme*						m_theme;
	SoundHandler*							m_sound_handler;
	const Drawable*							m_drawable;
	const sf::Shader*						m_shader;
	sf::Sprite*								m_bg;
	sf::Sprite*								m_bg_active;
	sf::Vector2u							m_intended_resolution;
	sf::Vector2f							m_original_size_coeff;
	sf::Vector2f							m_size_coeff;
	sf::Vector2f							m_position;
	sf::Vector2f							m_size;
	sf::Vector2f							m_global_position;
	sf::Vector2f							m_global_size;
	float									m_min_y_position;
	bool									m_input_valid;
	bool									m_hovering;
	bool									m_holding;
	bool									m_holding_current;
	bool									m_holding_wheel;
	bool									m_visible;
	bool									m_enabled;
	bool									m_initialized;

	bool									contains(sf::Vector2f point) const;
	bool									contains(float x, float y) const;
	virtual const sf::Shader*				getShader() const;
	virtual void							onHold();
	virtual void							onMouseEntered(sf::Event::MouseMoveEvent data);
	virtual void							onMouseLeft(sf::Event::MouseMoveEvent data);
	virtual void							onClicked(sf::Event::MouseButtonEvent data);
	virtual void							onUnclicked(sf::Event::MouseButtonEvent data);
	virtual void							onMoved(sf::Event::MouseMoveEvent data);
	virtual void							onReleased(sf::Event::MouseButtonEvent data);
	virtual void							onScrolled(sf::Event::MouseWheelScrollEvent data);
};

#endif