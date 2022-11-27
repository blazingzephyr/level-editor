////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#ifndef EDITOR_ARITHMETIC_HPP
#define EDITOR_ARITHMETIC_HPP

#include <concepts>

template<typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;

#endif