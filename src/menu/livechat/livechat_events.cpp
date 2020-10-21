// Copyright © 2018-2020  DarXe, Niventill
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
#include "livechat_proc.hpp"
#include "livechat_events.hpp"
#include "livechat_cmd.hpp"


//foward declarations
void serverConnect(); //from proc.hpp

bool LCEvent::Team(const std::string &line, const bool &nicksearch)
{
	leng = nick.length();
	if (line[gt] == '(' && line[gt + 1] == 'T' && line[gt + 2] == 'E' && line[gt + 3] == 'A' && line[gt + 4] == 'M')
		if (nicksearch)
			return 1;
		if (line[gt + 6 + leng] != nick[leng - 1] || line[gt + 5 + leng] != nick[leng - 2] || line[gt + 4 + leng] != nick[leng - 3])
			return 1;
		else
			return 0;
	return 0;
}

void pKarambol(const std::string &line)
{
	if (line.find("[Output] : Nie ma lekarzy na serwerze. Za ") != std::string::npos)
	{
		int delim, delim1, var;
		delim = line.find(" Za ");
		delim1 = line.find(" sek ");
		var = stoi(line.substr(delim + 4, delim1 - delim - 4));
		startCounter(var);
	}
	else if (line.find("[Output] : There's no medics right here on the serwer. Wait ") != std::string::npos)
	{
		int delim, delim1, var;
		delim = line.find(" Wait ");
		delim1 = line.find(" sek ");
		var = stoi(line.substr(delim + 6, delim1 - delim - 6));
		startCounter(var);
	}
}

bool LCEvent::PwOd(const std::string &line)
{
	if ((line[gt] == '*' && line[gt + 2] == 'P' && line[gt + 3] == 'M') || (line[gt] == '*' && line[gt + 2] == 'P' && line[gt + 3] == 'W'))
		return 1;
	else
		return 0;
}

bool LCEvent::PwDo(const std::string &line)
{
	if (line[gt] == '-' && line[gt + 1] == '>')
		return 1;
	else
		return 0;
}

void pNickChange(const std::string &line)
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

bool LCEvent::PrzelewyOd(const std::string &line)
{
	//[2020-08-09 21:06:56] [Output] : Gracz SpookyTank przelał tobie 1500$.
	//[2020-08-30 16:35:09] [Output] : Player DarXe transferred to you $1.
	if ((line.find("[Output] : Gracz ") != std::string::npos) || (line.find("[Output] : Player ") != std::string::npos))
		if ((line.find(" przelał tobie ") != std::string::npos) || (line.find(" transferred to you") != std::string::npos))
			return 1;
	return 0;
}

bool LCEvent::PrzelewyDo(const std::string &line)
{
	//[2020-08-29 15:34:28] [Output] : Przelałeś 1000000$ graczowi DarXe.
	//[2020-08-30 16:34:52] [Output] : You gave $1 to player DarXe.
	if ((line.find("[Output] : Przelałeś ") != std::string::npos) || (line.find("[Output] : You gave $") != std::string::npos))
		if ((line.find(" to player ") != std::string::npos) || (line.find(" graczowi ") != std::string::npos))
			return 1;
	return 0;
}

bool LCEvent::Komunikat(const std::string &line)
{
	if ((line[gt] == 'N' && line[gt + 1] == 'e' && line[gt + 3] == ' ' && line[gt + 8] == 'r') || (line[gt] == 'N' && line[gt + 1] == 'o' && line[gt + 3] == 'y' && line[gt + 4] == ' ' && line[gt + 9] == 'r'))
		return 1;
	else
		return 0;
}

bool LCEvent::Transport(const std::string &line)
{
	//[2019-05-24 17:02:41] [Output] : You've earned $2792. It has been transfered to your company's account.
	if ((line[gt] == 'Y' && line[gt + 4] == 'v' && line[gt + 14] == '$') ||
		//[2019-05-24 17:02:41] [Output] : Pieniądze za transport 3191$ zostały przelane na konto firmy.
		(line[gt] == 'P' && line[gt + 1] == 'i' && line[gt + 2] == 'e' && line[gt + 3] == 'n' && line[gt + 4] == 'i'))
		return 1;
	else
		return 0;
}

bool LCEvent::Nicknames(const std::string &line)
{
	for (int i = 0; i < nicknames.size(); i++)
	{
		s_temp = nicknames.at(i);
		leng = s_temp.length() - 1;
		//chat
		//if(line[gt+leng]==s_temp[leng]&&line[gt+leng-1]==s_temp[leng-1]&&line[gt+leng-2]==s_temp[leng-2])
		//	return 0;
		//join
		if (line[gt] == '*' && line[gt + leng + 3] == ' ' && line[gt + leng + 2] == s_temp[leng] && line[gt + leng + 1] == s_temp[leng - 1] && line[gt + leng] == s_temp[leng - 2])
			return 1;
		//afk
		if (line[gt + 3] == 'c' && line[gt + 4] == 'z' && line[gt + 5] == ' ' && line[gt + leng + 7] == ' ' && line[gt + leng + 6] == s_temp[leng] && line[gt + leng + 5] == s_temp[leng - 1] && line[gt + leng + 4] == s_temp[leng - 2])
			return 1;
	}
	return 0;
}

