// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//standard libraries
#include <sstream>
#include <string_view>
#include <windows.h>


//header includes
#include <var.hpp>
#include <config.hpp>
#include <common.hpp>
#include "../addons/loglookup.hpp"
#include <proc.hpp>
#include "livechat_eventhandlers.hpp"
#include "livechat_cmd.hpp"


//foward declarations
void serverConnect(); //from proc.hpp

void LCCommand::CheckCommandInput(const std::string &line)
{
	TimestampBeep(line);
	RenderEngineBeep(line);
	ClearChatBeep(line);
	SetDynamicRefreshBeep(line);

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
	SetMin(line);
	SetMax(line);
	SetRefresh(line);
}

void LCCommand::PreCheckCommandInput(const std::string &line)
{
	try
	{
		Timestamp(line);
		RenderEngine(line);
		ClearChat(line);
		SetDynamicRefresh(line);
	}
	catch (const int &e)
	{}
}

///////////////////* RECONNECT *///////////////////////////////////
inline void LCCommand::Reconnect(const std::string_view line)
{
	if (LCCmdEvent::Reconnect(line))
	{
		serverConnect();
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
}

inline bool LCCmdEvent::Reconnect(const std::string_view line)
{
	return (line.find("[Input]  : rr") != std::string::npos);
}

///////////////////* QUIT *////////////////////////////////////////
inline void LCCommand::Quit(const std::string_view line)
{
	if (LCCmdEvent::Quit(line))
	{
		closeLogus(((engLang)?"Closing MTA and Logus":"Zamykanie MTA i programu"));
		throw 1;
	}
}

inline bool LCCmdEvent::Quit(const std::string_view line)
{
	return (line.find("[Input]  : quit") != std::string::npos);
}

///////////////////* START TIMER */////////////////////////////////
inline void LCCommand::StartTimer(const std::string_view line)
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
}

inline bool LCCmdEvent::StartTimer(const std::string_view line)
{
	return (line.find("[Input]  : tt") != std::string::npos || line.find("[Input]  : t\'") != std::string::npos);
}

///////////////////* SET NICK *////////////////////////////////////
inline void LCCommand::SetNick(const std::string &line)
{
	if (LCCmdEvent::SetNick(line))
	{ //[2020-08-30 04:03:24] [Input]  : nick Niventill
		std::string tempnick = line.substr(gt, std::string::npos);
		std::istringstream ss(tempnick);
		ss >> tempnick >> tempnick;
		nick = tempnick;
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
}

inline bool LCCmdEvent::SetNick(const std::string_view line)
{
	return (line.find("[Input]  : nick ") != std::string::npos);
}

///////////////////* SET TRACK *///////////////////////////////////
inline void LCCommand::SetTrack(const std::string_view line)
{
	if (LCCmdEvent::SetTrack(line)) //set tr xx //SET TRACK
	{
		if (line[gt + 7] == '0')
		{
			trackId = 0;
			Beep(dzwiekGlowny, 150);
			throw 1;
		}
		else if (line[gt + 7] == 'a')
		{
			if (line[gt + 8] == '1')
				trackId = 1;
			else
				trackId = 3;
			Beep(dzwiekGlowny, 150);
			throw 1;
		}
		else
		{
			if (line[gt + 8] == '1')
				trackId = 4;
			else
				trackId = 2;
			Beep(dzwiekGlowny, 150);
			throw 1;
		}
	}
}

inline bool LCCmdEvent::SetTrack(const std::string_view line)
{
	return (line.find("[Input]  : set tr ") != std::string::npos);
}

///////////////////* SET TIMER *///////////////////////////////////
inline void LCCommand::SetTimer(const std::string_view line)
{
	if (LCCmdEvent::SetTimer(line)) //[Input]  : set t 00:00
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
		throw 1;
	}
}

