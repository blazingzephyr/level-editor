////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#include "control.hpp"

using sf::Event;
using sf::IntRect;
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
using std::map;

Control::Control() :

	m_window(nullptr),
	m_strings(nullptr),
	m_theme(nullptr),
	m_bg(nullptr),
	m_bg_active(nullptr),
	m_drawable(nullptr),
	m_shader(nullptr),
	m_intended_resolution(),
	m_size_coeff(1.f, 1.f),
	m_position(),
	m_size(),
	m_global_position(),
	m_global_size(),
	m_hovering(false),
	m_holding(false),
	m_holding_wheel(false),
	m_enabled(false),
	m_visible(false),
	m_initialized(false)
{

}

Control::Control(RenderWindow* window, Vector2u intended_resolution, map<String, String>* strings, const ControlTheme* theme, SoundHandler* handler, Vector2f position, Vector2f size,
	const IntRect& bg, const IntRect& bg_active, float min_y_position, bool visible, bool enabled) :

	m_window(window),
	m_strings(strings),
	m_theme(theme),
	m_bg(m_theme->texture ? new Sprite(*m_theme->texture, bg) : nullptr),
	m_bg_active(m_theme->texture ? new Sprite(*m_theme->texture, bg_active) : nullptr),
	m_sound_handler(handler),
	m_intended_resolution(intended_resolution),
	m_size_coeff(window->getSize().x / static_cast<float>(intended_resolution.x), window->getSize().y / static_cast<float>(intended_resolution.y)),
	m_original_size_coeff(window->getSize().x / static_cast<float>(intended_resolution.x), window->getSize().y / static_cast<float>(intended_resolution.y)),
	m_position(position),
	m_size(size),
	m_global_position(Vector2f(position.x * m_size_coeff.x, position.y * m_size_coeff.y)),
	m_global_size(Vector2f(size.x * m_size_coeff.x, size.y * m_size_coeff.y)),
	m_hovering(false),
	m_holding(false),
	m_holding_wheel(false),
	m_enabled(enabled),
	m_visible(visible),
	m_initialized(true),
	m_min_y_position(min_y_position),
	m_input_valid(true)
{
	m_drawable = m_bg,
	m_shader = getShader();
	m_bg->setPosition(m_global_position);
	m_bg_active->setPosition(m_global_position);
	m_bg->setScale(m_size_coeff);
	m_bg_active->setScale(m_size_coeff);
}

Control::~Control()
{
	m_bg = nullptr;
	m_bg_active = nullptr;

	delete m_bg;
	delete m_bg_active;
}

bool Control::getEnabled() const
{
	return m_enabled;
}

bool Control::getVisible() const
{
	return m_visible;
}

void Control::setEnabled(bool enabled)
{
	if (m_initialized)
	{
		m_enabled = enabled;
		m_shader = getShader();
	}
}

void Control::setVisible(bool visible)
{
	if (m_initialized)
	{
		m_visible = visible;
		m_shader = getShader();
	}
}

Vector2f Control::getPosition() const
{
	return m_position;
}

void Control::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_global_position = Vector2f(position.x * m_size_coeff.x, position.y * m_size_coeff.y);
	m_input_valid = position.y >= m_min_y_position;

	m_bg->setPosition(position * m_original_size_coeff.x);
	m_bg_active->setPosition(position * m_original_size_coeff.y);
}

void Control::onLanguageUpdated()
{

}

void Control::onThemeUpdated()
{
	if (m_initialized)
	{
		m_bg->setTexture(*m_theme->texture);
		m_bg_active->setTexture(*m_theme->texture);
		m_shader = getShader();
	}
}

void Control::onUpdated()
{
	if (m_holding || m_holding_wheel && m_hovering && m_enabled)
	{
		onHold();
	}
}

bool Control::onWindowEvent(sf::Event data)
{
	bool valid_event = true;
	switch (data.type)
	{
		case sf::Event::Resized:
		{
			onResized(data.size);
			break;
		}

		case sf::Event::MouseMoved:
		{
			onMouseMoved(data.mouseMove);
			break;
		}

		case sf::Event::MouseButtonPressed:
		{
			onMouseButtonPressed(data.mouseButton);
			break;
		}

		case sf::Event::MouseButtonReleased:
		{
			onMouseButtonReleased(data.mouseButton);
			break;
		}

		case sf::Event::MouseWheelScrolled:
		{
			onMouseWheelScrolled(data.mouseWheelScroll);
			break;
		}

		case sf::Event::KeyPressed:
		{
			onKeyPressed(data.key);
			break;
		}

		case sf::Event::KeyReleased:
		{
			onKeyReleased(data.key);
			break;
		}

		case sf::Event::TextEntered:
		{
			onTextEntered(data.text);
			break;
		}

		default:
		{
			valid_event = false;
			break;
		}
	}

	return valid_event;
}

