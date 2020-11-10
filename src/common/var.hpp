// Copyright © 2018-2020  DarXe
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef VAR_HPP_INCLUDED
#define VAR_HPP_INCLUDED


//standard libraries
#include <windows.h>
#include <string>
#include <vector>
#include <ctime>


//header includes
#include <timer.hpp>


//var (ZMIENNE)
//logus.ini
extern std::string relVer;
extern std::string titleVer;
extern std::string serverIP; //ip server
extern std::string ver; //version variable, not editable //zmienna wersji, nie wolno edytować
extern std::string updateChannel;
extern std::string mtaLocation;
extern int dzwiekGlowny; //sound message //dźwięk komunikatów
extern bool fLockTeam; //lock beep(TEAM)
extern bool fLockPW; //lock beep priv message
extern bool fLockReport; //lock beep for transport
extern bool fLockNick; //lock beep nick 'nick: message'
extern bool engLang; // Logus in English
extern bool chatSound; //the sound of any chat message //dźwięk każdej wiadomości na czacie
extern int lcLines; //displayed rows in LiveChat
extern int refresh; //refresh<ms> in LiveChat
extern int interval; //time interval between sounds //odstęp czasowy(ms) między kolejnymi dźwiękami
extern std::string nick; //nickname on MTA
extern bool dynamicRefresh; //dynamic refresh in LiveChat //dynamiczne odświeżanie w LC
extern std::vector <std::string> nicknames; //nicknames database
extern std::vector <std::string> phrases; //player nick's variants to look for
extern int czas; //TIMER time set by the player in seconds to load / unload the cargo
extern bool random; //TIMER random unloading, TRUE = 'skrypt' FALSE = 'sam wybiore'
extern long long money; //courses calculator - money for delivered courses //pieniądze za kursy
extern long long courses; //courses calculator - number of courses //ilość kursów
extern int maxsalary;
extern int minsalary;
extern short fastStart; //start Logus + LiveChat with MTA or skipping the version info
extern short trackId; //ap-ls ls-ap itp itd
extern bool autoMoveLogs; //amount of logs to move
extern float grade; //pay grade
extern float base_dealerBuy; //base price for skup pojazdu lol
extern float base_dealerSellCar; //base price for sprzedaz pojazdu osobowego lol
extern float base_dealerSellTransport; //base price for sprzedaz pojazdu dostawczego lol
extern bool dealerManual; //manual car database edit
extern short minRefresh; //minimal refresh in livechat
extern short maxRefresh; //max refresh in livechat
extern bool autoOpenGate;
extern bool timestamp;
extern bool renderEngine;

extern const short gt; //auxiliary variable
extern const HANDLE h;
 
extern std::string consoleLogPath;
extern std::string consoleLog1Path;
extern std::string consoleLog2Path;
extern std::string consoleLog3Path;
extern std::string consoleLog4Path;
extern std::string consoleLog5Path;

extern const std::string track[];
extern Timer mainTimer; //TIMER countdown of time for unloading //odliczanie czasu do rozładowania
extern int avg; //courses calculator - average //średnia kursów

#endif