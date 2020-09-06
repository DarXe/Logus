// Copyright © 2018-2020  DarXe
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#ifndef VAR_HPP_INCLUDED
#define VAR_HPP_INCLUDED

#include <windows.h>
#include <vector>
#include <ctime>

std::string genVer();

//var (ZMIENNE)
//logus.ini
extern std::string relVer;
extern std::string serverIP; //ip server
extern std::string ver; //version variable, not editable //zmienna wersji, nie wolno edytować
extern std::string updateChannel;
extern std::string mtaLocation;
extern int dzwiekGlowny; //sound message //dźwięk komunikatów
extern bool fLockTeam; //lock beep(TEAM)
extern bool fLockPW; //lock beep priv message
extern bool fLockKomunikat; //lock beep for transport
extern bool fLockNick; //lock beep nick 'nick: message'
extern bool engLang; // Logus in English
extern bool chatSound; //the sound of any chat message //dźwięk każdej wiadomości na czacie
extern std::string kolorGlowny; //main color //kolor główny(przy wyszukiwaniu logów)
extern int wyswietlaneWiersze; //displayed rows in LiveChat
extern int refresh; //refresh<ms> in LiveChat
extern int interval; //time interval between sounds //odstęp czasowy(ms) między kolejnymi dźwiękami
extern std::string nick; //nickname on MTA
extern bool dynamicRefresh; //dynamic refresh in LiveChat //dynamiczne odświeżanie w LC
extern std::vector<std::string> nicknames; //nicknames database
extern int czas; //TIMER time set by the player in seconds to load / unload the cargo
extern bool random; //TIMER random unloading, TRUE = 'skrypt' FALSE = 'sam wybiore'
extern int money; //courses calculator - money for delivered courses //pieniądze za kursy
extern int courses; //courses calculator - number of courses //ilość kursów
extern short fastStart; //start Logus + LiveChat with MTA or skipping the version info
extern bool codePage852; //false:UTF-8 lub true:852 (jesli wystepuja krytyczne bugi)
extern short trackId; //ap-ls ls-ap itp itd
extern bool autoMoveLogs; //amount of logs to move
extern float grade; //pay grade
extern std::string mess; // used in ifs to determine language
extern float base_dealerBuy; //base price for skup pojazdu lol
extern float base_dealerSellCar; //base price for sprzedaz pojazdu osobowego lol
extern float base_dealerSellTransport; //base price for sprzedaz pojazdu dostawczego lol
extern bool dealerManual; //manual car database edit
extern short minRefresh; //minimal refresh in livechat
extern short maxRefresh; //max refresh in livechat
extern bool autoOpenGate;

extern short gt; //auxiliary variable
extern int leng; //length
extern char wyb; //auxiliary variable //wybór w menu, tymczasowa w fTransport
extern HANDLE h;
extern COORD pos;
extern COORD tpos;
 
extern std::string consoleLogPath;
extern std::string consoleLog1Path;
extern std::string consoleLog2Path;
extern std::string consoleLog3Path;
extern std::string consoleLog4Path;
extern std::string consoleLog5Path;

extern std::string track[];
extern clock_t delay, delay2; //pomiary delay
extern int temp; //aux var //pomocnicza zmienna iloscLinijek w LiveChat
extern int temp2; //aux var //pomocnicza2 w LiveChat
extern std::string s_temp; //string temp
extern char _quit; //used in fConsoleInput (quits logus if mta was closed via "quit" in mta console)
extern int timer; //TIMER countdown of time for unloading //odliczanie czasu do rozładowania
extern bool isTimer; //TIMER aux var //pomocnicza zmienna - czy timer ma odliczac
extern bool isCzas; //TIMER aux var //pomocnicza zmienna - czas po zaladowaniu, odliczanie
extern int avg; //courses calculator - average //średnia kursów
extern bool timestamps; //show timestamps in LiveChat //pokaż date obok logów w LiveChat
extern clock_t t; // clock to check code speed

#endif