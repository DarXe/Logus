// Logus Copyright 2018-2019 (C) DarXe

#include <iostream>
#include <fstream> // fstream
//#include <cstdlib> // system("cls") || jest w windows.h
#include <time.h> //time.h || ctime - srand(time(NULL));
#include <conio.h> //getch();
#include <windows.h> //sleep();
#include <vector>
//#include "console.h"

using namespace std;

//var (ZMIENNE)

//logus.ini
string mtasa = "185.62.189.174:22003"; //ip serwera
const int ver = 190622; //zmienna wersji, nie wolno edytować
int dzwiekGlowny = 1777;
bool fLockTeam = 0;
bool fLockPW = 0;
bool fLockKomunikat = 0;
bool fLockNick = 0;
bool menuGlowne = 1;
bool chatSound = 0; //the sound of any chat message
string kolorGlowny = "A";
int wyswietlaneWiersze = 15;
int refresh = 300;
bool ang = 0;
int interval = 50; //time interval between sounds
string nick = "PodajSwojNick"; //nick na MTA
bool dynamicRefresh = 0;
vector<string> nicknames;
int czas = 90; //TIMER ustalony przez gracza czas w sekundach ładowania/rozładowywania danego towaru
bool random = 0; //TIMER losowy rozładunek, FALSE = 'sam wybiore'
int money = 0; //courses calculator - money for delivered courses
int courses = 0; //courses calculator - number of courses
bool fastStart = 0; //start Logus + LiveChat with MTA

int tempRefresh = 0; 
short gt = 33; //główny tekst
int leng = 0; //wyk. w funkcje
fstream plik;
string linia = " ";
char wyb = ' '; //wybór w menu; tymczasowa w fTransport
int iloscLinijekAll = 0;
string a = "console.log";
string b = "console.log.1";
string c = "console.log.2";
string d = "console.log.3";
string e = "console.log.4";
string f = "console.log.5";

//liveChat
//clock_t t1 = 0, t2 = 0; //pomiary delay
int iloscLinijek = 0;
string ostatniaLinia = ""; //ostatnia
string ostatniaLinia2 = ""; //przedostatnia
string ostatniaLinia3 = ""; //trzecia od dołu
string ostatniaLinia4 = ""; //czwarta od dołu
string ostatniaLinia5 = ""; //piata od dołu
int temp = 0; //pomocnicza zmienna iloscLinijek w LiveChat
int temp2 = 0; //pomocnicza2 w LiveChat
int errors = 0; //liczenie błędów, jeśli liczba linijek przekroczy 5;
string s_temp = ""; //string temp
int timer = 0; //TIMER odliczanie czasu do rozładowania
bool isTimer = 0; //TIMER pomocnicza zmienna - czy timer ma odliczac
bool isCzas = 0; //TIMER pomocnicza zmienna - czas po zaladowaniu, odliczanie
int avg = 0; //courses calculator - average

int console();
int all(string nazwa, int nrPliku);
void idzdoxy(int x, int y);
void liveChat(int wyswietlaneWiersze);
int liveChatBeep(string ostatniaLinia);
int teamsay(string nazwa, int nrPliku);
int pw(string nazwa, int nrPliku);
int przelewy(string nazwa, int nrPliku);
string randomColor();
void moveLogs();
int getVer();
void zapis();
void odczyt();
void patch();
void readDefault();

//func
//[2019-05-24 17:02:41] [Output] : Gracz: ASL|DarXe Team: 15, 3191$, Tytul: Gracz ASL|DarXe rozładował towar Pucolana, waga: 1, wynagrodzenie: 3191$.
bool fTeam(string linia, bool e) //e - uwzglednianie wlasnego nicku(wspolna funkcja, dlatego wyjatek)
{
    leng = nick.length();
    if(linia[gt]=='('&&linia[gt+1]=='T'&&linia[gt+2]=='E'&&linia[gt+3]=='A'&&linia[gt+4]=='M')
    {
        if(e) return 1;
        if(linia[gt+6+leng]!=nick[leng-1]&&linia[gt+5+leng]!=nick[leng-2]&&linia[gt+4+leng]!=nick[leng-3])
            return 1; 
        else return 0;
    }
    else return 0;
}
//(team) [pts]nick
//012345678

