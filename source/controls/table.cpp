////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#include "table.hpp"

using sf::IntRect;
using sf::RenderWindow;
using sf::String;
using sf::Vector2f;
using sf::Vector2u;
using std::map;
using std::vector;
using minijson::array_writer;
using minijson::object_writer;

Table::Table() : 
	
	Control(),
	m_create_button(),
	m_slider(),
	m_constructors_count(0),
	m_offset(0),
	m_row_offset(0)
{

}

Table::Table(RenderWindow* window, Vector2u intended_resolution, map<String, String>* strings, const ControlTheme* theme, SoundHandler* handler, const TextTheme* button_theme,
	Vector2f position, Vector2f size, const IntRect& bg, const IntRect& bg_focused,
	Vector2f create_button_position, Vector2f create_button_size, const IntRect& create_button_bg, const IntRect& create_button_bg_focused, String create_button_text,
	Vector2f slider_position, Vector2f slider_size, const IntRect& slider_bg, const IntRect& slider_bg_focused, Vector2f slider_thumb_size, const IntRect& slider_thumb, float scroll_multiplier,
	float row_offset, vector<ControlConstructor> row_constructors, ControlConstructor row_erase_button_constructor, float min_y_position, bool visible, bool enabled) :

	Control(window, intended_resolution, strings, theme, handler, position, size, bg, bg_focused, min_y_position, visible, enabled),
	m_create_button(
		window,
		intended_resolution,
		strings,
		theme,
		handler,
		button_theme,
		position + create_button_position,
		create_button_size,
		create_button_bg,
		create_button_bg_focused,
		create_button_text,
		[&, this]()
		{
			Control** row = new Control*[m_constructors_count + 1];
			Vector2f* row_positions = new Vector2f[m_constructors_count + 1];
			size_t i = 0;

			for (ControlConstructor constructor : m_control_constructors)
			{
				row[i] = constructControl(constructor);
				row_positions[i] = constructor.position;
				++i;
			}

			m_erase_button_constructor.action_empty = [=, this]()
			{
				auto iterator = std::find(m_controls.begin(), m_controls.end(), row);
				m_controls.erase(iterator);
				updateControlPositions();
			};

			row[m_constructors_count] = constructControl(m_erase_button_constructor);
			row_positions[m_constructors_count] = m_erase_button_constructor.position;

			m_controls.push_back(row);
			m_control_positions.push_back(row_positions);
			updateControlPositions();
		},
		[]() {},
		visible,
		enabled
	),

	m_slider(
		window,
		intended_resolution,
		strings,
		theme,
		handler,
		position + slider_position,
		slider_size,
		slider_bg,
		slider_bg_focused,
		slider_thumb_size,
		slider_thumb,
		0,
		0.1,
		0.1,
		scroll_multiplier,
		[this](float value)
		{
			m_offset = value;
			updateControlPositions();
		},
		true,
		visible,
		enabled
	),

	m_control_constructors(row_constructors),
	m_constructors_count(row_constructors.size()),
	m_controls(),
	m_offset(0.1),
	m_row_offset(row_offset),
	m_erase_button_constructor(row_erase_button_constructor),
	m_create_button_position(create_button_position),
	m_slider_position(slider_position)
{
	m_erase_button_constructor.intended_resolution = intended_resolution;
	m_erase_button_constructor.handler = handler;

	for (ControlConstructor& constructor : m_control_constructors)
	{
		constructor.intended_resolution = intended_resolution;
		constructor.handler = handler;
	}
}

size_t Table::getCount()
{
	return m_controls.size();
}

Control* Table::getControlAt(size_t i1, size_t i2)
{
	return m_controls[i1][i2];
}

