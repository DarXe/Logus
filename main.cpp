// Logus Copyright 2018-2019 (C) DarXe

#include <iostream>
#include <fstream>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <vector>

using namespace std;

//var (ZMIENNE)
//logus.ini
string mtasa = "185.62.189.174:22003"; //ip server; ip serwera
const int ver = 190622; //version variable, not editable; zmienna wersji, nie wolno edytować
int dzwiekGlowny = 1777; //sound message; dźwięk komunikatów
bool fLockTeam = 0; //lock beep(TEAM)
bool fLockPW = 0; //lock beep(TEAM)
bool fLockKomunikat = 0; //lock beep(TEAM)
bool fLockNick = 0; //lock beep nick 'nick: message'
bool menuGlowne = 1; //menu without PL chars; menu bez ąęźć.. 
bool chatSound = 0; //the sound of any chat message; dźwięk każdej wiadomości na czacie
string kolorGlowny = "A"; //main color; kolor główny(przy wyszukiwaniu logów)
int wyswietlaneWiersze = 15; //displayed rows in LiveChat
int refresh = 300; //refresh<ms> in LiveChat
bool ang = 0; //ANG version - flag on PTS
int interval = 50; //time interval between sounds; odstęp czasowy(ms) między kolejnymi dźwiękami
string nick = "PodajSwojNick"; //nickname on MTA; nick na MTA
bool dynamicRefresh = 0; //dynamic refresh in LiveChat; dynamiczne odświeżanie w LC
vector<string> nicknames; //nicknames database
int czas = 90; //TIMER time set by the player in seconds to load / unload the cargo;
bool random = 0; //TIMER random unloading, TRUE = 'skrypt' FALSE = 'sam wybiore'
int money = 0; //courses calculator - money for delivered courses; pieniądze za kurs
int courses = 0; //courses calculator - number of courses; ilość kursów
short fastStart = 0; //start Logus + LiveChat with MTA or skipping the version info
bool codePage852 = 0; //false:UTF-8 lub true:852 (jesli wystepuja krytyczne bugi)

short gt = 33; //auxiliary variable; gdzie sie zaczyna główny tekst
int leng = 0; //length
fstream plik;
string linia = " ";
char wyb = ' '; //auxiliary variable; wybór w menu; tymczasowa w fTransport
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
//clock_t t1 = 0, t2 = 0; //pomiary delay
int iloscLinijek = 0;
string ostatniaLinia[11]; //ostatnie linie
int temp = 0; //aux var; pomocnicza zmienna iloscLinijek w LiveChat
int temp2 = 0; //aux var; pomocnicza2 w LiveChat
int errors = 0; //the number of errors; liczenie błędów, jeśli liczba linijek przekroczy 10;
string s_temp = ""; //string temp
int timer = 0; //TIMER countdown of time for unloading; odliczanie czasu do rozładowania
bool isTimer = 0; //TIMER aux var; pomocnicza zmienna - czy timer ma odliczac
bool isCzas = 0; //TIMER aux var; pomocnicza zmienna - czas po zaladowaniu, odliczanie
int avg = 0; //courses calculator - average; średnia kursów
bool timestamps = 0; //show timestamps in LiveChat; pokaż date obok logów w LiveChat
string track[5] = {"########","AP1-LOT1","LOT2-AP1","AP2-LOT2","LOT1-AP2"};
short trackId = 0;

int console();
void liveChat(int &wyswietlaneWiersze);
void liveChatBeep(string &ostatniaLinia);
int all(string &nazwa, int nrPliku);
int teamsay(string &nazwa, int nrPliku);
int pw(string &nazwa, int nrPliku);
int przelewy(string &nazwa, int nrPliku);
int nickname(string &nazwa, int nrPliku);
string randomColor();
void moveLogs();
int getVer();
void zapis();
void odczyt();
void patch();
void readDefault();

//func
//(team) [pts]nick
bool fTeam(string &linia, bool e) //e - uwzglednianie wlasnego nicku(wspolna funkcja, dlatego wyjatek)
{
    leng = nick.length();
    if(linia[gt]=='('&&linia[gt+1]=='T'&&linia[gt+2]=='E'&&linia[gt+3]=='A'&&linia[gt+4]=='M')
    {
        if(e) return 1;
        if(linia[gt+6+leng]!=nick[leng-1]||linia[gt+5+leng]!=nick[leng-2]||linia[gt+4+leng]!=nick[leng-3])
            return 1; 
        else return 0;
    }
    else return 0;
}

bool fPwOd(string &linia, bool &ang)
{
    if(ang)
    {
        if(linia[gt]=='*'&&linia[gt+2]=='P'&&linia[gt+3]=='M')
            return 1;
        else return 0;
    }
    else
    {
        if(linia[gt]=='*'&&linia[gt+2]=='P'&&linia[gt+3]=='W')
            return 1;
        else return 0;
    }
}

bool fPwDo(string &linia)
{
    if(linia[gt]=='-'&&linia[gt+1]=='>')
        return 1;
    else return 0;
}

bool fPrzelewyOd(string &linia, bool &ang)
{
    leng = linia.length();
    if(ang)
    {
        if(linia[gt]=='P'&&linia[gt+1]=='l'&&linia[gt+2]=='a'&&linia[gt+3]=='y'&&linia[gt+4]=='e'&&linia[gt+6]==' '&&linia[leng-2]!='d'&&linia[leng-1]=='.'&&(linia[leng-3]!=' '&&linia[leng-5]!='e'))
            return 1;
        else return 0;
    }
    else
    {
        if(linia[gt]=='G'&&linia[gt+1]=='r'&&linia[gt+2]=='a'&&linia[gt+3]=='c'&&linia[gt+4]=='z'&&linia[gt+5]==' '&&linia[leng-2]=='$'&&linia[leng-1]=='.')
            return 1;
        else return 0;
    }
}

bool fPrzelewyDo(string &linia, bool &ang)
{
    if(ang)
    {
        if(linia[gt]=='Y'&&linia[gt+1]=='o'&&linia[gt+2]=='u'&&linia[gt+4]=='g'&&linia[gt+6]=='v')
            return 1;
        else return 0;
    }
    else
    {
        if(linia[gt]=='P'&&linia[gt+1]=='r'&&linia[gt+2]=='z'&&linia[gt+3]=='e'&&linia[gt+5]=='a')
            return 1;
        else return 0;
    }
}

bool fKomunikat(string &linia, bool &ang)
{
    if(ang)
    {
        if(linia[gt]=='N'&&linia[gt+1]=='e'&&linia[gt+3]==' '&&linia[gt+8]=='r')
            return 1;
        else return 0;
    }
    else
    {
        if(linia[gt]=='N'&&linia[gt+1]=='o'&&linia[gt+3]=='y'&&linia[gt+4]==' '&&linia[gt+9]=='r')
            return 1;
        else return 0;
    }
}

void co(string s, int n) //aux void
{
    cout<<s<<": "<<n<<endl;
}

void salaryForTransport(string &linia, bool &ang)
{
    if(ang)
    {
        if(linia[gt+19] == '.')
        {
            int liczba, mnoz=1000;
            for(int i = 48; i<52; i++)//57 58 59 60 61 $xxxx
            {
                liczba = linia[i];
                liczba -= 48;
                money += liczba*mnoz;
                mnoz /= 10;
            }
            courses++;
            zapis();
        }
        else if(linia[gt+18] == '.')
        {
            int liczba, mnoz=100;
            for(int i = 48; i<51; i++)//57 58 59 60 $xxx
            {
                liczba = linia[i];
                liczba -= 48;
                money += liczba*mnoz;
                mnoz /= 10;
            }
            courses++;
            zapis();
        }
    }
    else
    {
        if(linia[61] == '$')
        {
            int liczba, mnoz=1000;
            for(int i = 57; i<61; i++)//57 58 59 60 61 xxxx$
            {
                liczba = linia[i];
                liczba -= 48;
                money += liczba*mnoz;
                mnoz /= 10;
            }
            courses++;
            zapis();
        }
        else if(linia[60] == '$')
        {
            int liczba, mnoz=100;
            for(int i = 57; i<60; i++)//57 58 59 60 xxx$
            {
                liczba = linia[i];
                liczba -= 48;
                money += liczba*mnoz;
                mnoz /= 10;
            }
            courses++;
            zapis();
        }
    }
}

bool fTransport(string &linia, bool &ang)
{
    //[2019-05-24 17:02:41] [Output] : You've earned $2792. It has been transfered to your company's account.
    if(ang)
    {
        if(linia[gt]=='Y'&&linia[gt+4]=='v'&&linia[gt+14]=='$')
            return 1;
        else return 0;
    }
    //[2019-05-24 17:02:41] [Output] : Pieniądze za transport 3191$ zostały przelane na konto firmy.
    else
    {
        if(linia[gt]=='P'&&linia[gt+1]=='i'&&linia[gt+2]=='e'&&linia[gt+3]=='n'&&linia[gt+4]=='i')
            return 1;
        else return 0;
    }
}

