// Copyright (C) 2018-2019  DarXe

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <iostream>
#include <fstream>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <vector>

using namespace std;
#include "var.hpp"

int console();
void liveChat(int &wyswietlaneWiersze);
void liveChatBeep(string &ostatniaLinia);
int all(string &nazwa, int nrPliku);
int teamsay(string &nazwa, int nrPliku);
int pw(string &nazwa, int nrPliku);
int przelewy(string &nazwa, int nrPliku);
int nickname(string &nazwa, int nrPliku);
void moveLogs();
void menu();
void menuBezPL();
void wersja();

#include "patch.cpp"
#include "func.cpp"
#include "proc.cpp"
#include "randomLogus.cpp"

int main(int argc, char** argv) //maa main
{
	srand(time(NULL));
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
			Sleep(1000);
			cout<<"Dowolny klawisz - zamknij okno\n"<<endl;
			if(kbhit()) return 0;
		}
	plik.close();

	plik.open("logus.ini");
		if(plik.good())
		{
			if(getVer()<190622) patch_190622();
			else if(getVer() != ver) patch(); else odczyt();
		}
		else
		{
			zapis();
		}
	plik.close();

	SetConsoleTitle("Logus 19.7.21");

	srand(time(NULL));

	console();
	return 0;
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
		if(isTimer) delay2 = clock();
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
			if(isTimer) timer -= (clock()-delay2);
			liveChat(wyswietlaneWiersze); //run LiveChat
			break;
		} //set1    (ustawienia)
		case 'l':
		case 'L':
		{
			cls();
			lottoLogus();
			break;
		}
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
					cout<<" [m] Automatyczne przenoszenie logow: "; if(autoMoveLogs) cout<<"TAK, przy "<<autoMoveLogs<<" wierszach"; else cout<<"NIE"; cout<<endl;
					SetConsoleTextAttribute(h, 14);
					cout<<" [6] Czas rozladowywania towaru - "<<czas/60<<((czas%60<10)?":0":":")<<czas%60<<endl;
					cout<<" [7] Sam wybiore / Skrypt: "<<((random)?"5min - Skrypt":"6min - Sam wybiore")<<endl;
					SetConsoleTextAttribute(h, 7);
					cout<<" [8] F4/zarobione pieniadze od ostatniego wyzerowania: $"<<money<<endl;
					cout<<" [9] Liczba dostarczonych kursow: "<<courses<<endl;
					cout<<" [0] Ranga(%): "<<grade*100<<"%"<<endl;
					cout<<" # # Wyplata wynosi "<<"$"<<((money*0.87)-3500)*grade<<endl;
					if(courses) cout<<" # # Srednia na kurs wynosi $"<<money/courses<<endl;
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
					cout<<" [r] Przywróć ustawienia domyślne"<<endl;
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
					cout<<" [m] Automatyczne przenoszenie logów: "; if(autoMoveLogs) cout<<"TAK, przy "<<autoMoveLogs<<" wierszach"; else cout<<"NIE"; cout<<endl;
					SetConsoleTextAttribute(h, 14);
					cout<<" [6] Czas rozładowywania towaru - "<<czas/60<<((czas%60<10)?":0":":")<<czas%60<<endl;
					cout<<" [7] Sam wybiorę / Skrypt: "<<((random)?"5min - Skrypt":"6min - Sam wybiorę")<<endl;
					SetConsoleTextAttribute(h, 7);
					cout<<" [8] F4/zarobione pieniądze od ostatniego wyzerowania: $"<<money<<endl;
					cout<<" [9] Liczba dostarczonych kursów: "<<courses<<endl;
					cout<<" [0] Ranga w firmie: "<<grade*100<<"%"<<endl;
					cout<<" # # Wypłata wynosi "<<"$"<<((money*0.87)-3500)*grade<<endl;
					if(courses) cout<<" # # Średnia na kurs wynosi $"<<money/courses<<endl;
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
					case 'm':
					{
						cls();
						if(autoMoveLogs) autoMoveLogs = 0;
						else
							{
								while(true)
								{
									cout<<"Podaj ilosc wierszy, od jakiej maja byc przenoszone logi: ";
									if(!(cin>>autoMoveLogs))
									{
										intError();
										return 0;
									}
									if(autoMoveLogs < 50 || autoMoveLogs > 1500)
										cout<<"MIN 50; MAX 1500"<<endl;
									else
										break;
								}
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
					case '0':
					{
						cls();
						while(true)
						{
							cout<<"Podaj wartosc rangi(sama liczba, bez znaku %): ";
							if(!(cin>>grade))
							{
								intError();
								return 0;
							}
							if(grade < 20 || grade > 100)
								cout<<"MIN 20; MAX 100"<<endl;
							else
								break;
						}
						grade /= 100;
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

void liveChatBeep(string &ostatniaLinia) //bee
{
	//wiadomość pw
	if(!fLockPW){
		if(fPwOd(ostatniaLinia, ang))
		{
			Beep(dzwiekGlowny,300);
			Beep(0,interval);
			Beep(dzwiekGlowny,300);
			Beep(0,interval);
		}
	}

	//wiadomość teamowa
	if(!fLockTeam)
	{
		if(fTeam(ostatniaLinia, 0))
		{
			Beep(dzwiekGlowny,150);
			Beep(0,interval);
			Beep(dzwiekGlowny,150);
			Beep(0,interval);
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
			Beep(dzwiekGlowny,150);
			Beep(0,interval);
			Beep(dzwiekGlowny,150);
			Beep(0,interval);
		}
	}

	//nick z czatu dodany do ulubionych
	if(!fLockNick)
	{
		if(fNicknames(ostatniaLinia))
		{
			Beep(dzwiekGlowny,300);
			Beep(0,interval);
		}
	}

	if(fConsoleInput(ostatniaLinia))
	{
		Beep(dzwiekGlowny,100);
		Beep(0,interval);
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
	SetConsoleTextAttribute(h, 204); cout<<"\n "; SetConsoleTextAttribute(h, 12);
	cout<<" [Tab]Timestamps #"<<track[trackId]<<" # "<<"Payment $"<<((money*0.87)-3500)*grade;
	cout<<"\n#############################################"<<"#####[m]moveLogs()#####"<<endl;

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
	if(isTimer) delay = clock();
	iloscLinijek = 0;
	plik.open("console.log");
		while(!plik.eof())
		{
			getline(plik,linia);
			++iloscLinijek;
		}
		plik.close();

	getChat(iloscLinijek);
	if(isTimer) timer -= (clock()-delay);
	while(true)
	{   
		if(isTimer) delay = clock();
		
		iloscLinijek = 0;
		//zliczanie linijek w pliku z logami
		plik.open("console.log");
		while(!plik.eof())
		{
			getline(plik,linia);
			++iloscLinijek;
		}
		plik.close();
		//zapisanie informacji w pomocniczej zmiennej i odczekanie czasu
		temp = iloscLinijek;

		for(int i(0); i<20; i++) //odczekanie czasu
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
					isCzas = 0;
					timer = 0;
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
			case 48:
				{
					trackId = ((trackId)?0:1);
				}
				break;
			
			default:
				{
					def();
					getChat(iloscLinijek);
				}
				break;
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
				timer -= (clock()-delay);
				delay = clock();
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

		//he ad
		pos.X=0; pos.Y=0; SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, 12);
		cout<<"##############################LiveChat##############################"<<endl;
		SetConsoleTextAttribute(h, 204); cout<<" "; SetConsoleTextAttribute(h, 12);
		cout<<" Refresh:"<<refresh<<"ms"<<" # Wierszy:"<<iloscLinijek-1<<" # Errors:"<<errors<<" #  [ESC]Return to MENU    "<<endl;
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
		SetConsoleTextAttribute(h, 204); cout<<"\n "; SetConsoleTextAttribute(h, 12);
		cout<<" [Tab]Timestamps #"<<track[trackId]<<" # "<<"Payment $"<<((money*0.87)-3500)*grade;
		cout<<"\n#############################################"<<"#####[m]moveLogs()#####"<<endl;
		pos.X=0; pos.Y=0; SetConsoleCursorPosition(h, pos);
		
		if(isTimer) timer -= (clock()-delay);

		if(temp)
		{
			if(isTimer) delay = clock();
			if(dynamicRefresh && refresh > 500) refresh-=100; //jeśli pojawi się nowa wiadomość to zmniejsz częstotliwość odświeżania o 100ms
			cls();

			if(chatSound) {Beep(750,50); timer -= 50;} //dzwięk każdej nowej wiadomości czatu
		   
			plik.open("console.log");
				if(iloscLinijek <= 10)
				{
					switch (iloscLinijek) //bug fix
					{
					case 10:
						getline(plik, ostatniaLinia[9]);
					case 9:
						getline(plik, ostatniaLinia[8]);
					case 8:
						getline(plik, ostatniaLinia[7]);
					case 7:
						getline(plik, ostatniaLinia[6]);
					case 6:
						getline(plik, ostatniaLinia[5]);
					case 5:
						getline(plik, ostatniaLinia[4]);
					case 4:
						getline(plik, ostatniaLinia[3]);
					case 3:
						getline(plik, ostatniaLinia[2]);
					case 2:
						getline(plik, ostatniaLinia[1]);
						break;
					default:
						errors++;
						break;
					}
				}
				else
				{
					for(int i = 0; i < iloscLinijek-10; i++) getline(plik, ostatniaLinia[10]);
					for(int i = 9; i > 0; i--) getline(plik, ostatniaLinia[i]);
					//przechwycenie ostatnich linii
				}
			plik.close();

			getChat(iloscLinijek); //wyswietlenie czatu

			//19.05.29 rozwinięcie sprawdzania, do 5 ostatnich linii
			//19.07.04 rozwinięcie sprawdzania, do 10 ostatnich linii
			//zmiana ostatniaLinia1..2..3.. na tablice ostatniaLinia[]
			//19.07.21 usunięcie pętli, same case'y
			
			switch (temp)
			{
			case 10:
				liveChatBeep(ostatniaLinia[10]);
			case 9:
				liveChatBeep(ostatniaLinia[9]);
			case 8:
				liveChatBeep(ostatniaLinia[8]);
			case 7:
				liveChatBeep(ostatniaLinia[7]);
			case 6:
				liveChatBeep(ostatniaLinia[6]);
			case 5:
				liveChatBeep(ostatniaLinia[5]);
			case 4:
				liveChatBeep(ostatniaLinia[4]);
			case 3:
				liveChatBeep(ostatniaLinia[3]);
			case 2:
				liveChatBeep(ostatniaLinia[2]);
			case 1:
				liveChatBeep(ostatniaLinia[1]);
				break;
			default:
				if(temp>10) errors++;
				break;
			}

			if(autoMoveLogs && iloscLinijek > autoMoveLogs) moveLogs();
			if(isTimer) timer -= (clock()-delay);
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
	cout<<"  _________________"<<endl;
	cout<<" |      Autor      |"<<endl;
	cout<<" |      DarXe      |"<<endl;
	cout<<" |_________________|"<<endl;
	cout<<" | Wersja  19.7.21 |"<<endl;
	Beep(0,300);
	cout<<endl;
	cout<<" PLANY: "<<endl;
	cout<<" Kreator wlasnych powiadomien"<<endl;
	cout<<" Wyszukiwanie wiadomosci tylko wybranych przez siebie graczy"<<endl;
	cout<<" Wyszukiwanie po tagach, ktore bedzie sie tworzylo(wysylalo) w konsoli mta"<<endl;
	cout<<" Naprawienie problemu z polskimi znakami na systemach win7"<<endl;
	cout<<" Wykonanie i dodanie ikony programu"<<endl;
	Beep(0,300);
	cout<<endl;
	cout<<" Nie zapomnij zagladnac na githuba - znajdziesz tam informacje o tym-"<<endl;
	cout<<" -jak korzystac z programu (sa tam opisane wszystkie opcje)"<<endl;
	cout<<" https://github.com/DarXe/Logus/issues\n"<<endl;
	Beep(0,500);
	Beep(dzwiekGlowny,150);
	cout<<" Wcisnij klawisz, aby kontynuowac"<<endl; getch();
	cls();
	cout<<endl;
	cout<<" CO NOWEGO?"<<endl;
	SetConsoleTextAttribute(h, 7);
	cout<<" PTS TOTOLOTEK - Lotto Logus Beta"<<endl;
	cout<<" Projekt zostal rozpoczety 16 lipca. Posiada funkcje:"<<endl;
	cout<<"	* dodania graczy do listy"<<endl;
	cout<<"	* usunięcia jednego, wszystkich"<<endl;
	cout<<"	* testowe wypelnienie listy literami"<<endl;
	cout<<"	* jednorazowego losowania"<<endl;
	cout<<"	* wielokrotnego obejrzenia replay'u z losowania"<<endl;
	SetConsoleTextAttribute(h, 10);
	cout<<" LiveChat: Timestamps - ukrywanie daty i godziny logu"<<endl;
	cout<<" * Dziala to na podobnej zasadzie co /timestamp na samp"<<endl;
	cout<<" * Klawisz [Tab] Ukrywa/pokazuje te znaczniki czasu"<<endl;
	cout<<" LiveChat: Wyswietlanie aktualnej trasy i aktualizowanie jej po rozladunku."<<endl;
	cout<<" * Magazyny nie zrobia sie puste, jesli rozladowujemy tam skad wczesniej zaladowalismy."<<endl;
	cout<<" * Jest to opcja dla tych ktorzy jezdza stale trasy. Wystarczy zapamietac ktory rozladunek jest ktory."<<endl;
	cout<<" Uporzadkowano zmienne \"ostatniaLinia\", stworzenie tablicy"<<endl;
	cout<<" * to pozwolilo z latwoscia powiekszyc sprawdzanie wierszy do 10 linii-"<<endl;
	cout<<" * pokazanie sie erroru jest praktycznie niemozliwe"<<endl;
	cout<<" LiveChat: Automatyczne przenoszenie logow, gdy ich ilosc osiagnie ustalona wartosc(zalecane 500)"<<endl;
	cout<<" LiveChat: Liczenie i wyswietlanie wyplaty w naglowku LC"<<endl;
	cout<<" * Nalezy podac % rangi stanowiska oraz F4 (aktualizuje sie po dostarczeniu towaru)"<<endl;
	cout<<" Do MENU zostala dodana nowa opcja - [Enter] Uruchom MTA i polacz z PTS / Polacz ponownie"<<endl;
	cout<<" Wcisnij klawisz, aby kontynuowac"<<endl; getch();
	cls();
	cout<<" POPRAWKI"<<endl;
	cout<<" Naprawiono powiadomienia - nie bylo ich, jesli bylo mniej niz 5(10) wierszy w logu"<<endl;
	cout<<" * (moment po przeniesieniu logow)"<<endl;
	cout<<" Naprawiono opoznienia podczas korzystania z LiveChat - opcje wykonywane sa prawie natychmiastowo"<<endl;
	cout<<" * Przy odswiezaniu 1000ms opcja wykonuje sie po 50ms, po prostu dzielone jest przez 20"<<endl;
	cout<<" Naprawiono krytyczny blad, po wdrozeniu Timestamps"<<endl;
	cout<<" * Dodanie funkcji Timestamps spowodowalo, ze jesli plik console.log byl pusty to"<<endl;
	cout<<" * sprawdzane byly puste linie, teraz sprawdza tyle linii, ile jest w pliku."<<endl;
	cout<<" * (az osiagnie ilosc ustawionych wyswietlonych wierszy)"<<endl;
	cout<<" Naprawiono opoznienia odliczania timera. Potrafil mylic sie do 2 sekund na minute."<<endl;
	cout<<" * Zostaly odjete opoznienia dotyczace czasu algorytmow. Czas teraz odlicza co do 1ms."<<endl;
	cout<<" Naprawiono zle odczytywanie logow po ich przenoszeniu"<<endl;
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
	cout<<" [Enter] Uruchom MTA i połącz z PTS / Połącz ponownie"<<endl;
	cout<<" [L] PTS TOTOLOTEK - Lotto Logus Beta"<<endl;
	SetConsoleTextAttribute(h, 12);
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
	cout<<" [t] LiveChat - czat z gry w konsoli z komunikatami dźwiękowymi"<<endl;
	cout<<" [5] LiveChat - ustawienia"<<endl;
	SetConsoleTextAttribute(h, 11);
	cout<<" [1] Szukaj wiadomości teamowych w console.log"<<endl;
	cout<<" [2] Szukaj PW oraz odpowiedzi w console.log"<<endl;
	cout<<" [3] Szukaj wiadomości teamowych we wszystkich plikach .log"<<endl;
	cout<<" [4] Szukaj PW oraz odpowiedzi we wszystkich plikach .log"<<endl;
	SetConsoleTextAttribute(h, 12);
	cout<<" [p] Szukaj przelewów od i do graczy we wszystkich plikach"<<endl;
	cout<<" [n] Ilość wierszy w plikach"<<endl;
	SetConsoleTextAttribute(h, 11);
	cout<<" [w] Test ping - szybkie sprawdzenie, czy jest internet"<<endl;
	cout<<" [j] Menu bez polskich znaków"<<endl;
	cout<<" [9] Zmiana dźwięku na losowy"<<endl;
	cout<<" [0] Kodowanie: "<<((codePage852)?"852":"UTF-8")<<endl;
	cout<<" [i] INFO"<<endl;
	SetConsoleTextAttribute(h, 10);
	cout<<" __________________________________________________________________________________"<<endl;
	cout<<"                                [ESC] Wyjscie i zapis                              "<<endl;
}

void menuBezPL()
{
	SetConsoleTextAttribute(h, 10);
	cout<<" _______________________________________MENU_______________________________________"<<endl;
	SetConsoleTextAttribute(h, 11);
	cout<<" [Enter] Uruchom MTA i polacz z PTS / Polacz ponownie"<<endl;
	cout<<" [L] PTS TOTOLOTEK - Lotto Logus Beta"<<endl;
	SetConsoleTextAttribute(h, 12);
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
	cout<<" [t] LiveChat - czat z gry w konsoli z komunikatami dzwiekowymi"<<endl;
	cout<<" [5] LiveChat - ustawienia"<<endl;
	SetConsoleTextAttribute(h, 11);
	cout<<" [1] Szukaj wiadomosci teamowych w console.log"<<endl;
	cout<<" [2] Szukaj PW oraz odpowiedzi w console.log"<<endl;
	cout<<" [3] Szukaj wiadomosci teamowych we wszystkich plikach .log"<<endl;
	cout<<" [4] Szukaj PW oraz odpowiedzi we wszystkich plikach .log"<<endl;
	SetConsoleTextAttribute(h, 12);
	cout<<" [p] Szukaj przelewow od i do graczy we wszystkich plikach"<<endl;
	cout<<" [n] Ilosc wierszy w plikach"<<endl;
	SetConsoleTextAttribute(h, 11);
	cout<<" [w] Test ping - szybkie sprawdzenie, czy jest internet"<<endl;
	cout<<" [j] Menu z polskimi znakami"<<endl;
	cout<<" [9] Zmiana dzwieku na losowy"<<endl;
	cout<<" [0] Kodowanie: "<<((codePage852)?"852":"UTF-8")<<endl;
	cout<<" [i] INFO"<<endl;
	SetConsoleTextAttribute(h, 10);
	cout<<" __________________________________________________________________________________"<<endl;
	cout<<"                                [ESC] Wyjscie i zapis                              "<<endl;
}