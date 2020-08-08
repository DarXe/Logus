// Copyright (C) 2018-2020  DarXe

#ifndef VAR_HPP_INCLUDED
#define VAR_HPP_INCLUDED

//var (ZMIENNE)
//logus.ini
std::string tempVer;
std::string mtasa = "185.62.189.174:22003"; //ip server
std::string ver = genVer(); //version variable, not editable //zmienna wersji, nie wolno edytować
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
bool ang = 0; //ANG version - flag on PTS
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
short trackId = 0;
int autoMoveLogs = 0;
float grade = 0;
std::string mess; // used in ifs to determine language

const short gt = 33; //auxiliary variable
int leng = 0; //length
char wyb = ' '; //auxiliary variable //wybór w menu, tymczasowa w fTransport
int iloscLinijekAll = 0; //number of lines
std::string a = "console.log";
std::string b = "console.log.1";
std::string c = "console.log.2";
std::string d = "console.log.3";
std::string e = "console.log.4";
std::string f = "console.log.5";
std::string L = "logus.log";
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
COORD pos;

std::string track[5] = {"     [0]     "," (AP1 - LOT1)"," (LOT2 - AP1)"," (AP2 - LOT2)"," (LOT1 - AP2)"};
clock_t delay = 0, delay2 = 0; //pomiary delay
int temp = 0; //aux var //pomocnicza zmienna iloscLinijek w LiveChat
int temp2 = 0; //aux var //pomocnicza2 w LiveChat
int errors = 0; //the number of errors //liczenie błędów, jeśli liczba linijek przekroczy 10
std::string s_temp = ""; //string temp
int timer = 0; //TIMER countdown of time for unloading //odliczanie czasu do rozładowania
bool isTimer = 0; //TIMER aux var //pomocnicza zmienna - czy timer ma odliczac
bool isCzas = 0; //TIMER aux var //pomocnicza zmienna - czas po zaladowaniu, odliczanie
int avg = 0; //courses calculator - average //średnia kursów
bool timestamps = 0; //show timestamps in LiveChat //pokaż date obok logów w LiveChat
clock_t t; // clock to check code speed

#endif