void Control::onResized(Event::SizeEvent data)
{
	if (m_initialized)
	{
		float x = static_cast<float>(data.width) / static_cast<float>(m_intended_resolution.x);
		float y = static_cast<float>(data.height) / static_cast<float>(m_intended_resolution.y);

		m_size_coeff = Vector2f(x, y);
		m_global_position = Vector2f(m_position.x * x, m_position.y * y);
		m_global_size = Vector2f(m_size.x * x, m_size.y * y);
	}
}

void Control::onMouseMoved(Event::MouseMoveEvent data)
{
	if (m_initialized && m_input_valid && m_enabled)
	{
		bool hovering = contains(static_cast<float>(data.x), static_cast<float>(data.y));
		if (m_hovering != hovering)
		{
			m_hovering = hovering;
			m_shader = getShader();

			if (m_enabled)
			{
				if (hovering)
				{
					onMouseEntered(data);
				}
				else
				{
					onMouseLeft(data);
				}
			}
		}

		if (m_holding)
		{
			onMoved(data);
		}
	}
}

void Control::onMouseButtonPressed(Event::MouseButtonEvent data)
{
	if (m_initialized && m_input_valid)
	{
		if (m_hovering)
		{
			m_holding = data.button == Mouse::Left || data.button == Mouse::Right;
			m_holding_wheel = data.button == Mouse::HorizontalWheel || data.button == Mouse::VerticalWheel;
		}

		if (m_enabled)
		{
			if (m_holding || m_holding_wheel)
			{
				onClicked(data);
			}
			else
			{
				onUnclicked(data);
			}
		}
	}
}

void Control::onMouseButtonReleased(Event::MouseButtonEvent data)
{
	if (m_initialized && m_input_valid && m_enabled)
	{
		m_holding_current = m_holding;
		m_holding = false;
		m_holding_wheel = false;

		if (m_enabled && m_holding_current && m_hovering)
		{
			onReleased(data);
		}
	}
}

void Control::onMouseWheelScrolled(Event::MouseWheelScrollEvent data)
{
	if (m_initialized && m_enabled && m_hovering && m_input_valid)
	{
		onScrolled(data);
	}
}

void Control::onKeyPressed(Event::KeyEvent data)
{

}

void Control::onKeyReleased(Event::KeyEvent data)
{

}

void Control::onTextEntered(Event::TextEvent data)
{

}

void Control::draw(RenderTarget &target, RenderStates states) const
{
	if (m_initialized && m_visible)
	{
		states.shader = m_shader;
		target.draw(*m_drawable, states);
	}
}

bool Control::contains(Vector2f point) const
{
	return contains(point.x, point.y);
}

bool Control::contains(float x, float y) const
{
	return x >= m_global_position.x
		&& x <= m_global_position.x + m_global_size.x
		&& y >= m_global_position.y
		&& y <= m_global_position.y + m_global_size.y;
}

const Shader* Control::getShader() const
{
	return m_enabled ? m_hovering ? m_theme->hovering_shader : nullptr
		: m_hovering ? m_theme->disabled_hovering_shader : m_theme->disabled_shader;
}

void Control::onHold()
{

}

void Control::onMouseEntered(Event::MouseMoveEvent data)
{
	m_sound_handler->playSound(m_theme->enter_sound);
}

void Control::onMouseLeft(Event::MouseMoveEvent data)
{

}

void Control::onClicked(Event::MouseButtonEvent data)
{
	m_sound_handler->playSound(m_theme->click_sound);
}

void Control::onUnclicked(Event::MouseButtonEvent data)
{

}

void Control::onMoved(Event::MouseMoveEvent data)
{

}

void Control::onReleased(Event::MouseButtonEvent data)
{
	m_sound_handler->playSound(m_theme->release_sound);
}

void Control::onScrolled(Event::MouseWheelScrollEvent data)
{

}