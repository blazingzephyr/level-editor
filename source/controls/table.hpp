////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_TABLE_HPP
#define EDITOR_TABLE_HPP

#include "control.hpp"
#include "slider.hpp"
#include "../utility/control_constructor.hpp"
#include "../utility/construct_control.hpp"
#include <minijson/minijson_writer.hpp>
#include <vector>

class Table : public Control
{
public:
	Table();
	Table(sf::RenderWindow* window, sf::Vector2u intended_resolution, std::map<sf::String, sf::String>* strings, const ControlTheme* theme, SoundHandler* handler, const TextTheme* button_theme,
		sf::Vector2f position, sf::Vector2f size, const sf::IntRect& bg, const sf::IntRect& bg_focused,
		sf::Vector2f create_button_position, sf::Vector2f create_button_size, const sf::IntRect& create_button_bg, const sf::IntRect& create_button_bg_focused, sf::String create_button_text,
		sf::Vector2f slider_position, sf::Vector2f slider_size, const sf::IntRect& slider_bg, const sf::IntRect& slider_bg_focused, sf::Vector2f slider_thumb_size, const sf::IntRect& slider_thumb, float scroll_multiplier,
		float row_offset, std::vector<ControlConstructor> row_constructors, ControlConstructor row_erase_button_constructor, float min_y_position, bool visible = true, bool enabled = true);

	size_t							getCount();
	Control*						getControlAt(size_t i1, size_t i2);
	void							writeToJson(minijson::array_writer& writer, const char** field_names);
	void							setVisible(bool visible) override;
	void							setEnabled(bool enabled) override;
	void							setPosition(sf::Vector2f position) override;
	void							onThemeUpdated() override;
	void							onUpdated() override;
	bool							onWindowEvent(sf::Event data) override;
	void							draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	Button							m_create_button;
	FloatSlider						m_slider;
	std::vector<ControlConstructor>	m_control_constructors;
	size_t							m_constructors_count;
	ControlConstructor				m_erase_button_constructor;
	std::vector<Control**>			m_controls;
	std::vector<Vector2f*>			m_control_positions;
	float							m_offset;
	float							m_row_offset;
	sf::Vector2f					m_create_button_position;
	sf::Vector2f					m_slider_position;

	void							updateControlPositions();
};

#endif