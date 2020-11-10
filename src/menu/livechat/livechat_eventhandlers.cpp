// Copyright © 2018-2020  DarXe, Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//standard libraries
#include <sstream>
#include <windows.h>


//header includes
#include <var.hpp>
#include <config.hpp>
#include <common.hpp>
#include <debug.hpp>
#include "livechat_events.hpp"
#include "livechat_cmd.hpp"
#include "livechat_eventhandlers.hpp"

void LCEventHandler::CheckEventHandlers(const std::string &line)
{
	try
	{
		LCCommand::CheckCommandInput(line);

		PmFrom(line);
		Team(line);
		Nicknames(line);
		Transport(line);
		Report(line);
		TransfersFrom(line);
		BindKey(line);
		Freeze(line);
		NickChange(line);
		ContainsPhrase(line);

		if (chatSound)
			Beep(750, 50);
	}
	catch(const int &e)
	{}
}

inline void LCEventHandler::PmFrom(const std::string_view line)
{
	// beep na PW od gracza
	if (!fLockPW)
	{
		if (LCEvent::PmFrom(line))
		{
			//open the gate
			if (LCEvent::Open(line))
			{
				system("start bin\\pasteCmd.exe");
				toClipboard("open");

				Beep(dzwiekGlowny, 400);
				Beep(0, interval);

				LDebug::InfoOutput(line);
			}
			//other PM
			Beep(dzwiekGlowny, 300);
			Beep(0, interval);
			Beep(dzwiekGlowny, 300);
			Beep(0, interval);

			LDebug::InfoOutput(line);
			throw 1;
		}
	}
}

inline void LCEventHandler::Team(const std::string_view line)
{
	// beep na wiadomość teamową (ignoruje nick obecny w configu Logusia)
	if (!fLockTeam)
	{
		if (LCEvent::Team(line, false))
		{
			Beep(dzwiekGlowny, 150);
			Beep(0, interval);
			Beep(dzwiekGlowny, 150);
			Beep(0, interval);

			LDebug::InfoOutput(line);
			throw 1;
		}
	}
}

inline void LCEventHandler::Nicknames(const std::string_view line)
{
	// beep na nick z czatu dodany do ulubionych (join, afk, killmessage)
	if (!fLockNick && LCEvent::Nicknames(line))
	{
		Beep(dzwiekGlowny, 300);
		Beep(0, interval);
		throw 1;
	}
}

inline void LCEventHandler::Transport(const std::string_view line)
{
	// beep dostarczenie towaru, raport z frakcji
	if (!fLockReport && (LCEvent::TransportCompany(line) || LCEvent::TransportTruckerzy(line)))
	{
		SalaryForTransport(line, LCEvent::TransportCompany(line));
		if (trackId)
		{
			if (trackId == 4)
				trackId = 1;
			else
				trackId++;
		}
		Beep(dzwiekGlowny, 150);
		Beep(0, interval);
		Beep(dzwiekGlowny, 150);
		Beep(0, interval);
		Beep(dzwiekGlowny, 150);
		Beep(0, interval);
		saveConfig(0);
		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline void LCEventHandler::Report(const std::string_view line)
{
	// komunikat na raport frakcyjny
	if (!fLockReport && LCEvent::Report(line))
	{
		Beep(dzwiekGlowny, 150);
		Beep(0, interval);
		Beep(dzwiekGlowny, 150);
		Beep(0, interval);
		Beep(dzwiekGlowny, 150);
		Beep(0, interval);

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline void LCEventHandler::TransfersFrom(const std::string_view line)
{
	// beep na przelew
	if (LCEvent::TransfersFrom(line))
	{
		Beep(dzwiekGlowny, 400);
		Beep(0, interval);

		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline void LCEventHandler::BindKey(const std::string_view line)
{
	if (LCEvent::BindKey(line))
	{
		if (mainTimer.running)
		{
			mainTimer.stopCounter();
			LDebug::InfoOutput(line);;
		}
		else
		{
			mainTimer.startCounter();
			LDebug::InfoOutput(line);
		}
		throw 1;
	}
}

inline void LCEventHandler::Freeze(const std::string &line)
{
	// timer po wypadku
	if (LCEvent::Freeze(line) && line.find("[Output] : Nie ma lekarzy na serwerze. Za ") != std::string::npos)
	{
		int delim, delim1, var;
		delim = line.find(" Za ");
		delim1 = line.find(" sek ");
		var = stoi(line.substr(delim + 4, delim1 - delim - 4));
		mainTimer.startCounter(var);
		LDebug::InfoOutput(line);
		throw 1;
	}
	else if (LCEvent::Freeze(line) && line.find("[Output] : There's no medics right here on the serwer. Wait ") != std::string::npos)
	{
		int delim, delim1, var;
		delim = line.find(" Wait ");
		delim1 = line.find(" sek ");
		var = stoi(line.substr(delim + 6, delim1 - delim - 6));
		mainTimer.startCounter(var);
		LDebug::InfoOutput(line);
		throw 1;
	}
}

inline void LCEventHandler::NickChange(const std::string_view line)
{
	//[2020-08-30 04:03:19] [Output] : * Niventill is now known as test
	std::string tempnick = "[Output] : * " + nick + " is now known as ";
	if (line.find(tempnick) != std::string::npos)
	{
		std::string newnick, tempn;
		tempnick = line.substr(gt, std::string::npos);
		std::istringstream ss(tempnick);
		ss >> tempn >> tempn >> tempn >> tempn >> tempn >> tempn >> newnick;
		nick = newnick;
		throw 1;
	}
}

inline void LCEventHandler::SalaryForTransport(const std::string_view line, const bool &type)
{
	short delim = 0, delim1 = 0;
	std::string d1s, d1e, d2s, d2e; // 1 = polish, 2 = english, s = start, e = end
	if (type)
	//[2019-05-24 17:02:41] [Output] : Pieniądze za transport 3191$ zostały przelane na konto firmy.
	//[2019-05-24 17:02:41] [Output] : You've earned $2792. It has been transfered to your company's account.
		d1s = "rt ", d1e = "$ z", d2s = "d $", d2e = ". I";
	else
	//[2020-11-07 21:56:04] [Output] : Otrzymałeś 44$ za transport.
	//[2020-11-07 22:11:45] [Output] : Received $5 for transport.
		d1s = "eś ", d1e = "$ z", d2s = "d $", d2e = " fo";
	std::string tempSalary;
	if (line.find(d1s) != std::string::npos) //pol if
		delim = line.find(d1s);
	else if (line.find(d2s) != std::string::npos) //eng if
		delim = line.find(d2s);

	if (line.find(d1e) != std::string::npos) //pol if
		delim1 = line.find(d1e);
	else if (line.find(d2e) != std::string::npos) //eng if
		delim1 = line.find(d2e);

	tempSalary = line.substr(delim + 3, delim1 - delim - 3);
	money += stoi(tempSalary);
	courses++;

	if (stoi(tempSalary) < minsalary || minsalary == 0)
		minsalary = stoi(tempSalary);
	if (stoi(tempSalary) > maxsalary)
		maxsalary = stoi(tempSalary);
}

inline void LCEventHandler::ContainsPhrase(const std::string_view line)
{
	if(LCEvent::ContainsPhrase(line))
	{
		Beep(dzwiekGlowny, 300);
		Beep(0, interval);
		Beep(dzwiekGlowny, 300);
		Beep(0, interval);

		LDebug::InfoOutput(line);
		throw 1;
	}
}