//[2020-06-12 00:11:39] [Output] : msg: You cannot message yourself
bool LCEvent::BindKey(const std::string &line)
{
	return (line[gt] == 'm' && line[gt + 1] == 's' && line[gt + 2] == 'g' && line[gt + 3] == ':' && line[gt + 5] == 'P');
}

bool LCEvent::Open(const std::string &line)
{
	if (autoOpenGate)
		return (line[line.length() - 2] == 'n' && line[line.length() - 3] == 'e' && line[line.length() - 4] == 'p' && line[line.length() - 5] == 'o');
	else
		return 0;
}

bool LCEvent::Player(const std::string &line)
{
	return (line[gt] == '*' && line[gt] == '*');
}

bool LCEvent::PlayerCount(const std::string &line)
{
	//[2019-05-24 17:02:41] [Output] : You've earned $2792. It has been transfered to your company's account.
	if ((line[gt] == 'Y' && line[gt + 4] == 'v' && line[gt + 14] == '$') ||
		//[2019-05-24 17:02:41] [Output] : Pieniądze za transport 3191$ zostały przelane na konto firmy.
		(line[gt] == 'P' && line[gt + 1] == 'i' && line[gt + 2] == 'e' && line[gt + 3] == 'n' && line[gt + 4] == 'i'))
		return 1;
	else
		return 0;
}

bool liveChatBeep(std::string &ostatniaLinia) //bee
{
	//wiadomość pw
	if (!fLockPW)
	{
		if (LCEvent::PwOd(ostatniaLinia))
		{
			//open the gate
			if (LCEvent::Open(ostatniaLinia))
			{
				system("start bin\\pasteCmd.exe");
				toClipboard("open");

				Beep(dzwiekGlowny, 400);
				Beep(0, interval);

				std::fstream info;
				info.open("liveChatInfoOutput.log", std::ios::app);
				info << ostatniaLinia;
				info.close();
				return 1;
			}
			//other PM
			Beep(dzwiekGlowny, 300);
			Beep(0, interval);
			Beep(dzwiekGlowny, 300);
			Beep(0, interval);

			std::fstream info;
			info.open("liveChatInfoOutput.log", std::ios::app);
			info << ostatniaLinia;
			info.close();
			return 1;
		}
	}

	//wiadomość teamowa
	if (!fLockTeam)
	{
		if (LCEvent::Team(ostatniaLinia, 0))
		{
			Beep(dzwiekGlowny, 150);
			Beep(0, interval);
			Beep(dzwiekGlowny, 150);
			Beep(0, interval);

			std::fstream info;
			info.open("liveChatInfoOutput.log", std::ios::app);
			info << ostatniaLinia;
			info.close();
			return 1;
		}
	}

	//nick z czatu dodany do ulubionych
	if (!fLockNick)
	{
		if (LCEvent::Nicknames(ostatniaLinia))
		{
			Beep(dzwiekGlowny, 300);
			Beep(0, interval);
			return 1;
		}
	}

	//dostarczenie towaru, raport z frakcji
	if (!fLockKomunikat)
	{
		if (LCEvent::Transport(ostatniaLinia))
		{
			salaryForTransport(ostatniaLinia);
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

			std::fstream info;
			info.open("liveChatInfoOutput.log", std::ios::app);
			info << ostatniaLinia;
			info.close();
			return 1;
		}

		if (LCEvent::Komunikat(ostatniaLinia))
		{
			Beep(dzwiekGlowny, 150);
			Beep(0, interval);
			Beep(dzwiekGlowny, 150);
			Beep(0, interval);
			Beep(dzwiekGlowny, 150);
			Beep(0, interval);

			std::fstream info;
			info.open("liveChatInfoOutput.log", std::ios::app);
			info << ostatniaLinia;
			info.close();
			return 1;
		}

		pKarambol(ostatniaLinia);
	}

	//przelewy
	if (LCEvent::PrzelewyOd(ostatniaLinia))
	{
		Beep(dzwiekGlowny, 400);
		Beep(0, interval);

		std::fstream info;
		info.open("liveChatInfoOutput.log", std::ios::app);
		info << ostatniaLinia;
		info.close();
		return 1;
	}

	//klawisz zbindowany pod błąd /bind <key> <your_nick> msg x
	//aktualna funkcja - start timera
	if (LCEvent::BindKey(ostatniaLinia))
	{
		if (mainTimer.m_running)
		{
			stopCounter();
			std::fstream info;
			info.open("liveChatInfoOutput.log", std::ios::app);
			info << ostatniaLinia.substr(0, 33) << "Timer - STOP";
			info.close();
		}
		else
		{
			startCounter();
			std::fstream info;
			info.open("liveChatInfoOutput.log", std::ios::app);
			info << ostatniaLinia.substr(0, 33) << "Timer - START";
			info.close();
		}
		return 1;
	}

	pNickChange(ostatniaLinia);

	LCCommand::checkCommandInput(ostatniaLinia);

	if (chatSound)
	{
		Beep(750, 50);
	}

	return 1;
}