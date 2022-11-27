////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_CONSTRUCT_CONTROL_HPP
#define EDITOR_CONSTRUCT_CONTROL_HPP

#include "control_constructor.hpp"
#include "../controls/button.hpp"
#include "../controls/check_box.hpp"
#include "../controls/combo_box.hpp"
#include "../controls/control.hpp"
#include "../controls/input_control.hpp"
#include "../controls/label.hpp"
#include "../controls/numeric_up_down.hpp"
#include "../controls/slider.hpp"
#include "../controls/table.hpp"
#include "../controls/text_control.hpp"

Control* constructControl(const ControlConstructor& constructor);

#endif