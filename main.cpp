// Copyright (C) 2018-2020  DarXe

#include <iostream>
#include <fstream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <vector>
#include "logus.hpp"
#include "randomLogus.hpp"
#include "var.hpp"
//g++  main.cpp src\*.cpp
#define q(var) cout<<#var<<"="<<var<<endl
using namespace std;
#include "patch.cpp"
int console();
bool liveChat(int &wyswietlaneWiersze);
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
			std::cout<<"Error, nie odnaleziono pliku!"<<std::endl;
			std::cout<<"Program Logus musi znajdowac sie w folderze z logami MTA."<<std::endl;
			Sleep(500);
			std::cout<<"..\\MTA San Andreas 1.5\\MTA\\logs\\(tutaj wklej program)"<<std::endl;
			Sleep(500);
			std::cout<<"Nastepnie uruchom go ponownie\n"<<std::endl;
			Sleep(1000);
			std::cout<<"Dowolny klawisz - zamknij okno\n"<<std::endl;
			if(kbhit()) return 0;
		}
		
		{
			fstream fileInit;
			fileInit.open("console.log", ios::app); fileInit.close();
			fileInit.open("console.log.1", ios::app); fileInit.close();
			fileInit.open("console.log.2", ios::app); fileInit.close();
			fileInit.open("console.log.3", ios::app); fileInit.close();
			fileInit.open("console.log.4", ios::app); fileInit.close();
			fileInit.open("console.log.5", ios::app); fileInit.close();
			fileInit.open("logusInfoOutput.log", ios::app); fileInit.close();
			fileInit.open("logus.log", ios::app); fileInit.close();
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
	string _versionName_ = "Logus 20.5 Pre-Release";
	SetConsoleTitleA(_versionName_.c_str()); //verr
	std::srand(time(NULL));
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
			bool _quit = runLiveChat();
			if(!_quit) return closeLogus("Zamykanie MTA i programu"); //close Logus
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
			return closeLogus("Zamykanie programu");
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
			std::cout<<"Wierszy w plikach MTA: "<<lineCountAll<<std::endl;
			std::cout<<"Wierszy w logus.log: "<<lineCount<<std::endl;
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
			std::cout<<"Wierszy w plikach MTA: "<<lineCountAll<<std::endl;
			std::cout<<"Wierszy w logus.log: "<<lineCount<<std::endl;
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
			std::cout<<"Wierszy: "<<lineCountAll<<std::endl;
			break;
		}
		case 'n':
		{
			cls();
			lineCountAll = 0;
			lineCount = 0;
			lineCount=all(f,6);
			lineCountAll+=lineCount;
			std::cout<<"Wierszy: "<<lineCount<<std::endl;
			lineCount=all(e,5);
			lineCountAll+=lineCount;
			std::cout<<"Wierszy: "<<lineCount<<std::endl;
			lineCount=all(d,4);
			lineCountAll+=lineCount;
			std::cout<<"Wierszy: "<<lineCount<<std::endl;
			lineCount=all(c,3);
			lineCountAll+=lineCount;
			std::cout<<"Wierszy: "<<lineCount<<std::endl;
			lineCount=all(b,2);
			lineCountAll+=lineCount;
			std::cout<<"Wierszy: "<<lineCount<<std::endl;
			lineCount=all(a,1);
			lineCountAll+=lineCount;
			std::cout<<"Wierszy: "<<lineCount<<std::endl;
			std::cout<<std::endl;
			std::cout<<"Wierszy we wszystkich plikach MTA: "<<lineCountAll<<std::endl;
			std::cout<<"Ilosc wierszy w logus.log: "<<all(L,10)<<std::endl;
			break;
		}
		case 't':
		{
			cls();
			if(isTimer) timer -= (clock()-delay2);
			bool _quit = liveChat(wyswietlaneWiersze); //run LiveChat
			if(!_quit) return closeLogus("Zamykanie MTA i programu"); //close Logus
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
					std::cout<<" ________________________Ustawienia - LiveChat________________________"<<std::endl;
					SetConsoleTextAttribute(h, 7);
					std::cout<<" [r] Przywroc ustawienia domyslne"<<std::endl;
					std::cout<<" [a] Flaga na PTS: "<<((ang)?"ANG":"PL")<<std::endl;
					SetConsoleTextAttribute(h, 14);
					std::cout<<" [p] Dzwiek wiadomosci PW: "<<((!fLockPW)?"TAK":"NIE")<<std::endl;
					std::cout<<" [t] Dzwiek wiadomosci teamowych: "<<((!fLockTeam)?"TAK":"NIE")<<std::endl;
					std::cout<<" [s] Dzwiek komunikatow(raport, transport): "<<((!fLockKomunikat)?"TAK":"NIE")<<std::endl;
					std::cout<<" [k] Powiadomienia na czacie - wybrane nicki: "<<((!fLockNick)?"TAK":"NIE")<<std::endl;
					std::cout<<" [c] Dzwiek kazdej wiadmosci na czacie: "<<((chatSound)?"TAK":"NIE")<<std::endl;
					SetConsoleTextAttribute(h, 7);
					std::cout<<" [1] Liczba wyswietlanych wierszy: "<<wyswietlaneWiersze<<std::endl;
					std::cout<<" [2] Czestotliwosc odswiezania(100-5000): "<<refresh<<std::endl;
					std::cout<<" [3] Dynamiczne odswiezanie: "<<((dynamicRefresh)?"TAK":"NIE")<<std::endl;
					std::cout<<" [4] Czestotliwosc dzwieku(50-10000): "<<dzwiekGlowny<<std::endl;
					std::cout<<" [5] Przerwa miedzy dzwiekami(50-1000): "<<interval<<std::endl;
					std::cout<<" [m] Automatyczne przenoszenie logow: "; if(autoMoveLogs) std::cout<<"TAK, przy "<<autoMoveLogs<<" wierszach"; else std::cout<<"NIE"; std::cout<<std::endl;
					SetConsoleTextAttribute(h, 14);
					std::cout<<" [6] Czas rozladowywania towaru - "<<czas/60<<((czas%60<10)?":0":":")<<czas%60<<std::endl;
					std::cout<<" [7] Sam wybiore / Skrypt: "<<((random)?"5min - Skrypt":"6min - Sam wybiore")<<std::endl;
					SetConsoleTextAttribute(h, 7);
					std::cout<<" [8] F4 / zarobione pieniadze od ostatniego wyzerowania: $"<<money<<std::endl;
					std::cout<<" [9] Liczba dostarczonych kursow: "<<courses<<std::endl;
					std::cout<<" [0] Ranga w firmie: "<<grade*100<<"%"<<std::endl;
					int payment(0); payment = ((money*0.87)-3500)*grade;
					std::cout<<" # # Wyplata wynosi "<<"$"<<payment<<std::endl;
					if(courses) std::cout<<" # # Srednia na kurs wynosi $"<<money/courses<<std::endl;
					std::cout<<" [x] Wyzeruj stan F4 i kursow"<<std::endl;
					SetConsoleTextAttribute(h, 14);
					std::cout<<" [b] Nicknames - baza danych wybranych nickow"<<std::endl;
					std::cout<<" [n] Nickname: "<<nick<<std::endl;
					SetConsoleTextAttribute(h, 10);
					std::cout<<" _____________________________________________________________________"<<std::endl;
					std::cout<<"                         [ESC] Powrot i zapis                         "<<std::endl;
				}
				else
				{
					SetConsoleTextAttribute(h, 10);
					std::cout<<" ________________________Ustawienia - LiveChat________________________"<<std::endl;
					SetConsoleTextAttribute(h, 7);
					std::cout<<" [r] Przywróć ustawienia domyślne"<<std::endl;
					std::cout<<" [a] Flaga na PTS: "<<((ang)?"ANG":"PL")<<std::endl;
					SetConsoleTextAttribute(h, 14);
					std::cout<<" [p] Dźwięk wiadomości PW: "<<((!fLockPW)?"TAK":"NIE")<<std::endl;
					std::cout<<" [t] Dźwięk wiadomości teamowych: "<<((!fLockTeam)?"TAK":"NIE")<<std::endl;
					std::cout<<" [s] Dźwięk komunikatow(raport, transport): "<<((!fLockKomunikat)?"TAK":"NIE")<<std::endl;
					std::cout<<" [k] Powiadomienia na czacie - wybrane nicki: "<<((!fLockNick)?"TAK":"NIE")<<std::endl;
					std::cout<<" [c] Dźwięk każdej wiadomości na czacie: "<<((chatSound)?"TAK":"NIE")<<std::endl;
					SetConsoleTextAttribute(h, 7);
					std::cout<<" [1] Liczba wyświetlanych wierszy: "<<wyswietlaneWiersze<<std::endl;
					std::cout<<" [2] Częstotliwość odświeżania(100-5000): "<<refresh<<std::endl;
					std::cout<<" [3] Dynamiczne odświeżanie: "<<((dynamicRefresh)?"TAK":"NIE")<<std::endl;
					std::cout<<" [4] Częstotliwość dźwięku(50-10000): "<<dzwiekGlowny<<std::endl;
					std::cout<<" [5] Przerwa między dźwiękami(50-1000): "<<interval<<std::endl;
					std::cout<<" [m] Automatyczne przenoszenie logów: "; if(autoMoveLogs) std::cout<<"TAK, przy "<<autoMoveLogs<<" wierszach"; else std::cout<<"NIE"; std::cout<<std::endl;
					SetConsoleTextAttribute(h, 14);
					std::cout<<" [6] Czas rozładowywania towaru - "<<czas/60<<((czas%60<10)?":0":":")<<czas%60<<std::endl;
					std::cout<<" [7] Sam wybiorę / Skrypt: "<<((random)?"5min - Skrypt":"6min - Sam wybiorę")<<std::endl;
					SetConsoleTextAttribute(h, 7);
					std::cout<<" [8] F4 / zarobione pieniądze od ostatniego wyzerowania: $"<<money<<std::endl;
					std::cout<<" [9] Liczba dostarczonych kursów: "<<courses<<std::endl;
					std::cout<<" [0] Ranga w firmie: "<<grade*100<<"%"<<std::endl;
					int payment(0); payment = ((money*0.87)-3500)*grade;
					std::cout<<" # # Wyplata wynosi "<<"$"<<payment<<std::endl;
					if(courses) std::cout<<" # # Średnia na kurs wynosi $"<<money/courses<<std::endl;
					std::cout<<" [x] Wyzeruj stan F4 i kursów"<<std::endl;
					SetConsoleTextAttribute(h, 14);
					std::cout<<" [b] Nicknames - baza danych wybranych nicków"<<std::endl;
					std::cout<<" [n] Nickname: "<<nick<<std::endl;
					SetConsoleTextAttribute(h, 10);
					std::cout<<" _____________________________________________________________________"<<std::endl;
					std::cout<<"                         [ESC] Powrót i zapis                         "<<std::endl;
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
						std::cout<<"CZY NA PEWNO CHCESZ TO ZROBIC? ESC - Anuluj | Inny klawisz - zgoda"<<std::endl;
						if(getch() == 27) break;
						readDefault();
						std::cout<<"Ustawienia domyslne programu zostaly przywrocone!"<<std::endl;
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
							std::cout<<"Podaj nowa ilosc wyswietlanych wierszy: ";
							if(!(cin>>wyswietlaneWiersze))
							{
								intError();
								return 0;
							}
							if(wyswietlaneWiersze < 1 || wyswietlaneWiersze > 100)
								std::cout<<"MIN 1; MAX 100"<<std::endl;
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
							std::cout<<"Podaj nowa czestotliwosc odswiezania: ";
							if(!(cin>>refresh))
							{
								intError();
								return 0;
							}
							if(refresh < 100 || refresh > 5000)
								std::cout<<"MIN 100(0,1s); MAX 5000(5s)"<<std::endl;
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
							std::cout<<"Podaj nowa czestotliwosc dzwieku: ";
							if(!(cin>>dzwiekGlowny))
							{
								intError();
								return 0;
							}
							if(dzwiekGlowny < 50 || dzwiekGlowny > 10000)
								std::cout<<"MIN 50; MAX 10000"<<std::endl;
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
							std::cout<<"Podaj nowy odstep miedzy dzwiekami: ";
							if(!(cin>>interval))
							{
								intError();
								return 0;
							}
							if(interval < 50 || interval > 1000)
								std::cout<<"MIN 50; MAX 1000"<<std::endl;
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
									std::cout<<"Podaj ilosc wierszy, od jakiej maja byc przenoszone logi: ";
									if(!(cin>>autoMoveLogs))
									{
										intError();
										return 0;
									}
									if(autoMoveLogs < 50 || autoMoveLogs > 1500)
										std::cout<<"MIN 50; MAX 1500"<<std::endl;
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
						std::cout<<"Podaj minuty: ";
						if(!(cin>>temp))
						{
							intError();
							return 0;
						}
						std::cout<<"Podaj sekundy: ";
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
							std::cout<<"Podaj nowa ilosc $(sama liczba): ";
							if(!(cin>>money))
							{
								intError();
								return 0;
							}
							if(money < 0 || money > 9999999)
								std::cout<<"MIN 0; MAX 9999999"<<std::endl;
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
							std::cout<<"Podaj nowa ilosc kursow: ";
							if(!(cin>>courses))
							{
								intError();
								return 0;
							}
							if(courses < 0 || courses > 9999)
								std::cout<<"MIN 0; MAX 9999"<<std::endl;
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
							std::cout<<"Podaj wartosc rangi(sama liczba, bez znaku %): ";
							if(!(cin>>grade))
							{
								intError();
								return 0;
							}
							if(grade < 20 || grade > 100)
								std::cout<<"MIN 20; MAX 100"<<std::endl;
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
						std::cout<<"CZY NA PEWNO CHCESZ TO ZROBIC? ESC - Anuluj | Inny klawisz - zgoda"<<std::endl;
						if(getch() == 27) break;
						money = 0;
						courses = 0;
						cls();
						std::cout<<"(INFO) Wyzerowano."<<std::endl;
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
								std::cout<<" _____________________Ustawienia - Nicknames_____________________"<<std::endl;
								std::cout<<" (INFO) Mozesz tez wpisywac nazwy recznie w pliku logus.ini"<<std::endl;
								SetConsoleTextAttribute(h, 14);
								std::cout<<" [1] Dodaj nowego gracza"<<std::endl;
								std::cout<<" [2] Usun ostatnio dodanego gracza"<<std::endl;
								std::cout<<" [3] Wyswietl liste dodanych graczy"<<std::endl;
								std::cout<<" [4] Usun gracza o danym id z listy"<<std::endl;
								SetConsoleTextAttribute(h, 7);
								std::cout<<" [r] Wykonaj odczyt z pliku, jesli gracz zostal dodany w logus.ini"<<std::endl;
								std::cout<<" [x] Usun wszystkich graczy"<<std::endl;
								SetConsoleTextAttribute(h, 10);
								std::cout<<" ________________________________________________________________"<<std::endl;
								std::cout<<"                       [ESC] Powrot i zapis                      "<<std::endl;
							}
							else
							{
								std::cout<<" _____________________Ustawienia - Nicknames_____________________"<<std::endl;
								std::cout<<" (INFO) Możesz też wpisywać nazwy ręcznie w pliku logus.ini"<<std::endl;
								SetConsoleTextAttribute(h, 14);
								std::cout<<" [1] Dodaj nowego gracza"<<std::endl;
								std::cout<<" [2] Usuń ostatnio dodanego gracza"<<std::endl;
								std::cout<<" [3] Wyświetl listę dodanych graczy"<<std::endl;
								std::cout<<" [4] Usuń gracza o danym id z listy"<<std::endl;
								SetConsoleTextAttribute(h, 7);
								std::cout<<" [r] Wykonaj odczyt z pliku, jeśli gracz został dodany w logus.ini"<<std::endl;
								std::cout<<" [x] Usuń wszystkich graczy"<<std::endl;
								SetConsoleTextAttribute(h, 10);
								std::cout<<" ________________________________________________________________"<<std::endl;
								std::cout<<"                       [ESC] Powrot i zapis                      "<<std::endl;
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
										std::cout<<"Podaj dokladna nazwe gracza: ";
										cin>>s_temp;
										if(s_temp.length()<3)
											std::cout<<"Minimum 3 znaki!"<<std::endl;
										else
										{   
											cls();
											nicknames.push_back(s_temp);
											std::cout<<"Dodano gracza "<<s_temp<<std::endl;
											break;
										}
									}
									break;
								}
								case '2':
								{
									cls();
									if(nicknames.empty())
										std::cout<<"(INFO) Lista graczy jest pusta"<<std::endl;
									else
									{   
										std::cout<<"Usunieto gracza "<<nicknames.back()<<std::endl;
										nicknames.pop_back();
									}
									break;
								}
								case '3':
								{
									cls();
									if(nicknames.empty())
										std::cout<<"(INFO) Lista graczy jest pusta"<<std::endl;
									else
									{   
										for(int i = 0; i < nicknames.size(); i++)
										{
											std::cout<<i+1<<". "<<nicknames.at(i)<<std::endl;
										}
									}
									break;
								}
								case '4':
								{
									cls();
									if(nicknames.empty())
										std::cout<<"(INFO) Lista graczy jest pusta"<<std::endl;
									else
									{   
										cls();
										for(int i = 0; i < nicknames.size(); i++)
										{
											std::cout<<i+1<<". "<<nicknames.at(i)<<std::endl;
										}
										std::cout<<"Podaj id gracza, ktorego chcesz usunac: ";
										if(!(cin>>temp))
										{
											intError();
											return 0;
										}
										std::cout<<"Usunieto gracza "<<nicknames.at(temp-1)<<std::endl;
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
									std::cout<<"CZY NA PEWNO CHCESZ TO ZROBIC? ESC - Anuluj | Inny klawisz - zgoda"<<std::endl;
									if(getch() == 27) break;
									nicknames.clear();
									std::cout<<"Usunieto wszystkich graczy"<<std::endl;
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
						std::cout<<"Nazwa nicku potrzebna jest do poprawnego dzialania LiveChat"<<std::endl;
						while(true)
						{
							std::cout<<"Podaj swoj nowy nick: ";
							cin>>nick;
							if(nick.length()<3)
							{
								std::cout<<"MINIMUM 3 znaki"<<std::endl;
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
				std::cout<<"Kodowanie UTF-8"<<std::endl;
			}
			else
			{
				codePage852 = 1;
				SetConsoleOutputCP(852);
				SetConsoleCP(852); 
				std::cout<<"Kodowanie 852"<<std::endl;
			}
			break;
		}
		case 'j':
		{
			cls();
			if(menuGlowne)
			{
				menuGlowne = 0;
				std::cout<<"Menu z polskimi ogonkami"<<std::endl;
			}
			else
			{
				menuGlowne = 1;
				std::cout<<"Menu bez polskich ogonkow"<<std::endl;
			}
			break;
		}
		case '9':
		{
			cls();
			dzwiekGlowny = losuj(50,10000);
			std::cout<<dzwiekGlowny<<std::endl;
			break;
		}

		case 'w':
		{
			cls();
			while(true)
			{
				Beep(dzwiekGlowny,500);
				system("ping google.pl -n 2");
				std::cout<<std::endl;
				std::cout<<"POWROT - DOWOLNY KLAWISZ"<<std::endl;
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
			bool _quit = runLiveChat();
			if(!_quit) return closeLogus("Zamykanie MTA i programu"); //close Logus
			break;
		}
		default:
			def();
		}//switch
	}
	return 0;
}