bool fPwOd(string linia, bool ang)
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

bool fPwDo(string linia)
{
    if(linia[gt]=='-'&&linia[gt+1]=='>')
        return 1;
    else return 0;
}

bool fPrzelewyOd(string linia, bool ang)
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

bool fPrzelewyDo(string linia, bool ang)
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

bool fKomunikat(string linia, bool ang)
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

void co(string s, int n)//pomocnicze wyświetlenie tagu i zmiennej
{
    cout<<s<<": "<<n<<endl;
}

bool fTransport(string linia, bool ang)
{
    //linia = "[2019-05-24 17:02:41] [Output] : Pieniądze za transport 2191$ zostały przelane na konto firmy.";
    //[2019-05-24 17:02:41] [Output] : You've earned $2792. It has been transfered to your company's account.
    //[2019-05-24 17:02:41] [Output] : Pieniądze za transport 3191$ zostały przelane na konto firmy.
    if(ang)
    {
        if(linia[gt]=='Y'&&linia[gt+4]=='v'&&linia[gt+14]=='$')
        {
            if(linia[gt+19] == '.')
            {
                int liczba, mnoz=1000;
                for(int i = 48; i<52; i++)//57 58 59 60 61 xxxx$
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
                for(int i = 48; i<51; i++)//57 58 59 60 xxx$
                {
                    liczba = linia[i];
                    liczba -= 48;
                    money += liczba*mnoz;
                    mnoz /= 10;
                }
                courses++;
                zapis();
            }
            return 1;
        }
        else return 0;
    }
    else
    {
        if(linia[gt]=='P'&&linia[gt+1]=='i'&&linia[gt+2]=='e'&&linia[gt+3]=='n'&&linia[gt+4]=='i')
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
            return 1;
        }
        else return 0;
    }
}
//Otrzymałeś
//0123456789
bool fNick(string linia)
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

void startTimer()
{
    timer = czas*1000;
    if(random) timer += 300000; else timer += 360000;
    isTimer = 1;
    isCzas = 1;
    idzdoxy(0,2); cout<<"  Timer 0:00  [s]Stop Timer   ";
}

//[2019-06-28 11:58:25] [Input]  : test
bool fConsoleInput(string linia)
{
    if(linia[gt-10]=='I')
    {
        if(linia[gt]=='r'&&linia[gt+1]!='e')
        {
            s_temp = "start mtasa://"+mtasa;
            system(s_temp.c_str());
            return 1;
        }
        else if(linia[gt]=='t'&&linia[gt+1]!='e')
        {
            startTimer();
            return 1;
        }
        else return 0;
    }
    else return 0;
}

