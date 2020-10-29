// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//standard libraries
#include <windows.h>
#include <sstream>
#include <fstream>
#include <vector>


//header includes
#include <var.hpp>
#include <config.hpp>
#include <common.hpp>
#include "../addons/loglookup.hpp"
#include <proc.hpp>
#include "livechat_actions.hpp"
#include "livechat_cmd.hpp"


//foward declarations
void serverConnect(); //from proc.hpp

void LCCommand::CheckCommandInput(const std::string &line)
{
	Reconnect(line);
	Quit(line);
	StartTimer(line);
	SetNick(line);
	SetTrack(line);
	SetTimer(line);
	AddNickname(line);
	DelNickname(line);
	SetMoney(line);
	SetCourses(line);
	Reset(line);
	HardReset(line);
	FindTransfers(line);
	FindWord(line);
	FindConfig(line);
	FindConsoleLog(line);
	FindLogusLog(line);
}

bool LCCommand::Reconnect(const std::string &line)
{
	if (line.find("[Input]  : rr") != std::string::npos)
	{
		serverConnect();
		Beep(dzwiekGlowny, 150);
		return 1;
	}
	return 0;
}

bool LCCommand::Quit(const std::string &line)
{
	if (line.find("[Input]  : quit ") != std::string::npos)
	{
		closeLogus(((engLang)?"Closing MTA and Logus":"Zamykanie MTA i programu"));
		return 1;
	}
	return 0;
}

bool LCCommand::StartTimer(const std::string &line)
{
	if (line.find("[Input]  : tt") != std::string::npos)
	{
		mainTimer.startCounter();
		int temp;
		temp = czas * 1000 / 1.1;
		temp = czas * 1000 - temp;
		mainTimer.m_timer -= temp;
	}
	else if (line.find("[Input]  : t\'") != std::string::npos)
		mainTimer.startCounter();
	return 0;
}

bool LCCommand::SetNick(const std::string &line)
{
	if (line.find("[Input]  : nick ") != std::string::npos)
	{ //[2020-08-30 04:03:24] [Input]  : nick Niventill
		std::string tempnick = line.substr(gt, std::string::npos);
		std::istringstream ss(tempnick);
		ss >> tempnick >> tempnick;
		nick = tempnick;
		Beep(dzwiekGlowny, 150);
		return 1;
	}
	return 0;
}

short LCCommand::SetTrack(const std::string &line)
{
	if (line.find("[Input]  : set tr") != std::string::npos) //set tr xx //SET TRACK
	{
		if (line[gt + 7] == '0')
		{
			trackId = 0;
			Beep(dzwiekGlowny, 150);
			return 1;
		}
		else if (line[gt + 7] == 'a')
		{
			if (line[gt + 8] == '1')
				trackId = 1;
			else
				trackId = 3;
			Beep(dzwiekGlowny, 150);
			return 1;
		}
		else
		{
			if (line[gt + 8] == '1')
				trackId = 4;
			else
				trackId = 2;
			Beep(dzwiekGlowny, 150);
			return 1;
		}
	}
	return 0;
}

bool LCCommand::SetTimer(const std::string &line)
{
	if (line.find("[Input]  : set t ") != std::string::npos) //[Input]  : set t 00:00
	{
		std::string temptimer;
		int minutes, seconds, delim;
		delim = line.find("[Input]  : set t ");
		temptimer = line.substr(delim + 17, std::string::npos);
		sscanf_s(temptimer.c_str(), "%2d:%2d", &minutes, &seconds);
		minutes *= 60000;
		seconds *= 1000;
		minutes += seconds;
		mainTimer.start(minutes);
		return 1;
	}
	return 0;
}

bool LCCommand::AddNickname(const std::string &line)
{
	if (line.find("[Input]  : nickdb add ") != std::string::npos)
	{
		std::string tempn;
		int delim;
		delim = line.find("[Input]  : nickdb add ");
		tempn = line.substr(delim + 22, std::string::npos);
		tempn = removeSpaces(tempn);
		nicknames.push_back(tempn);
		saveConfig(0);
		Beep(dzwiekGlowny, 150);
		return 1;
	}
	return 0;
}

