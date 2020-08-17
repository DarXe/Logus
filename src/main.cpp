// Copyright (C) 2018-2020  DarXe

#define q(var) std::cout<<#var<<"="<<var<<"\n";
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <conio.h>
#include <windows.h>
#include <vector>
#include "ver.cpp"
#include "var.hpp"
#include "patch.cpp"
bool liveChat(int &wyswietlaneWiersze);
#include "logus.cpp"
#include "addons\randomLogus.cpp"
void wersja();
#include "menu\livechat_func.cpp"
#include "menu\livechat_proc.cpp"
#include "func.cpp" //functions
#include "proc.cpp" //procedures

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
			std::cout<<"Error, file not found!\n";
			std::cout<<"Program Logus musi znajdowac sie w folderze z logami MTA."<<std::endl;
			std::cout<<"Logus has to be in the MTA log directory.\n";
			Sleep(500);
			std::cout<<"..\\MTA San Andreas 1.5\\MTA\\logs\\\n\n";
			Sleep(500);
			std::cout<<"Nastepnie uruchom go ponownie\n";
			std::cout<<"Run it again when you're done\n\n";
			Sleep(3000);
			std::cout<<"Dowolny klawisz - zamknij Logus\n";
			std::cout<<"Any key - close Logus\n\n";
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
			cls();
			wersja();
		}
	file.close();

	#ifndef dupa
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(h, &CURSOR);
	#endif
	std::string _versionName_ = "Logus " + relVer;
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
			mess = engLang? "Closing MTA and Logus": "Zamykanie MTA i programu";
			if(!_quit) return closeLogus(mess); //close Logus
		}
	default:
		break;
	}

	menu();

	return 0;
}

void wersja()
{
	std::cout<<"  Witaj "<<nick<<" !"<<std::endl;
	Sleep(300);
	std::cout<<"  ___________________"<<std::endl;
	std::cout<<" |       Autor       |"<<std::endl;
	std::cout<<" |       DarXe       |"<<std::endl;
	std::cout<<" |     Niventill     |"<<std::endl;
	std::cout<<" |___________________|"<<std::endl;
	std::cout<<" |   Wersja "<<relVer<<"    |"<<std::endl; //verr
	/*Sleep(300); std::cout<<std::endl;
	std::cout<<" PLANY: "<<std::endl;
	std::cout<<" Kreator wlasnych powiadomien"<<std::endl;
	std::cout<<" Wyszukiwanie wiadomosci tylko wybranych przez siebie graczy"<<std::endl;
	std::cout<<" Wyszukiwanie po tagach, ktore bedzie sie tworzylo(wysylalo) w konsoli mta"<<std::endl;
	std::cout<<" Naprawienie problemu z polskimi znakami na systemach win7"<<std::endl;*/
	Sleep(300); std::cout<<std::endl;
	std::cout<<" Nie zapomnij zajrzeć na GitHub'a - znajdziesz tam informacje o tym"<<std::endl;
	std::cout<<" jak korzystać z programu (są tam opisane wszystkie opcje)"<<std::endl;
	std::cout<<" https://github.com/DarXe/Logus/blob/master/README.md\n"<<std::endl;
	Sleep(500); Beep(dzwiekGlowny,150);
	std::cout<<" Wciśnij klawisz, aby wyswietlić nowości"<<std::endl; getch();
	cls();

	////////////////////////////////////////////////////////////////// news goes here ////////////////////////////

	SetConsoleTextAttribute(h, 4);
	std::cout<<" SIERPIEŃ"<<std::endl;

	SetConsoleTextAttribute(h, 6);
	std::cout<<" 208_04 Poprawienie funkcji preConfig, dodanie preSelection(), preInputInt() oraz preInputString()\n";
	std::cout<<" 208_06 Uporządkowanie kodu i refaktoryzacja\n";
	std::cout<<" 208_06.1 Częściowe wsparcie dla języka angielskiego (jak widać nowości dalej sa po polsku Xd)\n";
	std::cout<<" * Niebawem zrobione będzie pełnoprawne wsparcie dla Win 7 (z pomocą conEmu)\n";

	std::cout<<"\n Wciśnij klawisz, aby kontynuować (ESC, aby pominąć INFO)"<<std::endl;
	if(getch() == 27)  cls(); return;
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

	std::cout<<"\n Wciśnij klawisz, aby kontynuować (ESC, aby pominąć INFO)"<<std::endl;
	if(getch() == 27)  cls(); return;
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

	std::cout<<"\n Wciśnij klawisz, aby kontynuować (ESC, aby pominąć INFO)"<<std::endl;
	if(getch() == 27)  cls(); return;
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

	std::cout<<"\n Wciśnij klawisz, aby kontynuować (ESC, aby pominąć INFO)"<<std::endl;
	if(getch() == 27)  cls(); return;
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

	cls();
}

//g++ src\main.cpp -o Logus.exe -static -s -Ofast