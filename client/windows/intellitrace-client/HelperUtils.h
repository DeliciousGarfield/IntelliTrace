#pragma once

#include <string>
#include <time.h>

class HelperUtils
{
public:
	static wchar_t* AnsiToUnicode(const char* szStr);
	static char* UnicodeToAnsi(const wchar_t* szStr);
	static std::wstring baseName(std::wstring path);
	static std::wstring appName(std::wstring baseName);
	static std::wstring localTime(time_t timestamp);
private:
	HelperUtils();
	~HelperUtils();
};