bool LCCommand::DelNickname(const std::string &line)
{
	if (line.find("[Input]  : nickdb del ") != std::string::npos)
	{
		std::string tempn;
		int delim;
		delim = line.find("[Input]  : nickdb del ");
		tempn = line.substr(delim + 22, std::string::npos);
		tempn = removeSpaces(tempn);
		for (int i = 0; i < nicknames.size(); i++)
		{
			if (nicknames.at(i) == tempn)
				nicknames.erase(nicknames.begin() + i);
		}
		saveConfig(0);
		Beep(dzwiekGlowny, 150);
		return 1;
	}
	return 0;
}

bool LCCommand::SetMoney(const std::string &line)
{
	if (line.find("[Input]  : set m ") != std::string::npos)
	{
		int delim = line.find("[Input]  : set m ");
		std::string tmoney = line.substr(delim + 16, std::string::npos);
		money = stoi(tmoney);
		saveConfig(0);
		Beep(dzwiekGlowny, 150);
		return 1;
	}
	return 0;
}

bool LCCommand::SetCourses(const std::string &line)
{
	if (line.find("[Input]  : set c ") != std::string::npos)
	{
		int delim = line.find("[Input]  : set c ");
		std::string tcourses = line.substr(delim + 17, std::string::npos);
		courses = stoi(tcourses);
		saveConfig(0);
		Beep(dzwiekGlowny, 150);
		return 1;
	}
	return 0;
}

bool LCCommand::HardReset(const std::string &line)
{
	if (line.find("[Input]  : set hre") != std::string::npos) //reset kursow /set re
	{
		money = 0;
		courses = 0;
		minsalary = 0;
		maxsalary = 0;
		saveConfig(0);
		Beep(dzwiekGlowny, 150);
		return 1;
	}
	return 0;
}

bool LCCommand::Reset(const std::string &line)
{
	if (line.find("[Input]  : set re") != std::string::npos) //reset kursow /set re
	{
		money = 0;
		courses = 0;
		saveConfig(0);
		Beep(dzwiekGlowny, 150);
		return 1;
	}
	return 0;
}

bool LCCommand::FindTransfers(const std::string &line)
{
	if (line.find("[Input]  : find tf") !=std::string::npos)
	{
		checkLogTransfersAll(LiveChat);
		Beep(dzwiekGlowny, 150);
		return 1;
	}
	return 0;
}

bool LCCommand::FindWord(const std::string &line)
{
	if (line.find("[Input]  : find Word ") != std::string::npos)
	{
		int delim = line.find("[Input]  : find Word ");
		std::string phrase = line.substr(delim + 21, std::string::npos);
		removeSpaces(phrase);
		findWordAll_CaseSensitive(phrase);
		Beep(dzwiekGlowny, 150);
		return 1;
	}
	else if (line.find("[Input]  : find word ") != std::string::npos)
	{
		int delim = line.find("[Input]  : find word ");
		std::string phrase = line.substr(delim + 21, std::string::npos);
		removeSpaces(phrase);
		findWordAll_NonCaseSensitive(phrase);
		Beep(dzwiekGlowny, 150);
	}
	return 0;
}

bool LCCommand::FindConfig(const std::string &line)
{
	if (line.find("[Input]  : find cfg") !=std::string::npos)
	{
		saveConfig(0);
		ShellExecute(0, 0, "logus.ini", 0, 0, SW_SHOW);
		Beep(dzwiekGlowny, 150);
		return 1;
	}
	return 0;
}

bool LCCommand::FindConsoleLog(const std::string &line)
{
	if (line.find("[Input]  : find console.log") !=std::string::npos)
	{
		saveConfig(0);
		ShellExecute(0, 0, consoleLogPath.c_str(), 0, 0, SW_SHOW);
		Beep(dzwiekGlowny, 150);
		return 1;
	}
	return 0;
}

bool LCCommand::FindLogusLog(const std::string &line)
{
	if (line.find("[Input]  : find logus.log") !=std::string::npos)
	{
		saveConfig(0);
		ShellExecute(0, 0, "logus.log", 0, 0, SW_SHOW);
		Beep(dzwiekGlowny, 150);
		return 1;
	}
	return 0;
}
