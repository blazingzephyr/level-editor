////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#include "input_control.hpp"

using sf::Clipboard;
using sf::Event;
using sf::IntRect;
using sf::Keyboard;
using sf::Mouse;
using sf::RenderStates;
using sf::RenderTarget;
using sf::RenderWindow;
using sf::Shader;
using sf::Sound;
using sf::Sprite;
using sf::String;
using sf::Vector2f;
using sf::Vector2u;
using sf::Text;
using std::make_pair;
using std::max;
using std::min;
using std::minmax;
using std::pair;
using std::map;

InputControl::InputControl() :

	TextControl::TextControl(),
	m_input_theme(nullptr),
	m_cursor(),
	m_selection(),
	m_focused(false),
	m_overwrite(false),
	m_cursor_position(0),
	m_selected(false),
	m_selection_offset(0),
	m_selection_range(0, 0),
	m_text_updated()
{

}

InputControl::InputControl(RenderWindow* window, Vector2u intended_resolution, map<String, String>* strings, const ControlTheme* theme, SoundHandler* handler, const TextTheme* text_theme, const InputControlTheme* input_control_theme,
	Vector2f position, Vector2f size, const IntRect& bg, const IntRect& bg_focused, String text, std::function<void(String)> updated, float min_y_position, bool visible, bool enabled) :

	TextControl::TextControl(window, intended_resolution, strings, theme, handler, text_theme, position, size, bg, bg_focused, text, min_y_position, visible, enabled),
	m_input_theme(input_control_theme),
	m_cursor(Vector2f(input_control_theme->cursor_width * m_size_coeff.x, m_global_size.y)),
	m_selection(Vector2f(0, size.y)),
	m_focused(false),
	m_overwrite(false),
	m_cursor_position(m_str_len),
	m_selected(false),
	m_selection_offset(0),
	m_selection_range(0, 0),
	m_text_updated(updated)
{
	m_cursor.setPosition(0, position.y);
	m_cursor.setFillColor(m_input_theme->cursor_color);
	m_selection.setPosition(0, position.y);
	m_selection.setFillColor(m_input_theme->selection_color);
}

sf::String InputControl::getText() const
{
	return m_text_string;
}

void InputControl::setCursor(size_t position)
{
	if (m_initialized && m_enabled && m_str_len >= position)
	{
		float character_position = m_text.findCharacterPos(position).x;
		float global_character_position = character_position * m_size_coeff.x / m_original_size_coeff.x;

		m_cursor_position = position;
		m_cursor.setPosition(character_position, m_position.y * m_original_size_coeff.x);

		bool leftmost = global_character_position < m_global_position.x;
		bool rightmost = global_character_position > m_global_position.x + m_global_size.x;

		if (leftmost || rightmost)
		{
			float diff = m_global_position.x + (leftmost ? -global_character_position : m_global_size.x - global_character_position);
			diff = diff / m_size_coeff.x * m_original_size_coeff.x;

			m_text.move(diff, 0);
			m_cursor.move(diff, 0);
		}

		bool outside_bounds = m_text_position.x < m_global_position.x&& m_text_position.x + m_text_global.width < m_global_size.x - m_global_size.x;
		if (outside_bounds)
		{
			float diff = (m_global_size.x - m_global_position.x) - (m_text_position.x + m_text_global.width);
			diff = diff / m_size_coeff.x * m_original_size_coeff.x;

			m_text.move(diff, 0);
			m_cursor.move(diff, 0);

			if (m_text_global.width < (m_global_size.x - m_global_position.x * 2))
			{
				diff = (m_global_position.x - m_text_position.x) / m_size_coeff.x * m_original_size_coeff.x;
				m_text.move(diff, 0);
				m_cursor.move(diff, 0);
			}
		}
	}
}

