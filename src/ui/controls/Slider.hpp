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

#ifndef LEVEL_EDITOR_SLIDER_HPP
#define LEVEL_EDITOR_SLIDER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "../interfaces/SpriteBasedControl.hpp"
#include "../../utility/Config.hpp"


namespace le
{
////////////////////////////////////////////////////////////
/// \brief Slider control
///
////////////////////////////////////////////////////////////
template <typename T>
requires std::is_arithmetic_v<T>
class Slider : public SpriteBasedControl
{
public:

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// Constructs an empty slider
	/// 
	////////////////////////////////////////////////////////////
	Slider();

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	/// 
	/// \param position          Position set to check box
	/// \param size              Size of check box
	/// \param thumbSize         Size of slider's thumb
	/// \param texture           Source texture
	/// \param spriteDefault     Sub-rectangle of the texture to assign to the default sprite
	/// \param spriteActive      Sub-rectangle of the texture to assign to the active sprite
	/// \param thumb             Sub-rectangle of the texture to assign to the thumb
	/// \param isVertical        true for vertical slider, false for horizontal slider
	/// \param min               Minimal accepted value
	/// \param max               Maximum accepted value
	/// \param value             Value to set to slider
	/// \param scrollMultiplier  Affects the amount of change on scrolling
	/// \param onValueChanged    Event raised when slider's value has changed
	/// \param onMaxValueChanged Event raised when slider's max value has changed
	/// \param enable            Enable this check box
	/// 
	////////////////////////////////////////////////////////////
	Slider(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& thumbSize, const sf::Texture& texture,
	const sf::IntRect& spriteDefault, const sf::IntRect& spriteActive, const sf::IntRect& thumb, bool isVertical,
	T min, T max, T value, float scrollMultiplier = 1.f, Event1<Slider<T>, T> onValueChanged = Event1<Slider<T>, T>(),
	Event1<Slider<T>, T> onMaxValueChanged = Event1<Slider<T>, T>(), bool enabled = true);

	////////////////////////////////////////////////////////////
	/// \brief Get slider's value
	/// 
	////////////////////////////////////////////////////////////
	T getValue() const;

	////////////////////////////////////////////////////////////
	/// \brief Set percentage
	///
	/// \param percentage New percentage
	/// \param raiseEvent Raise OnValueChanged event
	/// 
	////////////////////////////////////////////////////////////
	void setPercentage(float percentage, bool raiseEvent = true);

	////////////////////////////////////////////////////////////
	/// \brief Set value
	///
	/// \param value      New value
	/// \param raiseEvent Raise OnValueChanged event
	/// 
	////////////////////////////////////////////////////////////
	void setValue(T value, bool raiseEvent = true);

	////////////////////////////////////////////////////////////
	/// \brief Set max value
	///
	/// \param max        New max value
	/// \param raiseEvent Raise OnMaxValueChanged event
	/// 
	////////////////////////////////////////////////////////////
	void setMax(T max, bool raiseEvent = true);

	////////////////////////////////////////////////////////////
	/// \brief Draw the slider to a render target
	///
	/// \param target Render target to draw to
	/// \param states Current render states
	///
	////////////////////////////////////////////////////////////
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	////////////////////////////////////////////////////////////
	/// \brief Move thumb on mouse actions
	///
	////////////////////////////////////////////////////////////
	void moveThumb(float x, float y);

	////////////////////////////////////////////////////////////
	/// \brief Update thumb's position
	///
	////////////////////////////////////////////////////////////
	void updateThumbPosition();

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse wheel is scrolled 
	///        while the check box is being hovered
	/// 
	/// \param mouseWheelScroll Mouse wheel event parameters
	///
	////////////////////////////////////////////////////////////
	void onScrolledControl(sf::Event::MouseWheelScrollEvent mouseWheelScroll) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is pressed
	///
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	void onPressed(sf::Mouse::Button button, sf::Vector2f worldPos) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is pressed
	///        while the check box is being hovered
	/// 
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	void onClicked(sf::Mouse::Button button, sf::Vector2f worldPos) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when a mouse button is released
	/// 
	/// \param mouseButton Mouse button event parameters
	///
	////////////////////////////////////////////////////////////
	void onReleased(sf::Mouse::Button button, sf::Vector2f worldPos) override;

	////////////////////////////////////////////////////////////
	/// \brief Event triggered when the mouse cursor moves
	///        while the control is being hovered
	/// 
	/// \param mouseMove Mouse move event parameters
	///
	////////////////////////////////////////////////////////////
	void onMovedControl(sf::Event::MouseMoveEvent mouseMove) override;

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	Event1<Slider<T>, T> m_onValueChanged;    //!< Event raised when m_value changes
	Event1<Slider<T>, T> m_onMaxValueChanged; //!< Event raised when m_value changes
	SpriteComponent      m_thumb;             //!< Slider thumb
	sf::Vector2f         m_thumbSize;         //!< Thumb size
	bool                 m_isVertical;        //!< Enable vertical mode
	T                    m_min;               //!< Minimal accepted value
	T                    m_max;               //!< Maximum accepted value
	T                    m_range;             //!< Range of accepted values
	T                    m_value;             //!< Current value
	float                m_percentage;        //!< Value percentage
	float                m_scrollMultiplier;  //!< Affects the amount of change on scrolling
	bool                 m_isScrolling;       //!< Is user scrolling
};

using ByteSlider = Slider<uint8_t>;
using ShortSlider = Slider<uint16_t>;
using UintSlider = Slider<uint32_t>;
using IntSlider = Slider<int32_t>;
using FloatSlider = Slider<float_t>;

} //namespace le


#include "Slider.inl"
#endif // LEVEL_EDITOR_SLIDER_HPP