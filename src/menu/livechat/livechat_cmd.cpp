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
#include <proc.hpp>
#include "livechat_proc.hpp"
#include "livechat_cmd.hpp"


//foward declarations
void serverConnect(); //from proc.hpp

void LiveChatCMD::checkCommandInput(const std::string &line)
{
	reconnect(line);
	quit(line);
	startTimer(line);
	setNick(line);
	setTrack(line);
	setTimer(line);
	addNickname(line);
	delNickname(line);
	setMoney(line);
	setCourses(line);
	reset(line);
	hardReset(line);
}

bool LiveChatCMD::reconnect(const std::string &line)
{
	if (line.find("[Input]  : rr") != std::string::npos)
	{
		serverConnect();
		return 1;
	}
	return 0;
}

bool LiveChatCMD::quit(const std::string &line)
{
	if (line.find("[Input]  : quit") != std::string::npos)
	{
		mess = engLang ? "Closing MTA and Logus" : "Zamykanie MTA i programu";
		closeLogus(mess);
		return 1;
	}
	return 0;
}

bool LiveChatCMD::startTimer(const std::string &line)
{
	if (line.find("[Input]  : tt") != std::string::npos)
	{
		startCounter();
		temp = czas * 1000 / 1.1;
		temp = czas * 1000 - temp;
		mainTimer.m_timer -= temp;
	}
	else if (line.find("[Input]  : t\'") != std::string::npos)
		startCounter();
	return 0;
}

bool LiveChatCMD::setNick(const std::string &line)
{
	if (line.find("[Input]  : nick") != std::string::npos)
	{ //[2020-08-30 04:03:24] [Input]  : nick Niventill
		std::string tempnick = line.substr(gt, std::string::npos);
		std::istringstream ss(tempnick);
		ss >> tempnick >> tempnick;
		nick = tempnick;
		return 1;
	}
	return 0;
}

short LiveChatCMD::setTrack(const std::string &line)
{
	if (line.find("[Input]  : set tr") != std::string::npos) //set tr xx //SET TRACK
	{
		if (line[gt + 7] == '0')
		{
			trackId = 0;
			return 1;
		}
		else if (line[gt + 7] == 'a')
		{
			if (line[gt + 8] == '1')
				trackId = 1;
			else
				trackId = 3;
			return 1;
		}
		else
		{
			if (line[gt + 8] == '1')
				trackId = 4;
			else
				trackId = 2;
			return 1;
		}
	}
	return 0;
}

bool LiveChatCMD::setTimer(const std::string &line)
{
	if (line.find("[Input]  : set t ") != std::string::npos) //[Input]  : set t 00:00
	{
		std::string temptimer;
		int minutes, seconds, delim;
		delim = line.find("[Input]  : set t ");
		temptimer = line.substr(delim + 17, std::string::npos);
		sscanf_s(temptimer.c_str(), "%2d:%2d", &minutes, &seconds);
		minutes *= 60;
		minutes += seconds;
		mainTimer.start(minutes);
		return 1;
	}
	return 0;
}

bool LiveChatCMD::addNickname(const std::string &line)
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
		return 1;
	}
	return 0;
}

bool LiveChatCMD::delNickname(const std::string &line)
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
		return 1;
	}
	return 0;
}

bool LiveChatCMD::setMoney(const std::string &line)
{
	if (line.find("[Input]  : set m ") != std::string::npos)
	{
		int delim = line.find("[Input]  : set m ");
		std::string tmoney = line.substr(delim + 16, std::string::npos);
		money = stoi(tmoney);
		saveConfig(0);
		return 1;
	}
	return 0;
}

bool LiveChatCMD::setCourses(const std::string &line)
{
	if (line.find("[Input]  : set c ") != std::string::npos)
	{
		int delim = line.find("[Input]  : set c ");
		std::string tcourses = line.substr(delim + 17, std::string::npos);
		courses = stoi(tcourses);
		saveConfig(0);
		return 1;
	}
	return 0;
}

bool LiveChatCMD::hardReset(const std::string &line)
{
	if (line.find("[Input]  : set hre") != std::string::npos) //reset kursow /set re
	{
		money = 0;
		courses = 0;
		minsalary = 0;
		maxsalary = 0;
		saveConfig(0);
		return 1;
	}
	return 0;
}

bool LiveChatCMD::reset(const std::string &line)
{
	if (line.find("[Input]  : set re") != std::string::npos) //reset kursow /set re
	{
		money = 0;
		courses = 0;
		saveConfig(0);
		return 1;
	}
	return 0;
}

LiveChatCMD cmd;