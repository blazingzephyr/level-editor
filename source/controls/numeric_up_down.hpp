////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_NUMERIC_UP_DOWN_HPP
#define EDITOR_NUMERIC_UP_DOWN_HPP

#include "../utility/arithmetic.hpp"
#include "input_control.hpp"
#include "button.hpp"
#include <functional>
#include <regex>

template<typename T>
	requires arithmetic<T>
class NumericUpDown : public InputControl
{
public:
	NumericUpDown();
	NumericUpDown(sf::RenderWindow* window, sf::Vector2u intended_resolution, std::map<sf::String, sf::String>* strings, const ControlTheme* theme, SoundHandler* handler, const TextTheme* text_theme, const InputControlTheme* input_control_theme,
		sf::Vector2f field_position, sf::Vector2f field_size, const sf::IntRect& bg, const sf::IntRect& bg_focused, sf::Vector2f button_size,
		const sf::IntRect& top_button_bg, const sf::IntRect& top_button_bg_focused, const sf::IntRect& bottom_button_bg, const sf::IntRect& bottom_button_bg_focused,
		T min, T max, T step, T value, std::function<void(T)> updated, int scroll_time, float min_y_position, bool visible = true, bool enabled = true);

	T								getNumber() const;
	void							setEnabled(bool enabled) override;
	void							setPosition(sf::Vector2f position) override;
	void							setValue(T value);
	void							forceSetValue(T value);
	void							draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void							onUpdated() override;
	bool							onWindowEvent(sf::Event data) override;

protected:
	void							onUnclicked(sf::Event::MouseButtonEvent data) override;
	InputControl::ValidationResult	validateText(sf::String& buffer) override;

private:
	sf::Vector2f					m_button_size;
	std::function<void(T)>			m_value_updated;
	std::regex						m_first_condition;
	std::regex						m_second_condition;
	sf::String						m_last_valid;
	T								m_min;
	T								m_max;
	T								m_step;
	T								m_value;
	Button*							m_top_button;
	Button*							m_bottom_button;
	sf::Clock						m_clock;
	int								m_scroll_time;
	int								m_elapsed_time;
	bool							m_requires_restarting;
	bool							m_holding;
	bool							m_holding_first_time;

	void							updateText();
};

typedef NumericUpDown<sf::Uint8>	ByteNumeric;
typedef NumericUpDown<sf::Uint16>	UshortNumeric;
typedef NumericUpDown<sf::Uint32>	UintNumeric;
typedef NumericUpDown<int>			IntNumeric;
typedef NumericUpDown<float>		FloatNumeric;
typedef NumericUpDown<double>		DoubleNumeric;

#include "numeric_up_down.inl"
#endif