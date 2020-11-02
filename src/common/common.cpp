// Copyright © 2018-2020  DarXe
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//standard libraries
#include <iostream>
#include <sstream>
#include <fstream>
#include <conio.h>
#include <codecvt>
#include <iomanip>
#include <thread>
#include <windows.h>


//header includes
#include "var.hpp"
#include "common.hpp"


int randomize(int od, int doo)
{
	return rand() % (doo - od + 1) + od;
}

void cls()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition( hStdOut, homeCoords );
}

std::string getCurrentTime()
{
	auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "[%Y-%m-%d %H:%M:%S] ");
	return ss.str();
}

std::string getMTALocation()
{
	size_t bufferSize = 0xFFF;
#ifdef _WIN64
	std::wstring mtaRegKey = L"SOFTWARE\\WOW6432Node\\Multi Theft Auto: San Andreas All\\1.5";
#elif _WIN32
	std::wstring mtaRegKey = L"SOFTWARE\\Multi Theft Auto: San Andreas All\\1.5";
#endif
	std::wstring valueBuf;
	valueBuf.resize(bufferSize);
	auto cbData = static_cast<DWORD>(bufferSize * sizeof(wchar_t));
	auto rc = RegGetValueW(
		HKEY_LOCAL_MACHINE,
		mtaRegKey.c_str(),
		L"Last Run Location",
		RRF_RT_REG_SZ,
		nullptr,
		static_cast<void *>(valueBuf.data()),
		&cbData);
	if (rc == ERROR_SUCCESS)
	{
		cbData /= sizeof(wchar_t);
		valueBuf.resize(static_cast<size_t>(cbData - 1));
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
		return conv.to_bytes(valueBuf);
	}
	return "ERROR";
}

std::string getNickFromMTAConfig()
{
	std::ifstream check(mtaLocation + "\\MTA\\config\\coreconfig.xml", std::ios::in | std::ios::binary);
	if (!check.good())
	{
		check.close();
		return "";
	}
	else
	{
		std::string tempnick, newnick;
		for (int i = 0; i < 3; i++)
			getline(check, tempnick);
		int delim, delim1;

		delim = tempnick.find("<nick>");
		delim1 = tempnick.find("</nick>");
		check.close();
		return tempnick.substr(delim + 6, delim1 - delim - 6);
	}
	return "";
}

char wybor()
{
	engLang ? std::cout << "\n Choose an option (press a key)" : std::cout << "\n Wybierz opcje (wciśnij klawisz)";
	return getch();
}

void def()
{
	cls();
	engLang ? std::cout << "\a (INFO) Option not found!\n" : std::cout << "\a (INFO) Nie ma takiej opcji!\n";
}

std::string removeSpaces(std::string &line)
{
	if (isspace(line[0]))
		line.erase(0, 1);
	if (isspace(line.back()))
		line.erase(line.size() - 1);
	return line;
}

void toClipboard(const std::string &s)
{
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
	if (!hg)
	{
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

int power(int x, int y)
{
	int z = 1;
	for (int i = 0; i < y; i++)
	{
		z *= x;
	}
	return z;
}

std::string round(const long double x, const int dec)
{
    std::stringstream ss;
    ss << std::fixed;
    ss.precision(dec);
    ss << x;
    return ss.str();
}

/*
bool fNick(string &wyraz)
{
	for(int i = 0; i<nicknames.size(); i++)
	{
		s_temp = nicknames.at(i);
		leng = s_temp.length() - 1;
		//<nick>: message
		if(line[gt+leng]==s_temp[leng]&&line[gt+leng-1]==s_temp[leng-1]&&line[gt+leng-2]==s_temp[leng-2])
			return 1;
		//* <nick> joined
		if(line[gt]=='*'&&line[gt+leng+2]==s_temp[leng]&&line[gt+leng+1]==s_temp[leng-1]&&line[gt+leng]==s_temp[leng-2])
			return 1;
		//Gracz <nick> <action>
		if(line[gt+5]==' '&&line[gt+leng+6]==s_temp[leng]&&line[gt+leng+5]==s_temp[leng-1]&&line[gt+leng+4]==s_temp[leng-2])
			return 1;
	}
	return 0;
}
*/
