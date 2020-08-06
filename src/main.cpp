// Copyright (C) 2018-2020  DarXe

#include <iostream>
#include <fstream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <vector>
#include "var.hpp"
#define q(var) cout<<#var<<"="<<var<<std::endl
#include "patch.cpp"
bool liveChat(int &wyswietlaneWiersze);
void wersja();
#include "logus.cpp"
#include "lotto\randomLogus.cpp"

#include "func.cpp" //functions
#include "proc.cpp" //procedures

#include "menu\settings.cpp"
#include "menu\menu.cpp"

int main(int argc, char** argv) //maa main
{
	std::fstream file;
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
			std::fstream fileInit;
			fileInit.open("console.log", std::ios::app); fileInit.close();
			fileInit.open("console.log.1", std::ios::app); fileInit.close();
			fileInit.open("console.log.2", std::ios::app); fileInit.close();
			fileInit.open("console.log.3", std::ios::app); fileInit.close();
			fileInit.open("console.log.4", std::ios::app); fileInit.close();
			fileInit.open("console.log.5", std::ios::app); fileInit.close();
			fileInit.open("logusInfoOutput.log", std::ios::app); fileInit.close();
			fileInit.open("logus.log", std::ios::app); fileInit.close();
		}

	file.close();

	file.open("logus.ini");
		if(file.good())
		{
			if(getVer() != ver) patch(); else odczyt();
		}
		else
		{
			// installed OS detection, might be working funky :-D
			DWORD val;
			DWORD dataSize = sizeof(val);
			if (ERROR_SUCCESS == RegGetValueA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "CurrentMajorVersionNumber", RRF_RT_DWORD, nullptr, &val, &dataSize) && val>=10)
				codePage852 = 0;
			else
				codePage852 = 1;
			preConfig();
			zapis();
			wersja();
		}
	file.close();

	#ifndef dupa
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(h, &CURSOR);
	#endif
	std::string _versionName_ = "Logus 20.8";
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

	menu();

	return 0;
}