bool liveChat(int &wyswietlaneWiersze) //lc
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

		if(dynamicRefresh && refresh<950 && !kbhit()) refresh+=5;

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
					SetConsoleTextAttribute(h, 204); std::cout<<" "; SetConsoleTextAttribute(h, 12);
				}
				break;
			case 'm':
				{
					cls();
					std::cout<<"CZY NA PEWNO CHCESZ PRZENIESC LOGI z console.log DO PLIKU logus.log?\nESC - Anuluj | Inny klawisz - zgoda"<<std::endl;
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
			case 48: //48? it's funny, because it's 0 :D //clear track
				{
					trackId = ((trackId)?0:1);
				}
				break;
			case 'v': //save
				{
					pos.X=10; pos.Y=0; SetConsoleCursorPosition(h, pos);
					Beep(dzwiekGlowny, 100);
					std::cout<<"ZAPISANO!"; Sleep(500);
					zapis();
				}
				break;
			case 'r': //read
				{
					pos.X=10; pos.Y=0; SetConsoleCursorPosition(h, pos);
					Beep(dzwiekGlowny, 100);
					std::cout<<"WCZYTANO!"; Sleep(500);
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
				std::cout<<"  [t]Timer                     ";
			}
		}

		//he ad
		pos.X=0; pos.Y=0; SetConsoleCursorPosition(h, pos);
		SetConsoleTextAttribute(h, 12);
		std::cout<<"###############################LiveChat###############################"<<std::endl;
		SetConsoleTextAttribute(h, 204); std::cout<<" "; SetConsoleTextAttribute(h, 12);
		std::cout<<" Refresh:"<<refresh<<"ms"<<" # Wierszy:"<<lineCount-1<<" # Errors:"<<errors<<" #  [ESC]Return to MENU    "<<std::endl;
		if(isTimer)
		{
			SetConsoleTextAttribute(h, 170); std::cout<<" "; SetConsoleTextAttribute(h, 12);
			std::cout<<" Timer "<<timer/1000/60;
			if((timer/1000)%60<10) std::cout<<":0"; else std::cout<<":";
			std::cout<<(timer/1000)%60<<"  [s]Stop Timer # F4 ";
		}
		else
		{
			SetConsoleTextAttribute(h, 204); std::cout<<" "; SetConsoleTextAttribute(h, 12);
			std::cout<<" [t]Timer                  # F4 ";
		}
		if(courses) std::cout<<"$"<<money<<" # Courses:"<<courses<<" # Avg $"<<money/courses<<"                  ";
		else      std::cout<<"Dostarczone kursy: "<<courses<<"                                             ";
		SetConsoleTextAttribute(h, 204); std::cout<<"\n "; SetConsoleTextAttribute(h, 12);
		int payment(0); payment = ((money>0)?((money*0.87)-3500)*grade:0);
		std::cout<<" [Tab]Timestamps #"<<track[trackId]<<" # "<<"Payment $"<<payment;
		SetConsoleTextAttribute(h, 204);
		pos.X=69; pos.Y=1; SetConsoleCursorPosition(h, pos); std::cout<<" ";
		pos.X=69; pos.Y=2; SetConsoleCursorPosition(h, pos); std::cout<<" ";
		pos.X=69; pos.Y=3; SetConsoleCursorPosition(h, pos); std::cout<<" ";
		SetConsoleTextAttribute(h, 12);
		std::cout<<"\n################################################"<<"#####[m]moveLogs()####"<<std::endl;
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

		temp = lineCount-temp; //difference in the number of lines
		//if it is different, it means that a new message has appeared

		if(isTimer) timer -= (clock()-delay);

		if(temp > 0)
		{
			if(isTimer) delay = clock();

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
								error<<">>>>>>>>>>ERROR NR "<<errors<<"<<<<<<<<<<"<<std::endl;
								error<<"TYPE: PRE\n";
								error<<"ROWS: "<<lineCount<<"\n";
								error<<"Refresh: "<<refresh<<"\n";
								error<<"Temp: "<<temp<<"\n";
								error<<"Lck: "<<fLockTeam<<fLockPW<<fLockKomunikat<<fLockNick<<chatSound<<"\n";
								error<<"LAST(9)\n";
								for (size_t i = 9; i >= 1; i--)
								{
									error<<i<<". "<<ostatniaLinia[i]<<std::endl;
								}
								std::cout<<std::endl;
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
			if(dynamicRefresh && refresh > 300) refresh-=50; //if a new message appears, reduce the refresh rate by 100ms

			cls(); getChat(lineCount); //chat display

			//19.07.21 loops removed, only cases
			switch (temp)
			{
			case 10:
				if(!liveChatBeep(ostatniaLinia[10])) return 0;
			case 9:
				if(!liveChatBeep(ostatniaLinia[9])) return 0;
			case 8:
				if(!liveChatBeep(ostatniaLinia[8])) return 0;
			case 7:
				if(!liveChatBeep(ostatniaLinia[7])) return 0;
			case 6:
				if(!liveChatBeep(ostatniaLinia[6])) return 0;
			case 5:
				if(!liveChatBeep(ostatniaLinia[5])) return 0;
			case 4:
				if(!liveChatBeep(ostatniaLinia[4])) return 0;
			case 3:
				if(!liveChatBeep(ostatniaLinia[3])) return 0;
			case 2:
				if(!liveChatBeep(ostatniaLinia[2])) return 0;
			case 1:
				if(!liveChatBeep(ostatniaLinia[1])) return 0;
				break;
			default:
				{
					errors++;
					fstream error;
					error.open("logusErrors.log", ios::app);
						error<<">>>>>>>>>>ERROR NR "<<errors<<"<<<<<<<<<<"<<std::endl;
						error<<"TYPE: POST\n";
						error<<"ROWS: "<<lineCount<<"\n";
						error<<"Refresh: "<<refresh<<"\n";
						error<<"Temp: "<<temp<<"\n";
						error<<"Lck: "<<fLockTeam<<fLockPW<<fLockKomunikat<<fLockNick<<chatSound<<"\n";
						error<<"LAST(10)\n";
						for (size_t i = 10; i >= 1; i--)
						{
							error<<i<<". "<<ostatniaLinia[i]<<std::endl;
						}
						std::cout<<std::endl;
					error.close();
				}
				break;
			}
			
			if(autoMoveLogs && (lineCount > autoMoveLogs)) moveLogs();
			if(isTimer) timer -= (clock()-delay);
		}//if
		else file.close(); //fix
	}//while
	return 1;
}//liveChat()
void preNews();
void wersja()
{
	std::cout<<std::endl;
	std::cout<<"  Witaj "<<nick<<" !"<<std::endl;
	Sleep(300);
	std::cout<<"  ___________________"<<std::endl;
	std::cout<<" |       Autor       |"<<std::endl;
	std::cout<<" |       DarXe       |"<<std::endl;
	std::cout<<" |___________________|"<<std::endl;
	std::cout<<" |  Wersja 20.5-Pre  |"<<std::endl; //verr
	/*Sleep(300); std::cout<<std::endl;
	std::cout<<" PLANY: "<<std::endl;
	std::cout<<" Kreator wlasnych powiadomien"<<std::endl;
	std::cout<<" Wyszukiwanie wiadomosci tylko wybranych przez siebie graczy"<<std::endl;
	std::cout<<" Wyszukiwanie po tagach, ktore bedzie sie tworzylo(wysylalo) w konsoli mta"<<std::endl;
	std::cout<<" Naprawienie problemu z polskimi znakami na systemach win7"<<std::endl;*/
	Sleep(300); std::cout<<std::endl;
	std::cout<<" Nie zapomnij zagladnac na githuba - znajdziesz tam informacje o tym-"<<std::endl;
	std::cout<<" -jak korzystac z programu (sa tam opisane wszystkie opcje)"<<std::endl;
	std::cout<<" https://github.com/DarXe/Logus/blob/master/README.md\n"<<std::endl;
	Sleep(500); Beep(dzwiekGlowny,150);
	std::cout<<" Wcisnij klawisz, aby wyswietlic nowosci"<<std::endl; getch();
	cls();
	std::cout<<" CO NOWEGO?"<<std::endl;
	preNews();
	std::cout<<std::endl;
	std::cout<<" Wcisnij klawisz, aby wyswietlic MENU"<<std::endl;
	getch();
	cls();
}