bool fNicknames(string &linia)
{   
    for(int i = 0; i<nicknames.size(); i++)
    {
        s_temp = nicknames.at(i);
        leng = s_temp.length() - 1;
        if(linia[gt+leng]==s_temp[leng]&&linia[gt+leng-1]==s_temp[leng-1]&&linia[gt+leng-2]==s_temp[leng-2])
            return 1;
        if(linia[gt]=='*'&&linia[gt+leng+2]==s_temp[leng]&&linia[gt+leng+1]==s_temp[leng-1]&&linia[gt+leng]==s_temp[leng-2])
            return 1;
        if(linia[gt+5]==' '&&linia[gt+leng+6]==s_temp[leng]&&linia[gt+leng+5]==s_temp[leng-1]&&linia[gt+leng+4]==s_temp[leng-2])
            return 1;
    }
    return 0;
}

bool fNick(string &wyraz)
{   
    for(int i = 0; i<nicknames.size(); i++)
    {
        s_temp = nicknames.at(i);
        leng = s_temp.length() - 1;
        //<nick>: message
        if(linia[gt+leng]==s_temp[leng]&&linia[gt+leng-1]==s_temp[leng-1]&&linia[gt+leng-2]==s_temp[leng-2])
            return 1;
        //* <nick> joined
        if(linia[gt]=='*'&&linia[gt+leng+2]==s_temp[leng]&&linia[gt+leng+1]==s_temp[leng-1]&&linia[gt+leng]==s_temp[leng-2])
            return 1;
        //Gracz <nick> <action>
        if(linia[gt+5]==' '&&linia[gt+leng+6]==s_temp[leng]&&linia[gt+leng+5]==s_temp[leng-1]&&linia[gt+leng+4]==s_temp[leng-2])
            return 1;
    }
    return 0;
}

void startTimer(short getSeconds)
{
    if(getSeconds)
    {
        timer = getSeconds*1000;
    }
    else
    {
        timer = czas*1000;
        timer += refresh;
        if(random) timer += 300000; else timer += 360000;
        isCzas = 1;
    }
    isTimer = 1;
    pos.X=0; pos.Y=2; SetConsoleCursorPosition(h, pos);
    SetConsoleTextAttribute(h, 170); cout<<" "; SetConsoleTextAttribute(h, 12);
    cout<<" Timer 0:00  [s]Stop Timer   ";
}

//[2019-06-28 11:58:25] [Input]  : test
bool fConsoleInput(string &linia)
{
    if(linia[gt-10]=='I')
    {
        if(linia[gt]=='r'&&linia[gt+1]!='e') //r /reconnect
        {
            s_temp = "start mtasa://"+mtasa;
            system(s_temp.c_str());
            return 1;
        }
        else if(linia[gt]=='t'&&linia[gt+1]!='e') //t START TIMER
        {
            startTimer(0);
            return 1;
        }
        else if(linia[gt]=='s'&&linia[gt+1]=='e'&&linia[gt+2]=='t')
        {
            if(linia[gt+4]=='t'&&linia[gt+5]=='r') //set tr xx SET TRACK
            {
                if(linia[gt+7]=='0')
                {
                    trackId = 0;
                    return 1;
                }
                else if(linia[gt+7]=='a')
                {
                    if(linia[gt+8]=='1') trackId = 1;
                    else trackId = 3;
                    return 1;
                }
                else
                {
                    if(linia[gt+8]=='1') trackId = 4;
                    else trackId = 2;
                    return 1;
                }
                return 0;
            }
            else if(linia[gt+4]=='t') //set t m:ss || set t m ss SET TIMER M:SS
            {
                int liczba; int temp;
                liczba = linia[gt+6];//min
                liczba -= 48; temp = liczba*60;
                liczba = linia[gt+8];//sec
                liczba -= 48; liczba *=10; temp += liczba;
                liczba = linia[gt+9];//sec
                liczba -= 48; temp += liczba;
                startTimer(temp);
                return 1;
            }
            else return 0;
        }
        else return 0;
    }
    else return 0;
}

void nrPliku(int nr)
{
    if(nr != 10)
    {
        if(!nr)
            cout<<">>>>>>>>>>>>>>>>>>>> logus.log <<<<<<<<<<<<<<<<<<<<"<<endl;
        else
            cout<<">>>>>>>>>>>>>>>>>>>> Plik nr "<<nr<<" <<<<<<<<<<<<<<<<<<<<"<<endl;
    }
        
}
int losuj(int od, int doo)
{
    rand();
    return rand()%(doo - od + 1)+od;
}
void menu();
void menuBezPL();
void wersja();
void cls()
{
    system("cls");
}
char wybor()
{
    cout<<" Wybierz opcje : ";
    return getch();
}
void def()
{
    cls();
    cout<<"\a (INFO) Nie ma takiej opcji!"<<endl;
}
void color(string value);

void intError()
{
    cerr<<"\nERRROR! Podales litere/y!"<<endl;
    cout<<"Program wylaczy sie, uruchom go ponownie"<<endl;
    if(fastStart)
    {
        cout<<"\nMasz wlaczona funkcje fastStart!"<<endl;
        cout<<"Program automatycznie wylaczy funkcje 'szybki start' w celu uniknienia"<<endl;
        cout<<"ponownego polaczenia ze serwerem"<<endl;
        fastStart = 0;
        zapis();
    }
    getch();
}

int main(int argc, char** argv) //maa main
{
    /* int charr;
    while(true)
    {
        charr = getch();
        cout<<charr<<endl;
        if(charr == 27) break;
    }
    return 0;
    fstream plik11;
    string z[5];
    plik11.open("console.log");
    plik11>>z[0]>>z[1];
    cout<<z;
    plik11.close();
    return 0;*/
    fstream plik;
    plik.open("console.log");
        while(!plik.good())
        {
            Beep(dzwiekGlowny,125);
            Beep(0,interval);
            Beep(dzwiekGlowny,125);
            cout<<"Error, nie odnaleziono pliku!"<<endl;
            cout<<"Program Logus musi znajdowac sie w folderze z logami MTA."<<endl;
            Sleep(500);
            cout<<"..\\MTA San Andreas 1.5\\MTA\\logs\\(tutaj wklej program)"<<endl;
            Sleep(500);
            cout<<"Nastepnie uruchom go ponownie\n"<<endl;
            Sleep(2000);
        }
    plik.close();

    plik.open("logus.ini");
        if(plik.good())
        {
            if(getVer() != ver) patch(); else odczyt();
        }
        else
        {
            zapis();
        }
    plik.close();

    SetConsoleTitle("Logus 19.7.6-pre");

    srand(time(NULL));

    console();
    return 0;
}

int getVer()
{
    fstream plik;
    plik.open("logus.ini");
        for(int i(0); i<6; i++) getline(plik,s_temp);
        plik>>s_temp>>temp;
    plik.close();
    return temp;
}

void zapis(){ //saa save
    fstream plik;
    plik.open("logus.ini", ios::out);
        plik<<"////////////////////////////////////////////////////////////////////////////////////////////////\n";
        plik<<"//Witaj w pliku konfiguracyjnym. Aby ręcznie skonfigurować ustawienia, podmień liczbę na inną.\n";
        plik<<"//Pomiędzy nazwą ustawienia a wartością musi być odstęp spacji, np. nazwa_ustawienia: wartość.\n";
        plik<<"//Nie edytuj linii posiadających komentarz '//', w ustawieniach edytuj tylko wartosci\n";
        plik<<"//0 - fałsz, 1 - prawda, kolory: 1-9, A-F"<<endl;
        plik<<"////////////////////////////////////////////////////////////////////////////////////////////////\n";
        plik<<"wersja(nie_edytować): "<<ver<<"\n";
        plik<<"IP_serwera_MTA: "<<mtasa<<"\n";
        plik<<"język_ang_na_pts(0/1): "<<ang<<"\n";
        plik<<"nick_na_pts: "<<nick<<"\n";
        plik<<"dzwięk_główny: "<<dzwiekGlowny<<"\n";
        plik<<"kolor_główny: "<<kolorGlowny<<"\n";
        plik<<"menu_glówne_bez_polskich_znaków(0/1): "<<menuGlowne<<"\n";
        plik<<"wyświetlane_wiersze: "<<wyswietlaneWiersze<<"\n";
        plik<<"odświeżanie: "<<refresh<<"\n";
        plik<<"przerwa_między_dźwiękami: "<<interval<<"\n";
        plik<<"wyciszenie_komunikatu_team(0/1): "<<fLockTeam<<"\n";
        plik<<"wyciszenie_komunikatu_pw(0/1): "<<fLockPW<<"\n";
        plik<<"wyciszenie_komunikatu_raport(0/1): "<<fLockKomunikat<<"\n";
        plik<<"wyciszenie_komunikatu_nick(0/1): "<<fLockNick<<"\n";
        plik<<"dźwięk_każdej_nowej_wiadomości_czatu: "<<chatSound<<"\n";
        plik<<"dynamiczne_odświeżanie: "<<dynamicRefresh<<"\n";
        plik<<"czas_rozładowywania_towaru: "<<czas<<"\n";
        plik<<"cel_trasy_skrypt: "<<random<<"\n";
        plik<<"f4: "<<money<<"\n";
        plik<<"ilość_kursów: "<<courses<<"\n";
        plik<<"szybki_start: "<<fastStart<<"\n";
        plik<<"kodowanie852: "<<codePage852<<"\n";
        plik<<"////////////////////////////////////////////////////////////////////////////////////////////////\n";
        plik<<"//W tym miejscu znajduje sie lista zapisanych graczy."<<endl;
        plik<<"//Aby poprawnie dodać gracza przez plik należy ustalić też ilość graczy."<<endl;
        plik<<"//Zapisana jest ona po napisie 'ilość_graczy: ', po dwukropku musi być spacja."<<endl;
        plik<<"//Przykład:"<<endl;
        plik<<"//ilość_graczy: 2"<<endl;
        plik<<"//1 ASL|DarXe"<<endl;
        plik<<"//2 MERO4k"<<endl;
        plik<<"////////////////////////////////////////////////////////////////////////////////////////////////\n";
        plik<<"Lista zapisanych graczy: "<<endl;
        plik<<"ilość_graczy: "<<nicknames.size()<<endl;
        for(int i = 0; i < nicknames.size(); i++)
        {
            plik<<i+1<<" "<<nicknames.at(i)<<endl;
        }
        
    plik.close();
    cout<<"(INFO) Ustawienia zostaly zapisane."<<endl;
}

