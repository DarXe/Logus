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
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <vector>
#include "logus.hpp"
#include "randomLogus.hpp"
#include "var.hpp"
//#include "functions.hpp"

#define q(var) cout<<#var<<"="<<var<<endl //tests

using namespace std;
#include "patch.cpp"
int console();
void liveChat(int &wyswietlaneWiersze);
void menu();
void menuBezPL();
void wersja();

#include "func.cpp" //functions
#include "proc.cpp" //procedures

int main(int argc, char** argv) //maa main
{
	fstream file;
	file.open("console.log");
		while(!file.good())
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
	file.close();

	file.open("logus.ini");
		if(file.good())
		{
			if(getVer()<190622) patch_190622();
			else if(getVer() != ver) patch(); else odczyt();
		}
		else
		{
			zapis();
		}
	file.close();

	SetConsoleTitle("Logus 19.8.12-pre");
	srand(time(NULL));

	color(kolorGlowny);
	if(codePage852)
	{
		SetConsoleOutputCP(852); //code page 852
		SetConsoleCP(852);
	}
	else
	{
		SetConsoleOutputCP(65001); //code page utf-8
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

	console();

	return 0;
}

int console() //con
{
	int lineCount = 0;
	int lineCountAll = 0;
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

		switch(wyb) //set0 MENU
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
			lineCount = 0;
			lineCountAll = 0;
			lineCountAll+=teamsay(f,6);
			lineCountAll+=teamsay(e,5);
			lineCountAll+=teamsay(d,4);
			lineCountAll+=teamsay(c,3);
			lineCountAll+=teamsay(b,2);
			lineCountAll+=teamsay(a,1);
			lineCount=teamsay(L,0);
			cout<<"Wierszy w plikach MTA: "<<lineCountAll<<endl;
			cout<<"Wierszy w logus.log: "<<lineCount<<endl;
			break;
		}

		case '4':
		{
			cls();
			lineCount = 0;
			lineCountAll = 0;
			lineCountAll+=pw(f,6);
			lineCountAll+=pw(e,5);
			lineCountAll+=pw(d,4);
			lineCountAll+=pw(c,3);
			lineCountAll+=pw(b,2);
			lineCountAll+=pw(a,1);
			lineCount=pw(L,0);
			cout<<"Wierszy w plikach MTA: "<<lineCountAll<<endl;
			cout<<"Wierszy w logus.log: "<<lineCount<<endl;
			break;
		}
		case 'p':
		{
			cls();
			lineCountAll = 0;
			lineCountAll+=przelewy(f,6);
			lineCountAll+=przelewy(e,5);
			lineCountAll+=przelewy(d,4);
			lineCountAll+=przelewy(c,3);
			lineCountAll+=przelewy(b,2);
			lineCountAll+=przelewy(a,1);
			lineCountAll+=przelewy(L,0);
			cout<<"Wierszy: "<<lineCountAll<<endl;
			break;
		}
		case 'n':
		{
			cls();
			lineCountAll = 0;
			lineCount = 0;
			lineCount=all(f,6);
			lineCountAll+=lineCount;
			cout<<"Wierszy: "<<lineCount<<endl;
			lineCount=all(e,5);
			lineCountAll+=lineCount;
			cout<<"Wierszy: "<<lineCount<<endl;
			lineCount=all(d,4);
			lineCountAll+=lineCount;
			cout<<"Wierszy: "<<lineCount<<endl;
			lineCount=all(c,3);
			lineCountAll+=lineCount;
			cout<<"Wierszy: "<<lineCount<<endl;
			lineCount=all(b,2);
			lineCountAll+=lineCount;
			cout<<"Wierszy: "<<lineCount<<endl;
			lineCount=all(a,1);
			lineCountAll+=lineCount;
			cout<<"Wierszy: "<<lineCount<<endl;
			cout<<endl;
			cout<<"Wierszy we wszystkich plikach MTA: "<<lineCountAll<<endl;
			cout<<"Ilosc wierszy w logus.log: "<<all(L,10)<<endl;
			break;
		}
		case 't':
		{
			cls();
			if(isTimer) timer -= (clock()-delay2);
			liveChat(wyswietlaneWiersze); //run LiveChat
			break;
		} 
		case 'l':
		case 'L':
		{
			cls();
			lottoLogus(); //run Lotto Logus
			break;
		}
		case '5': //set1    SETTINGS one
		{
			cls();
			while(true)
			{
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
					cout<<" [8] F4 / zarobione pieniadze od ostatniego wyzerowania: $"<<money<<endl;
					cout<<" [9] Liczba dostarczonych kursow: "<<courses<<endl;
					cout<<" [0] Ranga w firmie: "<<grade*100<<"%"<<endl;
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
					cout<<" [8] F4 / zarobione pieniądze od ostatniego wyzerowania: $"<<money<<endl;
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
				Beep(dzwiekGlowny,100);
				
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
					break;
					case 'a':
					{
						cls();
						ang = (ang)?0:1;
						break;
					}
					case 'p':
					{
						cls();
						fLockPW = (fLockPW)?0:1;
						break;
					}
					case 't':
					{
						cls();
						fLockTeam = (fLockTeam)?0:1;
						break;
					}
					case 's':
					{
						cls();
						fLockKomunikat = (fLockKomunikat)?0:1;
						break;
					}
					case 'k':
					{
						cls();
						fLockNick = (fLockNick)?0:1;
						break;
					}
					case 'c':
					{
						cls();
						chatSound = (chatSound)?0:1;
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
						dynamicRefresh = (dynamicRefresh)?0:1;
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
						random = (random)?0:1;
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
						cls();
						cout<<"(INFO) Wyzerowano."<<endl;
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
								case '1': //set2 SETTINGS two
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

void liveChat(int &wyswietlaneWiersze) //lc
{
	string ostatniaLinia[11]; //ostatnie linie
	
	
	int lineCount = 0;
	fstream file;
	string line;

	if(isTimer) delay = clock();

	file.open("console.log");
		while(!file.eof())
		{
			getline(file,line);
			++lineCount;
		}
		file.close();
	getChat(lineCount);

	if(isTimer) timer -= (clock()-delay);
	while(true)
	{   
		if(isTimer) delay = clock();
		
		lineCount = 0;
		//counting lines in a log file
		file.open("console.log");
			while(!file.eof())
			{
				getline(file,line);
				++lineCount;
			}
		file.close();
		//saving information about the number of lines in an auxiliary variable
		temp = lineCount;

		for(int i(0); i<20; i++) //wait time
		{
			Sleep(refresh/20);
			if(kbhit()) break;
		}

		if(dynamicRefresh && refresh<2000 && !kbhit()) refresh+=10;

		//if key pressed
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
				}
				break;
			case 'm':
				{
					cls();
					cout<<"CZY NA PEWNO CHCESZ PRZENIESC LOGI z console.log DO PLIKU logus.log?\nESC - Anuluj | Inny klawisz - zgoda"<<endl;
					if(getch() == 27) {getChat(lineCount); break;}
					moveLogs();
				}
				break;
			case '\t':
				{
					timestamps = ((timestamps)?0:1);
					pos.X=0; pos.Y=4; SetConsoleCursorPosition(h, pos);
					cls(); getChat(lineCount);
				}
				break;
			case 48: //48? it's funny, because it's 0 :D
				{
					trackId = ((trackId)?0:1);
				}
				break;
			case 'v': //save
				{
					pos.X=10; pos.Y=0; SetConsoleCursorPosition(h, pos);
					Beep(dzwiekGlowny, 100);
					cout<<"ZAPISANO!"; Sleep(500);
					zapis();
				}
				break;
			case 'r': //read
				{
					pos.X=10; pos.Y=0; SetConsoleCursorPosition(h, pos);
					Beep(dzwiekGlowny, 100);
					cout<<"WCZYTANO!"; Sleep(500);
					odczyt();
				}
				break;
			
			default:
				{
					def();
					getChat(lineCount);
				}
				break;
			}
		}

		//timer countdown
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

		//he ad
		pos.X=0; pos.Y=0; SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, 12);
		cout<<"###############################LiveChat###############################"<<endl;
		SetConsoleTextAttribute(h, 204); cout<<" "; SetConsoleTextAttribute(h, 12);
		cout<<" Refresh:"<<refresh<<"ms"<<" # Wierszy:"<<lineCount-1<<" # Errors:"<<errors<<" #  [ESC]Return to MENU    "<<endl;
		if(isTimer)
		{
			SetConsoleTextAttribute(h, 170); cout<<" "; SetConsoleTextAttribute(h, 12);
			cout<<" Timer "<<timer/1000/60;
			if((timer/1000)%60<10) cout<<":0"; else cout<<":";
			cout<<(timer/1000)%60<<"  [s]Stop Timer # F4 ";
		}
		else
		{
			SetConsoleTextAttribute(h, 204); cout<<" "; SetConsoleTextAttribute(h, 12);
			cout<<" [t]Timer                  # F4 ";
		}
		if(courses) cout<<"$"<<money<<" # Courses:"<<courses<<" # Avg $"<<money/courses<<"                  ";
		else      cout<<"Dostarczone kursy: "<<courses<<"                                             ";
		SetConsoleTextAttribute(h, 204); cout<<"\n "; SetConsoleTextAttribute(h, 12);
		cout<<" [Tab]Timestamps #"<<track[trackId]<<" # "<<"Payment $"<<((money)?((money*0.87)-3500)*grade:0);
		SetConsoleTextAttribute(h, 204);
		pos.X=69; pos.Y=1; SetConsoleCursorPosition(h, pos); cout<<" ";
		pos.X=69; pos.Y=2; SetConsoleCursorPosition(h, pos); cout<<" ";
		pos.X=69; pos.Y=3; SetConsoleCursorPosition(h, pos); cout<<" ";
		SetConsoleTextAttribute(h, 12);
		cout<<"\n################################################"<<"#####[m]moveLogs()####"<<endl;
		pos.X=0; pos.Y=0; SetConsoleCursorPosition(h, pos);
		
		lineCount = 0;
		//counting lines in a log file after a time interval
		file.open("console.log");
			while(!file.eof())
			{
				getline(file,line);
				++lineCount;
			}
			file.clear();
			file.seekg(ios::beg); //instead of file.close() and file.open() go to begin line
		//file.close();

		temp = lineCount-temp; //difference in the number of lines
		//if it is different, it means that a new message has appeared

		if(isTimer) timer -= (clock()-delay);

		if(temp > 0)
		{
			if(isTimer) delay = clock();

			//file.open("console.log");
				if(lineCount <= 10)
				{
					switch (lineCount) //bug fix
					{
					case 10:
						getline(file, ostatniaLinia[9]);
					case 9:
						getline(file, ostatniaLinia[8]);
					case 8:
						getline(file, ostatniaLinia[7]);
					case 7:
						getline(file, ostatniaLinia[6]);
					case 6:
						getline(file, ostatniaLinia[5]);
					case 5:
						getline(file, ostatniaLinia[4]);
					case 4:
						getline(file, ostatniaLinia[3]);
					case 3:
						getline(file, ostatniaLinia[2]);
					case 2:
						getline(file, ostatniaLinia[1]);
						break;
					default:
						{
							errors++;
							//saving errors
							fstream error;
							error.open("logusErrors.log", ios::app);
								error<<">>>>>>>>>>ERROR NR "<<errors<<"<<<<<<<<<<"<<endl;
								error<<"TYPE: PRE\n";
								error<<"ROWS: "<<lineCount<<"\n";
								error<<"Refresh: "<<refresh<<"\n";
								error<<"Temp: "<<temp<<"\n";
								error<<"Lck: "<<fLockTeam<<fLockPW<<fLockKomunikat<<fLockNick<<chatSound<<"\n";
								error<<"LAST(9)\n";
								for (size_t i = 9; i >= 1; i--)
								{
									error<<i<<". "<<ostatniaLinia[i]<<endl;
								}
								cout<<endl;
							error.close();
						}
						break;
					}
				}
				else
				{
					for(int i = 0; i < lineCount-10; i++) getline(file, ostatniaLinia[10]);
					//capturing last lines
					for(int i = 9; i > 0; i--) {getline(file, ostatniaLinia[i]);}
				}
			file.close();

			if(chatSound) {Beep(750,50); timer -= 50;} //the sound of each new chat message
			if(dynamicRefresh && refresh > 500) refresh-=100; //if a new message appears, reduce the refresh rate by 100ms

			cls(); getChat(lineCount); //chat display

			//19.07.21 loops removed, only cases
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
				{
					errors++;
					fstream error;
					error.open("logusErrors.log", ios::app);
						error<<">>>>>>>>>>ERROR NR "<<errors<<"<<<<<<<<<<"<<endl;
						error<<"TYPE: POST\n";
						error<<"ROWS: "<<lineCount<<"\n";
						error<<"Refresh: "<<refresh<<"\n";
						error<<"Temp: "<<temp<<"\n";
						error<<"Lck: "<<fLockTeam<<fLockPW<<fLockKomunikat<<fLockNick<<chatSound<<"\n";
						error<<"LAST(10)\n";
						for (size_t i = 10; i >= 1; i--)
						{
							error<<i<<". "<<ostatniaLinia[i]<<endl;
						}
						cout<<endl;
					error.close();
				}
				break;
			}
			
			if(autoMoveLogs && lineCount > autoMoveLogs) moveLogs();
			if(isTimer) timer -= (clock()-delay);
		}//if
		else file.close(); //fix
	}//while
}//liveChat()
void preNews();
void wersja() //verr ver
{
	cout<<endl;
	cout<<"  Witaj "<<nick<<" !"<<endl;
	Sleep(300);
	cout<<"  _________________"<<endl;
	cout<<" |      Autor      |"<<endl;
	cout<<" |      DarXe      |"<<endl;
	cout<<" |_________________|"<<endl;
	cout<<" |Wersja  19.8.12-p|"<<endl;
	Sleep(300); cout<<endl;
	cout<<" PLANY: "<<endl;
	cout<<" Kreator wlasnych powiadomien"<<endl;
	cout<<" Wyszukiwanie wiadomosci tylko wybranych przez siebie graczy"<<endl;
	cout<<" Wyszukiwanie po tagach, ktore bedzie sie tworzylo(wysylalo) w konsoli mta"<<endl;
	cout<<" Naprawienie problemu z polskimi znakami na systemach win7"<<endl;
	cout<<" Wykonanie i dodanie ikony programu"<<endl;
	Sleep(300); cout<<endl;
	cout<<" Nie zapomnij zagladnac na githuba - znajdziesz tam informacje o tym-"<<endl;
	cout<<" -jak korzystac z programu (sa tam opisane wszystkie opcje)"<<endl;
	cout<<" https://github.com/DarXe/Logus/blob/master/README.md\n"<<endl;
	Sleep(500); Beep(dzwiekGlowny,150);
	cout<<" Wcisnij klawisz, aby wyswietlic nowosci"<<endl; getch();
	cls();
	cout<<" CO NOWEGO?"<<endl;
	preNews();
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
	cout<<" [L] PTS TOTOLOTEK - Lotto Logus"<<endl;
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
	cout<<"                                [ESC] Wyjście i zapis                              "<<endl;
}