inline bool LCCmdEvent::SetTimer(const std::string_view line)
{
	return (line.find("[Input]  : set t ") != std::string::npos);
}

///////////////////* ADD NICKNAME *////////////////////////////////
inline void LCCommand::AddNickname(const std::string_view line)
{
	if (LCCmdEvent::AddNickname(line))
	{
		std::string tempn;
		int delim;
		delim = line.find("[Input]  : nickdb add ");
		tempn = line.substr(delim + 22, std::string::npos);
		tempn = removeSpaces(tempn);
		nicknames.push_back(tempn);
		saveConfig(0);
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
}

inline bool LCCmdEvent::AddNickname(const std::string_view line)
{
	return (line.find("[Input]  : nickdb add ") != std::string::npos);
}

///////////////////* DEL NICKNAME *////////////////////////////////
inline void LCCommand::DelNickname(const std::string_view line)
{
	if (LCCmdEvent::DelNickname(line))
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
		throw 1;
	}
}

inline bool LCCmdEvent::DelNickname(const std::string_view line)
{
	return (line.find("[Input]  : nickdb del ") != std::string::npos);
}

///////////////////* SET MONEY *///////////////////////////////////
inline void LCCommand::SetMoney(const std::string &line)
{
	if (LCCmdEvent::SetMoney(line))
	{
		int delim = line.find("[Input]  : set m ");
		std::string tmoney = line.substr(delim + 17, std::string::npos);
		try {
			money = stoi(tmoney);
		}
		catch (const std::invalid_argument& arg) {}
		saveConfig(0);
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
}

inline bool LCCmdEvent::SetMoney(const std::string_view line)
{
	return (line.find("[Input]  : set m ") != std::string::npos);
}

///////////////////* SET COURSES */////////////////////////////////
inline void LCCommand::SetCourses(const std::string &line)
{
	if (LCCmdEvent::SetCourses(line))
	{
		int delim = line.find("[Input]  : set c ");
		std::string tcourses = line.substr(delim + 17, std::string::npos);
		try {
			courses = stoi(tcourses);
		}
		catch (const std::invalid_argument& arg) {
	
		}
		saveConfig(0);
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
}

inline bool LCCmdEvent::SetCourses(const std::string_view line)
{
	return (line.find("[Input]  : set c ") != std::string::npos);
}

///////////////////* HARD RESET *//////////////////////////////////
inline void LCCommand::HardReset(const std::string_view line)
{
	if (LCCmdEvent::HardReset(line)) //reset kursow /set re
	{
		money = 0;
		courses = 0;
		minsalary = 0;
		maxsalary = 0;
		saveConfig(0);
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
}

inline bool LCCmdEvent::HardReset(const std::string_view line)
{
	return (line.find("[Input]  : set hre") != std::string::npos);
}

///////////////////* SOFT RESET *//////////////////////////////////
inline void LCCommand::Reset(const std::string_view line)
{
	if (LCCmdEvent::Reset(line)) //reset kursow /set re
	{
		money = 0;
		courses = 0;
		saveConfig(0);
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
}

inline bool LCCmdEvent::Reset(const std::string_view line)
{
	return (line.find("[Input]  : set re") != std::string::npos);
}

///////////////////* FIND TRANSFERS *//////////////////////////////
inline void LCCommand::FindTransfers(const std::string_view line)
{
	if (LCCmdEvent::FindTransfers(line))
	{
		checkLogTransfersAll(LiveChat);
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
}

inline bool LCCmdEvent::FindTransfers(const std::string_view line)
{
	return (line.find("[Input]  : find tf") != std::string::npos);
}

///////////////////* FIND WORD *///////////////////////////////////
inline void LCCommand::FindWord(const std::string &line)
{
	if (line.find("[Input]  : find Word ") != std::string::npos)
	{
		int delim = line.find("[Input]  : find Word ");
		std::string phrase = line.substr(delim + 21, std::string::npos);
		removeSpaces(phrase);
		findWordAll_CaseSensitive(phrase);
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
	else if (line.find("[Input]  : find word ") != std::string::npos)
	{
		int delim = line.find("[Input]  : find word ");
		std::string phrase = line.substr(delim + 21, std::string::npos);
		removeSpaces(phrase);
		findWordAll_NonCaseSensitive(phrase);
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
}

inline bool LCCmdEvent::FindWord(const std::string_view line)
{
	return (line.find("[Input]  : find Word ") != std::string::npos || line.find("[Input]  : find word ") != std::string::npos);
}

///////////////////* FIND CONFIG */////////////////////////////////
inline void LCCommand::FindConfig(const std::string_view line)
{
	if (LCCmdEvent::FindConfig(line))
	{
		saveConfig(0);
		ShellExecute(0, 0, "logus.ini", 0, 0, SW_SHOW);
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
}

inline bool LCCmdEvent::FindConfig(const std::string_view line)
{
	return (line.find("[Input]  : find cfg") != std::string::npos);
}

///////////////////* FIND CONSOLE LOG *////////////////////////////
inline void LCCommand::FindConsoleLog(const std::string_view line)
{
	if (LCCmdEvent::FindConsoleLog(line))
	{
		saveConfig(0);
		ShellExecute(0, 0, consoleLogPath.c_str(), 0, 0, SW_SHOW);
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
}

inline bool LCCmdEvent::FindConsoleLog(const std::string_view line)
{
	return (line.find("[Input]  : find console.log") != std::string::npos);
}

///////////////////* FIND LOGUS LOG *//////////////////////////////
inline void LCCommand::FindLogusLog(const std::string_view line)
{
	if (LCCmdEvent::FindLogusLog(line))
	{
		saveConfig(0);
		ShellExecute(0, 0, "logus.log", 0, 0, SW_SHOW);
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
}

inline bool LCCmdEvent::FindLogusLog(const std::string_view line)
{
	return (line.find("[Input]  : find logus.log") != std::string::npos);
}

///////////////////* TIMESTAMP *///////////////////////////////////
inline void LCCommand::Timestamp(const std::string_view line)
{
	if (LCCmdEvent::Timestamp(line)) //reset kursow /set re
	{
		timestamp ? timestamp = 0 : timestamp = 1;
		saveConfig(0);
		throw 1;
	}
}

inline void LCCommand::TimestampBeep(const std::string_view line)
{
	if (LCCmdEvent::Timestamp(line)) //reset kursow /set re
	{
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
}

inline bool LCCmdEvent::Timestamp(const std::string_view line)
{
	return (line.find("[Input]  : set ts") != std::string::npos);
}

///////////////////* RENDER ENGINE *///////////////////////////////
inline void LCCommand::RenderEngine(const std::string_view line)
{
	if (LCCmdEvent::RenderEngine(line)) //reset kursow /set re
	{
		renderEngine ? renderEngine = 0 : renderEngine = 1;
		saveConfig(0);
		throw 1;
	}
}

inline void LCCommand::RenderEngineBeep(const std::string_view line)
{
	if (LCCmdEvent::RenderEngine(line)) //reset kursow /set re
	{
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
}

inline bool LCCmdEvent::RenderEngine(const std::string_view line)
{
	return (line.find("[Input]  : set engine") != std::string::npos);
}

///////////////////* CLEAR CHAT *//////////////////////////////////
inline void LCCommand::ClearChat(const std::string_view line)
{
	if (LCCmdEvent::ClearChat(line)) //reset kursow /set re
	{
		clslegacy();
		throw 1;
	}
}

inline void LCCommand::ClearChatBeep(const std::string_view line)
{
	if (LCCmdEvent::ClearChat(line)) //reset kursow /set re
	{
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
}

inline bool LCCmdEvent::ClearChat(const std::string_view line)
{
	return (line.find("[Input]  : cls") != std::string::npos);
}

///////////////////* SET REFRESH */////////////////////////////////
inline void LCCommand::SetRefresh(const std::string &line)
{
	if (LCCmdEvent::SetRefresh(line))
	{
		int delim = line.find("[Input]  : set refr ");
		std::string tref = line.substr(delim + 20, std::string::npos);
		try {
			refresh = stoi(tref);
		}
		catch (const std::invalid_argument& arg) {}
		saveConfig(0);
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
}

inline bool LCCmdEvent::SetRefresh(const std::string_view line)
{
	return (line.find("[Input]  : set refr ") != std::string::npos);
}

///////////////////* SET MIN */////////////////////////////////////
inline void LCCommand::SetMin(const std::string &line)
{
	if (LCCmdEvent::SetMin(line))
	{
		int delim = line.find("[Input]  : set minr ");
		std::string tmin = line.substr(delim + 20, std::string::npos);
		try {
			minRefresh = stoi(tmin);
		}
		catch (const std::invalid_argument& arg) {}
		saveConfig(0);
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
}

inline bool LCCmdEvent::SetMin(const std::string_view line)
{
	return (line.find("[Input]  : set minr ") != std::string::npos);
}

///////////////////* SET MAX */////////////////////////////////////
inline void LCCommand::SetMax(const std::string &line)
{
	if (LCCmdEvent::SetMax(line))
	{
		int delim = line.find("[Input]  : set maxr ");
		std::string tmax = line.substr(delim + 20, std::string::npos);
		try {
			maxRefresh = stoi(tmax);
		}
		catch (const std::invalid_argument& arg) {}
		saveConfig(0);
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
}

inline bool LCCmdEvent::SetMax(const std::string_view line)
{
	return (line.find("[Input]  : set maxr ") != std::string::npos);
}

///////////////////* SET DYNAMIC REFRESH */////////////////////////
inline void LCCommand::SetDynamicRefresh(const std::string_view line)
{
	if (LCCmdEvent::SetDynamicRefresh(line)) //reset kursow /set re
	{
		dynamicRefresh ? dynamicRefresh = 0 : dynamicRefresh= 1;
		saveConfig(0);
		throw 1;
	}
}

inline void LCCommand::SetDynamicRefreshBeep(const std::string_view line)
{
	if (LCCmdEvent::SetDynamicRefresh(line)) //reset kursow /set re
	{
		Beep(dzwiekGlowny, 150);
		throw 1;
	}
}

inline bool LCCmdEvent::SetDynamicRefresh(const std::string_view line)
{
	return (line.find("[Input]  : set dyn") != std::string::npos);
}

bool LCCmdEvent::CheckCommandEvents(const std::string_view line)
{
	if (Reconnect(line))
		return 1;
	else if (Quit(line))
		return 1;
	else if (StartTimer(line))
		return 1;
	else if (SetNick(line))
		return 1;
	else if (SetTrack(line))
		return 1;
	else if (SetTimer(line))
		return 1;
	else if (AddNickname(line))
		return 1;
	else if (DelNickname(line))
		return 1;
	else if (SetMoney(line))
		return 1;
	else if (SetCourses(line))
		return 1;
	else if (Reset(line))
		return 1;
	else if (HardReset(line))
		return 1;
	else if (FindTransfers(line))
		return 1;
	else if (FindWord(line))
		return 1;
	else if (FindConfig(line))
		return 1;
	else if (FindConsoleLog(line))
		return 1;
	else if (FindLogusLog(line))
		return 1;
	else if (Timestamp(line))
		return 1;
	else if (RenderEngine(line))
		return 1;
	else if (ClearChat(line))
		return 1;
	else if (SetMax(line))
		return 1;
	else if (SetMin(line))
		return 1;
	else if (SetRefresh(line))
		return 1;
	else if (SetDynamicRefresh(line))
		return 1;
	else
		return 0;
}
