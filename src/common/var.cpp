// Copyright © 2018-2020  DarXe
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//header includes
#include "var.hpp"


//forward declarations
std::string genVer(); //from config.hpp


//var (ZMIENNE)
//logus.ini
std::string relVer;
std::string titleVer;
std::string serverIP = "185.62.189.174:22003"; //ip server
std::string ver = genVer(); //version variable, not editable //zmienna wersji, nie wolno edytować
std::string updateChannel = "experimental";
std::string mtaLocation = "";
int dzwiekGlowny = 1777; //sound message //dźwięk komunikatów
bool fLockTeam = 0; //lock beep(TEAM)
bool fLockPW = 0; //lock beep priv message
bool fLockReport = 0; //lock beep for transport
bool fLockNick = 0; //lock beep nick 'nick: message'
bool engLang = 0; // Logus in English
bool chatSound = 0; //the sound of any chat message //dźwięk każdej wiadomości na czacie
int lcLines = 15; //displayed rows in LiveChat
int refresh = 300; //refresh<ms> in LiveChat
int interval = 50; //time interval between sounds //odstęp czasowy(ms) między kolejnymi dźwiękami
std::string nick = "PodajSwojNick"; //nickname on MTA
bool dynamicRefresh = 0; //dynamic refresh in LiveChat //dynamiczne odświeżanie w LC
std::vector <std::string> nicknames; //nicknames database
std::vector <std::string> phrases; //player nick's variants to look for
int czas = 90; //TIMER time set by the player in seconds to load / unload the cargo
bool random = 0; //TIMER random unloading, TRUE = 'skrypt' FALSE = 'sam wybiore'
long long money = 0; //courses calculator - money for delivered courses //pieniądze za kursy
long long courses = 0; //courses calculator - number of courses //ilość kursów
int maxsalary = 0;
int minsalary = 0;
short fastStart = 0; //start Logus + LiveChat with MTA or skipping the version info
short trackId = 0; //ap-ls ls-ap itp itd
bool autoMoveLogs = 1; //auto move Logs?
float grade = 0; //pay grade
float base_dealerBuy = 0.40; //base price for skup pojazdu lol
float base_dealerSellCar = 0.65; //base price for sprzedaz pojazdu osobowego lol
float base_dealerSellTransport = 0.80; //base price for sprzedaz pojazdu dostawczego lol
bool dealerManual = 0; //manual car database edit
short minRefresh = 250; //minimal refresh in livechat
short maxRefresh = 1250; //max refresh in livechat
bool autoOpenGate = 0;
bool timestamp = 0;
bool renderEngine = 1;

const short gt = 33; //auxiliary variable
const HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

std::string consoleLogPath;
std::string consoleLog1Path;
std::string consoleLog2Path;
std::string consoleLog3Path;
std::string consoleLog4Path;
std::string consoleLog5Path;

const std::string track[] = {"     [0]     "," (AP1 - LOT1)"," (LOT2 - AP1)"," (AP2 - LOT2)"," (LOT1 - AP2)"};
Timer mainTimer;
int avg = 0; //courses calculator - average //średnia kursów
