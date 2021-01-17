// Copyright © 2018-2020  DarXe, Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

//standard libraries
#include <string>
#include <string_view>

//header includes
#include <var.hpp>
#include <config.hpp>
#include <common.hpp>
#include "livechat_eventhandlers.hpp"
#include "livechat_events.hpp"
#include "livechat_cmd.hpp"

//foward declarations
void serverConnect(); //from proc.hpp

bool LCEvent::Team(const std::string_view line, const bool &includePlayer, const bool &onlyPlayer)
{
  // [2020-10-28 17:42:08] [Output] : (TEAM) Niventill: ess
  if (lcompare(line, "[Output] : (TEAM) "))
  {
    if (lcompare(line, "[Output] : (TEAM) " + nick))
    {
      if (includePlayer)
        return 1;
      else
        return 0;
    }
    if (!onlyPlayer)
      return 1;
  }
  return 0;
}

bool LCEvent::PmFrom(const std::string_view line)
{
  //[2020-11-08 19:29:09] [Output] : * PW od PanZer:
  //[2020-11-08 19:29:09] [Output] : * PW from PanZer:
  return lcompare(line, "[Output] : * PW od ") || lcompare(line, "[Output] : * PW from ");
}

bool LCEvent::PmTo(const std::string_view line)
{
  //[2020-11-08 19:28:56] [Output] : -> PanZer:
  return lcompare(line, "[Output] : -> ");
}

bool LCEvent::TransfersFrom(const std::string_view line)
{
  //[2020-08-09 21:06:56] [Output] : Gracz SpookyTank przelał tobie 1500$.
  //[2020-08-30 16:35:09] [Output] : Player DarXe transferred to you $1.
  if (lcompare(line, "[Output] : Gracz ") || lcompare(line, "[Output] : Player "))
    return (line.find(" przelał tobie ") != std::string::npos) || (line.find(" transferred to you") != std::string::npos);
  return 0;
}

bool LCEvent::TransfersTo(const std::string_view line)
{
  //[2020-08-29 15:34:28] [Output] : Przelałeś 1000000$ graczowi DarXe.
  //[2020-08-30 16:34:52] [Output] : You gave $1 to player DarXe.
  if (lcompare(line, "[Output] : Przelałeś ") || lcompare(line, "[Output] : You gave $"))
    return (line.find(" to player ") != std::string::npos) || (line.find(" graczowi ") != std::string::npos);
  return 0;
}

bool LCEvent::Report(const std::string_view line)
{
  // [Output] : Nowy raport - autor: Niventill, kategoria: Naprawa
  // [Output] : author: Niventill, category: Repair
  return lcompare(line, "[Output] : Nowy raport - ") || lcompare(line, "[Output] : New report - ");
}

bool LCEvent::TransportCompany(const std::string_view line)
{
  //[2019-05-24 17:02:41] [Output] : You've earned $2792. It has been transfered to your company's account.
  //[2019-05-24 17:02:41] [Output] : Pieniądze za transport 3191$ zostały przelane na konto firmy.
  return lcompare(line, "[Output] : Pieniądze za ") || lcompare(line, "[Output] : You've ");
}

bool LCEvent::TransportTruckerzy(const std::string_view line)
{
  //[2020-11-07 21:56:04] [Output] : Otrzymałeś 44$ za transport.
  //[2020-11-07 22:11:45] [Output] : Received $5 for transport.
  return lcompare(line, "[Output] : Otrzymałeś ") || lcompare(line, "[Output] : Received $");
}

bool LCEvent::Nicknames(const std::string_view line)
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
    if (lcompare(line, "[Output] : * " + nicknames[i]))
      return 1;
    //afk
    if (lcompare(line, "[Output] : Gracz " + nicknames[i] + " zaraz ") || lcompare(line, "[Output] : Player " + nicknames[i] + " is away "))
      return 1;
    if (lcompare(line, "[Output] : Gracz " + nicknames[i] + " wrócił ") || lcompare(line, "[Output] : Player " + nicknames[i] + " returned "))
      return 1;
  }
  return 0;
}

bool LCEvent::BindKey(const std::string_view line)
{
  //[2020-06-12 00:11:39] [Output] : msg: Player not found
  return lcompare(line, "[Output] : msg: Player not ");
}