//Ogolne
void nrPliku(int nr)
{
    if(nr != 10)
        cout<<">>>>>>>>>>>>>>>>>>>>Plik nr "<<nr<<"<<<<<<<<<<<<<<<<<<<<"<<endl;
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
    fstream plik;
    plik.open("console.log");
        while(!plik.good())
        {
            Beep(dzwiekGlowny,125);
            Beep(0,interval);
            Beep(dzwiekGlowny,125);
            cout<<"Error, nie odnaleziono pliku!"<<endl;
            cout<<"Program Logus musi znajdowac sie w folderze z logami mta."<<endl;
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

    SetConsoleTitle("Logus 19.6.28");

    srand(time(NULL));

    console();
    //ftest();
    //system("pause");
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

void zapis(){ //sa save
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
    bool fastStart = 0;
}

int console() //con
{
    SetConsoleOutputCP(65001); //kodowanie utf-8
    SetConsoleCP(65001);
    if(fastStart)
    {
        s_temp = "start mtasa://"+mtasa;
        system(s_temp.c_str());
        cls();
        Beep(dzwiekGlowny,100);
        color(kolorGlowny);
        liveChat(wyswietlaneWiersze);
    }
    else wersja();
    
    while(true)
    {
        Beep(dzwiekGlowny,100);
        color(kolorGlowny);

        /* sprawdzanie polskich znaków
        system("chcp");
        system("chcp 1250");
        cout<<"ę e"<<endl;
        cout<<"? u"<<endl;
        cout<<"ó o"<<endl;
        cout<<"ł l"<<endl;
        cout<<"ś s"<<endl;
        cout<<"ą a"<<endl;
        cout<<"ż z"<<endl;
        cout<<"ź x"<<endl;
        cout<<"ć c"<<endl;
        cout<<"ń n"<<endl;
        system("chcp");
        */

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
            for(int i = 0; i<5; i++){
                Sleep(400);
                cout<<".";
            }
            break;
        }

        switch(wyb)
        {
        case '1':
        {
            cls();
            teamsay(a,0);
            break;
        }
        case '2':
        {
            cls();
            pw(a,0);
            break;
        }
        case '3':
        {
            cls();
            iloscLinijekAll = 0;
            iloscLinijekAll+=teamsay(f,5);
            iloscLinijekAll+=teamsay(e,4);
            iloscLinijekAll+=teamsay(d,3);
            iloscLinijekAll+=teamsay(c,2);
            iloscLinijekAll+=teamsay(b,1);
            iloscLinijekAll+=teamsay(a,0);
            cout<<"Wierszy: "<<iloscLinijekAll<<endl;
            break;
        }

        case '4':
        {
            cls();
            iloscLinijekAll = 0;
            iloscLinijekAll+=pw(f,5);
            iloscLinijekAll+=pw(e,4);
            iloscLinijekAll+=pw(d,3);
            iloscLinijekAll+=pw(c,2);
            iloscLinijekAll+=pw(b,1);
            iloscLinijekAll+=pw(a,0);
            cout<<"Wierszy: "<<iloscLinijekAll<<endl;
            break;
        }
        case 'n':
        {
            cls();
            iloscLinijekAll = 0;
            iloscLinijek = 0;
            iloscLinijek=all(f,5);
            iloscLinijekAll+=iloscLinijek;
            cout<<"Wierszy: "<<iloscLinijek<<endl;
            iloscLinijek=all(e,4);
            iloscLinijekAll+=iloscLinijek;
            cout<<"Wierszy: "<<iloscLinijek<<endl;
            iloscLinijek=all(d,3);
            iloscLinijekAll+=iloscLinijek;
            cout<<"Wierszy: "<<iloscLinijek<<endl;
            iloscLinijek=all(c,2);
            iloscLinijekAll+=iloscLinijek;
            cout<<"Wierszy: "<<iloscLinijek<<endl;
            iloscLinijek=all(b,1);
            iloscLinijekAll+=iloscLinijek;
            cout<<"Wierszy: "<<iloscLinijek<<endl;
            iloscLinijek=all(a,0);
            iloscLinijekAll+=iloscLinijek;
            cout<<"Wierszy: "<<iloscLinijek<<endl;
            cout<<endl;
            cout<<"Wierszy we wszystkich plikach: "<<iloscLinijekAll<<endl;
            break;
        }
        case 't':
        {
            cls();
            liveChat(wyswietlaneWiersze); //uruchomienie funkcji liveChat
            break;
        } //set    (ustawienia)
        case '5':
        {
            cls();
            while(true)
            {
                Beep(dzwiekGlowny,100);
                cout<<" ________________________Ustawienia - LiveChat________________________"<<endl;
                cout<<" (INFO) Mozesz tez zmienic ustawienia recznie - w pliku logus.ini"<<endl;
                cout<<" [a] Flaga na PTS: "<<((ang)?"ANG":"PL")<<endl;
                cout<<" [p] Dzwiek wiadomosci PW: "<<((!fLockPW)?"TAK":"NIE")<<endl;
                cout<<" [t] Dzwiek wiadomosci teamowych: "<<((!fLockTeam)?"TAK":"NIE")<<endl;
                cout<<" [s] Dzwiek komunikatow(raport, transport): "<<((!fLockKomunikat)?"TAK":"NIE")<<endl;
                cout<<" [k] Powiadomienia na czacie - wybrane nicki: "<<((!fLockNick)?"TAK":"NIE")<<endl;
                cout<<" [c] Dzwiek kazdej wiadmosci na czacie: "<<((chatSound)?"TAK":"NIE")<<endl;
                cout<<endl;
                cout<<" [1] Liczba wyswietlanych wierszy: "<<wyswietlaneWiersze<<endl;
                cout<<" [2] Czestotliwosc odswiezania(100-5000): "<<refresh<<endl;
                cout<<" [3] Dynamiczne odswiezanie: "<<((dynamicRefresh)?"TAK":"NIE")<<endl;
                cout<<" [4] Czestotliwosc dzwieku(50-10000): "<<dzwiekGlowny<<endl;
                cout<<" [5] Przerwa miedzy dzwiekami(50-1000): "<<interval<<endl;
                cout<<endl;
                cout<<" [6] Czas rozladowywania towaru - "<<czas/60<<((czas%60<10)?":0":":")<<czas%60<<endl;
                cout<<" [7] Sam wybiore / Skrypt: "<<((random)?"5min - Skrypt":"6min - Sam wybiore")<<endl;
                cout<<endl;
                cout<<" [8] F4/zarobione pieniadze od ostatniego wyzerowania: $"<<money<<endl;
                cout<<" [9] Liczba dostarczonych kursow: "<<courses<<endl;
                cout<<" [x] Wyzeruj stan F4 i kursow"<<endl;
                cout<<endl;
                cout<<" [b] Nicknames - baza danych wybranych nickow"<<endl;
                cout<<" [n] Nickname: "<<nick<<endl;
                cout<<" _____________________________________________________________________"<<endl;
                cout<<"                         [ESC] Powrot i zapis                        "<<endl;
                wyb = wybor();
                if(wyb == 27){
                    cls();
                    zapis();
                    break;
                }
                    
                switch(wyb)
                {
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
                            Beep(dzwiekGlowny,100);
                            cout<<" _____________________Ustawienia - Nicknames_____________________"<<endl;
                            cout<<" (INFO) Mozesz tez wpisywac nazwy recznie w pliku logus.ini"<<endl;
                            cout<<" [1] Dodaj nowego gracza"<<endl;
                            cout<<" [2] Usun ostatnio dodanego gracza"<<endl;
                            cout<<" [3] Wyswietl liste dodanych graczy"<<endl;
                            cout<<" [4] Usun gracza o danym id z listy\n"<<endl;
                            cout<<" [r] Wykonaj odczyt z pliku, jesli gracz zostal dodany w logus.ini"<<endl;
                            cout<<" [x] Usun wszystkich graczy"<<endl;
                            cout<<" ________________________________________________________________"<<endl;
                            cout<<"                       [ESC] Powrot i zapis                      "<<endl;
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
            kolorGlowny = randomColor();
            break;
        }
        case 'p':
        {
            cls();
            iloscLinijekAll = 0;
            iloscLinijekAll+=przelewy(f,5);
            iloscLinijekAll+=przelewy(e,4);
            iloscLinijekAll+=przelewy(d,3);
            iloscLinijekAll+=przelewy(c,2);
            iloscLinijekAll+=przelewy(b,1);
            iloscLinijekAll+=przelewy(a,0);
            cout<<"Wierszy: "<<iloscLinijekAll<<endl;
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
            if(fastStart)
                fastStart = 0;
            else
                fastStart = 1;
            break;
        }
        default:
            def();
        }//switch
    }
    return 0;
}

void ftest(){
    fstream plik;
    plik.open("ftest.ini", ios::out);
        int dane = 4;
        int k = 5532;
        int kk = 5533;
        string p = "ini_name: ";
        p = "ini_name1: ";
        plik<<p<<22<<"\n";
        p = "ini_name2: ";
        plik<<p<<44<<"\n";
        p = "ini_name3: ";
        plik<<p<<55<<"\n";
        p = "ini_name4: ";
        plik<<p<<66;
    plik.close();
    plik.open("ftest.ini");
        while(!plik.eof()){
            plik>>p;
            plik>>k;
            cout<<k<<" ";
        }
    plik.close();
}

int liveChatBeep(string ostatniaLinia) //bee
{
    int temp = 0;
    //wiadomość pw
    if(!fLockPW){
        if(fPwOd(ostatniaLinia, ang))
        {
            Beep(dzwiekGlowny,300);
            Beep(0,interval);
            temp+=interval; temp+=300;
            Beep(dzwiekGlowny,300);
            Beep(0,interval);
            temp+=interval; temp+=300;
            //refresh = tempRefresh;
        }
    }
    //wiadomość teamowa
    if(!fLockTeam)
    {
        if(fTeam(ostatniaLinia, 0))
        {
            Beep(dzwiekGlowny,150);
            Beep(0,interval);
            temp+=interval; temp+=150;
            Beep(dzwiekGlowny,150);
            Beep(0,interval);
            temp+=interval; temp+=150;
            //refresh = tempRefresh;
        }
    }
    //dostarczenie towaru, raport z frakcji
    if(!fLockKomunikat)
    {
        if(fTransport(ostatniaLinia, ang)||fKomunikat(ostatniaLinia, ang))
        {
            Beep(dzwiekGlowny,150);
            Beep(0,interval);
            temp+=interval; temp+=150;
            Beep(dzwiekGlowny,150);
            Beep(0,interval);
            temp+=interval; temp+=150;
            Beep(dzwiekGlowny,150);
            Beep(0,interval);
            temp+=interval; temp+=150;
            //refresh = tempRefresh;
        }
    }
    //nick z czatu dodany do ulubionych
    if(!fLockNick)
    {
        if(fNick(ostatniaLinia))
        {
            Beep(dzwiekGlowny,300);
            Beep(0,interval);
            temp+=interval; temp+=300;
            //refresh = tempRefresh;
        }
    }
    if(fConsoleInput(ostatniaLinia))
    {
        Beep(dzwiekGlowny,100);
        Beep(0,interval);
        temp+=interval; temp+=500;
    }
    return temp;
}

int all(string nazwa, int nr)
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

void liveChat(int wyswietlaneWiersze) //lc //ilosc wierszy wyswietlanych
{
    while(true)
    {   
        temp2 = 0;
        //t1 = clock(); // start
        if(kbhit())
        {
            wyb = getch();
            if(wyb == 27) { cls(); break;}
            switch (wyb)
            {
            case 't':
                {
                    Beep(dzwiekGlowny, 100);
                    startTimer();
                }
                break;
            case 's':
                {
                    Beep(dzwiekGlowny, 100);
                    isTimer = 0;
                    idzdoxy(0,2); cout<<"  [t]Timer                     ";
                }
                break;
                
            case 'm':
                {
                    cls();
                    cout<<"CZY NA PEWNO CHCESZ PRZENIESC LOGI DO PLIKU logus.log?\nESC - Anuluj | Inny klawisz - zgoda"<<endl;
                    if(getch() == 27) break;
                    moveLogs();
                }
                break;
            
            default:
                {
                    def();
                    cout<<"\n czekaj.."<<endl;
                }
            }
        }

        iloscLinijek = 0; //unfortunately :D Tak, to tylko jedna linijka bugowała :)

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
        iloscLinijek = 0;
        Sleep(refresh);

        //zliczanie linijek w pliku z logami nr2
        plik.open("console.log");
        while(!plik.eof())
        {
            getline(plik,linia);
            ++iloscLinijek;
        }
        plik.close();

        //t1 = clock() - t1;
        if(dynamicRefresh && refresh<2000) refresh+=10;

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
                            timer-=interval; timer-=150;
                            Beep(dzwiekGlowny+50,150);
                            Beep(0,interval);
                            timer-=interval; timer-=150;
                            Beep(dzwiekGlowny+100,150);
                            Beep(0,interval);
                            timer-=interval; timer-=150;
                            isCzas = 0;
                        }
                    }
                    else
                    {
                        if(timer<360000)
                        {
                            Beep(dzwiekGlowny,150);
                            Beep(0,interval);
                            timer-=interval; timer-=150;
                            Beep(dzwiekGlowny+50,150);
                            Beep(0,interval);
                            timer-=interval; timer-=150;
                            Beep(dzwiekGlowny+100,150);
                            Beep(0,interval);
                            timer-=interval; timer-=150;
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
                idzdoxy(0,2); cout<<"  [t]Timer                     ";
            }
        }
        temp = iloscLinijek-temp; //różnica linijek
        //jeśli po odczekaniu czasu ilości się różnią to znaczy, że ktoś coś napisał
        
        idzdoxy(0, 0);
        cout<<" ###############################LiveChat###############################"<<endl;
        cout<<"  Refresh:"<<refresh<<"ms"<<" # Wierszy:"<<iloscLinijek-1<<" # Errors:"<<errors<<" #  [ESC]Return to MENU"<<endl;
        if(isTimer)
        {
            cout<<"  Timer "<<timer/1000/60;
            if((timer/1000)%60<10) cout<<":0"; else cout<<":";
            cout<<(timer/1000)%60<<"  [s]Stop Timer    ";
        }
        else cout<<"  [t]Timer                     ";
        if(money&&courses) cout<<"$"<<money<<" # Courses:"<<courses<<" # Avg $"<<money/courses<<"                  ";
        else      cout<<"Dostarczone kursy:0                                             ";
        cout<<"\n ######################################################################"<<endl;

        if(temp)
        {
            if(dynamicRefresh && refresh>500) refresh-=100; //jeśli pojawi się nowa wiadomość to zmniejsz częstotliwość odświeżania o 100ms
            cls();
            cout<<" ###############################LiveChat###############################"<<endl;
            cout<<"  Refresh:"<<refresh<<"ms"<<" # Wierszy:"<<iloscLinijek-1<<" # Errors:"<<errors<<" #  [ESC]Return to MENU"<<endl;
            if(isTimer)
            {
                cout<<"  Timer "<<timer/1000/60;
                if((timer/1000)%60<10) cout<<":0"; else cout<<":";
                cout<<(timer/1000)%60<<"  [s]Stop Timer    ";
            }
            else cout<<"  [t]Timer                     ";
            if(money&&courses) cout<<"$"<<money<<" # Courses:"<<courses<<" # Avg $"<<money/courses<<"                  ";
            else      cout<<"                                                         ";
            cout<<"\n ######################################################################"<<endl;

            if(chatSound) {Beep(750,50); timer -= 50;} //dzwięk każdej nowej wiadomości czatu

            //t2 = clock();
           
            plik.open("console.log");
            for(int i = 0; i < iloscLinijek-5; i++)
            {
                getline(plik, ostatniaLinia5);
            }
            getline(plik, ostatniaLinia4);
            getline(plik, ostatniaLinia3); 
            getline(plik, ostatniaLinia2); //przechwycenie przedostatniej linii
            getline(plik, ostatniaLinia); //przechwycenie ostatniej linii
            plik.close();

            //pobranie linii, które nie mają być wyświetlone
            plik.open("console.log");
            for(int i = 0; i < iloscLinijek-wyswietlaneWiersze-1; i++)
            {
                getline(plik, linia);
            }
            
            //wyświetlenie pozostałych linii
            for(int i = 0; i < wyswietlaneWiersze; i++)
            {
                getline(plik, linia);
                cout<<" "<<linia<<endl;
            }
            plik.close();

            //t2 = clock() - t2;

            //19.5.29 rozwinięcie sprawdzania, do 5 ostatnich linii
            if(temp == 1){
                temp2=liveChatBeep(ostatniaLinia);
            }
            else if(temp == 2){
                temp2=liveChatBeep(ostatniaLinia2);
                temp2+=liveChatBeep(ostatniaLinia);
            }
            else if(temp == 3){
                temp2=liveChatBeep(ostatniaLinia3);
                temp2+=liveChatBeep(ostatniaLinia2);
                temp2+=liveChatBeep(ostatniaLinia);
            }
            else if(temp == 4){
                temp2=liveChatBeep(ostatniaLinia4);
                temp2+=liveChatBeep(ostatniaLinia3);
                temp2+=liveChatBeep(ostatniaLinia2);
                temp2+=liveChatBeep(ostatniaLinia);
            }
            else if(temp == 5){
                temp2=liveChatBeep(ostatniaLinia5);
                temp2+=liveChatBeep(ostatniaLinia4);
                temp2+=liveChatBeep(ostatniaLinia3);
                temp2+=liveChatBeep(ostatniaLinia2);
                temp2+=liveChatBeep(ostatniaLinia);
            }
            else errors++;
            
            timer -= temp2;
        }//if
    }//while
}//liveChat()

int teamsay(string nazwa, int nr)
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
                        break;
                    }
                    cls();
                }
            }
        }
    plik.close();

    return iloscLinijek;
}

