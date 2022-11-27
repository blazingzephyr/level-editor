////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_COMBO_BOX_HPP
#define EDITOR_COMBO_BOX_HPP

#include "text_control.hpp"
#include "button.hpp"

class ComboBox : public TextControl
{
public:
	ComboBox();
	ComboBox(sf::RenderWindow* window, sf::Vector2u intended_resolution, std::map<sf::String, sf::String>* strings, const ControlTheme* theme, SoundHandler* handler, const TextTheme* text_theme, sf::Vector2f position, sf::Vector2f size,
		const sf::IntRect& bg, const sf::IntRect& bg_focused, float button_offset, sf::Vector2f button_size,
		const sf::IntRect& left_button_bg, const sf::IntRect& left_button_bg_focused, const sf::IntRect& right_button_bg, const sf::IntRect& right_button_bg_focused,
		std::vector<sf::String> items, size_t index, int scroll_time, std::function<void(size_t)> updated, float min_y_position, bool visible = true, bool enabled = true);

	sf::String					getItem() const;
	size_t						getIndex() const;
	void						forceSetIndex(size_t index);
	void						setEnabled(bool enabled);
	void						setIndex(size_t index);
	void						setItems(std::vector<sf::String> items, size_t new_index);
	void						setPosition(sf::Vector2f position) override;
	void onLanguageUpdated() override;
	void						onThemeUpdated() override;
	void						onUpdated() override;
	bool						onWindowEvent(sf::Event data) override;
	void						draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::function<void(size_t)>	m_value_updated;
	sf::Vector2f				m_button_size;
	float						m_button_offset;
	Button*						m_backwards_button;
	Button*						m_forward_button;
	std::vector<sf::String>		m_items;
	size_t						m_items_count;
	size_t						m_index;
	sf::String					m_item;
	sf::Clock					m_clock;
	int							m_scroll_time;
	int							m_elapsed_time;
	bool						m_requires_restarting;
	bool						m_holding;
	bool						m_holding_first_time;
	bool						m_extra_holding_check;

	void						moveIndex(sf::Int8 summand);
};

#endif