void odczyt() //re read
{
    fstream plik;
    plik.open("logus.ini");
        for(int i(0); i<6; i++) getline(plik,s_temp);
        plik>>s_temp>>temp;
        plik>>s_temp>>mtasa;
        plik>>s_temp>>ang;
        plik>>s_temp>>nick;
        plik>>s_temp>>dzwiekGlowny;
        plik>>s_temp>>kolorGlowny;
        plik>>s_temp>>menuGlowne;
        plik>>s_temp>>wyswietlaneWiersze;
        plik>>s_temp>>refresh;
        plik>>s_temp>>interval;
        plik>>s_temp>>fLockTeam;
        plik>>s_temp>>fLockPW;
        plik>>s_temp>>fLockKomunikat;
        plik>>s_temp>>fLockNick;
        plik>>s_temp>>chatSound;
        plik>>s_temp>>dynamicRefresh;
        plik>>s_temp>>czas;
        plik>>s_temp>>random;
        plik>>s_temp>>money;
        plik>>s_temp>>courses;
        plik>>s_temp>>fastStart;
        plik>>s_temp>>codePage852;
    plik.close();

    plik.open("logus.ini");
        do //naprawa błędu po aktualizacji (błędne wczytanie z listy Nicknames)
        {
            getline(plik,s_temp);
        } while (s_temp[0]!='L');
        
        plik>>s_temp;
        plik>>leng;
        nicknames.clear();
        for(int i = 0; i < leng; i++)
        {
            plik>>temp>>s_temp;
            nicknames.push_back(s_temp);
        }
        cout<<"(INFO) Wczytano ustawienia."<<endl;
    plik.close();
}

void patch() //pa patch
{
    fstream plik;
    plik.open("logus.ini");
        for(int i(0); i<6; i++) getline(plik,s_temp);
        plik>>s_temp>>ang;
        plik>>s_temp>>nick;
        plik>>s_temp>>dzwiekGlowny;
        plik>>s_temp>>kolorGlowny;
        plik>>s_temp>>menuGlowne;
        plik>>s_temp>>wyswietlaneWiersze;
        plik>>s_temp>>refresh;
        plik>>s_temp>>interval;
        plik>>s_temp>>fLockTeam;
        plik>>s_temp>>fLockPW;
        plik>>s_temp>>fLockKomunikat;
        plik>>s_temp>>fLockNick;
        plik>>s_temp>>chatSound;
        plik>>s_temp>>dynamicRefresh;
        plik>>s_temp>>czas;
        plik>>s_temp>>random;
    plik.close();

    plik.open("logus.ini");
        do 
        {
            getline(plik,s_temp);
        } while (s_temp[0]!='L');
        
        plik>>s_temp;
        plik>>leng;
        nicknames.clear();
        for(int i = 0; i < leng; i++)
        {
            plik>>temp>>s_temp;
            nicknames.push_back(s_temp);
        }
        cout<<"(INFO) Wczytano ustawienia. Wykonano aktualizacje do wersji "<<ver<<"."<<endl;
    plik.close();
    zapis();
}

void readDefault()
{
    dzwiekGlowny = 1777;
    fLockTeam = 0;
    fLockPW = 0;
    fLockKomunikat = 0;
    fLockNick = 0;
    menuGlowne = 1;
    chatSound = 0;
    kolorGlowny = "A";
    wyswietlaneWiersze = 15;
    refresh = 300;
    ang = 0;
    interval = 50;
    nick = "PodajSwojNick";
    dynamicRefresh = 0;
    czas = 90;
    random = 0;
    mtasa = "185.62.189.174:22003";
    money = 0;
    courses = 0;
    fastStart = 0;
    codePage852 = 0;
}