void menu()
{
	SetConsoleTextAttribute(h, 10);
	std::cout<<" _______________________________________MENU_______________________________________"<<std::endl;
	SetConsoleTextAttribute(h, 11);
	std::cout<<" [Enter] Uruchom MTA i połącz z PTS / Połącz ponownie"<<std::endl;
	std::cout<<" [L] PTS TOTOLOTEK - Lotto Logus"<<std::endl;
	SetConsoleTextAttribute(h, 12);
	std::cout<<" [s] Szybki start LiveChat + PTS: ";
	switch (fastStart)
	{
	case 0:
		std::cout<<"Nie, ale wyświetl info o wersji";
		break;
	case 1:
		std::cout<<"Tak, uruchom MTA:PTS przy starcie Logusa";
		break;
	default:
		std::cout<<"Nie uruchamiaj, ani nie wyświetlaj info o wersji";
		break;
	}
	std::cout<<std::endl;
	std::cout<<" [t] LiveChat - czat z gry w konsoli z komunikatami dźwiękowymi"<<std::endl;
	std::cout<<" [5] LiveChat - ustawienia"<<std::endl;
	SetConsoleTextAttribute(h, 11);
	std::cout<<" [1] Szukaj wiadomości teamowych w console.log"<<std::endl;
	std::cout<<" [2] Szukaj PW oraz odpowiedzi w console.log"<<std::endl;
	std::cout<<" [3] Szukaj wiadomości teamowych we wszystkich plikach .log"<<std::endl;
	std::cout<<" [4] Szukaj PW oraz odpowiedzi we wszystkich plikach .log"<<std::endl;
	SetConsoleTextAttribute(h, 12);
	std::cout<<" [p] Szukaj przelewów od i do graczy we wszystkich plikach"<<std::endl;
	std::cout<<" [n] Ilość wierszy w plikach"<<std::endl;
	SetConsoleTextAttribute(h, 11);
	std::cout<<" [w] Test ping - szybkie sprawdzenie, czy jest internet"<<std::endl;
	std::cout<<" [j] Menu bez polskich znaków"<<std::endl;
	std::cout<<" [9] Zmiana dźwięku na losowy"<<std::endl;
	std::cout<<" [0] Kodowanie: "<<((codePage852)?"852":"UTF-8")<<std::endl;
	std::cout<<" [i] INFO"<<std::endl;
	SetConsoleTextAttribute(h, 10);
	std::cout<<" __________________________________________________________________________________"<<std::endl;
	std::cout<<"                                [ESC] Wyjście i zapis                              "<<std::endl;
}

