// Copyright (C) 2018-2019  DarXe

//var (ZMIENNE)
//logus.ini
string mtasa = "185.62.189.174:22003"; //ip server
const int ver = 190804; //version variable, not editable //zmienna wersji, nie wolno edytować
int dzwiekGlowny = 1777; //sound message //dźwięk komunikatów
bool fLockTeam = 0; //lock beep(TEAM)
bool fLockPW = 0; //lock beep priv message
bool fLockKomunikat = 0; //lock beep for transport
bool fLockNick = 0; //lock beep nick 'nick: message'
bool menuGlowne = 0; //menu without PL chars //menu bez ąęźć.. 
bool chatSound = 0; //the sound of any chat message //dźwięk każdej wiadomości na czacie
string kolorGlowny = "A"; //main color //kolor główny(przy wyszukiwaniu logów)
int wyswietlaneWiersze = 15; //displayed rows in LiveChat
int refresh = 300; //refresh<ms> in LiveChat
bool ang = 0; //ANG version - flag on PTS
int interval = 50; //time interval between sounds //odstęp czasowy(ms) między kolejnymi dźwiękami
string nick = "PodajSwojNick"; //nickname on MTA
bool dynamicRefresh = 0; //dynamic refresh in LiveChat //dynamiczne odświeżanie w LC
vector<string> nicknames; //nicknames database
int czas = 90; //TIMER time set by the player in seconds to load / unload the cargo
bool random = 0; //TIMER random unloading, TRUE = 'skrypt' FALSE = 'sam wybiore'
int money = 0; //courses calculator - money for delivered courses //pieniądze za kursy
int courses = 0; //courses calculator - number of courses //ilość kursów
short fastStart = 0; //start Logus + LiveChat with MTA or skipping the version info
bool codePage852 = 0; //false:UTF-8 lub true:852 (jesli wystepuja krytyczne bugi)
short trackId = 0;
int autoMoveLogs = 0;
float grade = 0;

short gt = 33; //auxiliary variable
int leng = 0; //length
fstream plik;
string linia = " ";
char wyb = ' '; //auxiliary variable //wybór w menu, tymczasowa w fTransport
int iloscLinijekAll = 0; //number of lines
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
COORD pos;
string a = "console.log";
string b = "console.log.1";
string c = "console.log.2";
string d = "console.log.3";
string e = "console.log.4";
string f = "console.log.5";
string L = "logus.log";

//liveChat
clock_t delay = 0, delay2 = 0; //pomiary delay
int iloscLinijek = 0;
string ostatniaLinia[11]; //ostatnie linie
int temp = 0; //aux var //pomocnicza zmienna iloscLinijek w LiveChat
int temp2 = 0; //aux var //pomocnicza2 w LiveChat
int errors = 0; //the number of errors //liczenie błędów, jeśli liczba linijek przekroczy 10
string s_temp = ""; //string temp
int timer = 0; //TIMER countdown of time for unloading //odliczanie czasu do rozładowania
bool isTimer = 0; //TIMER aux var //pomocnicza zmienna - czy timer ma odliczac
bool isCzas = 0; //TIMER aux var //pomocnicza zmienna - czas po zaladowaniu, odliczanie
int avg = 0; //courses calculator - average //średnia kursów
bool timestamps = 0; //show timestamps in LiveChat //pokaż date obok logów w LiveChat
string track[5] = {"     [0]     "," (AP1 - LOT1)"," (LOT2 - AP1)"," (AP2 - LOT2)"," (LOT1 - AP2)"};