int console() //con
{
    color(kolorGlowny);
    if(codePage852)
    {
        SetConsoleOutputCP(852); //kodowanie 852
        SetConsoleCP(852);
    }
    else
    {
        SetConsoleOutputCP(65001); //kodowanie utf-8
        SetConsoleCP(65001); 
    }

    switch (fastStart)
    {
    case 0:
        wersja();
        break;
    case 1:
        {
            s_temp = "start mtasa://"+mtasa;
            system(s_temp.c_str());
            cls();
            Beep(dzwiekGlowny,100);
            liveChat(wyswietlaneWiersze);
        }
    default:
        break;
    }

    while(true)
    {
        color(kolorGlowny);
        Beep(dzwiekGlowny,100);

        if(menuGlowne)
        {
            menuBezPL();
        }
        else menu();

        wyb = wybor();
        if(wyb == 27){
            cls();
            zapis();
            cout<<"\nBye bye";
            for(int i = 0; i<3; i++){
                cout<<".";
                Sleep(400);
            }
            break;
        }

        switch(wyb) //set0
        {
        case '1':
        {
            cls();
            teamsay(a,1);
            break;
        }
        case '2':
        {
            cls();
            pw(a,1);
            break;
        }
        case '3':
        {
            cls();
            iloscLinijek = 0;
            iloscLinijekAll = 0;
            iloscLinijekAll+=teamsay(f,6);
            iloscLinijekAll+=teamsay(e,5);
            iloscLinijekAll+=teamsay(d,4);
            iloscLinijekAll+=teamsay(c,3);
            iloscLinijekAll+=teamsay(b,2);
            iloscLinijekAll+=teamsay(a,1);
            iloscLinijek=teamsay(L,0);
            cout<<"Wierszy w plikach MTA: "<<iloscLinijekAll<<endl;
            cout<<"Wierszy w logus.log: "<<iloscLinijek<<endl;
            break;
        }

        case '4':
        {
            cls();
            iloscLinijek = 0;
            iloscLinijekAll = 0;
            iloscLinijekAll+=pw(f,6);
            iloscLinijekAll+=pw(e,5);
            iloscLinijekAll+=pw(d,4);
            iloscLinijekAll+=pw(c,3);
            iloscLinijekAll+=pw(b,2);
            iloscLinijekAll+=pw(a,1);
            iloscLinijek=pw(L,0);
            cout<<"Wierszy w plikach MTA: "<<iloscLinijekAll<<endl;
            cout<<"Wierszy w logus.log: "<<iloscLinijek<<endl;
            break;
        }
        case 'p':
        {
            cls();
            iloscLinijekAll = 0;
            iloscLinijekAll+=przelewy(f,6);
            iloscLinijekAll+=przelewy(e,5);
            iloscLinijekAll+=przelewy(d,4);
            iloscLinijekAll+=przelewy(c,3);
            iloscLinijekAll+=przelewy(b,2);
            iloscLinijekAll+=przelewy(a,1);
            iloscLinijekAll+=przelewy(L,0);
            cout<<"Wierszy: "<<iloscLinijekAll<<endl;
            break;
        }
        case 'n':
        {
            cls();
            iloscLinijekAll = 0;
            iloscLinijek = 0;
            iloscLinijek=all(f,6);
            iloscLinijekAll+=iloscLinijek;
            cout<<"Wierszy: "<<iloscLinijek<<endl;
            iloscLinijek=all(e,5);
            iloscLinijekAll+=iloscLinijek;
            cout<<"Wierszy: "<<iloscLinijek<<endl;
            iloscLinijek=all(d,4);
            iloscLinijekAll+=iloscLinijek;
            cout<<"Wierszy: "<<iloscLinijek<<endl;
            iloscLinijek=all(c,3);
            iloscLinijekAll+=iloscLinijek;
            cout<<"Wierszy: "<<iloscLinijek<<endl;
            iloscLinijek=all(b,2);
            iloscLinijekAll+=iloscLinijek;
            cout<<"Wierszy: "<<iloscLinijek<<endl;
            iloscLinijek=all(a,1);
            iloscLinijekAll+=iloscLinijek;
            cout<<"Wierszy: "<<iloscLinijek<<endl;
            cout<<endl;
            cout<<"Wierszy we wszystkich plikach MTA: "<<iloscLinijekAll<<endl;
            cout<<"Ilosc wierszy w logus.log: "<<all(L,10)<<endl;
            break;
        }
        case 't':
        {
            cls();
            liveChat(wyswietlaneWiersze); //run LiveChat
            break;
        } //set1    (ustawienia)
        case '5':
        {
            cls();
            while(true)
            {
                Beep(dzwiekGlowny,100);
                if(menuGlowne)
                {
                    SetConsoleTextAttribute(h, 10);
                    cout<<" ________________________Ustawienia - LiveChat________________________"<<endl;
                    SetConsoleTextAttribute(h, 7);
                    cout<<" [r] Przywroc ustawienia domyslne"<<endl;
                    cout<<" [a] Flaga na PTS: "<<((ang)?"ANG":"PL")<<endl;
                    SetConsoleTextAttribute(h, 14);
                    cout<<" [p] Dzwiek wiadomosci PW: "<<((!fLockPW)?"TAK":"NIE")<<endl;
                    cout<<" [t] Dzwiek wiadomosci teamowych: "<<((!fLockTeam)?"TAK":"NIE")<<endl;
                    cout<<" [s] Dzwiek komunikatow(raport, transport): "<<((!fLockKomunikat)?"TAK":"NIE")<<endl;
                    cout<<" [k] Powiadomienia na czacie - wybrane nicki: "<<((!fLockNick)?"TAK":"NIE")<<endl;
                    cout<<" [c] Dzwiek kazdej wiadmosci na czacie: "<<((chatSound)?"TAK":"NIE")<<endl;
                    SetConsoleTextAttribute(h, 7);
                    cout<<" [1] Liczba wyswietlanych wierszy: "<<wyswietlaneWiersze<<endl;
                    cout<<" [2] Czestotliwosc odswiezania(100-5000): "<<refresh<<endl;
                    cout<<" [3] Dynamiczne odswiezanie: "<<((dynamicRefresh)?"TAK":"NIE")<<endl;
                    cout<<" [4] Czestotliwosc dzwieku(50-10000): "<<dzwiekGlowny<<endl;
                    cout<<" [5] Przerwa miedzy dzwiekami(50-1000): "<<interval<<endl;
                    SetConsoleTextAttribute(h, 14);
                    cout<<" [6] Czas rozladowywania towaru - "<<czas/60<<((czas%60<10)?":0":":")<<czas%60<<endl;
                    cout<<" [7] Sam wybiore / Skrypt: "<<((random)?"5min - Skrypt":"6min - Sam wybiore")<<endl;
                    SetConsoleTextAttribute(h, 7);
                    cout<<" [8] F4/zarobione pieniadze od ostatniego wyzerowania: $"<<money<<endl;
                    cout<<" [9] Liczba dostarczonych kursow: "<<courses<<endl;
                    cout<<" [x] Wyzeruj stan F4 i kursow"<<endl;
                    SetConsoleTextAttribute(h, 14);
                    cout<<" [b] Nicknames - baza danych wybranych nickow"<<endl;
                    cout<<" [n] Nickname: "<<nick<<endl;
                    SetConsoleTextAttribute(h, 10);
                    cout<<" _____________________________________________________________________"<<endl;
                    cout<<"                         [ESC] Powrot i zapis                         "<<endl;
                }
                else
                {
                    SetConsoleTextAttribute(h, 10);
                    cout<<" ________________________Ustawienia - LiveChat________________________"<<endl;
                    SetConsoleTextAttribute(h, 7);
                    cout<<" [r] Przywróc ustawienia domyślne"<<endl;
                    cout<<" [a] Flaga na PTS: "<<((ang)?"ANG":"PL")<<endl;
                    SetConsoleTextAttribute(h, 14);
                    cout<<" [p] Dźwięk wiadomości PW: "<<((!fLockPW)?"TAK":"NIE")<<endl;
                    cout<<" [t] Dźwięk wiadomości teamowych: "<<((!fLockTeam)?"TAK":"NIE")<<endl;
                    cout<<" [s] Dźwięk komunikatow(raport, transport): "<<((!fLockKomunikat)?"TAK":"NIE")<<endl;
                    cout<<" [k] Powiadomienia na czacie - wybrane nicki: "<<((!fLockNick)?"TAK":"NIE")<<endl;
                    cout<<" [c] Dźwięk każdej wiadomości na czacie: "<<((chatSound)?"TAK":"NIE")<<endl;
                    SetConsoleTextAttribute(h, 7);
                    cout<<" [1] Liczba wyświetlanych wierszy: "<<wyswietlaneWiersze<<endl;
                    cout<<" [2] Częstotliwość odświeżania(100-5000): "<<refresh<<endl;
                    cout<<" [3] Dynamiczne odświeżanie: "<<((dynamicRefresh)?"TAK":"NIE")<<endl;
                    cout<<" [4] Częstotliwość dźwięku(50-10000): "<<dzwiekGlowny<<endl;
                    cout<<" [5] Przerwa między dźwiękami(50-1000): "<<interval<<endl;
                    SetConsoleTextAttribute(h, 14);
                    cout<<" [6] Czas rozładowywania towaru - "<<czas/60<<((czas%60<10)?":0":":")<<czas%60<<endl;
                    cout<<" [7] Sam wybiorę / Skrypt: "<<((random)?"5min - Skrypt":"6min - Sam wybiorę")<<endl;
                    SetConsoleTextAttribute(h, 7);
                    cout<<" [8] F4/zarobione pieniądze od ostatniego wyzerowania: $"<<money<<endl;
                    cout<<" [9] Liczba dostarczonych kursów: "<<courses<<endl;
                    cout<<" [x] Wyzeruj stan F4 i kursów"<<endl;
                    SetConsoleTextAttribute(h, 14);
                    cout<<" [b] Nicknames - baza danych wybranych nicków"<<endl;
                    cout<<" [n] Nickname: "<<nick<<endl;
                    SetConsoleTextAttribute(h, 10);
                    cout<<" _____________________________________________________________________"<<endl;
                    cout<<"                         [ESC] Powrót i zapis                         "<<endl;
                }
                
                wyb = wybor();
                if(wyb == 27){
                    cls();
                    zapis();
                    break;
                }
                    
                switch(wyb)
                {
                    case 'r':
                    {
                        cls();
                        cout<<"CZY NA PEWNO CHCESZ TO ZROBIC? ESC - Anuluj | Inny klawisz - zgoda"<<endl;
                        if(getch() == 27) break;
                        readDefault();
                        cout<<"Ustawienia domyslne programu zostaly przywrocone!"<<endl;
                    }
                    case 'a':
                    {
                        cls();
                        if(ang)
                            ang = 0;
                        else
                            ang = 1;
                        break;
                    }
                    case 'p':
                    {
                        cls();
                        if(fLockPW)
                            fLockPW = 0;
                        else
                            fLockPW = 1;
                        break;
                    }
                    case 't':
                    {
                        cls();
                        if(fLockTeam)
                            fLockTeam = 0;
                        else
                            fLockTeam = 1;
                        break;
                    }
                    case 's':
                    {
                        cls();
                        if(fLockKomunikat)
                            fLockKomunikat = 0;
                        else
                            fLockKomunikat = 1;
                        break;
                    }
                    case 'k':
                    {
                        cls();
                        if(fLockNick)
                            fLockNick = 0;
                        else
                            fLockNick = 1;
                        break;
                    }
                    case 'c':
                    {
                        cls();
                        if(chatSound)
                            chatSound = 0;
                        else
                            chatSound = 1;
                        break;
                    }
                    case '1':
                    {
                        cls();
                        while(true)
                        {
                            cout<<"Podaj nowa ilosc wyswietlanych wierszy: ";
                            if(!(cin>>wyswietlaneWiersze))
                            {
                                intError();
                                return 0;
                            }
                            if(wyswietlaneWiersze < 1 || wyswietlaneWiersze > 100)
                                cout<<"MIN 1; MAX 100"<<endl;
                            else
                                break;
                        }
                        cls();
                        break;
                    }
                    case '2':
                    {
                        cls();
                        while(true)
                        {
                            cout<<"Podaj nowa czestotliwosc odswiezania: ";
                            if(!(cin>>refresh))
                            {
                                intError();
                                return 0;
                            }
                            if(refresh < 100 || refresh > 5000)
                                cout<<"MIN 100(0,1s); MAX 5000(5s)"<<endl;
                            else
                                break;
                        }
                        cls();
                        break;
                    }
                    case '3':
                    {
                        cls();
                        if(dynamicRefresh)
                            dynamicRefresh = 0;
                        else
                            dynamicRefresh = 1;
                        break;
                    }
                    case '4':
                    {
                        cls();
                        while(true)
                        {
                            cout<<"Podaj nowa czestotliwosc dzwieku: ";
                            if(!(cin>>dzwiekGlowny))
                            {
                                intError();
                                return 0;
                            }
                            if(dzwiekGlowny < 50 || dzwiekGlowny > 10000)
                                cout<<"MIN 50; MAX 10000"<<endl;
                            else
                                break;
                        }
                        cls();
                        break;
                    }
                    case '5':
                    {
                        cls();
                        while(true)
                        {
                            cout<<"Podaj nowy odstep miedzy dzwiekami: ";
                            if(!(cin>>interval))
                            {
                                intError();
                                return 0;
                            }
                            if(interval < 50 || interval > 1000)
                                cout<<"MIN 50; MAX 1000"<<endl;
                            else
                                break;
                        }
                        cls();
                        break;
                    }
                    case '6':
                    {
                        cls();
                        cout<<"Podaj minuty: ";
                        if(!(cin>>temp))
                        {
                            intError();
                            return 0;
                        }
                        cout<<"Podaj sekundy: ";
                        if(!(cin>>temp2))
                        {
                            intError();
                            return 0;
                        }
                        czas = (temp*60) + temp2;
                        break;
                    }
                    case '7':
                    {
                        cls();
                        if(random)
                            random = 0;
                        else
                            random = 1;
                        break;
                    }
                    case '8':
                    {
                        cls();
                        while(true)
                        {
                            cout<<"Podaj nowa ilosc $(sama liczba): ";
                            if(!(cin>>money))
                            {
                                intError();
                                return 0;
                            }
                            if(money < 0 || money > 9999999)
                                cout<<"MIN 0; MAX 9999999"<<endl;
                            else
                                break;
                        }
                        cls();
                        break;
                    }
                    case '9':
                    {
                        cls();
                        while(true)
                        {
                            cout<<"Podaj nowa ilosc kursow: ";
                            if(!(cin>>courses))
                            {
                                intError();
                                return 0;
                            }
                            if(courses < 0 || courses > 9999)
                                cout<<"MIN 0; MAX 9999"<<endl;
                            else
                                break;
                        }
                        cls();
                        break;
                    }
                    case 'x':
                    {
                        cls();
                        cout<<"CZY NA PEWNO CHCESZ TO ZROBIC? ESC - Anuluj | Inny klawisz - zgoda"<<endl;
                        if(getch() == 27) break;
                        money = 0;
                        courses = 0;
                        break;
                    }
                    case 'b':
                    {
                        cls();
                        while(true)
                        {
                            SetConsoleTextAttribute(h, 10);
                            Beep(dzwiekGlowny,100);
                            if(menuGlowne)
                            {
                                cout<<" _____________________Ustawienia - Nicknames_____________________"<<endl;
                                cout<<" (INFO) Mozesz tez wpisywac nazwy recznie w pliku logus.ini"<<endl;
                                SetConsoleTextAttribute(h, 14);
                                cout<<" [1] Dodaj nowego gracza"<<endl;
                                cout<<" [2] Usun ostatnio dodanego gracza"<<endl;
                                cout<<" [3] Wyswietl liste dodanych graczy"<<endl;
                                cout<<" [4] Usun gracza o danym id z listy"<<endl;
                                SetConsoleTextAttribute(h, 7);
                                cout<<" [r] Wykonaj odczyt z pliku, jesli gracz zostal dodany w logus.ini"<<endl;
                                cout<<" [x] Usun wszystkich graczy"<<endl;
                                SetConsoleTextAttribute(h, 10);
                                cout<<" ________________________________________________________________"<<endl;
                                cout<<"                       [ESC] Powrot i zapis                      "<<endl;
                            }
                            else
                            {
                                cout<<" _____________________Ustawienia - Nicknames_____________________"<<endl;
                                cout<<" (INFO) Możesz też wpisywać nazwy ręcznie w pliku logus.ini"<<endl;
                                SetConsoleTextAttribute(h, 14);
                                cout<<" [1] Dodaj nowego gracza"<<endl;
                                cout<<" [2] Usuń ostatnio dodanego gracza"<<endl;
                                cout<<" [3] Wyświetl listę dodanych graczy"<<endl;
                                cout<<" [4] Usuń gracza o danym id z listy"<<endl;
                                SetConsoleTextAttribute(h, 7);
                                cout<<" [r] Wykonaj odczyt z pliku, jeśli gracz został dodany w logus.ini"<<endl;
                                cout<<" [x] Usuń wszystkich graczy"<<endl;
                                SetConsoleTextAttribute(h, 10);
                                cout<<" ________________________________________________________________"<<endl;
                                cout<<"                       [ESC] Powrot i zapis                      "<<endl;
                            }
                            wyb = wybor();
                            if(wyb == 27){
                                cls();
                                zapis();
                                break;
                            }
                            switch(wyb)
                            {
                                case '1': //set2
                                {
                                    cls();
                                    while(true)
                                    {
                                        cout<<"Podaj dokladna nazwe gracza: ";
                                        cin>>s_temp;
                                        if(s_temp.length()<3)
                                            cout<<"Minimum 3 znaki!"<<endl;
                                        else
                                        {   
                                            cls();
                                            nicknames.push_back(s_temp);
                                            cout<<"Dodano gracza "<<s_temp<<endl;
                                            break;
                                        }
                                    }
                                    break;
                                }
                                case '2':
                                {
                                    cls();
                                    if(nicknames.empty())
                                        cout<<"(INFO) Lista graczy jest pusta"<<endl;
                                    else
                                    {   
                                        cout<<"Usunieto gracza "<<nicknames.back()<<endl;
                                        nicknames.pop_back();
                                    }
                                    break;
                                }
                                case '3':
                                {
                                    cls();
                                    if(nicknames.empty())
                                        cout<<"(INFO) Lista graczy jest pusta"<<endl;
                                    else
                                    {   
                                        for(int i = 0; i < nicknames.size(); i++)
                                        {
                                            cout<<i+1<<". "<<nicknames.at(i)<<endl;
                                        }
                                    }
                                    break;
                                }
                                case '4':
                                {
                                    cls();
                                    if(nicknames.empty())
                                        cout<<"(INFO) Lista graczy jest pusta"<<endl;
                                    else
                                    {   
                                        cls();
                                        for(int i = 0; i < nicknames.size(); i++)
                                        {
                                            cout<<i+1<<". "<<nicknames.at(i)<<endl;
                                        }
                                        cout<<"Podaj id gracza, ktorego chcesz usunac: ";
                                        if(!(cin>>temp))
                                        {
                                            intError();
                                            return 0;
                                        }
                                        cout<<"Usunieto gracza "<<nicknames.at(temp-1)<<endl;
                                        nicknames.erase(nicknames.begin()+temp-1);
                                    }
                                    break;
                                }
                                case 'r':
                                {
                                    cls();
                                    odczyt();
                                    zapis();
                                    break;
                                }
                                case 'x':
                                {
                                    cls();
                                    cout<<"CZY NA PEWNO CHCESZ TO ZROBIC? ESC - Anuluj | Inny klawisz - zgoda"<<endl;
                                    if(getch() == 27) break;
                                    nicknames.clear();
                                    cout<<"Usunieto wszystkich graczy"<<endl;
                                    break;
                                }
                                default: def();
                            }
                        }
                        break;
                    }
                    case 'n':
                    {
                        cls();
                        cout<<"Nazwa nicku potrzebna jest do poprawnego dzialania LiveChat"<<endl;
                        while(true)
                        {
                            cout<<"Podaj swoj nowy nick: ";
                            cin>>nick;
                            if(nick.length()<3)
                            {
                                cout<<"MINIMUM 3 znaki"<<endl;
                            }
                            else break;
                        }
                        cls();
                        break;
                    }
                    default: def();
                }
            }
            break;
        }
        case '0':
        {
            cls();
            if(codePage852)
            {
                codePage852 = 0;
                SetConsoleOutputCP(65001);
                SetConsoleCP(65001); 
                cout<<"Kodowanie UTF-8"<<endl;
            }
            else
            {
                codePage852 = 1;
                SetConsoleOutputCP(852);
                SetConsoleCP(852); 
                cout<<"Kodowanie 852"<<endl;
            }
            break;
        }
        case 'j':
        {
            cls();
            if(menuGlowne)
            {
                menuGlowne = 0;
                cout<<"Menu z polskimi ogonkami"<<endl;
            }
            else
            {
                menuGlowne = 1;
                cout<<"Menu bez polskich ogonkow"<<endl;
            }
            break;
        }
        case '9':
        {
            cls();
            dzwiekGlowny = losuj(50,10000);
            cout<<dzwiekGlowny<<endl;
            break;
        }

        case 'w':
        {
            cls();
            while(true)
            {
                Beep(dzwiekGlowny,500);
                system("ping google.pl -n 2");
                cout<<endl;
                cout<<"POWROT - DOWOLNY KLAWISZ"<<endl;
                if(kbhit())
                {
                    getch();
                    cls();
                    break;
                }
            }
            break;
        }
        case 'i':
        {
            cls();
            wersja();
            break;
        }
        case 's':
        {
            cls();
            switch (fastStart)
            {
            case 0:
                fastStart = 1;
                break;
            case 1:
                fastStart = 2;
                break;
            default:
                fastStart = 0;
            break;
            }
            break;
        }
        case 13:
        {
            cls();
            s_temp = "start mtasa://"+mtasa;
            system(s_temp.c_str());
            break;
        }
        default:
            def();
        }//switch
    }
    return 0;
}

