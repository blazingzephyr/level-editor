////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright (c) 2023 ZaBlazzingZeif
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "InputControl.hpp"


namespace le
{
////////////////////////////////////////////////////////////
InputControl::InputControl() :

TextBasedControl::TextBasedControl(),
m_focused(false),
m_inputStyle(nullptr),
m_string(),
m_strLen(0),
m_onTextUpdated([](InputControl&, sf::String) {}),
m_selected(false),
m_selection(),
m_selectionOffset(0),
m_selectionRange(0, 0),
m_cursor(),
m_cursorPosition(0),
m_overwrite(false)
{
}


////////////////////////////////////////////////////////////
InputControl::InputControl(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Texture& texture,
const sf::IntRect& spriteDefault, const sf::IntRect& spriteFocused, const TextTheme* textTheme, const InputTextStyle* inputStyle,
Event1<InputControl, sf::String> onTextUpdated, const sf::String& string, bool enabled) :

TextBasedControl::TextBasedControl(position, sf::Vector2f(0, 0), size, texture, spriteDefault, spriteFocused,
textTheme, false, enabled),

m_focused(false),
m_inputStyle(inputStyle),
m_string(string),
m_strLen(string.getSize()),
m_onTextUpdated(onTextUpdated),
m_selected(false),
m_selection(),
m_selectionOffset(0),
m_selectionRange(0, 0),
m_cursor(sf::Vector2f(inputStyle ? inputStyle->m_cursorWidth : 0, size.y)),
m_cursorPosition(m_strLen),
m_overwrite(false)
{
	this->m_text = le::TextComponent(sf::Vector2f(0, 0), sf::Vector2u(size), textTheme->m_default, string, sf::Vector2f(0, 0));
	this->m_selection.setFillColor(inputStyle ? inputStyle->m_selection : sf::Color(0, 0, 255, 100));
	this->m_cursor.setFillColor(inputStyle ? inputStyle->m_cursor : sf::Color::White);
}


////////////////////////////////////////////////////////////
const sf::String& InputControl::getText() const
{
	return this->m_string;
}


////////////////////////////////////////////////////////////
void InputControl::setString(const sf::String& string, bool raiseEvent)
{
	this->m_cursorPosition = string.getSize();
	clearSelection();
	updateText(0, string, raiseEvent);
}


////////////////////////////////////////////////////////////
void InputControl::setCursor(size_t index)
{
	if (this->m_enabled && this->m_strLen >= index)
	{
		float characterPosition = this->m_text.findCharacterPos(index).x;
		this->m_cursor.setPosition(characterPosition, 0);
		this->m_cursorPosition = index;

		auto move = [this](float diff)
		{
			this->m_text.moveText(diff, 0);
			this->m_cursor.move(diff, 0);
		};

		bool leftmost = characterPosition < 0;
		if (leftmost || characterPosition > this->m_size.x)
		{
			move(leftmost ? -characterPosition : this->m_size.x - characterPosition);
		}

		sf::Vector2f position = getPosition();
		sf::Vector2f textPosition = this->m_text.getTextPosition();
		sf::FloatRect textBounds = this->m_text.getLocalBounds();

		bool outsideBounds = textPosition.x < position.x && textPosition.x + textBounds.width < 0;
		if (outsideBounds)
		{
			move(this->m_size.x - position.x - textPosition.x - textBounds.width);

			if (textBounds.width < (this->m_size.x - position.x * 2))
			{
				move(position.x - textPosition.x);
			}
		}
	}
}


////////////////////////////////////////////////////////////
void InputControl::onTextEntered(sf::Uint32 unicode)
{
	if (unicode > 159 || unicode < 127 && unicode > 30 && this->m_enabled && this->m_focused)
	{
		inputText(unicode);
	}
}


////////////////////////////////////////////////////////////
void InputControl::onKeyPressed(sf::Event::KeyEvent key)
{
	if (this->m_enabled && this->m_focused)
	{
		switch (key.code)
		{
			case sf::Keyboard::Insert:
			{
				this->m_overwrite = !this->m_overwrite;
				break;
			}

			case sf::Keyboard::Backspace:
			{
				eraseText(this->m_cursorPosition > 0,
					this->m_selectionRange.second == this->m_selectionRange.first ?1 :
					this->m_selectionRange.second - this->m_selectionRange.first, this->m_selected ? 0 : -1);
				break;
			}

			case sf::Keyboard::Delete:
			{
				eraseText(true, this->m_selectionRange.second - this->m_selectionRange.first, 0);
				break;
			}

			case sf::Keyboard::Left:
			{
				updatePosition(this->m_cursorPosition > 0, this->m_selectionRange.first, -1);
				break;
			}

			case sf::Keyboard::Right:
			{
				updatePosition(this->m_cursorPosition < this->m_strLen, this->m_selectionRange.second, 1);
				break;
			}

			case sf::Keyboard::A:
			{
				if (key.control)
				{
					this->m_selected = true;
					this->m_selectionRange = std::make_pair(0, this->m_strLen);

					sf::FloatRect textBounds = this->m_text.getGlobalBounds();
					float width = this->m_size.x;
					
					bool wider = textBounds.width > width;
					float selectionOffset = wider ? 0 : textBounds.left;

					this->m_selectionOffset = selectionOffset;
					this->m_selection.setPosition(selectionOffset, 0);
					this->m_selection.setSize(sf::Vector2f(wider ? width : textBounds.width, this->m_size.y));
					setCursor(this->m_strLen);
				}
				break;
			}

			case sf::Keyboard::Home:
			{
				clearSelection();
				setCursor(0);
				break;
			}

			case sf::Keyboard::End:
			{
				clearSelection();
				setCursor(this->m_strLen);
				break;
			}

			case sf::Keyboard::C:
			{
				if (key.control && this->m_selected)
				{
					sf::String clipboard_string = this->m_string.substring(
						this->m_selectionRange.first,
						this->m_selectionRange.second - this->m_selectionRange.first
					);

					sf::Clipboard::setString(clipboard_string);
				}
				break;
			}

			case sf::Keyboard::V:
			{
				if (key.control)
				{
					sf::String clipboard_string = sf::Clipboard::getString();
					inputText(clipboard_string);
				}
				break;
			}

			case sf::Keyboard::X:
			{
				if (key.control && m_selected)
				{
					sf::String buffer = this->m_string;
					buffer.erase(this->m_selectionRange.first,
						this->m_selectionRange.second == this->m_selectionRange.first ? 1 :
						this->m_selectionRange.second - this->m_selectionRange.first
					);

					ValidationResult result = validateText(buffer);
					if (result != ValidationResult::Invalid)
					{
						sf::String clipboard_string = this->m_string.substring(
							this->m_selectionRange.first,
							this->m_selectionRange.second - this->m_selectionRange.first
						);

						sf::Clipboard::setString(clipboard_string);
						updateText(0, buffer);
					}
				}
				break;
			}
		}
	}
}


////////////////////////////////////////////////////////////
void InputControl::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	TextBasedControl::draw(target, states);
	if (this->m_focused)
	{
		states.transform *= getTransform();
		target.draw(this->m_selection, states);
		target.draw(this->m_cursor, states);
	}
}