int pw(string nazwa, int nr)
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
                        break;
                    }
                    cls();
                }
            }
        }
    plik.close();

    return iloscLinijek;
}

int przelewy(string nazwa, int nr)
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

//jakas funkcja z neta, może się przydać kiedyś do czyszczenia w inny sposób w LiveChat
//i się przydała :)
void idzdoxy(int x, int y){
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;

    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);
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
    Beep(dzwiekGlowny,150);
    Beep(dzwiekGlowny,150);
    Beep(dzwiekGlowny,150);
    cout<<endl;
    cout<<"  Witaj "<<nick<<" !"<<endl;
    cout<<"  _______________"<<endl;
    cout<<" |     Autor     |"<<endl;
    cout<<" |     DarXe     |"<<endl;
    cout<<" |_______________|"<<endl;
    cout<<" |Wersja 19.6.28p|"<<endl;
    cout<<endl;
    cout<<" PLANY: "<<endl;
    
    cout<<" znalezienie przyczyny braku polskich znakow na systemach win7"<<endl;
    cout<<" mozliwosc zmiany dlugosci dzwieku dla powiadomien"<<endl;
    cout<<" mozliwosc zmiany ilosci dzwiekow dla powiadomien"<<endl;
    cout<<" Dodanie ikony programu\n"<<endl;
    cout<<" Wcisnij klawisz, aby kontynuowac"<<endl; getch();
    cout<<endl;
    cout<<" CO NOWEGO?"<<endl;
    cout<<" Naprawienie bledu po aktualizacji - lista zapisanych graczy Nicknames nie wczytywala sie"<<endl;
    cout<<"     Bylo to spowodowane dodaniem kolejnego ustawienia, po nowej aktualizacji"<<endl;
    cout<<" Naprawiono blad przy wyszukiwaniu wiadomosci (team) wyslanych przez siebie"<<endl;
    cout<<"     Spowodowany byl wylaczeniem powiadomienia dzwiekowego na wlasny nick"<<endl;
    cout<<" Naprawiono buga przy podawaniu litery zamiast liczby - potrzebny restart programu"<<endl;
    cout<<" Od teraz przy pierwszym uruchomieniu programu po aktualizacji pojawi sie info o tym"<<endl;
    cout<<" Zrealizowano pomysl gracza Niventill - dodano mozliwosc odpalenia Logusa razem z serwerem PTS"<<endl;
    cout<<" Gracz ten podsunal tez pomysl szybkiego startu - pomijanie info o wersji, wybranie LiveChat"<<endl;
    cout<<"     wszystko to powiazane bedzie z opcja odpalenia Logusa wraz z MTA"<<endl;
    cout<<" Zmieniono sposob wyswietlania przeszukiwanych logow na zasadzie 'stron'"<<endl;
    cout<<"     Dowolny klawisz - nastepne 30 wierszy. [ESC] przejscie do nastepnego pliku"<<endl;
    cout<<" Opracowanie funkcji liczacej sume i sredni zarobek z dostarczonych kursow w LiveChat"<<endl;
    cout<<" Czyszczenie pliku console.log - na ktorym dziala LiveChat i zachowanie przy tym logow (optymalizacja)"<<endl;
    cout<<"     opcja jest dostepna w funkcji LiveChat pod klawiszem[m]"<<endl;
    cout<<" Opracowanie funkcji czytajacej konsole z mta (F8, tylda)"<<endl;
    cout<<"     Polecenia nalezy wyslac w tej konsoli, bez znaku '/'. 2 nowe polecenia:"<<endl;
    cout<<"     t - start timera, od teraz nie trzeba go uruchamiac przez konsole"<<endl;
    cout<<"     r - zwykly /reconnect"<<endl;
    cout<<" Dodano auto-zapis po kazdym dostarczonym kursie"<<endl;
    cout<<" Nowy wyglad naglowka w LiveChat"<<endl;
    cout<<" W ustawieniach Nicknames dodano wyswietlenie aktualnej listy graczy przy usuwaniu po id z tej listy"<<endl;
    cout<<endl;
    cout<<" USTAWIENIA"<<endl;
    cout<<"     Szybki start w MENU glownym, opcja [s]"<<endl;
    cout<<" LiveChat"<<endl;
    cout<<"     Zmiana klawisza stopu Timera z [c] na [s]"<<endl;
    cout<<"     Ustawianie aktualnego F4, opcja [8]"<<endl;
    cout<<"     Ustawianie aktualnej ilosci kursow, opcja [9]"<<endl;
    cout<<"     Wyzeruj stan F4 i ilosc kursow, opcja [x]"<<endl;
    cout<<"     Wspomniana wyzej opcja [m], sluzy do przenoszenia logow do oddzielnego pliku z glownego pliku"<<endl;
    cout<<endl;
    cout<<" Wcisnij klawisz, aby wyswietlic MENU"<<endl;
    getch();
    cls();
}
void menu()
{
    cout<<" _______________________________MENU_______________________________"<<endl;
    cout<<" [t] LiveChat - czat z gry w konsoli z komunikatami dźwiękowymi"<<endl;
    cout<<" [5] LiveChat - ustawienia"<<endl;
    cout<<" [s] Szybki start LiveChat + PTS: "<<((fastStart)?"TAK":"NIE")<<endl;
    cout<<endl;
    cout<<" [1] Szukaj wiadomości teamowych w najnowszym pliku"<<endl;
    cout<<" [2] Szukaj PW oraz odpowiedzi w najnowszym pliku"<<endl;
    cout<<" [3] Szukaj wiadomości teamowych we wszystkich plikach"<<endl;
    cout<<" [4] Szukaj PW oraz odpowiedzi we wszystkich plikach"<<endl;
    cout<<endl;
    cout<<" [p] Szukaj przelewów od i do graczy we wszystkich plikach"<<endl;
    cout<<" [n] Ilość wierszy w plikach"<<endl;
    cout<<" [w] Test ping - szybkie sprawdzenie, czy jest internet"<<endl;
    cout<<" [j] Menu bez polskich znaków"<<endl;
    cout<<" [i] INFO"<<endl;
    cout<<endl;
    cout<<" [9] Zmiana dźwięku na losowy"<<endl;
    cout<<" [0] Zmiana koloru MENU na losowy"<<endl;
    cout<<" __________________________________________________________________"<<endl;
    cout<<"                       [ESC] Wyjście i zapis                      "<<endl;
}
void menuBezPL()
{
    cout<<" _______________________________MENU_______________________________"<<endl;
    cout<<" [t] LiveChat - Czat z gry w konsoli z komunikatami dzwiekowymi"<<endl;
    cout<<" [5] LiveChat - ustawienia"<<endl;
    cout<<" [s] Szybki start LiveChat + PTS: "<<((fastStart)?"TAK":"NIE")<<endl;
    cout<<endl;
    cout<<" [1] Szukaj wiadomosci teamowych w najnowszym pliku"<<endl;
    cout<<" [2] Szukaj PW oraz odpowiedzi w najnowszym pliku"<<endl;
    cout<<" [3] Szukaj wiadomosci teamowych we wszystkich plikach"<<endl;
    cout<<" [4] Szukaj PW oraz odpowiedzi we wszystkich plikach"<<endl;
    cout<<endl;
    cout<<" [p] Szukaj przelewow od i do graczy we wszystkich plikach"<<endl;
    cout<<" [n] Ilosc wierszy w plikach"<<endl;
    cout<<" [w] Test ping - szybkie sprawdzenie, czy jest internet"<<endl;
    cout<<" [j] Menu z polskimi znakami"<<endl;
    cout<<" [i] INFO"<<endl;
    cout<<endl;
    cout<<" [9] Zmiana dzwieku na losowy"<<endl;
    cout<<" [0] Zmiana koloru MENU na losowy"<<endl;
    cout<<" __________________________________________________________________"<<endl;
    cout<<"                       [ESC] Wyjscie i zapis                      "<<endl;
}