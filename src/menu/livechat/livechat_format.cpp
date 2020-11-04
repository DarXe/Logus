// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//standard libraries
#include <string_view>
#include <windows.h>
#include <iostream>
#include <deque>


//header includes
#include "livechat_events.hpp"
#include <common.hpp>
#include <stopwatch.hpp>
#include <debug.hpp>
#include <var.hpp>
#include "livechat_format.hpp"

inline void LCFormat::Standard(std::string_view line)
{
	// [2020-11-03 19:40:09] [Output] : Niventill: ess 
	if (LCEvent::NormalMessage(line))
	{
		if (line.size() > gt)
			line.remove_prefix(gt);
		int textPos = line.find(":");

		SetConsoleTextAttribute(h, 10);
		if (textPos != std::string_view::npos)
		{
			std::cout << line.substr(0, textPos+1);
			SetConsoleTextAttribute(h, 15);
			std::cout << line.substr(textPos+1, std::string_view::npos) << '\n';
		}
		else
		{
			std::cout << line << '\n';
		}
		throw 1;
	}
}

inline void LCFormat::Pm(std::string_view line)
{
	// [2020-11-03 19:40:09] [Output] : * PW od Niventill: ess 
	// [2020-11-03 19:40:09] [Output] : -> Niventill: ess
	// [2020-11-03 19:40:09] [Output] : * PM from Niventill: ess 
	if (LCEvent::PmFrom(line) || LCEvent::PmTo(line))
	{
		if (line.size() > gt)
			line.remove_prefix(gt);
		int textPos = line.find(":");

		SetConsoleTextAttribute(h, 2);
		if (textPos != std::string_view::npos)
		{
			std::cout << line.substr(0, textPos+1);
			SetConsoleTextAttribute(h, 7);
			std::cout << line.substr(textPos+1, std::string_view::npos) << '\n';
		}
		else
		{
			std::cout << line << '\n';
		}
		throw 1;
	}
}

inline void LCFormat::Admin(std::string_view line)
{
	// [2020-10-28 17:42:08] [Output] : (ADMIN) Niventill: ess
	if (LCEvent::Admin(line, true))
	{
		if (line.size() > gt)
			line.remove_prefix(gt);
		int textPos = line.find(":");

		SetConsoleTextAttribute(h, 4);
		if (textPos != std::string_view::npos)
		{
			std::cout << line.substr(0, textPos+1);
			SetConsoleTextAttribute(h, 7);
			std::cout << line.substr(textPos+1, std::string_view::npos) << '\n';
		}
		else
		{
			std::cout << line << '\n';
		}
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
		if (line.size() > gt)
			line.remove_prefix(gt);

		SetConsoleTextAttribute(h, 6);
		std::cout << line << '\n';
		throw 1;
	}
}

inline void LCFormat::Info(std::string_view line)
{
	// [2020-10-28 17:42:08] [Output] : * typical wiadomosc
	if (line[gt] == '*')
	{
		if (line.size() > gt)
			line.remove_prefix(gt);

		SetConsoleTextAttribute(h, 14);
		std::cout << line << '\n';
		throw 1;
	}
}

inline void LCFormat::Input(std::string_view line)
{
	// [2020-11-03 23:06:48] [Input]  : disconnect
	if (LCEvent::Input(line))
	{
		if (line.size() > gt)
			line.remove_prefix(gt);

		SetConsoleTextAttribute(h, 12);
		std::cout << line << '\n';
		throw 1;
	}
}

inline void LCFormat::Team(std::string_view line)
{
	// [2020-10-28 17:42:08] [Output] : (ADMIN) Niventill: ess
	if (LCEvent::Team(line, true))
	{
		if (line.size() > gt)
			line.remove_prefix(gt);
		int textPos = line.find(":");

		SetConsoleTextAttribute(h, 2);
		if (textPos != std::string_view::npos)
		{
			std::cout << line.substr(0, textPos+1);
			SetConsoleTextAttribute(h, 7);
			std::cout << line.substr(textPos+1, std::string_view::npos) << '\n';
		}
		else
		{
			std::cout << line << '\n';
		}
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
	if (LCEvent::ContainsPhrase(line))
	{
		if (line.size() > gt)
			line.remove_prefix(gt);
		size_t pos = 0;
		size_t phrasePos = 0, len = 0;

		SetConsoleTextAttribute(h, 2);
		if (pos != std::string_view::npos)
		{
			//q(line);
			std::cout << line.substr(0, line.find(":")+1); //dark green to ":"
			line.remove_prefix(line.find(":")+1);
			while (true)
			{
				phrasePos = findPhrase(line, pos, len);
				if (phrasePos == std::string_view::npos)
					break;

				SetConsoleTextAttribute(h, 7); //gray
				std::cout << line.substr(pos, phrasePos - pos); //gray from last occurence (or ":")to phrase occurence

				SetConsoleTextAttribute(h, 9); //blue
				std::cout << line.substr(phrasePos, len); //blue
				pos = phrasePos + len;
			}
			SetConsoleTextAttribute(h, 7);
			std::cout << line.substr(pos, std::string::npos) << '\n';
		}
		else
		{
			std::cout << line << '\n';
		}
		throw 1;
	}
}

inline void LCFormat::Default(std::string_view line)
{
	if (line.size() > gt)
		line.remove_prefix(gt);

	SetConsoleTextAttribute(h, 10);
	std::cout << line << '\n';
	throw 1;
}

inline void LCFormat::Nothing(std::string_view line)
{
	if (line.size() > gt)
		line.remove_prefix(gt);

	std::cout << line << '\n';
	throw 1;
}

void LCFormat::ParseLines(const std::deque<std::string> &lastLines, const bool &timestamp)
{
	for (int i = 0; i < lastLines.size(); i++)
	{
		std::string_view line = lastLines.at(i);
		if (timestamp && line.size() > gt)
		{
			SetConsoleTextAttribute(h, 10);
			std::cout << line.substr(0, 21) << ' ';
		}
		if (LCEvent::Nicknames(line) || LCEvent::Transport(line) || LCEvent::Report(line) || LCEvent::TransfersFrom(line) || LCEvent::PmFrom(line) || LCEvent::ContainsPhrase(line) || LCEvent::Team(line, 0))
		{
			SetConsoleTextAttribute(h, 160);
			std::cout << "=>";
		}
		try
		{
			//LCFormat::Nothing(line);
			LCFormat::ContainsPhrase(line);
			LCFormat::Standard(line);
			LCFormat::Pm(line);
			LCFormat::Admin(line);
			LCFormat::Transfers(line);
			LCFormat::Info(line);
			LCFormat::Input(line);
			LCFormat::Team(line);

			LCFormat::Default(line);
		}
		catch(const int& e)
		{}
	}
}