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

#ifndef LEVEL_EDITOR_IO_HPP
#define LEVEL_EDITOR_IO_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cassert>
#include <format>
#include <SFML/System/String.hpp>


namespace le
{
////////////////////////////////////////////////////////////
/// \brief Read a file and return its content.
///
/// \param path Full path to the file. If the path does not exist,
///			    the application crashes
/// 
/// \return Contents of the file
///
////////////////////////////////////////////////////////////
std::string readFile(std::string path);

////////////////////////////////////////////////////////////
/// \brief Write content to a file.
///
/// \param path    Full path to the file. If the path does not exist,
///			       the application crashes
/// 
/// \param content Contents to write to the file
///
////////////////////////////////////////////////////////////
void writeFile(std::string path, std::wstring content);

////////////////////////////////////////////////////////////
//void massert(bool expression, wchar_t* message)
//{
//	if (!expression)
//	{
//		_wassert(message, );
//	}
//}

} // namespace le


#endif // LEVEL_EDITOR_IO_HPP