////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

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