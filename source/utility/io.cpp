////////////////////////////////////////////////////////////
//
// MISSING COPYRIGHT
// 
////////////////////////////////////////////////////////////

#pragma warning(disable : 6386)
#pragma warning(disable : 6387)
#include "io.hpp"

using std::allocator;
using std::basic_string;
using std::char_traits;
using std::codecvt_utf8;
using std::format;
using std::string;
using std::string_view;
using std::to_string;
using std::wstring;
using std::wstring_convert;
using std::chrono::system_clock;
using std::chrono::time_point;

std::locale wlocale = std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>);
string readFile(sf::String path)
{
	FILE* file = nullptr;
	fopen_s(&file, path.toAnsiString().data(), "rb");
	assert(file != 0, "io.hpp", 39, "ERROR: File \"" + path + "\" doesn't exist.", 256);

	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	rewind(file);

	char* char_buffer = new char[size + 1];
	char_buffer[size] = '\0';
	assert(char_buffer != NULL, "io.hpp", 46, "ERROR: 'char* buffer' has been incorrectly allocated.", 257);

	size_t result = fread(char_buffer, 1, size, file);
	fclose(file);
	assert(result == size, "io.hpp", 50, "ERROR: Unable to read from \"" + path + "\".", 258);

	string buffer = string(char_buffer);
	delete[] char_buffer;
	return buffer;

}

void writeFile(string path, string content)
{
	FILE* file = nullptr;
	fopen_s(&file, path.data(), "w+");

	const char* buffer = content.data();
	size_t size = content.size();

	size_t result = fwrite(buffer, 1, size, file);
	fclose(file);
	assert(result == size, "io.hpp", 50, "ERROR: Unable to write to \"" + path + "\".", 258);
}

void assert(bool condition_expression, string source, size_t line, string message, int exit_code)
{
	if (!condition_expression)
	{
		FILE* log = nullptr;
		fopen_s(&log, "crash.log", "a+");

		time_point now = system_clock::now();
		string buffer = "\n\n" + format("{:%d-%m-%Y %H:%M:%OS}", now) +
			"\n" + source +
			"\n" + "Line " + to_string(line) +
			"\n" + "Code " + format("{:#08x}", exit_code) +
			"\n" + message;

		const char* char_buffer = buffer.data();
		fwrite(char_buffer, 1, strlen(char_buffer), log);

		fclose(log);
		exit(exit_code);
	}
}

wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;

wstring toWide(string str)
{
	return converter.from_bytes(str);
}

wstring toWide(string_view str)
{
	return converter.from_bytes(str.data());
}

string toAnsi(wstring wstr)
{
	return converter.to_bytes(wstr);
}