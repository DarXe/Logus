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
#include <debug.hpp>
#include "livechat.hpp"
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
	AutoReconnectBeep(line);

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
	SetLoadingTime(line);
	FindTransfers(line);
	FindWord(line);
	OpenConfig(line);
	OpenConsoleLog(line);
	OpenLogusLog(line);
	SetMin(line);
	SetMax(line);
	SetRefresh(line);
	Reset(line);
	HardReset(line);
}

void LCCommand::PreCheckCommandInput(const std::string &line, bool &isAutoJoin)
{
	try
	{
		Timestamp(line);
		RenderEngine(line);
		ClearChat(line);
		SetDynamicRefresh(line);
		AutoReconnect(line, isAutoJoin);
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

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::Reconnect(const std::string_view line)
{
	return lcompare(line, "[Input]  : rr");
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
	return lcompare(line, "[Input]  : quit");
}

///////////////////* START TIMER */////////////////////////////////
inline void LCCommand::StartTimer(const std::string_view line)
{
	if (lcompare(line, "[Input]  : tt"))
	{
		mainTimer.startCounter();
		int temp;
		temp = czas * 1000 / 1.1;
		temp = czas * 1000 - temp;
		mainTimer.timer -= temp;
	}
	else if (lcompare(line, "[Input]  : t\'"))
		mainTimer.startCounter();
}

inline bool LCCmdEvent::StartTimer(const std::string_view line)
{
	return lcompare(line, "[Input]  : tt") || lcompare(line, "[Input]  : t\'");
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

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::SetNick(const std::string_view line)
{
	return lcompare(line, "[Input]  : nick ");
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

			LDebug::InfoOutput(line);
			throw 1;
		}
		else if (line[gt + 7] == 'a')
		{
			if (line[gt + 8] == '1')
				trackId = 1;
			else
				trackId = 3;
			Beep(dzwiekGlowny, 150);

			LDebug::InfoOutput(line);
			throw 1;
		}
		else
		{
			if (line[gt + 8] == '1')
				trackId = 4;
			else
				trackId = 2;
			Beep(dzwiekGlowny, 150);

			LDebug::InfoOutput(line);
			throw 1;
		}
	}
}

inline bool LCCmdEvent::SetTrack(const std::string_view line)
{
	return lcompare(line, "[Input]  : set tr ");
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
	return lcompare(line, "[Input]  : set t ");
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

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::AddNickname(const std::string_view line)
{
	return lcompare(line, "[Input]  : nickdb add ");
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

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::DelNickname(const std::string_view line)
{
	return lcompare(line, "[Input]  : nickdb del ");
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

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::SetMoney(const std::string_view line)
{
	return lcompare(line, "[Input]  : set m ");
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

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::SetCourses(const std::string_view line)
{
	return lcompare(line, "[Input]  : set c ");
}

///////////////////* SET LOADING TIME *///////////////////////////////////
inline void LCCommand::SetLoadingTime(const std::string_view line)
{
	if (LCCmdEvent::SetLoadingTime(line)) //[Input]  : set t 00:00
	{
		std::string temptimer;
		int minutes, seconds, delim;
		delim = line.find("[Input]  : set l ");
		temptimer = line.substr(delim + 17, std::string::npos);
		sscanf_s(temptimer.c_str(), "%2d:%2d", &minutes, &seconds);
		minutes *= 60;
		minutes += seconds;
		czas = minutes;

		saveConfig(0);
		Beep(dzwiekGlowny, 150);

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::SetLoadingTime(const std::string_view line)
{
	return lcompare(line, "[Input]  : set l ");
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

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::HardReset(const std::string_view line)
{
	return lcompare(line, "[Input]  : set hre");
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

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::Reset(const std::string_view line)
{
	return lcompare(line, "[Input]  : set re");
}

///////////////////* FIND TRANSFERS *//////////////////////////////
inline void LCCommand::FindTransfers(const std::string_view line)
{
	if (LCCmdEvent::FindTransfers(line))
	{
		checkLogTransfersAll(LiveChat);
		Beep(dzwiekGlowny, 150);

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::FindTransfers(const std::string_view line)
{
	return lcompare(line, "[Input]  : find tf");
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

		LDebug::InfoOutput(line);
		throw 1;
	}
	else if (line.find("[Input]  : find word ") != std::string::npos)
	{
		int delim = line.find("[Input]  : find word ");
		std::string phrase = line.substr(delim + 21, std::string::npos);
		removeSpaces(phrase);
		findWordAll_NonCaseSensitive(phrase);
		Beep(dzwiekGlowny, 150);

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::FindWord(const std::string_view line)
{
	return lcompare(line, "[Input]  : find Word ") || lcompare(line, "[Input]  : find word ");
}

///////////////////* FIND CONFIG */////////////////////////////////
inline void LCCommand::OpenConfig(const std::string_view line)
{
	if (LCCmdEvent::OpenConfig(line))
	{
		saveConfig(0);
		ShellExecute(0, 0, "logus.ini", 0, 0, SW_SHOW);
		Beep(dzwiekGlowny, 150);

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::OpenConfig(const std::string_view line)
{
	return lcompare(line, "[Input]  : open cfg");
}

///////////////////* FIND CONSOLE LOG *////////////////////////////
inline void LCCommand::OpenConsoleLog(const std::string_view line)
{
	if (LCCmdEvent::OpenConsoleLog(line))
	{
		saveConfig(0);
		ShellExecute(0, 0, consoleLogPath.c_str(), 0, 0, SW_SHOW);
		Beep(dzwiekGlowny, 150);

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::OpenConsoleLog(const std::string_view line)
{
	return lcompare(line, "[Input]  : open console.log");
}

///////////////////* FIND LOGUS LOG *//////////////////////////////
inline void LCCommand::OpenLogusLog(const std::string_view line)
{
	if (LCCmdEvent::OpenLogusLog(line))
	{
		saveConfig(0);
		ShellExecute(0, 0, "logus.log", 0, 0, SW_SHOW);
		Beep(dzwiekGlowny, 150);

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::OpenLogusLog(const std::string_view line)
{
	return lcompare(line, "[Input]  : open logus.log");
}

///////////////////* TIMESTAMP *///////////////////////////////////
inline void LCCommand::Timestamp(const std::string_view line)
{
	if (LCCmdEvent::Timestamp(line)) //reset kursow /set re
	{
		timestamp = !timestamp;
		LCCore::ForceReload();
		saveConfig(0);
		throw 1;
	}
}

inline void LCCommand::TimestampBeep(const std::string_view line)
{
	if (LCCmdEvent::Timestamp(line)) //reset kursow /set re
	{
		Beep(dzwiekGlowny, 150);

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::Timestamp(const std::string_view line)
{
	return lcompare(line, "[Input]  : set ts");
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

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::RenderEngine(const std::string_view line)
{
	return lcompare(line, "[Input]  : set engine");
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

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::ClearChat(const std::string_view line)
{
	return lcompare(line, "[Input]  : cls");
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

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::SetRefresh(const std::string_view line)
{
	return lcompare(line, "[Input]  : set refr ");
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

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::SetMin(const std::string_view line)
{
	return lcompare(line, "[Input]  : set minr ");
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

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::SetMax(const std::string_view line)
{
	return lcompare(line, "[Input]  : set maxr ");
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

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::SetDynamicRefresh(const std::string_view line)
{
	return lcompare(line, "[Input]  : set dyn");
}

///////////////////* AUTO RECONNECT */////////////////////////
inline void LCCommand::AutoReconnect(const std::string_view line, bool &isAutoJoin)
{
	if (LCCmdEvent::AutoReconnect(line)) //reset kursow /set re
	{
		if (!isAutoJoin)
		{
			isAutoJoin = true;
			serverConnect();
		}
		else
			isAutoJoin = false;
		
		throw 1;
	}
}

inline void LCCommand::AutoReconnectBeep(const std::string_view line)
{
	if (LCCmdEvent::AutoReconnect(line)) //reset kursow /set re
	{
		Beep(dzwiekGlowny, 150);

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline bool LCCmdEvent::AutoReconnect(const std::string_view line)
{
	return lcompare(line, "[Input]  : autorr");
}

bool LCCmdEvent::CheckCommandEvents(const std::string_view line)
{
	if (Reconnect(line)
	|| Quit(line)
	|| StartTimer(line)
	|| SetNick(line)
	|| SetTrack(line)
	|| SetTimer(line)
	|| AddNickname(line)
	|| DelNickname(line)
	|| SetMoney(line)
	|| SetCourses(line)
	|| SetLoadingTime(line)
	|| Reset(line)
	|| HardReset(line)
	|| FindTransfers(line)
	|| FindWord(line)
	|| OpenConfig(line)
	|| OpenConsoleLog(line)
	|| OpenLogusLog(line)
	|| Timestamp(line)
	|| RenderEngine(line)
	|| ClearChat(line)
	|| SetMax(line)
	|| SetMin(line)
	|| SetRefresh(line)
	|| SetDynamicRefresh(line)
	|| AutoReconnect(line))
		return 1;
	else
		return 0;
}
