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
#include "../menu/livechat/livechat.hpp"
#include "common.hpp"


int randomize(int od, int doo)
{
	return rand() % (doo - od + 1) + od;
}

void clslegacy()
{
	system("cls");
}

void cls()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = {0, 0};

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(h, &csbi )) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	FillConsoleOutputCharacter(h, ' ', cellCount, homeCoords, &count);
	FillConsoleOutputAttribute(h, csbi.wAttributes, cellCount, homeCoords, &count);

	/* Move the cursor home */
	SetConsoleCursorPosition(h, homeCoords);
}

void clsa()
{
	COORD pos = {0, 0};
	for (int i = 1; i < 4; i++)
	{
		pos.Y = i;
		SetConsoleCursorPosition(h, pos);
		std::cout << "                                                                                            ";
	}
	pos.X = 0; pos.Y = 0; SetConsoleCursorPosition(h, pos);
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

std::string utf8_substr(const std::string &str, int start, int length)
{
    int i,ix,j,realstart,reallength;
	auto strlen = [&i, &str]()
	{
		unsigned char c= str[i];
		if (c>=192 && c<=223) i+=1;
		else if (c>=224 && c<=239) i+=2;
		else if (c>=240 && c<=247) i+=3;
		else if (c>=248 && c<=255) throw 1;//invalid utf8
	};
	try
	{
		if (length==0) return "";
		if (start<0 || length <0)
		{
			//find j=utf8_strlen(str);
			for(j=0,i=0,ix=str.length(); i<ix; i+=1, j++)
			{
				strlen();
			}
			if (length !=INT_MAX && j+length-start<=0) return "";
			if (start  < 0 ) start+=j;
			if (length < 0 ) length=j+length-start;       
		}
	
		j=0,realstart=0,reallength=0;
		for(i=0,ix=str.length(); i<ix; i+=1, j++)
		{
			if (j==start) { realstart=i; }
			if (j>=start && (length==INT_MAX || j<=start+length)) { reallength=i-realstart; }
			strlen();
		}
		if (j==start) { realstart=i; }
		if (j>=start && (length==INT_MAX || j<=start+length)) { reallength=i-realstart; }
	}
	catch (const int &e)
	{
		return "";
	}
    return str.substr(realstart,reallength);
}

int GetCursorPosX()
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    GetConsoleScreenBufferInfo(h, &cbsi);
    return cbsi.dwCursorPosition.X;
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
