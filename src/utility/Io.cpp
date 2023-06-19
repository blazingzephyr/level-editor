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

#pragma warning(disable : 6386)
#pragma warning(disable : 6387)
#pragma warning(disable : 26815)

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Io.hpp"


namespace le
{
////////////////////////////////////////////////////////////
std::string readFile(std::string path)
{
	FILE* file = nullptr;
	fopen_s(&file, path.c_str(), "rb");
	//massert(file != nullptr, path.c_str() + " doesn't exist.");

	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);

	char* charBuffer = new char[size + 1];
	charBuffer[size] = '\0';
	//massert(charBuffer != NULL, "Buffer has been allocated incorrectly.");

	size_t result = fread(charBuffer, 1, size, file);
	fclose(file);
	//massert(result == size, "Unable to read from " + path.c_str());

	std::string buffer = std::string(charBuffer);
	delete[] charBuffer;
	return buffer;
}


////////////////////////////////////////////////////////////
void writeFile(std::string path, std::wstring content)
{
	FILE* file = nullptr;
	fopen_s(&file, path.c_str(), "w+");
	printf("%i", fwide(file, 1));

	if (file == 0)
	{
		assert(false);
	}
	

	const wchar_t* buffer = (content + L'\0').c_str();
	int result = fputws(buffer, file);

	if (result == EOF)
	{
		std::perror("fputws()"); // POSIX requires that errno is set
	}

	fclose(file);
}



} // namespace le