void InputControl::onKeyPressed(Event::KeyEvent data)
{
	if (m_initialized && m_enabled && m_focused)
	{
		switch (data.code)
		{
			case Keyboard::Insert:
			{
				m_overwrite = !m_overwrite;
				break;
			}

			case Keyboard::Backspace:
			{
				eraseText(m_cursor_position > 0, m_selection_range.second == m_selection_range.first ? 1 : m_selection_range.second - m_selection_range.first, m_selected ? 0 : -1);
				break;
			}

			case Keyboard::Delete:
			{
				eraseText(true, m_selection_range.second - m_selection_range.first, 0);
				break;
			}

			case Keyboard::Left:
			{
				updatePosition(m_cursor_position > 0, m_selection_range.first, -1);
				break;
			}

			case Keyboard::Right:
			{
				updatePosition(m_cursor_position < m_str_len, m_selection_range.second, 1);
				break;
			}

			case Keyboard::A:
			{
				if (data.control)
				{
					m_selected = true;
					m_selection_range = make_pair(0, m_str_len);
					m_selection_offset = m_text_global.left;
					m_selection.setPosition(m_text_position.x - m_text_origin.x, m_position.y * m_original_size_coeff.x);
					m_selection.setSize(Vector2f(m_text_local.width, m_size.y));
					setCursor(m_str_len);
				}
				break;
			}

			case Keyboard::Home:
			{
				disableSelection();
				setCursor(0);
				break;
			}

			case Keyboard::End:
			{
				disableSelection();
				setCursor(m_str_len);
				break;
			}

			case Keyboard::C:
			{
				if (data.control && m_selected)
				{
					String clipboard_string = m_text_string.substring(m_selection_range.first, m_selection_range.second - m_selection_range.first);
					Clipboard::setString(clipboard_string);
				}
				break;
			}

			case Keyboard::V:
			{
				if (data.control)
				{
					String clipboard_string = Clipboard::getString();
					inputText(clipboard_string);
				}
				break;
			}

			case Keyboard::X:
			{
				if (data.control && m_selected)
				{
					String buffer = m_text_string;
					buffer.erase(m_selection_range.first, m_selection_range.second == m_selection_range.first ? 1 : m_selection_range.second - m_selection_range.first);

					ValidationResult valid = validateText(buffer);
					if (valid != ValidationResult::Invalid)
					{
						String clipboard_string = m_text_string.substring(m_selection_range.first, m_selection_range.second - m_selection_range.first);
						Clipboard::setString(clipboard_string);
						updateText(0, buffer);
					}
				}
				break;
			}
		}
	}
}

void InputControl::onTextEntered(Event::TextEvent data)
{
	if (m_initialized && m_enabled && m_focused)
	{
		wchar_t character = data.unicode;
		if (character > 159 || character < 127 && character > 30)
		{
			inputText(String(character));
		}
	}
}

void InputControl::onResized(sf::Event::SizeEvent data)
{
	TextControl::onResized(data);
	m_text_local = m_text.getLocalBounds();
	m_text_bounds = sf::FloatRect(
		(m_text_position.x - m_text_origin.x) * m_size_coeff.x / m_original_size_coeff.x,
		m_global_position.y,
		m_text_local.width * m_size_coeff.y / m_original_size_coeff.y,
		m_global_size.y
	);
}

void InputControl::onMouseEntered(Event::MouseMoveEvent data)
{
	Control::onMouseEntered(data);
	m_window->setMouseCursor(*m_input_theme->mouse_cursor_text);
}

void InputControl::onMouseLeft(Event::MouseMoveEvent data)
{
	Control::onMouseLeft(data);
	m_window->setMouseCursor(*m_input_theme->mouse_cursor_default);
}

void InputControl::onClicked(Event::MouseButtonEvent data)
{
	Control::onClicked(data);
	m_focused = true;
	m_selected = false;
	m_selection_range = make_pair(0, 0);
	m_drawable = m_bg_active;

	m_text_local = m_text.getLocalBounds();
	m_control_rect = sf::FloatRect(m_global_position, m_global_size);
	m_text_bounds = sf::FloatRect(
		(m_text_position.x - m_text_origin.x) * m_size_coeff.x / m_original_size_coeff.x,
		m_global_position.y,
		m_text_local.width * m_size_coeff.y / m_original_size_coeff.y,
		m_global_size.y
	);

	float x = data.x / m_size_coeff.x * m_original_size_coeff.x;
	bool contains = m_control_rect.contains(data.x, data.y);

	if (contains)
	{
		contains = m_text_bounds.contains(data.x, data.y);
		if (contains)
		{
			bool set = false;
			for (size_t i = m_str_len + 1; i >= 0 && !set; --i)
			{
				float glyph_left = m_text.findCharacterPos(i).x;
				if (glyph_left <= x)
				{
					float glyph_right = m_text.findCharacterPos(i + 1).x;
					bool leftmost = abs(glyph_left - x) < abs(glyph_right - x);

					set = true;
					m_selection_offset = leftmost ? glyph_left : glyph_right;
					setCursor(leftmost ? i : i + 1);
				}
			}
		}
		else
		{
			size_t index = x < m_text_position.x - m_text_origin.x ? 0 : m_str_len;
			setCursor(index);
			m_selection_offset = m_text.findCharacterPos(index).x;
		}
	}
}

