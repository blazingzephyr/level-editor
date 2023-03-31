// MIT License
// 
// Copyright (c) 2022 ZaBlazzingZephyr
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

#include "construct_control.hpp"

Control* constructControl(const ControlConstructor& constructor)
{
	if (constructor.control_type == "Button")
	{
		return new Button(
			constructor.window,
			constructor.intended_resolution,
			constructor.strings,
			constructor.theme,
			constructor.handler,
			constructor.text_theme,
			constructor.position,
			constructor.size,
			constructor.bg_rect,
			constructor.bg_active_rect,
			constructor.text,
			constructor.action_empty,
			[]() {},
			constructor.min_y_position,
			constructor.visible,
			constructor.enabled
		);
	}
	else if (constructor.control_type == "CheckBox")
	{
		return new CheckBox(
			constructor.window,
			constructor.intended_resolution,
			constructor.strings,
			constructor.theme,
			constructor.handler,
			constructor.position,
			constructor.size,
			constructor.bg_rect,
			constructor.bg_active_rect,
			constructor.action_boolean,
			constructor.checked,
			constructor.min_y_position,
			constructor.visible,
			constructor.enabled
		);
	}
	else if (constructor.control_type == "ComboBox")
	{
		return new ComboBox(
			constructor.window,
			constructor.intended_resolution,
			constructor.strings,
			constructor.theme,
			constructor.handler,
			constructor.text_theme,
			constructor.position,
			constructor.size,
			constructor.bg_rect,
			constructor.bg_active_rect,
			constructor.button_offset,
			constructor.button_size,
			constructor.first_button_bg_rect,
			constructor.first_button_bg_focused_rect,
			constructor.second_button_bg_rect,
			constructor.second_button_bg_focused_rect,
			constructor.items,
			constructor.index,
			constructor.scroll_time,
			constructor.action_numeric,
			constructor.min_y_position,
			constructor.visible,
			constructor.enabled
		);
	}
	else if (constructor.control_type == "Control")
	{
		return new Control(
			constructor.window,
			constructor.intended_resolution,
			constructor.strings,
			constructor.theme,
			constructor.handler,
			constructor.position,
			constructor.size,
			constructor.bg_rect,
			constructor.bg_active_rect,
			constructor.min_y_position,
			constructor.visible,
			constructor.enabled
		);
	}
	else if (constructor.control_type == "InputControl")
	{
		return new InputControl(
			constructor.window,
			constructor.intended_resolution,
			constructor.strings,
			constructor.theme,
			constructor.handler,
			constructor.text_theme,
			constructor.input_control_theme,
			constructor.position,
			constructor.size,
			constructor.bg_rect,
			constructor.bg_active_rect,
			constructor.text,
			constructor.action_string,
			constructor.min_y_position,
			constructor.visible,
			constructor.enabled
		);
	}
	else if (constructor.control_type == "Label")
	{
		return new Label(
			constructor.window,
			constructor.intended_resolution,
			constructor.strings,
			constructor.theme,
			constructor.handler,
			constructor.text_theme,
			constructor.position,
			constructor.size,
			constructor.text,
			constructor.rotation_angle,
			constructor.enabled
		);
	}
	else if (constructor.control_type == "ByteNumeric")
	{
		return new ByteNumeric(
			constructor.window,
			constructor.intended_resolution,
			constructor.strings,
			constructor.theme,
			constructor.handler,
			constructor.text_theme,
			constructor.input_control_theme,
			constructor.position,
			constructor.size,
			constructor.bg_rect,
			constructor.bg_active_rect,
			constructor.button_size,
			constructor.first_button_bg_rect,
			constructor.first_button_bg_focused_rect,
			constructor.second_button_bg_rect,
			constructor.second_button_bg_focused_rect,
			constructor.min,
			constructor.max,
			constructor.step,
			constructor.value,
			constructor.action_numeric,
			constructor.scroll_time,
			constructor.min_y_position,
			constructor.visible,
			constructor.enabled
		);
	}
	else if (constructor.control_type == "UshortNumeric")
	{
		return new UshortNumeric(
			constructor.window,
			constructor.intended_resolution,
			constructor.strings,
			constructor.theme,
			constructor.handler,
			constructor.text_theme,
			constructor.input_control_theme,
			constructor.position,
			constructor.size,
			constructor.bg_rect,
			constructor.bg_active_rect,
			constructor.button_size,
			constructor.first_button_bg_rect,
			constructor.first_button_bg_focused_rect,
			constructor.second_button_bg_rect,
			constructor.second_button_bg_focused_rect,
			constructor.min,
			constructor.max,
			constructor.step,
			constructor.value,
			constructor.action_numeric,
			constructor.scroll_time,
			constructor.min_y_position,
			constructor.visible,
			constructor.enabled
		);
	}
	else if (constructor.control_type == "UintNumeric")
	{
		return new UintNumeric(
			constructor.window,
			constructor.intended_resolution,
			constructor.strings,
			constructor.theme,
			constructor.handler,
			constructor.text_theme,
			constructor.input_control_theme,
			constructor.position,
			constructor.size,
			constructor.bg_rect,
			constructor.bg_active_rect,
			constructor.button_size,
			constructor.first_button_bg_rect,
			constructor.first_button_bg_focused_rect,
			constructor.second_button_bg_rect,
			constructor.second_button_bg_focused_rect,
			constructor.min,
			constructor.max,
			constructor.step,
			constructor.value,
			constructor.action_numeric,
			constructor.scroll_time,
			constructor.min_y_position,
			constructor.visible,
			constructor.enabled
		);
	}
	else if (constructor.control_type == "IntNumeric")
	{
		return new IntNumeric(
			constructor.window,
			constructor.intended_resolution,
			constructor.strings,
			constructor.theme,
			constructor.handler,
			constructor.text_theme,
			constructor.input_control_theme,
			constructor.position,
			constructor.size,
			constructor.bg_rect,
			constructor.bg_active_rect,
			constructor.button_size,
			constructor.first_button_bg_rect,
			constructor.first_button_bg_focused_rect,
			constructor.second_button_bg_rect,
			constructor.second_button_bg_focused_rect,
			constructor.min,
			constructor.max,
			constructor.step,
			constructor.value,
			constructor.action_numeric,
			constructor.scroll_time,
			constructor.min_y_position,
			constructor.visible,
			constructor.enabled
		);
	}
	else if (constructor.control_type == "FloatNumeric")
	{
		return new FloatNumeric(
			constructor.window,
			constructor.intended_resolution,
			constructor.strings,
			constructor.theme,
			constructor.handler,
			constructor.text_theme,
			constructor.input_control_theme,
			constructor.position,
			constructor.size,
			constructor.bg_rect,
			constructor.bg_active_rect,
			constructor.button_size,
			constructor.first_button_bg_rect,
			constructor.first_button_bg_focused_rect,
			constructor.second_button_bg_rect,
			constructor.second_button_bg_focused_rect,
			constructor.min,
			constructor.max,
			constructor.step,
			constructor.value,
			constructor.action_numeric,
			constructor.scroll_time,
			constructor.min_y_position,
			constructor.visible,
			constructor.enabled
		);
	}
	else if (constructor.control_type == "DoubleNumeric")
	{
		return new DoubleNumeric(
			constructor.window,
			constructor.intended_resolution,
			constructor.strings,
			constructor.theme,
			constructor.handler,
			constructor.text_theme,
			constructor.input_control_theme,
			constructor.position,
			constructor.size,
			constructor.bg_rect,
			constructor.bg_active_rect,
			constructor.button_size,
			constructor.first_button_bg_rect,
			constructor.first_button_bg_focused_rect,
			constructor.second_button_bg_rect,
			constructor.second_button_bg_focused_rect,
			constructor.min,
			constructor.max,
			constructor.step,
			constructor.value,
			constructor.action_numeric,
			constructor.scroll_time,
			constructor.min_y_position,
			constructor.visible,
			constructor.enabled
		);
	}
	else if (constructor.control_type == "ByteSlider")
	{
		return new ByteSlider(
			constructor.window,
			constructor.intended_resolution,
			constructor.strings,
			constructor.theme,
			constructor.handler,
			constructor.position,
			constructor.size,
			constructor.bg_rect,
			constructor.bg_active_rect,
			constructor.thumb_size,
			constructor.thumb_rect,
			constructor.min,
			constructor.max,
			constructor.value,
			constructor.scroll_multiplier,
			constructor.action_numeric,
			constructor.vertical,
			constructor.min_y_position,
			constructor.visible,
			constructor.enabled
		);
	}
	else if (constructor.control_type == "UshortSlider")
	{
		return new UshortSlider(
			constructor.window,
			constructor.intended_resolution,
			constructor.strings,
			constructor.theme,
			constructor.handler,
			constructor.position,
			constructor.size,
			constructor.bg_rect,
			constructor.bg_active_rect,
			constructor.thumb_size,
			constructor.thumb_rect,
			constructor.min,
			constructor.max,
			constructor.value,
			constructor.scroll_multiplier,
			constructor.action_numeric,
			constructor.vertical,
			constructor.min_y_position,
			constructor.visible,
			constructor.enabled
		);
	}
	else if (constructor.control_type == "UintSlider")
	{
		return new UintSlider(
			constructor.window,
			constructor.intended_resolution,
			constructor.strings,
			constructor.theme,
			constructor.handler,
			constructor.position,
			constructor.size,
			constructor.bg_rect,
			constructor.bg_active_rect,
			constructor.thumb_size,
			constructor.thumb_rect,
			constructor.min,
			constructor.max,
			constructor.value,
			constructor.scroll_multiplier,
			constructor.action_numeric,
			constructor.vertical,
			constructor.min_y_position,
			constructor.visible,
			constructor.enabled
		);
	}
	else if (constructor.control_type == "IntSlider")
	{
		return new IntSlider(
			constructor.window,
			constructor.intended_resolution,
			constructor.strings,
			constructor.theme,
			constructor.handler,
			constructor.position,
			constructor.size,
			constructor.bg_rect,
			constructor.bg_active_rect,
			constructor.thumb_size,
			constructor.thumb_rect,
			constructor.min,
			constructor.max,
			constructor.value,
			constructor.scroll_multiplier,
			constructor.action_numeric,
			constructor.vertical,
			constructor.min_y_position,
			constructor.visible,
			constructor.enabled
		);
	}
	else if (constructor.control_type == "FloatSlider")
	{
		return new FloatSlider(
			constructor.window,
			constructor.intended_resolution,
			constructor.strings,
			constructor.theme,
			constructor.handler,
			constructor.position,
			constructor.size,
			constructor.bg_rect,
			constructor.bg_active_rect,
			constructor.thumb_size,
			constructor.thumb_rect,
			constructor.min,
			constructor.max,
			constructor.value,
			constructor.scroll_multiplier,
			constructor.action_numeric,
			constructor.vertical,
			constructor.min_y_position,
			constructor.visible,
			constructor.enabled
		);
	}
	else if (constructor.control_type == "DoubleSlider")
	{
		return new DoubleSlider(
			constructor.window,
			constructor.intended_resolution,
			constructor.strings,
			constructor.theme,
			constructor.handler,
			constructor.position,
			constructor.size,
			constructor.bg_rect,
			constructor.bg_active_rect,
			constructor.thumb_size,
			constructor.thumb_rect,
			constructor.min,
			constructor.max,
			constructor.value,
			constructor.scroll_multiplier,
			constructor.action_numeric,
			constructor.vertical,
			constructor.min_y_position,
			constructor.visible,
			constructor.enabled
		);
	}
	else if (constructor.control_type == "Table")
	{
		return new Table(
			constructor.window,
			constructor.intended_resolution,
			constructor.strings,
			constructor.theme,
			constructor.handler,
			constructor.text_theme,
			constructor.position,
			constructor.size,
			constructor.bg_rect,
			constructor.bg_active_rect,
			constructor.create_button_position,
			constructor.create_button_size,
			constructor.create_button_bg,
			constructor.create_button_bg_focused,
			constructor.create_button_text,
			constructor.slider_position,
			constructor.slider_size,
			constructor.slider_bg,
			constructor.slider_bg_focused,
			constructor.slider_thumb_size,
			constructor.slider_thumb,
			constructor.scroll_multiplier,
			constructor.row_offset,
			constructor.row_constructors,
			*constructor.row_erase_button,
			constructor.min_y_position,
			constructor.visible,
			constructor.enabled
		);
	}
	else
	{
		return nullptr;
	}
}