void menuBezPL()
{
	SetConsoleTextAttribute(h, 10);
	cout<<" _______________________________________MENU_______________________________________"<<endl;
	SetConsoleTextAttribute(h, 11);
	cout<<" [Enter] Uruchom MTA i polacz z PTS / Polacz ponownie"<<endl;
	cout<<" [L] PTS TOTOLOTEK - Lotto Logus"<<endl;
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

void preNews()
{
	SetConsoleTextAttribute(h, 7);
	cout<<" Lotto Logus"<<endl;
	cout<<" * Dodano nowa opcje, dzieki ktorej mozna sprawdzic % szanse wygranej gracza i pustego losu"<<endl;
	cout<<" * Losuje 4 nicki z listy dodanych graczy i generuje 10000 losowan liczac % szanse dla kazdego gracza"<<endl;
	cout<<" * Lekko zmieniono animacje oraz edytowano napisy w losowaniu, powtorce losowania\n"<<endl;
	SetConsoleTextAttribute(h, 10);
	cout<<" Zmiany"<<endl;
	cout<<" Naprawiono wyswietlanie wyplaty, ktora byla na minusie przy zerowym F4."<<endl;
	cout<<"   * Przy niskim zarobku wyplata bedzie wyswietlana na minusie"<<endl;
	cout<<" Dodano komunikat. Po przeniesieniu logow w konsoli pojawi sie bialy napis"<<endl;
	SetConsoleTextAttribute(h, 15);
	cout<<" Brak wierszy po przeniesieniu logow!"<<endl;
	SetConsoleTextAttribute(h, 10);
	cout<<" Dorobiono prawą scianę do naglówka w LiveChat."<<endl;
	cout<<" Zmiana nazwy programu z Logus-v19.x.x na samo Logus"<<endl;
	cout<<" Od teraz nie trzeba bedzie robic kolejnych skrotow do programu"<<endl;
	cout<<"   * Wystarczy zrobic to ostatni raz, po tej aktualizacji"<<endl;
	cout<<"   * Dodatkowo wklejając do logow nową wersje nadpisujemy starą - nie trzeba kasowac"<<endl;
	SetConsoleTextAttribute(h, 7);
	cout<<" Porada: Jak szybko zaktualizowac Logusa?"<<endl;
	cout<<" Jesli nie masz jeszcze skrotu to wykorzystaj ten sposob przy next aktualizacji"<<endl;
	cout<<"   * Wystarczy miec skrot do Logusa na pulpicie - zaznaczamy ją jednym kliknieciem"<<endl;
	cout<<"   * wciskamy kombinacje Alt+Enter, a po pojawieniu sie okna kombinacje Alt+T"<<endl;
	cout<<"   * ii.. jestesmy w katalogu z logami. Wklejamy tutaj pobranego Logusa."<<endl;
	cout<<" Zoptymalizowano przenoszenie logow ( bez uzycia push_back() )"<<endl;
	SetConsoleTextAttribute(h, 10);
	cout<<" Dodano generowanie informacji na temat bledow do pliku logusError.log (tam gdzie Logus)"<<endl;
	cout<<" Dodano 2 opcje w LiveChat - [v]Zapis [r]Odczyt"<<endl;
	cout<<"   * Sluzy to do szybkiej edycji ustawien i ich zapisu, bez wychodzienia z LC"<<endl;
	cout<<"   * Nalezy zapisac [v], dodac recznie ustawienia w logus.ini i pozniej wczytac [r]"<<endl;
	cout<<" Ciag dalszy poszukiwan problemu z pomijaniem niektorych komunikatow"<<endl;
	cout<<"   * Jak na razie przenioslem odpowiednio kod w celu najlepszej wydajnosci przy sprawdzaniu"<<endl;
}