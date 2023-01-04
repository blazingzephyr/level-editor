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

#ifndef LEVEL_EDITOR_CALL_HPP
#define LEVEL_EDITOR_CALL_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <concepts>
#include <variant>

namespace le
{
////////////////////////////////////////////////////////////
/// \brief If all Inputs classes are derived from Expected or if both are the same class,
/// provides the member constant value equal to true. Otherwise value is false
///
////////////////////////////////////////////////////////////
template <typename Expected, typename... Input>
concept are_similar_v = (std::is_same_v<Expected, Input> || ...) || (std::is_base_of_v<Expected, Input> || ...);

////////////////////////////////////////////////////////////
/// \brief Alias for simplified std::visit call
///
/// \typeparam Expected Expected function type
/// \typeparam Result   Return type of the function
/// \typeparam Input    Input variant
/// 
////////////////////////////////////////////////////////////
template <typename Expected, typename Result, typename... Input>
requires are_similar_v<Expected, Input...>
Result visit(Result(Expected::* method)(), std::variant<Input...> variant)
{
	return std::visit(method, variant);
}


////////////////////////////////////////////////////////////
/// \brief Alias for simplified std::visit call
///
/// \typeparam Expected Expected function type
/// \typeparam Result   Return type of the function
/// \typeparam Input    Input variant
/// 
////////////////////////////////////////////////////////////
template <typename Expected, typename Result, typename... Input>
requires are_similar_v<Expected, Input...>
Result visit(Result(Expected::* method)() const, std::variant<Input...> variant)
{
	return std::visit(method, variant);
}


////////////////////////////////////////////////////////////
/// \brief Alias for simplified std::visit call
///
/// \typeparam Expected Expected function type
/// \typeparam Result   Return type of the function
/// \typeparam Input    Input variant
/// \typeparam Args     Function arguments
/// 
////////////////////////////////////////////////////////////
template <typename Expected, typename Result, typename... Input, typename... Args>
requires are_similar_v<Expected, Input...>
Result visit(Result(Expected::* method)(Args...), std::variant<Input...> variant, Args... args)
{
	return std::visit(method, variant, std::variant<Args...>(args...));
}


////////////////////////////////////////////////////////////
/// \brief Alias for simplified std::visit call
///
/// \typeparam Expected Expected function type
/// \typeparam Result   Return type of the function
/// \typeparam Input    Input variant
/// \typeparam Args     Function arguments
/// 
////////////////////////////////////////////////////////////
template <typename Expected, typename Result, typename... Input, typename... Args>
requires are_similar_v<Expected, Input...>
Result visit(Result(Expected::* method)(Args...) const, std::variant<Input...> variant, Args... args)
{
	return std::visit(method, variant, std::variant<Args...>(args...));
}

} // namespace le


#endif // LEVEL_EDITOR_CALL_HPP