void InputControl::onUnclicked(Event::MouseButtonEvent data)
{
	m_focused = false;
	m_drawable = m_bg;
}

void InputControl::onMoved(Event::MouseMoveEvent data)
{
	bool contains = m_control_rect.contains(data.x, data.y) && m_text_bounds.contains(data.x, data.y);
	if (contains)
	{
		pair<float, float> selection_range = minmax({ float(data.x / m_size_coeff.x * m_original_size_coeff.x), m_selection_offset });
		pair<float, float> selection = make_pair(m_selection_offset, m_selection_offset);
		m_selection_range = make_pair(m_cursor_position, m_cursor_position);

		for (size_t i = 0; i < m_text_string.getSize(); i++)
		{
			const float glyph_left = m_text.findCharacterPos(i).x;
			const float glyph_right = m_text.findCharacterPos(i + 1).x;

			const float interLeft = max(selection_range.first, glyph_left);
			const float interRight = min(selection_range.second, glyph_right);

			if (interLeft < interRight)
			{
				selection.first = min(glyph_left, selection.first);
				selection.second = max(glyph_right, selection.second);

				m_selection_range.first = min(i, m_selection_range.first);
				m_selection_range.second = max(i + 1, m_selection_range.second);
			}
		}

		Vector2f size = Vector2f(selection.second - selection.first, m_size.y);
		m_selection.setPosition(selection.first, m_position.y * m_original_size_coeff.x);
		m_selection.setSize(size);
		m_selected = true;
	}
}

InputControl::ValidationResult InputControl::validateText(String& buffer)
{
	return ValidationResult::Valid;
}

void InputControl::draw(RenderTarget& target, RenderStates states) const
{
	TextControl::draw(target, states);
	if (m_initialized && m_enabled && m_focused)
	{
		target.draw(m_cursor, states);
		if (m_selected)
		{
			glEnable(GL_SCISSOR_TEST);
			glScissor(m_global_position.x, target.getSize().y - m_global_position.y - m_global_size.y, m_global_size.x, m_global_size.y);
			target.draw(m_selection, states);
			glDisable(GL_SCISSOR_TEST);
		}
	}
}

inline void InputControl::updatePosition(bool condition, size_t selection_position, long long offset)
{
	if (condition && !m_holding)
	{
		size_t cursor_position = m_selected ? selection_position : m_cursor_position + offset;
		m_selected = false;
		m_selection_range = make_pair(0, 0);
		setCursor(cursor_position);
	}
}

void InputControl::eraseText(bool condition, size_t last, long long offset)
{
	String buffer = m_text_string;
	if (m_selected)
	{
		buffer.erase(m_selection_range.first, last);
	}
	else if (condition && m_str_len > 0)
	{
		buffer.erase(m_cursor_position + offset, 1);
	}

	updateText(offset, buffer);
}

void InputControl::inputText(String characters)
{
	size_t length = characters.getSize();
	String buffer = m_text_string;

	if (m_selected)
	{
		buffer.replace(m_selection_range.first, m_selection_range.second - m_selection_range.first, characters);
	}
	else if (m_overwrite)
	{
		buffer.replace(m_cursor_position, length, characters);
	}
	else
	{
		buffer.insert(m_cursor_position, characters);
	}

	updateText(length, buffer);
}

void InputControl::updateText(size_t offset, String buffer)
{
	ValidationResult valid = validateText(buffer);
	if (valid != ValidationResult::Invalid)
	{
		size_t cursor_position = m_selected ? m_selection_range.first : m_cursor_position;
		cursor_position += offset;

		if (m_selected)
		{
			m_selected = false;
			m_selection_range = make_pair(0, 0);
		}

		setText(buffer);

		if (valid == ValidationResult::Valid)
			setCursor(cursor_position);

		m_sound_handler->playSound(m_input_theme->input_sound);
		m_text_updated(buffer);
	}
}

void InputControl::disableSelection()
{
	if (m_selected)
	{
		m_selected = false;
		m_selection_range = make_pair(0, 0);
	}
}