void Table::writeToJson(array_writer& writer, const char** field_names)
{
	for (auto& row : m_controls)
	{
		object_writer inner = writer.nested_object();
		for (size_t i = 0; i < m_constructors_count; i++)
		{
			Control* control = row[i];

			CheckBox* check_box = dynamic_cast<CheckBox*>(control);
			if (check_box)
			{
				inner.write(field_names[i], check_box->getChecked());
				continue;
			}

			ComboBox* combo_box = dynamic_cast<ComboBox*>(control);
			if (combo_box)
			{
				inner.write(field_names[i], combo_box->getItem().toAnsiString());
				continue;
			}

			UintNumeric* uint_numeric = dynamic_cast<UintNumeric*>(control);
			if (uint_numeric)
			{
				inner.write(field_names[i], uint_numeric->getNumber());
				continue;
			}

			IntNumeric* int_numeric = dynamic_cast<IntNumeric*>(control);
			if (int_numeric)
			{
				inner.write(field_names[i], int_numeric->getNumber());
				continue;
			}

			FloatNumeric* float_numeric = dynamic_cast<FloatNumeric*>(control);
			if (float_numeric)
			{
				inner.write(field_names[i], float_numeric->getNumber());
				continue;
			}

			InputControl* input_control = dynamic_cast<InputControl*>(control);
			if (input_control)
			{
				string value = input_control->getText().toAnsiString();
				if (value != "")
				{
					inner.write(field_names[i], value);
				}
				continue;
			}
		}

		inner.close();
	}
	
	writer.close();
}

void Table::setVisible(bool visible)
{
	Control::setVisible(visible);
	m_create_button.setVisible(visible);
	m_slider.setVisible(visible);

	for (Control** row : m_controls)
	{
		for (size_t i = 0; i < m_constructors_count + 1; i++)
		{
			row[i]->setVisible(visible);
		}
	}

	for (ControlConstructor& constructor : m_control_constructors)
	{
		constructor.visible = visible;
	}
}

void Table::setEnabled(bool enabled)
{
	Control::setEnabled(enabled);
	m_create_button.setEnabled(enabled);
	m_slider.setEnabled(enabled);

	for (Control** row : m_controls)
	{
		for (size_t i = 0; i < m_constructors_count + 1; i++)
		{
			row[i]->setEnabled(enabled);
		}
	}

	for (ControlConstructor& constructor : m_control_constructors)
	{
		constructor.enabled = enabled;
	}
}

void Table::setPosition(sf::Vector2f position)
{
	Control::setPosition(position);
	updateControlPositions();

	m_create_button.setPosition(position + m_create_button_position);
	m_slider.setPosition(position + m_slider_position);
}

void Table::onThemeUpdated()
{
	m_create_button.onThemeUpdated();
	m_slider.onThemeUpdated();

	for (Control** row : m_controls)
	{
		for (size_t i = 0; i < m_constructors_count + 1; i++)
		{
			row[i]->onThemeUpdated();
		}
	}
}

void Table::onUpdated()
{
	m_create_button.onUpdated();
	m_slider.onUpdated();

	for (Control** row : m_controls)
	{
		for (size_t i = 0; i < m_constructors_count + 1; i++)
		{
			row[i]->onUpdated();
		}
	}
}

bool Table::onWindowEvent(sf::Event data)
{
	m_create_button.onWindowEvent(data);
	m_slider.onWindowEvent(data);

	bool valid = true;
	for (Control** row : m_controls)
	{
		for (size_t i = 0; i < m_constructors_count + 1 && valid; i++)
		{
			valid = row[i]->onWindowEvent(data);
		}
	}

	return valid;
}

void Table::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_create_button, states);
	target.draw(m_slider, states);

	for (Control** row : m_controls)
	{
		for (size_t i = 0; i < m_constructors_count + 1; i++)
		{
			target.draw(*row[i]);
		}
	}
}

void Table::updateControlPositions()
{
	float vertical_offset = m_position.y - m_offset;
	m_slider.setMax(m_row_offset * m_controls.size());

	for (size_t i = 0; i < m_controls.size(); ++i)
	{
		Control** row = m_controls[i];
		for (size_t j = 0; j < m_constructors_count + 1; j++)
		{
			Vector2f position = m_control_positions[i][j];
			row[j]->setPosition(Vector2f(m_position.x + position.x, vertical_offset + position.y));
		}

		vertical_offset += m_row_offset;
	}
}