bool liveChat(int &wyswietlaneWiersze) //lc
{
	bool isAutoJoin = false;
	std::string ostatniaLinia[11]; //ostatnie linie
	int lineCount = 0;
	std::fstream file;
	std::string line;

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

		if(!isAutoJoin)
		{
			for(int i(0); i<20; i++) //wait time
			{
				Sleep(refresh/20);
				if(kbhit()) break;
			}
		}
		else
		{
			serverConnect();
			for(int i(5); i>0; i--) //wait 5s
			{
				pos.X=3; pos.Y=4; SetConsoleCursorPosition(h, pos);
				SetConsoleTextAttribute(h, 12); std::cout<<" autoJoin: trying to connect in "<<i<<"s ";
				Sleep(5000/5);
				if(kbhit()) break;
			}
		}

		if(dynamicRefresh && refresh<950 && !kbhit()) refresh+=5;

		//if key pressed
		if(kbhit())
		{
			switch (getch())
			{
			case 27: cls(); return 1;
			case 't': startTimer(); break;
			case 's': stopTimer(); break;
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
			case 13: //enter start autoJoin
			{
				isAutoJoin = true;
				pos.X=3; pos.Y=4; SetConsoleCursorPosition(h, pos);
				SetConsoleTextAttribute(h, 12); std::cout<<"    START autoJoin    ";
				Beep(dzwiekGlowny, 750);
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

		liveChatHead(lineCount);
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
			file.seekg(std::ios::beg); //instead of file.close() and file.open() go to begin line

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
							std::fstream error;
							error.open("logusErrors.log", std::ios::app);
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
					std::fstream error;
					error.open("logusErrors.log", std::ios::app);
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

			if(isAutoJoin)
			{
				switch (temp)
				{
				case 10:
					if(ostatniaLinia[10][gt] != 'c') stopAutoJoin(isAutoJoin);
				case 9:
					if(ostatniaLinia[9][gt] != 'c') stopAutoJoin(isAutoJoin);
				case 8:
					if(ostatniaLinia[8][gt] != 'c') stopAutoJoin(isAutoJoin);
				case 7:
					if(ostatniaLinia[7][gt] != 'c') stopAutoJoin(isAutoJoin);
				case 6:
					if(ostatniaLinia[6][gt] != 'c') stopAutoJoin(isAutoJoin);
				case 5:
					if(ostatniaLinia[5][gt] != 'c') stopAutoJoin(isAutoJoin);
				case 4:
					if(ostatniaLinia[4][gt] != 'c') stopAutoJoin(isAutoJoin);
				case 3:
					if(ostatniaLinia[3][gt] != 'c') stopAutoJoin(isAutoJoin);
				case 2:
					if(ostatniaLinia[2][gt] != 'c') stopAutoJoin(isAutoJoin);
				case 1:
					if(ostatniaLinia[1][gt] != 'c') stopAutoJoin(isAutoJoin);
					break;
				
				default:
					break;
				}
			}

			if(autoMoveLogs && (lineCount > autoMoveLogs)) moveLogs();
			if(isTimer) timer -= (clock()-delay);
		}//if
		else file.close(); //fix
	}//while
	return 1;
}//liveChat()
void News();
void wersja()
{
	std::cout<<std::endl;
	std::cout<<"  Witaj "<<nick<<" !"<<std::endl;
	Sleep(300);
	std::cout<<"  ___________________"<<std::endl;
	std::cout<<" |       Autor       |"<<std::endl;
	std::cout<<" |       DarXe       |"<<std::endl;
	std::cout<<" |     Niventill     |"<<std::endl;
	std::cout<<" |___________________|"<<std::endl;
	std::cout<<" |    Wersja 20.8    |"<<std::endl; //verr
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
	News();
	cls();
}

void News() //news
{
	SetConsoleTextAttribute(h, 10);
	std::cout<<" Od 12 sierpnia '19 prace nad programem zostały wstrzymane"<<std::endl;
	std::cout<<" Nowy Rok, nowe wyzwania - kontynuacja rozwoju programu :)"<<std::endl;
	SetConsoleTextAttribute(h, 4);
	std::cout<<" ZMIANY - początek roku"<<std::endl;
	SetConsoleTextAttribute(h, 6);
	std::cout<<" Jeszcze w sierpniu zmieniono system sprawdzania nowych linii"<<std::endl;
	std::cout<<" 201_2 Wylaczono powiadomienia na kazda wiadomosc gracza dodanego do Nicknames"<<std::endl;
	std::cout<<" * Pozostaje powiadomienie na wejscie i wyjscie z serwera oraz na status AFK danego gracza"<<std::endl;
	std::cout<<" 202_13 Poprawiono blad przy wyswietlaniu wyplaty wiekszej niz $1000000 w LiveChat oraz ustawieniach"<<std::endl;
	std::cout<<" * Dodatkowo juz nie bedzie wyswietlana wyplata mniejsza niz 0"<<std::endl;
	std::cout<<" 202_13 Zmodyfikowano sprawdzanie warunków przy dostarczonym towarze"<<std::endl;
	std::cout<<" * Jest to kolejna próba testów z serii 'co powoduje pomijanie zapisu niektórych kursów'"<<std::endl;
	std::cout<<" 202_13 Po wciśnięciu entera wraz z uruchomieniem serwera włączy się funkcja LiveChat"<<std::endl;
		std::cout<<"\n Wciśnij klawisz, aby kontynuować (ESC, aby pominac INFO)"<<std::endl;
		if(getch() == 27) return; cls();
	SetConsoleTextAttribute(h, 4);
	std::cout<<" MARZEC"<<std::endl;
	SetConsoleTextAttribute(h, 6);
	std::cout<<" 203_1 Zmieniono polecenie reconnect z 'r' na 'rr'"<<std::endl;
	std::cout<<" 203_1 Dodano nowy plik .log, aby mieć szybszy dostęp do logów z powiadomień(PW, TEAM, TOWAR, PRZELEWY)"<<std::endl;
	std::cout<<" * Po wyłączeniu komunikatu dźwiękowego w opcjach linijka z logiem nie pojawi się w tym pliku"<<std::endl;
	std::cout<<" * Plik znajduje się w folderze logs, logusInfoOutput.log"<<std::endl;
	std::cout<<" 203_1 Zmieniono kolorystykę czatu w LiveChat oddzielając wiadomość od nazwy gracza"<<std::endl;
	std::cout<<" * Jak na razie zmiany zostały wprowadzone w trybie bez daty(Timestamps)"<<std::endl;
	std::cout<<" 203_2 Został dodany kolor żółty dla powiadomień zaczynających się od '*'"<<std::endl;
	std::cout<<" 203_3 Dodano nową komendę - ustawienie F4 z poziomu konsoli MTA"<<std::endl;
	std::cout<<" * Wpisując w konsoli 'set m KWOTA', F4 ustawi się na podaną wartość"<<std::endl;
	std::cout<<" * Dodano też komendę na ustawienie ilości kursów - set c KURSY"<<std::endl;
		std::cout<<"\n Wciśnij klawisz, aby kontynuować (ESC, aby pominac INFO)"<<std::endl;
		if(getch() == 27) return; cls();
	SetConsoleTextAttribute(h, 4);
	std::cout<<" MAJ"<<std::endl;
	SetConsoleTextAttribute(h, 6);
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
	std::cout<<" 205_91 Usunięto Logus-pre, od teraz Logus.exe na masterze jest aktualnym wydaniem Pre-Realease"<<std::endl;
	std::cout<<" 205_10 Poprawiono czyszczenie czatu po przeniesieniu logów"<<std::endl;
	std::cout<<" 205_10 Rozmiar Logusa jako aplikacji .exe o wiele się zmniejszył"<<std::endl;
	std::cout<<" 205_11 Dodano nową funkcje w LiveChat - [Enter] autoJoin"<<std::endl;
	std::cout<<" * Dopóki nie nastąpi połączenie z serwerem, Logus łączy się z nim co 5 sekund"<<std::endl;
	std::cout<<" 205_11.1 Zmiana funkcji sprawdzającej podania napisu zamiast liczby"<<std::endl;
	std::cout<<" * Teraz nie jest potrzebne restartowanie programu w przypadku pomyłki"<<std::endl;
	std::cout<<" 205_11.2 Dodano prekonfigurację w przypadku braku pliku logus.ini"<<std::endl;
		std::cout<<"\n Wciśnij klawisz, aby kontynuować (ESC, aby pominac INFO)"<<std::endl;
		if(getch() == 27) return; cls();
	SetConsoleTextAttribute(h, 4);
	std::cout<<" CZERWIEC-LIPIEC"<<std::endl;
	SetConsoleTextAttribute(h, 6);
	std::cout<<" 206_9 Zmieniono system sprawdzania połączenia wi-fi, opcja 'w' z menu"<<std::endl;
	std::cout<<" * Od teraz Logus uruchomi powiadomienie dźwiękowe tylko wtedy, kiedy wróci internet"<<std::endl;
	std::cout<<" 206_10 Ping (opcja 'w') dodano możliwość sprawdzenia innego adresu"<<std::endl;
	std::cout<<" 206_11 Dodano powiadomienia na przelewy od innych graczy"<<std::endl;
	std::cout<<" 206_12 Dodano możliwość ustawienia timera pod bind z mta (pomysł - arki)"<<std::endl;
	std::cout<<" * wystarczy zrobić binda /bind <klawisz> xxx(nick, który nie istnieje) msg x"<<std::endl;
	std::cout<<" 206_12.1 Ponowne włączenie bindu na timer wyłącza go (dłuższy Beep)"<<std::endl;
	std::cout<<" 206_15 Ukryto migający kursor w konsoli"<<std::endl;
	std::cout<<" 206_28 Dodano tryb automatycznego otwierania bramy, gdy ktoś poprosi o open na PW"<<std::endl;
	std::cout<<" * 207_5 Konwersja makra na pasteCmd.exe"<<std::endl;
	std::cout<<" 207_31 Wydanie wersji 20.7"<<std::endl;
	std::cout<<" 208_04 Poprawienie funkcji preConfig, dodanie preSelection(), preInputInt() oraz preInputString()\n";
}

//g++ src\main.cpp -o Logus.exe -static -s -Ofast