void funcTest(){
    ;
}

void liveChatBeep(string &ostatniaLinia) //bee
{
    //wiadomość pw
    if(!fLockPW){
        if(fPwOd(ostatniaLinia, ang))
        {
            Beep(dzwiekGlowny,300);
            Beep(0,interval);
            timer-=interval; timer-=300;
            Beep(dzwiekGlowny,300);
            Beep(0,interval);
            timer-=interval; timer-=300;
        }
    }

    //wiadomość teamowa
    if(!fLockTeam)
    {
        if(fTeam(ostatniaLinia, 0))
        {
            Beep(dzwiekGlowny,150);
            Beep(0,interval);
            timer-=interval; timer-=150;
            Beep(dzwiekGlowny,150);
            Beep(0,interval);
            timer-=interval; timer-=150;
        }
    }

    //dostarczenie towaru, raport z frakcji
    if(!fLockKomunikat)
    {
        if(fTransport(ostatniaLinia, ang)||fKomunikat(ostatniaLinia, ang))
        {
            if(fTransport(ostatniaLinia, ang))
            {
                salaryForTransport(ostatniaLinia, ang);
                if(trackId)
                {
                    if(trackId == 4) trackId = 1;
                    else trackId++;
                }
            }
            Beep(dzwiekGlowny,150);
            Beep(0,interval);
            timer-=interval; timer-=150;
            Beep(dzwiekGlowny,150);
            Beep(0,interval);
            timer-=interval; timer-=150;
            Beep(dzwiekGlowny,150);
            Beep(0,interval);
            timer-=interval; timer-=150;
        }
    }

    //nick z czatu dodany do ulubionych
    if(!fLockNick)
    {
        if(fNicknames(ostatniaLinia))
        {
            Beep(dzwiekGlowny,300);
            Beep(0,interval);
            timer-=interval; timer-=300;
        }
    }

    if(fConsoleInput(ostatniaLinia))
    {
        Beep(dzwiekGlowny,100);
        Beep(0,interval);
        timer-=interval; timer-=100;
    }
}

