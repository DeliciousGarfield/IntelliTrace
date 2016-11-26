#include "HelperUtils.h"
#include <windows.h>
#include <sstream>

wchar_t* HelperUtils::AnsiToUnicode(const char* szStr)
{
	int nLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szStr, -1, NULL, 0);
	if (nLen == 0)
	{
		return NULL;
	}
	wchar_t* pResult = new wchar_t[nLen];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szStr, -1, pResult, nLen);
	return pResult;
}

char* HelperUtils::UnicodeToAnsi(const wchar_t* szStr)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
	{
		return NULL;
	}
	char* pResult = new char[nLen];
	WideCharToMultiByte(CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL);
	return pResult;
}

std::wstring HelperUtils::baseName(std::wstring path)
{
	std::size_t pos = path.rfind('\\');

	if (pos == std::string::npos)
		return path;
	else
		return path.substr(path.rfind('\\') + 1);
}

std::wstring HelperUtils::appName(std::wstring baseName)
{
	return baseName.substr(0, baseName.rfind(TEXT(".exe")));
}

std::wstring HelperUtils::localTime(time_t timestamp)
{
	std::wostringstream ss;

	struct tm localtime;
	localtime_s(&localtime, &timestamp);

	CHAR format[256];
	strftime(format, sizeof(format) / sizeof(CHAR), "%H:%M:%S", &localtime);
	ss << format;

	return ss.str();
}