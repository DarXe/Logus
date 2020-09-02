// Copyright © 2018-2020  DarXe
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#ifndef VAR_HPP_INCLUDED
#define VAR_HPP_INCLUDED

//var (ZMIENNE)
//logus.ini
std::string serverIP = "185.62.189.174:22003"; //ip server
std::string ver = genVer(); //version variable, not editable //zmienna wersji, nie wolno edytować
std::string mtaLocation = "";
int dzwiekGlowny = 1777; //sound message //dźwięk komunikatów
bool fLockTeam = 0; //lock beep(TEAM)
bool fLockPW = 0; //lock beep priv message
bool fLockKomunikat = 0; //lock beep for transport
bool fLockNick = 0; //lock beep nick 'nick: message'
bool engLang = 0; // Logus in English
bool chatSound = 0; //the sound of any chat message //dźwięk każdej wiadomości na czacie
std::string kolorGlowny = "A"; //main color //kolor główny(przy wyszukiwaniu logów)
int wyswietlaneWiersze = 15; //displayed rows in LiveChat
int refresh = 300; //refresh<ms> in LiveChat
int interval = 50; //time interval between sounds //odstęp czasowy(ms) między kolejnymi dźwiękami
std::string nick = "PodajSwojNick"; //nickname on MTA
bool dynamicRefresh = 0; //dynamic refresh in LiveChat //dynamiczne odświeżanie w LC
std::vector<std::string> nicknames; //nicknames database
int czas = 90; //TIMER time set by the player in seconds to load / unload the cargo
bool random = 0; //TIMER random unloading, TRUE = 'skrypt' FALSE = 'sam wybiore'
int money = 0; //courses calculator - money for delivered courses //pieniądze za kursy
int courses = 0; //courses calculator - number of courses //ilość kursów
short fastStart = 0; //start Logus + LiveChat with MTA or skipping the version info
bool codePage852 = 0; //false:UTF-8 lub true:852 (jesli wystepuja krytyczne bugi)
short trackId = 0; //ap-ls ls-ap itp itd
bool autoMoveLogs = 0; //amount of logs to move
float grade = 0; //pay grade
std::string mess; // used in ifs to determine language
float base_dealerBuy = 0.40; //base price for skup pojazdu lol
float base_dealerSellCar = 0.65; //base price for sprzedaz pojazdu osobowego lol
float base_dealerSellTransport = 0.80; //base price for sprzedaz pojazdu dostawczego lol
bool dealerManual = 0; //manual car database edit
short minRefresh = 250; //minimal refresh in livechat
short maxRefresh = 1250; //max refresh in livechat
bool autoOpenGate = 0;

const short gt = 33; //auxiliary variable
int leng = 0; //length
char wyb = ' '; //auxiliary variable //wybór w menu, tymczasowa w fTransport
const HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
COORD pos;
COORD tpos;

std::string consoleLogPath;
std::string consoleLog1Path;
std::string consoleLog2Path;
std::string consoleLog3Path;
std::string consoleLog4Path;
std::string consoleLog5Path;

const std::string track[5] = {"     [0]     "," (AP1 - LOT1)"," (LOT2 - AP1)"," (AP2 - LOT2)"," (LOT1 - AP2)"};
clock_t delay = 0, delay2 = 0; //pomiary delay
int temp = 0; //aux var //pomocnicza zmienna iloscLinijek w LiveChat
int temp2 = 0; //aux var //pomocnicza2 w LiveChat
std::string s_temp = ""; //string temp
char _quit; //used in fConsoleInput (quits logus if mta was closed via "quit" in mta console)
int timer = 0; //TIMER countdown of time for unloading //odliczanie czasu do rozładowania
bool isTimer = 0; //TIMER aux var //pomocnicza zmienna - czy timer ma odliczac
bool isCzas = 0; //TIMER aux var //pomocnicza zmienna - czas po zaladowaniu, odliczanie
int avg = 0; //courses calculator - average //średnia kursów
bool timestamps = 0; //show timestamps in LiveChat //pokaż date obok logów w LiveChat
clock_t t; // clock to check code speed

#endif