int all(string &nazwa, int nr)
{
    int iloscLinijek = 0;
    nrPliku(nr);

    fstream plik;
    plik.open(nazwa.c_str());
        while(!plik.eof())
        {
            getline(plik,linia);
            iloscLinijek++;
        }
    plik.close();

    return iloscLinijek;
}

void getChat(int &iloscLinijek)
{
    pos.X=0; pos.Y=0; SetConsoleCursorPosition(h, pos);
    SetConsoleTextAttribute(h, 12);
    cout<<"##############################LiveChat##############################"<<endl;
    SetConsoleTextAttribute(h, 204); cout<<" "; SetConsoleTextAttribute(h, 12);
    cout<<" Refresh:"<<refresh<<"ms"<<" # Wierszy:"<<iloscLinijek-1<<" # Errors:"<<errors<<" #  [ESC]Return to MENU"<<endl;
    if(isTimer)
    {
        SetConsoleTextAttribute(h, 170); cout<<" "; SetConsoleTextAttribute(h, 12);
        cout<<" Timer "<<timer/1000/60;
        if((timer/1000)%60<10) cout<<":0"; else cout<<":";
        cout<<(timer/1000)%60<<"  [s]Stop Timer    ";
    }
    else 
    {
        SetConsoleTextAttribute(h, 204); cout<<" "; SetConsoleTextAttribute(h, 12);
        cout<<" [t]Timer                     ";
    }
    if(money&&courses) cout<<"$"<<money<<" # Courses:"<<courses<<" # Avg $"<<money/courses<<"                  ";
    else      cout<<"Dostarczone kursy: "<<courses<<"                                             ";
    cout<<"\n#########################################"<<track[trackId]<<"#[m]moveLogs()#####"<<endl;

    plik.open("console.log");
        //pobranie linii, które nie mają być wyświetlone
        for(int i = 0; i < iloscLinijek-wyswietlaneWiersze-1; i++)
        {
            getline(plik, linia);
        }
        //bug fix
        if((iloscLinijek-1)<=wyswietlaneWiersze)
        {
            temp2 = wyswietlaneWiersze;
            wyswietlaneWiersze = iloscLinijek-1;
        }
        //wyświetlenie pozostałych linii
        for(int i = 0; i < wyswietlaneWiersze; i++)
        {
            getline(plik, linia);
            if(fNicknames(linia)||fTransport(linia,ang)||fKomunikat(linia,ang)||fPrzelewyOd(linia,ang)||fPwOd(linia,ang)||fTeam(linia,0))
            {
                if(timestamps)
                {
                    SetConsoleTextAttribute(h, 160); cout<<" "<<linia<<endl;
                }
                else
                {
                    SetConsoleTextAttribute(h, 10); cout<<"# ";
                    SetConsoleTextAttribute(h, 160); cout<<linia.substr(gt)<<endl;
                }
            }
            else
            {
                if(timestamps)
                {
                    SetConsoleTextAttribute(h, 170); cout<<" ";
                    SetConsoleTextAttribute(h, 10); cout<<linia<<endl;
                }
                else
                {
                    SetConsoleTextAttribute(h, 10); cout<<"# "<<linia.substr(gt)<<endl;
                }
            }
        }
        if((iloscLinijek-1)<=wyswietlaneWiersze) wyswietlaneWiersze = temp2;//bug fix
    plik.close();
}