bool LCEvent::Open(const std::string_view line)
{
  return (line[line.length() - 2] == 'n' && line[line.length() - 3] == 'e' && line[line.length() - 4] == 'p' && line[line.length() - 5] == 'o');
}

/*bool LCEvent::Player(const std::string_view line)
{
	return (line[gt] == '*' && line[gt] == '*');
}*/

/*bool LCEvent::PlayerCount(const std::string_view line)
{
	//[2019-05-24 17:02:41] [Output] : You've earned $2792. It has been transfered to your company's account.
	//[2019-05-24 17:02:41] [Output] : Pieniądze za transport 3191$ zostały przelane na konto firmy.
	return ((line[gt] == 'Y' && line[gt + 4] == 'v' && line[gt + 14] == '$') || (line[gt] == 'P' && line[gt + 1] == 'i' && line[gt + 2] == 'e' && line[gt + 3] == 'n' && line[gt + 4] == 'i'));
}*/

bool LCEvent::Freeze(const std::string_view line)
{
  return lcompare(line, "[Output] : Nie ma lekarzy na serwerze. Za ") || lcompare(line, "[Output] : There's no medics right here on the serwer. Wait ");
}

bool LCEvent::NickChange(const std::string_view line)
{
  //[2020-08-30 04:03:19] [Output] : * Niventill is now known as test
  return lcompare(line, "[Output] : * " + nick + " is now known as ");
}

bool LCEvent::ContainsPhrase(const std::string_view line, const bool &format)
{
  // [2020-10-29 15:54:05] [Output] : Gracz: DarXe Team: 15, 3152$, Tytul: Gracz DarXe rozładował towar Pucolana, waga: 1.1, wynagrodzenie: 3152$.
  // i sporo innych rzeczy, co sprawia, że if niżej jest nieczytelny
  if (format)
  {
    if (lcompare(line, "[Output] : Gracz: " + nick + " Team: ") || lcompare(line, "[Output] : Name: " + nick + ", "))
      return 0;
  }
  else
  {
    if (LCEvent::PmTo(line) || (fLockTeam && LCEvent::Team(line, 1, 1)) || (!fLockTeam && LCEvent::Team(line, 0)) || (!fLockPW && LCEvent::PmFrom(line)) || LCEvent::Input(line) || lcompare(line, "[Output] : " + nick) ||
        lcompare(line, "[Output] : Gracz: " + nick + " Team: ") || lcompare(line, "[Output] : Name: " + nick + ", "))
      return 0;
  }
  for (int i = 0; i < phrases.size(); i++)
  {
    if (line.find(phrases[i], line.find(":", gt)) != std::string::npos)
      return 1;
  }
  return 0;
}

bool LCEvent::NormalMessage(const std::string_view line)
{
  for (int i = gt; i < line.size(); i++)
  {
    if (line[i] == ' ')
      return 0;
    else if (line[i] == ':')
      return 1;
  }
  return 0;
}

bool LCEvent::Admin(const std::string_view line, const bool &includePlayer)
{
  // [2020-10-28 17:42:08] [Output] : (ADMIN) Niventill: ess
  if (lcompare(line, "[Output] : (ADMIN) "))
  {
    if (lcompare(line, "[Output] : (ADMIN) " + nick))
    {
      if (includePlayer)
        return 1;
      else
        return 0;
    }
    return 1;
  }
  else
    return 0;
}

bool LCEvent::Input(const std::string_view line)
{
  // [2020-11-03 23:06:48] [Input]  : disconnect
  if (line[gt - 10] == 'I')
    return 1;
  return 0;
}

bool LCEvent::CB(const std::string_view line)
{
  // [2020-10-28 17:42:08] [Output] : (CB 19): ess
  return lcompare(line, "[Output] : (CB ");
}

bool notifCheck(std::string_view line)
{
  return (LCEvent::Nicknames(line) || LCEvent::TransportCompany(line) || LCEvent::TransportTruckerzy(line) || LCEvent::Report(line) || LCEvent::TransfersFrom(line) || LCEvent::PmFrom(line) || LCEvent::ContainsPhrase(line) || LCEvent::Team(line, 0));
}