void menuBezPL()
{
	SetConsoleTextAttribute(h, 10);
	std::cout<<" _______________________________________MENU_______________________________________"<<std::endl;
	SetConsoleTextAttribute(h, 11);
	std::cout<<" [Enter] Uruchom MTA i polacz z PTS / Polacz ponownie"<<std::endl;
	std::cout<<" [L] PTS TOTOLOTEK - Lotto Logus"<<std::endl;
	SetConsoleTextAttribute(h, 12);
	std::cout<<" [s] Szybki start LiveChat + PTS: ";
	switch (fastStart)
	{
	case 0:
		std::cout<<"Nie, ale wyswietl info o wersji";
		break;
	case 1:
		std::cout<<"Tak, uruchom MTA:PTS przy starcie Logusa";
		break;
	default:
		std::cout<<"Nie uruchamiaj, ani nie wyswietlaj info o wersji";
		break;
	}
	std::cout<<std::endl;
	std::cout<<" [t] LiveChat - czat z gry w konsoli z komunikatami dzwiekowymi"<<std::endl;
	std::cout<<" [5] LiveChat - ustawienia"<<std::endl;
	SetConsoleTextAttribute(h, 11);
	std::cout<<" [1] Szukaj wiadomosci teamowych w console.log"<<std::endl;
	std::cout<<" [2] Szukaj PW oraz odpowiedzi w console.log"<<std::endl;
	std::cout<<" [3] Szukaj wiadomosci teamowych we wszystkich plikach .log"<<std::endl;
	std::cout<<" [4] Szukaj PW oraz odpowiedzi we wszystkich plikach .log"<<std::endl;
	SetConsoleTextAttribute(h, 12);
	std::cout<<" [p] Szukaj przelewow od i do graczy we wszystkich plikach"<<std::endl;
	std::cout<<" [n] Ilosc wierszy w plikach"<<std::endl;
	SetConsoleTextAttribute(h, 11);
	std::cout<<" [w] Test ping - szybkie sprawdzenie, czy jest internet"<<std::endl;
	std::cout<<" [j] Menu z polskimi znakami"<<std::endl;
	std::cout<<" [9] Zmiana dzwieku na losowy"<<std::endl;
	std::cout<<" [0] Kodowanie: "<<((codePage852)?"852":"UTF-8")<<std::endl;
	std::cout<<" [i] INFO"<<std::endl;
	SetConsoleTextAttribute(h, 10);
	std::cout<<" __________________________________________________________________________________"<<std::endl;
	std::cout<<"                                [ESC] Wyjscie i zapis                              "<<std::endl;
}

