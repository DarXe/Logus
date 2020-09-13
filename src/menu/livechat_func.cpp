// Copyright © 2018-2020  DarXe, Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//standard libraries
#include <windows.h>
#include <sstream>
#include <fstream>
#include <vector>


//header includes
#include "../var.hpp"
#include "../config.hpp"
#include "../common.hpp"
#include "livechat_proc.hpp"
#include "livechat_func.hpp"


//foward declarations
void serverConnect(); //from proc.hpp

bool fTeam(const std::string &line, bool e)
{
	leng = nick.length();
	if (line[gt] == '(' && line[gt + 1] == 'T' && line[gt + 2] == 'E' && line[gt + 3] == 'A' && line[gt + 4] == 'M')
	{
		if (e)
			return 1;
		if (line[gt + 6 + leng] != nick[leng - 1] || line[gt + 5 + leng] != nick[leng - 2] || line[gt + 4 + leng] != nick[leng - 3])
			return 1;
		else
			return 0;
	}
	else
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
		startTimer(var);
	}
	else if (line.find("[Output] : There's no medics right here on the serwer. Wait ") != std::string::npos)
	{
		int delim, delim1, var;
		delim = line.find(" Wait ");
		delim1 = line.find(" sek ");
		var = stoi(line.substr(delim + 6, delim1 - delim - 6));
		startTimer(var);
	}
}

bool fPwOd(const std::string &line)
{
	if ((line[gt] == '*' && line[gt + 2] == 'P' && line[gt + 3] == 'M') || (line[gt] == '*' && line[gt + 2] == 'P' && line[gt + 3] == 'W'))
		return 1;
	else
		return 0;
}

bool fPwDo(const std::string &line)
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

bool fPrzelewyOd(const std::string &line)
{
	//[2020-08-09 21:06:56] [Output] : Gracz SpookyTank przelał tobie 1500$.
	//[2020-08-30 16:35:09] [Output] : Player DarXe transferred to you $1.
	if ((line.find("[Output] : Gracz ") != std::string::npos) || (line.find("[Output] : Player ") != std::string::npos))
		if ((line.find(" przelał tobie ") != std::string::npos) || (line.find(" transferred to you") != std::string::npos))
			return 1;
	return 0;
}

bool fPrzelewyDo(const std::string &line)
{
	//[2020-08-29 15:34:28] [Output] : Przelałeś 1000000$ graczowi DarXe.
	//[2020-08-30 16:34:52] [Output] : You gave $1 to player DarXe.
	if ((line.find("[Output] : Przelałeś ") != std::string::npos) || (line.find("[Output] : You gave $") != std::string::npos))
		if ((line.find(" to player ") != std::string::npos) || (line.find(" graczowi ") != std::string::npos))
			return 1;
	return 0;
}

bool fKomunikat(const std::string &line)
{
	if ((line[gt] == 'N' && line[gt + 1] == 'e' && line[gt + 3] == ' ' && line[gt + 8] == 'r') || (line[gt] == 'N' && line[gt + 1] == 'o' && line[gt + 3] == 'y' && line[gt + 4] == ' ' && line[gt + 9] == 'r'))
		return 1;
	else
		return 0;
}

bool fTransport(const std::string &line)
{
	//[2019-05-24 17:02:41] [Output] : You've earned $2792. It has been transfered to your company's account.
	if ((line[gt] == 'Y' && line[gt + 4] == 'v' && line[gt + 14] == '$') ||
		//[2019-05-24 17:02:41] [Output] : Pieniądze za transport 3191$ zostały przelane na konto firmy.
		(line[gt] == 'P' && line[gt + 1] == 'i' && line[gt + 2] == 'e' && line[gt + 3] == 'n' && line[gt + 4] == 'i'))
		return 1;
	else
		return 0;
}

bool fNicknames(const std::string &line)
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
bool fBindKey(const std::string &line)
{
	return (line[gt] == 'm' && line[gt + 1] == 's' && line[gt + 2] == 'g' && line[gt + 3] == ':' && line[gt + 5] == 'P');
}

bool fOpen(const std::string &line)
{
	if (autoOpenGate)
		return (line[line.length() - 2] == 'n' && line[line.length() - 3] == 'e' && line[line.length() - 4] == 'p' && line[line.length() - 5] == 'o');
	else
		return 0;
}

bool player(const std::string &line)
{
	return (line[gt] == '*' && line[gt] == '*');
}

bool fPlayerCount(const std::string &line)
{
	//[2019-05-24 17:02:41] [Output] : You've earned $2792. It has been transfered to your company's account.
	if ((line[gt] == 'Y' && line[gt + 4] == 'v' && line[gt + 14] == '$') ||
		//[2019-05-24 17:02:41] [Output] : Pieniądze za transport 3191$ zostały przelane na konto firmy.
		(line[gt] == 'P' && line[gt + 1] == 'i' && line[gt + 2] == 'e' && line[gt + 3] == 'n' && line[gt + 4] == 'i'))
		return 1;
	else
		return 0;
}

