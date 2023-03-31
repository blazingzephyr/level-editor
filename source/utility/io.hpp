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

#ifndef EDITOR_IO_HPP
#define EDITOR_IO_HPP
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <chrono>
#include <codecvt>
#include <ctime>
#include "io.hpp"
#include <io.h>
#include <iostream>
#include <fcntl.h>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <SFML/System/String.hpp>

std::string readFile(sf::String path);
void writeFile(std::string path, std::string content);
void assert(bool condition_expression, std::string source, size_t line, std::string message, int exit_code = -1);

std::wstring toWide(std::string str);
std::wstring toWide(std::string_view str);
std::string toAnsi(std::wstring str);

template <class TInput, class TOutput>
std::basic_string<TOutput, std::char_traits<TOutput>, std::allocator<TOutput>> convertTo(
	std::basic_string<TInput, std::char_traits<TInput>, std::allocator<TInput>> str,
	size_t(*base_str_len)(TInput const* base_str),
	errno_t(*converter)(size_t* dst_size, TOutput* dst, size_t src_size, TInput const* src, size_t count)
);

#endif