void preNews() //news
{
	SetConsoleTextAttribute(h, 10);
	std::cout<<" Od 12 sierpnia '19 prace nad programem zostały wstrzymane"<<std::endl;
	std::cout<<" Nowy Rok, nowe wyzwania - kontynuacja rozwoju programu :)"<<std::endl;
	SetConsoleTextAttribute(h, 7);
	std::cout<<" Zmiany"<<std::endl;
	std::cout<<" Jeszcze w sierpniu zmieniono system sprawdzania nowych linii"<<std::endl;
	std::cout<<" 201_2 Wylaczono powiadomienia na kazda wiadomosc gracza dodanego do Nicknames"<<std::endl;
	std::cout<<" * Pozostaje powiadomienie na wejscie i wyjscie z serwera oraz na status AFK danego gracza"<<std::endl;
	std::cout<<" 202_13 Poprawiono blad przy wyswietlaniu wyplaty wiekszej niz $1000000 w LiveChat oraz ustawieniach"<<std::endl;
	std::cout<<" * Dodatkowo juz nie bedzie wyswietlana wyplata mniejsza niz 0"<<std::endl;
	std::cout<<" 202_13 Zmodyfikowano sprawdzanie warunków przy dostarczonym towarze"<<std::endl;
	std::cout<<" * Jest to kolejna próba testów z serii 'co powoduje pomijanie zapisu niektórych kursów'"<<std::endl;
	std::cout<<" 202_13 Po wciśnięciu entera wraz z uruchomieniem serwera włączy się funkcja LiveChat"<<std::endl;
	
	std::cout<<" 203_1 Zmieniono polecenie reconnect z 'r' na 'rr'"<<std::endl;
	std::cout<<" 203_1 Dodano nowy plik .log, aby mieć szybszy dostęp do logów z powiadomień(PW, TEAM, TOWAR)"<<std::endl;
	std::cout<<" * Po wyłączeniu komunikatu dźwiękowego w opcjach linijka z logiem nie pojawi się w tym pliku"<<std::endl;
	std::cout<<" * Plik znajduje się w folderze logs, logusInfoOutput.log"<<std::endl;
	std::cout<<" 203_1 Zmieniono kolorystykę czatu w LiveChat oddzielając wiadomość od nazwy gracza"<<std::endl;
	std::cout<<" * Jak na razie zmiany zostały wprowadzone w trybie bez daty(Timestamps)"<<std::endl;
	std::cout<<" 203_2 Został dodany kolor żółty dla powiadomień zakończonych na '!' oraz zaczynających '*'"<<std::endl;
	std::cout<<" * Bindy oraz inne wiadomości zawierające wykrzyknik też są kolorowane"<<std::endl;
	std::cout<<" 203_3 Dodano nową komendę - ustawienie F4 z poziomu konsoli MTA"<<std::endl;
	std::cout<<" * Wpisując w konsoli 'set m KWOTA', F4 ustawi się na podaną wartość"<<std::endl;
	std::cout<<" * Dodano też komendę na ustawienie ilości kursów - set c KURSY"<<std::endl;
	std::cout<<" 203_3 Usunięto kolorowanie powiadomień z wykrzyknikami"<<std::endl;

	std::cout<<" 205_6 Dodano dodatkowy warunek sprawdzający nick"<<std::endl;
	std::cout<<" * Teraz Logus bierze pod uwagę długość nicku zmniejszając szanse na błędny komunikat"<<std::endl;
	std::cout<<" 205_6 Przypisano dodatkowe działanie komendzie 'quit' z mta"<<std::endl;
	std::cout<<" * Logus wyłączy się automatycznie wraz z grą (zapisując ustawienia)"<<std::endl;
	std::cout<<" 205_6 Naprawiono problem z odczytywaniem plików log, jeśli nie zostały stworzone przez mta"<<std::endl;
	std::cout<<" * Jeśli takich plików nie ma to Logus sam je zainicjuje (pliki log.1 log.2 itd.)"<<std::endl;
	std::cout<<" 205_6 Zmieniono animacje wyłączenia programu"<<std::endl;
	std::cout<<" * Dodano dźwięki, tekst jest różny w zależności od powodu zamknięcia programu"<<std::endl;
	std::cout<<" 205_61 Dodano komendę na reset kursów i $ z poziomu konsoli mta"<<std::endl;
	std::cout<<" * 'set reset', 'set re'"<<std::endl;
	std::cout<<" 205_9 Edytowano zmianę wartości ms dynamicznym odświeżaniu"<<std::endl;
	
}

//
//todo: Wer-Dar 6:37, to były czasy
//console - wychodzenie przez quit ma tez wylaczac Logusa
//baza graczy - wybieranie powiadomien dla kazdego gracza (join, quit, afk, chat)
//
//g++ -g .\Logus\main.cpp .\Logus\src\*.cpp -o .\Logus\Logus-pre.exe -static gg

//g++ -g main.cpp src\*.cpp -o Logus-pre.exe -static
//g++  main.cpp src\*.cpp -o Logus.exe -static -s -Os
//* HydroMoon has left the game (Quit)
//* HydroMoon has joined the game
//30 kwietnia 2020