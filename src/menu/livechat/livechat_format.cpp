// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//standard libraries
#include <string_view>
#include <windows.h>
#include <iostream>
#include <conio.h>


//header includes
#include "livechat_events.hpp"
#include "livechat_cmd.hpp"
#include <common.hpp>
#include <var.hpp>
#include "livechat_format.hpp"


//static variables
static short lastcolor;

inline bool LCFormat::isNewLine(std::string_view line)
{
	return (line[0] == '[' && line[5] == '-' && line[8] == '-' && line[14] == ':');
}

inline void LCFormat::Standard(std::string_view line)
{
	// [2020-11-03 19:40:09] [Output] : Niventill: ess 
	if (LCEvent::NormalMessage(line))
	{
		if (isNewLine(line))
			line.remove_prefix(gt);
		int textPos = line.find(":");

		LCFormat::SetColor(10);
		if (textPos != std::string_view::npos)
		{
			std::cout << line.substr(0, textPos+1);
			LCFormat::SetColor(15);
			std::cout << line.substr(textPos+1, std::string_view::npos);
		}
		else
			std::cout << line;

		throw 1;
	}
}

inline void LCFormat::NonStandard(std::string_view line)
{
	if (LCEvent::PmFrom(line) || LCEvent::PmTo(line) || LCEvent::Team(line, true) || LCEvent::CB(line) || LCEvent::Admin(line, true))
	{
		line.remove_prefix(gt);
		int textPos = line.find(":");

		LCFormat::SetColor(2);
		if (textPos != std::string_view::npos)
		{
			std::cout << line.substr(0, textPos+1);
			LCFormat::SetColor(7);
			std::cout << line.substr(textPos+1, std::string_view::npos);
		}
		else
			std::cout << line;

		throw 1;
	}
}

inline void LCFormat::Transfers(std::string_view line)
{
	//[2020-08-09 21:06:56] [Output] : Gracz SpookyTank przelał tobie 1500$.
	//[2020-08-30 16:35:09] [Output] : Player DarXe transferred to you $1.
	//[2020-08-29 15:34:28] [Output] : Przelałeś 1000000$ graczowi DarXe.
	//[2020-08-30 16:34:52] [Output] : You gave $1 to player DarXe.
	if (LCEvent::TransfersFrom(line) || LCEvent::TransfersTo(line))
	{
		if (isNewLine(line))
			line.remove_prefix(gt);

		LCFormat::SetColor(6);
		std::cout << line;

		throw 1;
	}
}

inline void LCFormat::Info(std::string_view line)
{
	// [2020-10-28 17:42:08] [Output] : * typical wiadomosc
	if (line[gt] == '*')
	{
		if (isNewLine(line))
			line.remove_prefix(gt);

		LCFormat::SetColor(14);
		std::cout << line;

		throw 1;
	}
}

inline void LCFormat::Input(std::string_view line)
{
	// [2020-11-03 23:06:48] [Input]  : disconnect
	if (LCEvent::Input(line))
	{
		if (LCCmdEvent::CheckCommandEvents(line))
			LCFormat::SetColor(4);
		else
			LCFormat::SetColor(12);
		if (isNewLine(line))
			line.remove_prefix(gt);
		std::cout << line;

		throw 1;
	}
}

static size_t findPhrase(std::string_view line, const size_t &pos, size_t &len)
{
	for(int i = pos; i < line.size(); i++)
	{
		for (int a = 0; a < phrases.size(); a++)
		{
			if (line.substr(i, phrases[a].size()) == phrases[a])
			{
				len = phrases[a].size();
				return i;		
			}
		}
	}
	return std::string_view::npos;
}

inline void LCFormat::ContainsPhrase(std::string_view line)
{
	if (LCEvent::ContainsPhraseFormat(line))
	{
		if (isNewLine(line))
			line.remove_prefix(gt);
		size_t pos = 0, len = 0;
		LCFormat::SetColor(2);
		
		//q(line);
		std::cout << line.substr(0, line.find(":")+1); //dark green to ":"
		line.remove_prefix(line.find(":")+1);
		while (true)
		{
			size_t phrasePos = findPhrase(line, pos, len);
			if (phrasePos == std::string_view::npos)
				break;

			LCFormat::SetColor(7); //gray
			std::cout << line.substr(pos, phrasePos - pos); //gray from last occurence (or ":")to phrase occurence

			LCFormat::SetColor(9); //blue
			std::cout << line.substr(phrasePos, len); //blue
			pos = phrasePos + len;
		}
		LCFormat::SetColor(7);
		std::cout << line.substr(pos, std::string::npos);

		throw 1;
	}
}

inline void LCFormat::Default(std::string_view line)
{
	if (isNewLine(line))
	{
		line.remove_prefix(gt);
		LCFormat::SetColor(10);
	}
	else
		LCFormat::SetColor(lastcolor);
	std::cout << line;

	throw 1;
}

inline void LCFormat::Nothing(std::string_view line)
{
	if (isNewLine(line))
		line.remove_prefix(gt);

	std::cout << line;

	throw 1;
}

inline void LCFormat::SetColor(const short &color)
{
	SetConsoleTextAttribute(h, color);
	lastcolor = color;
}

void LCFormat::ParseLines(const std::deque<std::string> &lastLines, std::deque<int> &lastLinesSize, const bool &timestamp)
{
	for (int i = 0; i < lastLines.size(); i++)
	{
		std::string_view line = lastLines.at(i);
		if (isspace(line.back()))
			line.remove_suffix(1);
		if (timestamp && isNewLine(line))
		{
			LCFormat::SetColor(10);
			std::cout << '[' << line.substr(12, 10);
		}
		bool notif = notifCheck(line);
		if (notif)
		{
			LCFormat::SetColor(160);
			std::cout << "=>";
		}
		try
		{
			//LCFormat::Nothing(line);
			LCFormat::ContainsPhrase(line);
			LCFormat::Standard(line);
			LCFormat::NonStandard(line);
			LCFormat::Transfers(line);
			LCFormat::Info(line);
			LCFormat::Input(line);

			LCFormat::Default(line);
		}
		catch(const int& e)
		{
			//q(lastLinesSize[i]); getch();
			int size = GetCursorPosX();
			int offset = lastLinesSize[i] - size;
			if (offset > 0)
			{
				std::string d(offset, ' ');
				std::cout << d;
			}
			std::cout << '\n';
			lastLinesSize[i] = size;
			/*COORD pos; pos.X = lastLinesSize[i]; pos.Y = i;
			SetConsoleCursorPosition(h, pos); std::cout << " << size: " << lastLinesSize[i] << '\n';*/
		}
	}
}