void liveChat(int &wyswietlaneWiersze) //lc
{
    iloscLinijek = 0;
    plik.open("console.log");
        while(!plik.eof())
        {
            getline(plik,linia);
            ++iloscLinijek;
        }
        plik.close();

    getChat(iloscLinijek);

    while(true)
    {   
        iloscLinijek = 0;
        //zliczanie linijek w pliku z logami
        plik.open("console.log");
        while(!plik.eof())
        {
            getline(plik,linia);
            ++iloscLinijek;
        }
        plik.close();

        //zapisanie informacji w pomocniczej zmiennej, wyzerowanie licznika i odczekanie czasu
        temp = iloscLinijek;
        for(int i(0); i<20; i++)
        {
            Sleep(refresh/20);
            if(kbhit()) break;
        }
        if(dynamicRefresh && refresh<2000 && !kbhit()) refresh+=10;

        if(kbhit())
        {
            wyb = getch();
            if(wyb == 27) { cls(); break;}
            switch (wyb)
            {
            case 't':
                {
                    Beep(dzwiekGlowny, 100);
                    startTimer(0);
                }
                break;
            case 's':
                {
                    Beep(dzwiekGlowny, 100);
                    isTimer = 0;
                    pos.X=0; pos.Y=2; SetConsoleCursorPosition(h, pos);
                    SetConsoleTextAttribute(h, 204); cout<<" "; SetConsoleTextAttribute(h, 12);
                    cout<<" [t]Timer                     ";
                }
                break;
            case 'm':
                {
                    cls();
                    cout<<"CZY NA PEWNO CHCESZ PRZENIESC LOGI z console.log DO PLIKU logus.log?\nESC - Anuluj | Inny klawisz - zgoda"<<endl;
                    if(getch() == 27) {getChat(iloscLinijek); break;}
                    moveLogs();
                }
                break;
            case '\t':
                {
                    timestamps = ((timestamps)?0:1);
                    pos.X=0; pos.Y=4; SetConsoleCursorPosition(h, pos);
                    cls(); getChat(iloscLinijek);
                }
                break;
            case 127:
                {
                    trackId = ((trackId)?0:1);
                }
                break;
            
            default:
                {
                    def();
                    getChat(iloscLinijek);
                    break;
                }
            }
        }

        iloscLinijek = 0;
        //zliczanie linijek w pliku z logami po odstępie czasowym
        plik.open("console.log");
        while(!plik.eof())
        {
            getline(plik,linia);
            ++iloscLinijek;
        }
        plik.close();

        if(isTimer)
        {
            if(timer>0) 
            {
                timer -= refresh;
                if(isCzas)
                {
                    if(random)
                    {
                        if(timer<300000)
                        {
                            Beep(dzwiekGlowny,150);
                            Beep(0,interval);
                            Beep(dzwiekGlowny+50,150);
                            Beep(0,interval);
                            Beep(dzwiekGlowny+100,150);
                            Beep(0,interval);
                            timer-=(interval*3); timer-=450;
                            isCzas = 0;
                        }
                    }
                    else
                    {
                        if(timer<360000)
                        {
                            Beep(dzwiekGlowny,150);
                            Beep(0,interval);
                            Beep(dzwiekGlowny+50,150);
                            Beep(0,interval);
                            Beep(dzwiekGlowny+100,150);
                            Beep(0,interval);
                            timer-=(interval*3); timer-=450;
                            isCzas = 0;
                        }
                    }
                }
            }
            else
            {
                Beep(dzwiekGlowny-100,150);
                Beep(0,interval);
                Beep(dzwiekGlowny-50,150);
                Beep(0,interval);
                Beep(dzwiekGlowny,150);
                Beep(0,interval);
                isTimer = 0;
                pos.X=0; pos.Y=2; SetConsoleCursorPosition(h, pos);
                cout<<"  [t]Timer                     ";
            }
        }
        temp = iloscLinijek-temp; //różnica linijek
        //jeśli po odczekaniu czasu ilości się różnią to znaczy, że ktoś coś napisał
        //he-ad
        pos.X=0; pos.Y=0; SetConsoleCursorPosition(h, pos);
        SetConsoleTextAttribute(h, 12);
        cout<<"##############################LiveChat##############################"<<endl;
        SetConsoleTextAttribute(h, 204); cout<<" "; SetConsoleTextAttribute(h, 12);
        cout<<" Refresh:"<<refresh<<"ms"<<" # Wierszy:"<<iloscLinijek-1<<" # Errors:"<<errors<<" #  [ESC]Return to MENU"<<endl;
        if(isTimer)
        {
            SetConsoleTextAttribute(h, 170); cout<<" "; SetConsoleTextAttribute(h, 12);
            cout<<" Timer "<<timer/1000/60;
            if((timer/1000)%60<10) cout<<":0"; else cout<<":";
            cout<<(timer/1000)%60<<"  [s]Stop Timer    ";
        }
        else 
        {
            SetConsoleTextAttribute(h, 204); cout<<" "; SetConsoleTextAttribute(h, 12);
            cout<<" [t]Timer                     ";
        }
        if(money&&courses) cout<<"$"<<money<<" # Courses:"<<courses<<" # Avg $"<<money/courses<<"                  ";
        else      cout<<"Dostarczone kursy: "<<courses<<"                                             ";
        cout<<"\n#########################################"<<track[trackId]<<"#[m]moveLogs()#####"<<endl;
        pos.X=0; pos.Y=0; SetConsoleCursorPosition(h, pos);

        if(temp)
        {
            if(dynamicRefresh && refresh>500) refresh-=100; //jeśli pojawi się nowa wiadomość to zmniejsz częstotliwość odświeżania o 100ms
            cls();

            if(chatSound) {Beep(750,50); timer -= 50;} //dzwięk każdej nowej wiadomości czatu
           
            plik.open("console.log");
                if(iloscLinijek <= 10)
                {
                    for(int i = 0; i < iloscLinijek-1; i++) getline(plik, ostatniaLinia[1]);
                }
                else
                {
                    for(int i = 0; i < iloscLinijek-10; i++) getline(plik, ostatniaLinia[10]);
                    for (int i = 9; i > 0; i--) getline(plik, ostatniaLinia[i]);
                    //przechwycenie ostatnich linii
                }
            plik.close();

            getChat(iloscLinijek); //wyswietlenie czatu

            //19.05.29 rozwinięcie sprawdzania, do 5 ostatnich linii
            //19.07.04 rozwinięcie sprawdzania, do 10 ostatnich linii
            //zmiana ostatniaLinia1..2..3.. na tablice ostatniaLinia[]
            switch (temp)
            {
            case 1:
                liveChatBeep(ostatniaLinia[1]);
                break;
            case 2:
            {
                for(int i(2); i > 0; i--) liveChatBeep(ostatniaLinia[i]);
                break;
            }
            case 3:
            {
                for(int i(3); i > 0; i--) liveChatBeep(ostatniaLinia[i]);
                break;
            }
            case 4:
            {
                for(int i(4); i > 0; i--) liveChatBeep(ostatniaLinia[i]);
                break;
            }       
            case 5:
            {
                for(int i(5); i > 0; i--) liveChatBeep(ostatniaLinia[i]);
                break;
            }
            case 6:
            {
                for(int i(6); i > 0; i--) liveChatBeep(ostatniaLinia[i]);
                break;
            }
            case 7:
            {
                for(int i(7); i > 0; i--) liveChatBeep(ostatniaLinia[i]);
                break;
            }
            case 8:
            {
                for(int i(8); i > 0; i--) liveChatBeep(ostatniaLinia[i]);
                break;
            }
            case 9:
            {
                for(int i(9); i > 0; i--) liveChatBeep(ostatniaLinia[i]);
                break;
            }
            case 10:
            {
                for(int i(10); i > 0; i--) liveChatBeep(ostatniaLinia[i]);
                break;
            }
            default:
            {
                if(temp>10) errors++;
            }
            break;
            }
        }//if
    }//while
}//liveChat()

int teamsay(string &nazwa, int nr)
{
    //randomColor();
    int iloscLinijek = 0;
    nrPliku(nr);

    fstream plik;
    plik.open(nazwa.c_str());
        while(!plik.eof())
        {
            getline(plik,linia);
            if(fTeam(linia, 1))
            {
                cout<<++iloscLinijek<<linia<<endl;
                if(iloscLinijek%30 == 0)
                {
                    cout<<"PLIK "<<nr<<" [ESC] "<<((!nr)?"Wyjscie":"Nastepny plik")<<" | Nastepne 30 wierszy... (dowolny klawisz)"<<endl;
                    if(getch() == 27)
                    {
                        cls();
                        while(!plik.eof())
                        {
                            getline(plik,linia);
                            if(fTeam(linia, 1)) iloscLinijek++;
                        }
                        break;
                    }
                    cls();
                }
            }
        }
    plik.close();

    return iloscLinijek;
}

int pw(string &nazwa, int nr)
{
    //randomColor();
    int iloscLinijek = 0;
    nrPliku(nr);

    fstream plik;
    plik.open(nazwa.c_str());
        while(!plik.eof())
        {
            getline(plik,linia);
            if(fPwOd(linia, ang)||fPwDo(linia))
            {
                cout<<++iloscLinijek<<linia<<endl;
                if(iloscLinijek%30 == 0)
                {
                    cout<<"PLIK "<<nr<<" [ESC] "<<((!nr)?"Wyjscie":"Nastepny plik")<<" | Nastepne 30 wierszy... (dowolny klawisz)"<<endl;
                    if(getch() == 27)
                    {
                        cls();
                        while(!plik.eof())
                        {
                            getline(plik,linia);
                            if(fPwOd(linia, ang)||fPwDo(linia)) iloscLinijek++;
                        }
                        break;
                    }
                    cls();
                }
            }
        }
    plik.close();

    return iloscLinijek;
}

int przelewy(string &nazwa, int nr)
{
    //randomColor();
    int iloscLinijek = 0;
    nrPliku(nr);

    fstream plik;
    plik.open(nazwa.c_str());
        while(!plik.eof())
        {
            getline(plik,linia);
            if(fPrzelewyOd(linia, ang)||fPrzelewyDo(linia, ang))
            {
                cout<<++iloscLinijek<<linia<<endl;
                if(iloscLinijek%30 == 0)
                {
                    cout<<"PLIK "<<nr<<" [ESC] "<<((!nr)?"Wyjscie":"Nastepny plik")<<" | Nastepne 30 wierszy... (dowolny klawisz)"<<endl;
                    if(getch() == 27)
                    {
                        cls();
                        while(!plik.eof())
                        {
                            getline(plik,linia);
                            if(fPrzelewyOd(linia, ang)||fPrzelewyDo(linia, ang)) iloscLinijek++;
                        }
                        break;
                    }
                    cls();
                }
            }
        }
    plik.close();

    return iloscLinijek;
}
int nickname(string &nazwa, int nr)
{
    //randomColor();
    int iloscLinijek = 0;
    nrPliku(nr);
    fstream plik;
    plik.open(nazwa.c_str());
        while(!plik.eof())
        {
            plik>>linia>>linia>>linia>>linia; //wyrazy
            if(fNick(linia))
            {
                cout<<++iloscLinijek<<linia<<endl;
                if(iloscLinijek%30 == 0)
                {
                    cout<<"PLIK "<<nr<<" [ESC] "<<((!nr)?"Wyjscie":"Nastepny plik")<<" | Nastepne 30 wierszy... (dowolny klawisz)"<<endl;
                    if(getch() == 27)
                    {
                        cls();
                        while(!plik.eof())
                        {
                            getline(plik,linia);
                            if(fPrzelewyOd(linia, ang)||fPrzelewyDo(linia, ang)) iloscLinijek++;
                        }
                        break;
                    }
                    cls();
                }
            }
        }
    plik.close();

    return iloscLinijek;
}

void testLos()
{
    int a = 0;
    int b5=0,b6=0,b7=0,b8=0,b9=0;
    while(true)
    {
        a = losuj(0,10000);
        cout<<a<<endl;
        Beep(500,250);
        if(a > 9000)
            b9++;
        else
        {
            if(a > 8000)
                b8++;
            else
            {
                if(a > 7000)
                    b7++;
                else
                {
                    if(a > 6000)
                        b6++;
                    else
                        b5++;
                }
            }
        }
        cout<<b5<<":"<<b6<<":"<<b7<<":"<<b8<<":"<<b9<<endl;
        if(kbhit())
            break;
    }
    system("pause");
}

void color(string value)
{
    string value0 = "color 0"+value;
    system(value0.c_str());
}