char fConsoleInput(const std::string &line) //fci
{
	if (line[gt - 10] == 'I')
	{
		if (line[gt] == 'r' && line[gt + 1] == 'r') //rr /reconnect
		{
			serverConnect();
			return 1;
		}
		else if (line[gt] == 'q' && line[gt + 1] == 'u' && line[gt + 2] == 'i' && line[gt + 3] == 't') //quit /close mta & Logus
		{
			return 2;
		}
		else if (line[gt] == 'e' && line[gt + 1] == 'x' && line[gt + 2] == 'i' && line[gt + 3] == 't') //quit /close mta & Logus
		{
			return 2;
		}
		else if (line[gt] == 't') //t START TIMER
		{
			if (line[gt + 1] == 't') //tt START TIMER waga 100%
			{
				startTimer();
				temp = czas * 1000 / 1.1;
				temp = czas * 1000 - temp;
				timer -= temp;
			}
			else if (line[gt + 1] == '\'')
				startTimer();
			return 0;
		}
		else if (line.find("[Input]  : nick") != std::string::npos)
		{ //[2020-08-30 04:03:24] [Input]  : nick Niventill
			std::string tempnick = line.substr(gt, std::string::npos);
			std::istringstream ss(tempnick);
			ss >> tempnick >> tempnick;
			nick = tempnick;
			return 1;
		}
		else if (line[gt] == 's' && line[gt + 1] == 'e' && line[gt + 2] == 't')
		{
			if (line[gt + 4] == 't' && line[gt + 5] == 'r') //set tr xx //SET TRACK
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
				return 0;
			}
			else if (line[gt + 4] == 't') //set t m:ss || set t m ss //SET TIMER
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
					startTimer(minutes);
				}
				return 0;
			}
			else if (line[gt + 4] == 'n')
			{ //[2020-03-01 02:16:00] [Input]  : set n add nick
				if (line[gt + 6] == 'a' && line[gt + 7] == 'd' && line[gt + 8] == 'd')
				{
					std::string tempn;
					int delim;
					delim = line.find("[Input]  : set n add ");
					tempn = line.substr(delim + 21, std::string::npos);
					tempn = removeSpaces(tempn);
					nicknames.push_back(tempn);
					saveConfig(0);
					return 1;
				}
				else if (line[gt + 6] == 'd' && line[gt + 7] == 'e' && line[gt + 8] == 'l')
				{
					std::string tempn;
					int delim;
					delim = line.find("[Input]  : set n del ");
					tempn = line.substr(delim + 21, std::string::npos);
					tempn = removeSpaces(tempn);
					for (int i = 0; i < nicknames.size(); i++)
					{
						if (nicknames.at(i) == tempn)
							nicknames.erase(nicknames.begin() + i);
					}
					saveConfig(0);
					return 1;
				}
				else
					return 0;
			}
			else if (line[gt + 4] == 'm') //set m x xx xxx.. //SET MONEY (f4)
			{							  //[2020-03-01 02:16:00] [Input]  : set m x
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
			else if (line[gt + 4] == 'c') //set c x //SET COURSES
			{							  //[2020-03-01 02:16:00] [Input]  : set c x
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
			else if (line[gt + 4] == 'r' && line[gt + 5] == 'e') //reset kursow /set re
			{
				money = 0;
				courses = 0;
				minsalary = 0;
				maxsalary = 0;
				saveConfig(0);
				return 1;
			}
			else
				return 0;
		}
		else
			return 0;
	}
	else
		return 0;
}

bool liveChatBeep(std::string &ostatniaLinia) //bee
{
	//wiadomość pw
	if (!fLockPW)
	{
		if (fPwOd(ostatniaLinia))
		{
			//open the gate
			if (fOpen(ostatniaLinia))
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
		if (fTeam(ostatniaLinia, 0))
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
		if (fNicknames(ostatniaLinia))
		{
			Beep(dzwiekGlowny, 300);
			Beep(0, interval);
			return 1;
		}
	}

	//dostarczenie towaru, raport z frakcji
	if (!fLockKomunikat)
	{
		if (fTransport(ostatniaLinia))
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

		if (fKomunikat(ostatniaLinia))
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
	if (fPrzelewyOd(ostatniaLinia))
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
	if (fBindKey(ostatniaLinia))
	{
		if (isTimer)
		{
			stopTimer();
			std::fstream info;
			info.open("liveChatInfoOutput.log", std::ios::app);
			info << ostatniaLinia.substr(0, 33) << "Timer - STOP";
			info.close();
		}
		else
		{
			startTimer();
			std::fstream info;
			info.open("liveChatInfoOutput.log", std::ios::app);
			info << ostatniaLinia.substr(0, 33) << "Timer - START";
			info.close();
		}
		return 1;
	}

	pNickChange(ostatniaLinia);

	_quit = fConsoleInput(ostatniaLinia);
	if (_quit)
	{
		Beep(dzwiekGlowny, 100);
		Beep(0, interval);
		if (_quit == 2)
			return 0; //close Logus
	}

	if (chatSound)
	{
		Beep(750, 50);
		timer -= 50; //darxe po co to?
	}

	return 1;
}