////////////////////////////////////////////////////////////
InputControl::ValidationResult InputControl::validateText(sf::String& buffer)
{
	return ValidationResult::Valid;
}


////////////////////////////////////////////////////////////
void InputControl::onClicked(sf::Mouse::Button button, sf::Vector2f worldPos)
{
	TextBasedControl::onClicked(button, worldPos);
	this->m_focused = true;
	this->m_sprite.setUseAlt(true);
	clearSelection();

	sf::Transform transform = getParentTransform() * getTransform();
	sf::FloatRect textBounds = this->m_text.getGlobalBounds();
	sf::FloatRect rect = transform.transformRect(sf::FloatRect(textBounds.left, 0, textBounds.width, this->m_size.y));

	if (rect.contains(worldPos))
	{
		bool set = false;
		for (size_t i = this->m_strLen + 1; i >= 0 && !set; --i)
		{
			float glyphLeft = characterPos(i);
			if (glyphLeft <= worldPos.x)
			{
				float glyphRight = characterPos(i + 1);
				bool leftmost = abs(glyphLeft - worldPos.x) < abs(glyphRight - worldPos.x);

				set = true;
				this->m_selectionOffset = leftmost ? glyphLeft : glyphRight;
				setCursor(leftmost ? i : i + 1);
			}
		}
	}
	else
	{
		bool isLeftmost = worldPos.x < rect.left;
		size_t index = isLeftmost ? 0 : this->m_strLen;
		setCursor(index);
		this->m_selectionOffset = characterPos(index);
	}
}


////////////////////////////////////////////////////////////
void InputControl::onUnclicked(sf::Mouse::Button button, sf::Vector2f worldPos)
{
	this->m_focused = false;
	this->m_sprite.setUseAlt(false);
	clearSelection();
}