string randomColor()
{
    int los = 0;
    string zwroc = " ";
    los = rand()%15;
    switch(los)
    {
    case 0:
        color("1");
        zwroc = "1";
        break;
    case 1:
        color("2");
        zwroc = "2";
        break;
    case 2:
        color("3");
        zwroc = "3";
        break;
    case 3:
        color("4");
        zwroc = "4";
        break;
    case 4:
        color("5");
        zwroc = "5";
        break;
    case 5:
        color("6");
        zwroc = "6";
        break;
    case 6:
        color("7");
        zwroc = "7";
        break;
    case 7:
        color("8");
        zwroc = "8";
        break;
    case 8:
        color("9");
        zwroc = "9";
        break;
    case 9:
        color("A");
        zwroc = "A";
        break;
    case 10:
        color("B");
        zwroc = "B";
        break;
    case 11:
        color("C");
        zwroc = "C";
        break;
    case 12:
        color("D");
        zwroc = "D";
        break;
    case 13:
        color("E");
        zwroc = "E";
        break;
    case 14:
        color("F");
        zwroc = "F";
        break;
    default:
        def();
    }
    return zwroc;
}

void moveLogs() //clean and move logs from console.log to logus.log
{
    vector <string> logs;
    fstream plik;
    fstream plik2;
    plik.open("console.log");
        while(!plik.eof())
        {
            getline(plik, linia);
            logs.push_back(linia);
        }
    plik.close();
    plik2.open("logus.log", ios::app);
        for(int i = 0; i<logs.size()-1; i++)
        {
            plik2<<logs.at(i)<<endl;
        }
    plik2.close();
    plik.open("console.log", ios::out);
    plik.close();
}

void wersja() //verr ver
{
    cout<<endl;
    cout<<"  Witaj "<<nick<<" !"<<endl;
    Beep(0,300);
    cout<<"  _______________"<<endl;
    cout<<" |     Autor     |"<<endl;
    cout<<" |     DarXe     |"<<endl;
    cout<<" |_______________|"<<endl;
    cout<<" | Wersja 19.7.6p|"<<endl;
    Beep(0,300);
    cout<<endl;
    cout<<" PLANY: "<<endl;
    cout<<" Naprawienie problemu z polskimi znakami na systemach win7"<<endl;
    cout<<" Kreator wlasnych powiadomien"<<endl;
    cout<<" Wykonanie i dodanie ikony programu"<<endl;
    cout<<" Wyszukiwanie wiadomosci tylko wybranych przez siebie graczy"<<endl;
    cout<<" Wyszukiwanie po tagach, ktore bedzie sie tworzylo(wysylalo) w konsoli mta"<<endl;
    Beep(0,300);
    cout<<endl;
    cout<<" Nie zapomnij zagladnac na githuba - znajdziesz tam informacje o tym"<<endl;
    cout<<" jak korzystac z programu - sa tam opisane wszystkie opcje\n"<<endl;
    Beep(0,1000);
    Beep(dzwiekGlowny,150);
    Beep(dzwiekGlowny,150);
    Beep(dzwiekGlowny,150);
    cout<<" Wcisnij klawisz, aby kontynuowac"<<endl; getch();
    cls();
    cout<<endl;
    cout<<" CO NOWEGO?"<<endl;
    cout<<" Naprawienie powiadomien - nie bylo ich, jesli bylo mniej niz 5(10) wierszy w logu"<<endl;
    cout<<"     (moment po przeniesieniu logow)"<<endl;
    cout<<" Uporzadkowanie zmiennych \"ostatniaLinia\", stworzenie tablicy"<<endl;
    cout<<"     to pozwolilo z latwoscia powiekszyc sprawdzanie wierszy do 10 linii"<<endl;
    cout<<"     pokazanie sie erroru jest praktycznie niemozliwe"<<endl;
    cout<<" Nowa funkcja w LiveChat! Timestamps - ukrywanie daty i godziny logu"<<endl;
    cout<<"     Dziala to na podobnej zasadzie co /timestamp na samp"<<endl;
    cout<<"     Klawisz [Tab] Ukrywa/pokazuje te znaczniki czasu"<<endl;
    cout<<" Naprawienie opoznien podczas korzystania z LiveChat - opcje wykonywane sa prawie natychmiastowo"<<endl;
    cout<<"     Przy odswiezaniu 1000ms opcja wykonuje sie po 50ms, po prostu dzielone jest przez 20"<<endl;
    cout<<" Naprawienie krytycznego bledu, po wdrozeniu Timestamps"<<endl;
    cout<<"     Dodanie funkcji Timestamps spowodowalo, ze jesli plik console.log byl pusty to"<<endl;
    cout<<"     sprawdzane byly puste linie, teraz sprawdza tyle linii, ile jest w pliku"<<endl;
    cout<<"     (az osiagnie ilosc ustawionych wyswietlonych wierszy)"<<endl;
    cout<<endl;
    cout<<" Wcisnij klawisz, aby wyswietlic MENU"<<endl;
    getch();
    cls();
}
void menu()
{
    SetConsoleTextAttribute(h, 10);
    cout<<" _______________________________________MENU_______________________________________"<<endl;
    SetConsoleTextAttribute(h, 11);
    cout<<" [t] LiveChat - czat z gry w konsoli z komunikatami dźwiękowymi"<<endl;
    cout<<" [5] LiveChat - ustawienia"<<endl;
    cout<<" [s] Szybki start LiveChat + PTS: ";
    switch (fastStart)
    {
    case 0:
        cout<<"Nie, ale wyświetl info o wersji";
        break;
    case 1:
        cout<<"Tak, uruchom MTA:PTS przy starcie Logusa";
        break;
    default:
        cout<<"Nie uruchamiaj, ani nie wyświetlaj info o wersji";
        break;
    }
    cout<<endl;
    SetConsoleTextAttribute(h, 12);
    cout<<" [1] Szukaj wiadomości teamowych w console.log"<<endl;
    cout<<" [2] Szukaj PW oraz odpowiedzi w console.log"<<endl;
    cout<<" [3] Szukaj wiadomości teamowych we wszystkich plikach .log"<<endl;
    cout<<" [4] Szukaj PW oraz odpowiedzi we wszystkich plikach .log"<<endl;
    SetConsoleTextAttribute(h, 11);
    cout<<" [p] Szukaj przelewów od i do graczy we wszystkich plikach"<<endl;
    cout<<" [n] Ilość wierszy w plikach"<<endl;
    SetConsoleTextAttribute(h, 12);
    cout<<" [w] Test ping - szybkie sprawdzenie, czy jest internet"<<endl;
    cout<<" [j] Menu bez polskich znaków"<<endl;
    cout<<" [i] INFO"<<endl;
    cout<<" [9] Zmiana dźwięku na losowy"<<endl;
    cout<<" [0] Kodowanie: "<<((codePage852)?"852":"UTF-8")<<endl;
    SetConsoleTextAttribute(h, 10);
    cout<<" __________________________________________________________________________________"<<endl;
    cout<<"                                [ESC] Wyjscie i zapis                              "<<endl;
}
void menuBezPL()
{
    SetConsoleTextAttribute(h, 10);
    cout<<" _______________________________________MENU_______________________________________"<<endl;
    SetConsoleTextAttribute(h, 11);
    cout<<" [t] LiveChat - Czat z gry w konsoli z komunikatami dzwiekowymi"<<endl;
    cout<<" [5] LiveChat - ustawienia"<<endl;
    cout<<" [s] Szybki start LiveChat + PTS: ";
    switch (fastStart)
    {
    case 0:
        cout<<"Nie, ale wyswietl info o wersji";
        break;
    case 1:
        cout<<"Tak, uruchom MTA:PTS przy starcie Logusa";
        break;
    default:
        cout<<"Nie uruchamiaj, ani nie wyswietlaj info o wersji";
        break;
    }
    cout<<endl;
    SetConsoleTextAttribute(h, 12);
    cout<<" [1] Szukaj wiadomosci teamowych w console.log"<<endl;
    cout<<" [2] Szukaj PW oraz odpowiedzi w console.log"<<endl;
    cout<<" [3] Szukaj wiadomosci teamowych we wszystkich plikach .log"<<endl;
    cout<<" [4] Szukaj PW oraz odpowiedzi we wszystkich plikach .log"<<endl;
    SetConsoleTextAttribute(h, 11);
    cout<<" [p] Szukaj przelewow od i do graczy we wszystkich plikach"<<endl;
    cout<<" [n] Ilosc wierszy w plikach"<<endl;
    SetConsoleTextAttribute(h, 12);
    cout<<" [w] Test ping - szybkie sprawdzenie, czy jest internet"<<endl;
    cout<<" [j] Menu z polskimi znakami"<<endl;
    cout<<" [i] INFO"<<endl;
    cout<<" [9] Zmiana dzwieku na losowy"<<endl;
    cout<<" [0] Kodowanie: "<<((codePage852)?"852":"UTF-8")<<endl;
    SetConsoleTextAttribute(h, 10);
    cout<<" __________________________________________________________________________________"<<endl;
    cout<<"                                [ESC] Wyjscie i zapis                              "<<endl;
}