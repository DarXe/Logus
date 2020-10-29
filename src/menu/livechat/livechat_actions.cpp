// Copyright © 2018-2020  DarXe, Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//standard libraries
#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>
#include <sstream>


//header includes
#include <var.hpp>
#include <config.hpp>
#include <common.hpp>
#include <debug.hpp>
#include "livechat_events.hpp"
#include "livechat_cmd.hpp"
#include "livechat_actions.hpp"

void LCAction::CheckActions(const std::string &line)
{
	LCAction::PmFrom(line);
	LCAction::Team(line);
	LCAction::Nicknames(line);
	LCAction::Transport(line);
	LCAction::Report(line);
	LCAction::TransfersFrom(line);
	LCAction::BindKey(line);
	LCAction::Freeze(line);
	LCAction::NickChange(line);
	LCAction::ContainsPhrase(line);

	LCCommand::CheckCommandInput(line);

	if (chatSound)
		Beep(750, 50);
}

void LCAction::PmFrom(const std::string &line)
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
		}
	}
}

void LCAction::Team(const std::string &line)
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
		}
	}
}

void LCAction::Nicknames(const std::string &line)
{
	// beep na nick z czatu dodany do ulubionych (join, afk, killmessage)
	if (!fLockNick && LCEvent::Nicknames(line))
	{
			Beep(dzwiekGlowny, 300);
			Beep(0, interval);
	}
}

void LCAction::Transport(const std::string &line)
{
	// beep dostarczenie towaru, raport z frakcji
	if (!fLockReport && LCEvent::Transport(line))
	{
		SalaryForTransport(line);
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

		LDebug::InfoOutput(line);
	}
}

void LCAction::Report(const std::string &line)
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
	}
}

void LCAction::TransfersFrom(const std::string &line)
{
	// beep na przelew
	if (LCEvent::TransfersFrom(line))
	{
		Beep(dzwiekGlowny, 400);
		Beep(0, interval);

		LDebug::InfoOutput(line);
	}
}

void LCAction::BindKey(const std::string &line)
{
	if (LCEvent::BindKey(line))
	{
		if (mainTimer.m_running)
		{
			mainTimer.stopCounter();
			LDebug::InfoOutput(line);;
		}
		else
		{
			mainTimer.startCounter();
			LDebug::InfoOutput(line);
		}
	}
}

void LCAction::Freeze(const std::string &line)
{
	// timer po wypadku
	if (LCEvent::Freeze(line) && line.find("[Output] : Nie ma lekarzy na serwerze. Za ") != std::string::npos)
	{
		int delim, delim1, var;
		delim = line.find(" Za ");
		delim1 = line.find(" sek ");
		var = stoi(line.substr(delim + 4, delim1 - delim - 4));
		mainTimer.startCounter(var);
	}
	else if (LCEvent::Freeze(line) && line.find("[Output] : There's no medics right here on the serwer. Wait ") != std::string::npos)
	{
		int delim, delim1, var;
		delim = line.find(" Wait ");
		delim1 = line.find(" sek ");
		var = stoi(line.substr(delim + 6, delim1 - delim - 6));
		mainTimer.startCounter(var);
	}
}

void LCAction::NickChange(const std::string &line)
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
	}
}

void LCAction::SalaryForTransport(const std::string &line)
{
	//[2019-05-24 17:02:41] [Output] : Pieniądze za transport 3191$ zostały przelane na konto firmy.
	//[2019-05-24 17:02:41] [Output] : You've earned $2792. It has been transfered to your company's account.
	short delim = 0, delim1 = 0;
	std::string tempSalary;
	if (line.find("rt ") != std::string::npos) //pol if
		delim = line.find("rt ");
	else if (line.find("d $") != std::string::npos) //eng if
		delim = line.find("d $");

	if (line.find("$ z") != std::string::npos) //pol if
		delim1 = line.find("$ z");
	else if (line.find(". I") != std::string::npos) //eng if
		delim1 = line.find(". I");

	tempSalary = line.substr(delim + 3, delim1 - delim - 3);
	money += stoi(tempSalary);
	courses++;

	if (stoi(tempSalary) < minsalary || minsalary == 0)
		minsalary = stoi(tempSalary);
	if (stoi(tempSalary) > maxsalary)
		maxsalary = stoi(tempSalary);

	saveConfig(0);
}

void LCAction::ContainsPhrase(const std::string &line)
{
	if(LCEvent::ContainsPhrase(line))
	{
		Beep(dzwiekGlowny, 300);
		Beep(0, interval);
		Beep(dzwiekGlowny, 300);
		Beep(0, interval);

		LDebug::InfoOutput(line);
	}
}