////////////////////////////////////////////////////////////
void InputControl::onMovedControl(sf::Vector2f worldPos)
{
	sf::Vector2f position = getParentTransform().transformPoint(getPosition());
	if (position.x <= worldPos.x && worldPos.x <= position.x + this->m_size.x)
	{
		std::pair<float, float> selectionPositions = std::minmax({ worldPos.x, this->m_selectionOffset });
		std::pair<float, float> selection = std::make_pair(this->m_selectionOffset, this->m_selectionOffset);
		this->m_selectionRange = std::make_pair(this->m_cursorPosition, this->m_cursorPosition);

		for (size_t i = 0; i < this->m_strLen; i++)
		{
			const float glyphLeft = characterPos(i);
			const float glyphRight = characterPos(i + 1);

			const float interLeft = std::max(selectionPositions.first, glyphLeft);
			const float interRight = std::min(selectionPositions.second, glyphRight);

			if (interLeft < interRight)
			{
				selection.first = std::min(glyphLeft, selection.first);
				selection.second = std::max(glyphRight, selection.second);

				this->m_selectionRange.first = std::min(i, this->m_selectionRange.first);
				this->m_selectionRange.second = std::max(i + 1, this->m_selectionRange.second);
			}
		}

		sf::Vector2f size = sf::Vector2f(selection.second - selection.first, this->m_size.y);
		this->m_selection.setPosition(selection.first - getPosition().x, 0);
		this->m_selection.setSize(size);
		this->m_selected = true;
	}
}


////////////////////////////////////////////////////////////
void InputControl::onEntered(sf::Vector2f worldPos)
{
	TextBasedControl::onEntered(worldPos);
	if (this->m_inputStyle && this->m_inputStyle->m_cursorText)
	{
		this->m_window->setMouseCursor(*this->m_inputStyle->m_cursorText);
	}
}


////////////////////////////////////////////////////////////
void InputControl::onLeft(sf::Vector2f worldPos)
{
	TextBasedControl::onLeft(worldPos);

	if (this->m_inputStyle && this->m_inputStyle->m_cursorDefault)
	{
		this->m_window->setMouseCursor(*this->m_inputStyle->m_cursorDefault);
	}
}


////////////////////////////////////////////////////////////
void InputControl::updatePosition(bool condition, size_t selectionPosition, long long offset)
{
	if (condition && !this->m_holding)
	{
		size_t cursorPosition = this->m_selected ? selectionPosition : this->m_cursorPosition + offset;
		clearSelection();
		setCursor(cursorPosition);
	}
}


////////////////////////////////////////////////////////////
void InputControl::inputText(sf::String characters)
{
	size_t length = characters.getSize();
	sf::String buffer = this->m_string;

	if (this->m_selected)
	{
		buffer.replace(this->m_selectionRange.first, this->m_selectionRange.second - this->m_selectionRange.first, characters);
	}
	else if (this->m_overwrite)
	{
		buffer.replace(this->m_cursorPosition, length, characters);
	}
	else
	{
		buffer.insert(this->m_cursorPosition, characters);
	}

	updateText(length, buffer);
}


////////////////////////////////////////////////////////////
void InputControl::eraseText(bool condition, size_t last, size_t offset)
{
	sf::String buffer = this->m_string;
	if (this->m_selected)
	{
		buffer.erase(this->m_selectionRange.first, last);
	}
	else if (condition && this->m_strLen > 0)
	{
		buffer.erase(this->m_cursorPosition + offset, 1);
	}

	updateText(offset, buffer);
}


////////////////////////////////////////////////////////////
void InputControl::updateText(size_t offset, sf::String buffer, bool raiseEvent)
{
	ValidationResult result = validateText(buffer);
	if (result != ValidationResult::Invalid)
	{
		size_t cursorPosition = this->m_selected ? this->m_selectionRange.first : this->m_cursorPosition;
		cursorPosition += offset;

		this->m_string = buffer;
		this->m_strLen = buffer.getSize();
		this->m_text.setString(buffer);
		this->m_text.resetTextOffset();
		clearSelection();

		if (result == ValidationResult::Valid)
		{
			setCursor(cursorPosition);
		}

		if (raiseEvent)
		{
			m_onTextUpdated(*this, this->m_string);
		}
	}
}


////////////////////////////////////////////////////////////
void InputControl::clearSelection()
{
	this->m_selected = false;
	this->m_selectionOffset = 0;
	this->m_selectionRange = std::make_pair(0, 0);
	this->m_selection.setSize(sf::Vector2f(0, 0));
}


////////////////////////////////////////////////////////////
float InputControl::characterPos(size_t index)
{
	sf::Vector2f characterPosition = this->m_text.findCharacterPos(index);
	return getCombinedTransform().transformPoint(characterPosition).x;
}

} //namespace le