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
#include "livechat_actions.hpp"
#include "livechat_events.hpp"
#include "livechat_cmd.hpp"


//foward declarations
void serverConnect(); //from proc.hpp

bool LCEvent::Team(const std::string &line, const bool &includePlayer)
{
	// [2020-10-28 17:42:08] [Output] : (TEAM) Niventill: ess
	if (line.find("[Output] : (TEAM) ") != std::string::npos)
	{
		if (line.find("[Output] : (TEAM) " + nick) != std::string::npos)
			if (includePlayer)
				return 1;
			else
				return 0;
		return 1;
	}
	else
		return 0;
}

bool LCEvent::PmFrom(const std::string &line)
{
	return (line.find("[Output] : * PW od ") != std::string::npos || line.find("[Output] : * PM from ") != std::string::npos);
}

bool LCEvent::PmTo(const std::string &line)
{
	return (line.find("[Output] : -> ") != std::string::npos);
}

bool LCEvent::TransfersFrom(const std::string &line)
{
	//[2020-08-09 21:06:56] [Output] : Gracz SpookyTank przelał tobie 1500$.
	//[2020-08-30 16:35:09] [Output] : Player DarXe transferred to you $1.
	if ((line.find("[Output] : Gracz ") != std::string::npos) || (line.find("[Output] : Player ") != std::string::npos))
		return ((line.find(" przelał tobie ") != std::string::npos) || (line.find(" transferred to you") != std::string::npos));
	return 0;
}

bool LCEvent::TransfersTo(const std::string &line)
{
	//[2020-08-29 15:34:28] [Output] : Przelałeś 1000000$ graczowi DarXe.
	//[2020-08-30 16:34:52] [Output] : You gave $1 to player DarXe.
	if ((line.find("[Output] : Przelałeś ") != std::string::npos) || (line.find("[Output] : You gave $") != std::string::npos))
		return ((line.find(" to player ") != std::string::npos) || (line.find(" graczowi ") != std::string::npos));
	return 0;
}

bool LCEvent::Report(const std::string &line)
{
	// [Output] : Nowy raport - autor: Niventill, kategoria: Naprawa
	// [Output] : author: Niventill, category: Repair
	return (line.find("[Output] : Nowy raport - ") != std::string::npos || line.find("[Output] : New report - ") != std::string::npos);
}

bool LCEvent::Transport(const std::string &line)
{
	//[2019-05-24 17:02:41] [Output] : You've earned $2792. It has been transfered to your company's account.
	//[2019-05-24 17:02:41] [Output] : Pieniądze za transport 3191$ zostały przelane na konto firmy.
	return (line.find("[Output] : Pieniądze za ") != std::string::npos || line.find("[Output] : You've ") != std::string::npos);
}

bool LCEvent::Nicknames(const std::string &line)
{
	//[2020-10-28 18:29:00] [Output] : Gracz Niventill zaraz wraca.
	//[2020-10-28 18:29:00] [Output] : Player Niventill is away from keyboard.
	//[2020-10-28 18:29:01] [Output] : Gracz Niventill wrócił.
	//[2020-10-28 18:29:00] [Output] : Player Niventill returned.
	//[2020-10-28 19:05:51] [Output] : * SpookyTank has joined the game
	for (int i = 0; i < nicknames.size(); i++)
	{
		//chat
		//if(line[gt+leng]==s_temp[leng]&&line[gt+leng-1]==s_temp[leng-1]&&line[gt+leng-2]==s_temp[leng-2])
		//	return 0;
		//join
		if (line.find("[Output] : * " + nicknames.at(i)) != std::string::npos)
			return 1;
		//afk
		if (line.find("[Output] : Gracz " + nicknames.at(i) + " zaraz ") != std::string::npos || line.find("[Output] : Player " + nicknames.at(i) + " is away ") != std::string::npos)
			return 1;
		if (line.find("[Output] : Gracz " + nicknames.at(i) + " wrócił ") != std::string::npos || line.find("[Output] : Player " + nicknames.at(i) + " returned ") != std::string::npos)
			return 1;
	}
	return 0;
}

bool LCEvent::BindKey(const std::string &line)
{
	//[2020-06-12 00:11:39] [Output] : msg: You cannot message yourself
	return (line.find("[Output] : msg: You cannot ") != std::string::npos);
}

bool LCEvent::Open(const std::string &line)
{
	return (line[line.length() - 2] == 'n' && line[line.length() - 3] == 'e' && line[line.length() - 4] == 'p' && line[line.length() - 5] == 'o');
}

/*bool LCEvent::Player(const std::string &line)
{
	return (line[gt] == '*' && line[gt] == '*');
}*/

/*bool LCEvent::PlayerCount(const std::string &line)
{
	//[2019-05-24 17:02:41] [Output] : You've earned $2792. It has been transfered to your company's account.
	//[2019-05-24 17:02:41] [Output] : Pieniądze za transport 3191$ zostały przelane na konto firmy.
	return ((line[gt] == 'Y' && line[gt + 4] == 'v' && line[gt + 14] == '$') || (line[gt] == 'P' && line[gt + 1] == 'i' && line[gt + 2] == 'e' && line[gt + 3] == 'n' && line[gt + 4] == 'i'));
}*/

bool LCEvent::Freeze(const std::string &line)
{
	return (line.find("[Output] : Nie ma lekarzy na serwerze. Za ") != std::string::npos || line.find("[Output] : There's no medics right here on the serwer. Wait ") != std::string::npos);
}

bool LCEvent::NickChange(const std::string &line)
{
	//[2020-08-30 04:03:19] [Output] : * Niventill is now known as test
	return (line.find("[Output] : * " + nick + " is now known as ") != std::string::npos);
}

bool LCEvent::ContainsPhrase(const std::string &line)
{
	if (LCEvent::PmFrom(line) || LCEvent::Team(line, 0) || line.find("[Output] : " + nick) != std::string::npos)
		return 0;
	for (int i = 0; i < phrases.size(); i++)
	{
		if (line.find(phrases[i], line.find(":", gt)) != std::string::npos)
			return 1;
	}
	return 0;
}