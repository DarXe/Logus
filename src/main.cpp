// Copyright © 2018-2020  DarXe
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#define q(var) std::cout<<#var<<"="<<var<<"\n";
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <filesystem>
#include <thread>

#include "ver.cpp"
#include "var.hpp"
#include "common.cpp"
#include "config.cpp"
#include "updater.cpp"
bool liveChat();
void wersja();
#include "proc.cpp" //procedures

#include "menu\menu.cpp"

int main(int argc, char** argv) //maa main
{	
	std::fstream inifile;
	inifile.open("logus.ini");
	if(inifile.good())
	{
		readConfig(0);
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

		mtaLocation = getMTALocation();
		if (GetUserDefaultUILanguage() != 1045)
			engLang = 1;
		else
			engLang = 0;
		if (getNickFromMTAConfig() != "")
			nick = getNickFromMTAConfig();
		preConfig();
		saveConfig();
		cls();
		wersja();
	}
	inifile.close();
	
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
	std::ifstream test;
	while (true)
	{
		test.open(mtaLocation + "\\MTA\\logs\\console.log");
		if (!test.good() && mtaLocation != "ERROR")
		{
			std::string temploc;
			std::cout << ((engLang)?" Found MTA Path: ":" Znaleziona ścieżka MTA: ");
			std::cout << mtaLocation << '\n';
			std::cout << ((engLang)?" MTA directory found, but console.log file couldn't been found\n":" Udało się znaleźć lokalizację MTA, ale nie znaleziono pliku console.log\n");
			std::cout << ((engLang)?" Make sure you ran MTA after it's installation. If you did so and it's still not working, pray and blame your computer\n Press any key to try find MTA path again":
			" Upewnij się, że MTA zostało uruchomione po jego zainstalowaniu.\n Jeśli poblem nadal występuje, pomódl się i poprzeklinaj na kąkuter\n Wciśnij dowolny klawisz aby spróbować znaleźć lokalizację MTA ponownie");
			getch(); mtaLocation = getMTALocation();
		}
		else if (!test.good() && mtaLocation == "ERROR")
		{
			std::string temploc;
			std::cout << ((engLang)?" MTA directory not found. Please enter path manually\n":" Nie udało się znaleźć lokalizacji MTA. Proszę podaj lokalizację manualnie\n");
			std::cout << ((engLang)?" It has to be the main directory, eg. C:\\Program Files (x86)\\MTA San Andreas 1.5\n":" Ścieżka musi być ścieżką główną, np. C:\\Program Files (x86)\\MTA San Andreas 1.5\n");
			std::cout << ((engLang)?" Enter path: ":" Podaj ścieżkę: "); getline(std::cin, mtaLocation);
		}
		else
		{
			test.close();
			consoleLogPath = mtaLocation + "\\MTA\\logs\\console.log";
			consoleLog1Path = mtaLocation + "\\MTA\\logs\\console.log.1";
			consoleLog2Path = mtaLocation + "\\MTA\\logs\\console.log.2";
			consoleLog3Path = mtaLocation + "\\MTA\\logs\\console.log.3";
			consoleLog4Path = mtaLocation + "\\MTA\\logs\\console.log.4";
			consoleLog5Path = mtaLocation + "\\MTA\\logs\\console.log.5";
			break;
		}
	}

	//q(mtaLocation); q(consoleLogPath); q(consoleLog1Path); q(consoleLog2Path); q(consoleLog3Path); q(consoleLog4Path); q(consoleLog5Path); getch(); return 0;
	std::fstream fileInit;
	std::cout<<" Updating files...\n\n";
	fileInit.open(consoleLogPath, std::ios::app); fileInit.close();
	fileInit.open(consoleLog1Path, std::ios::app); fileInit.close();
	fileInit.open(consoleLog2Path, std::ios::app); fileInit.close();
	fileInit.open(consoleLog3Path, std::ios::app); fileInit.close();
	fileInit.open(consoleLog4Path, std::ios::app); fileInit.close();
	fileInit.open(consoleLog5Path, std::ios::app); fileInit.close();
	fileInit.open("liveChatInfoOutput.log", std::ios::app); fileInit.close();
	fileInit.open("logus.log", std::ios::app); fileInit.close();

	cls();
	#ifndef SHOWCURSOR
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(h, &CURSOR);
	#endif
	std::string _versionName_ = "Logus " + relVer;
	SetConsoleTitleA(_versionName_.c_str()); //verr
	std::srand(time(NULL));
	color(kolorGlowny);

	if (getVer() != ver)
		showUpdateInfo();
	else
	{
		if (updateChannel != "disable")
			runUpdater();
	}

	switch (fastStart)
	{
	case 0:
		wersja();
		break;
	case 1:
		{
			runLiveChat();
			mess = engLang? "Closing MTA and Logus": "Zamykanie MTA i programu";
			if(_quit == 2) return closeLogus(mess); //close Logus
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
	std::cout<<" |      Autorzy      |"<<std::endl;
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
	std::cout<<" WRZESIEŃ"<<std::endl;

	SetConsoleTextAttribute(h, 6);
	std::cout<<" 209_01 Wykrycie wypadku uruchomi teraz także timer (resetując przy okazji inne timery)\n";
	std::cout<<" 209_01 Dodano nowe ustawienie - automatyczne otwieranie bramy po otrzymaniu PW kończącego się na ""open""\n";
	std::cout<<" 209_01 Poprawiono kilka błędów powstałych po optymalizacji liveChat, teraz powinno być git\n";

	std::cout<<"\n Wciśnij klawisz, aby kontynuować (ESC, aby pominąć INFO)"<<std::endl;
	if(getch() == 27)
	{
		cls();
		return;
	}
	cls();
	SetConsoleTextAttribute(h, 4);
	std::cout<<" SIERPIEŃ"<<std::endl;

	SetConsoleTextAttribute(h, 6);
	std::cout<<" 208_31 Wyszukiwanie logów (przelewów, wiadomości teamowych itp) działa teraz tak jak nigdy dotąd\n";
	std::cout<<" 208_31 Dalsza optymalizacja liveChat - chodzi naprawdę szybko :-)\n";
	std::cout<<" 208_31 Nowe ustawienie - maksymalny i minimalny dynamiczny refresh\n";
	std::cout<<" 208_31 Dodano także nowe bugi, tj. brak kompatybilności ustawień z poprzednimi wersjami...\n";
	std::cout<<" * Kosztem tego jest config v2, czyli 57 biednych else ifów pracujących na czarno\n";
	std::cout<<" 208_31 Przebudowa niektórych komend w taki sposób, aby przyjmowały dowolne wartości\n";
	std::cout<<" 208_31 Nowe komendy w LiveChat - set n add nick i set n del nick (usuwa lub dodaje nick do bazy nicków)\n";
	std::cout<<" 208_31 Automatyczne wyszukiwanie nicku i lokalizacji MTA\n";
	std::cout<<" 208_25 Gruntowna przebudowa LiveChat, w końcu mniejsze zużycie I/O i brak pomijania logów!\n";
	std::cout<<" 208_17 Dodanie integracji z komisem, tj. możliwość sprawdzenia cen pojazdów w komisie\n";
	std::cout<<" * Niebawem zrobione będzie pełnoprawne wsparcie dla Win 7 (z pomocą conEmu)\n";
	std::cout<<" 208_06.1 Częściowe wsparcie dla języka angielskiego (jak widać nowości dalej sa po polsku Xd)\n";
	std::cout<<" 208_06 Uporządkowanie kodu i refaktoryzacja\n";
	std::cout<<" 208_04 Poprawienie funkcji preConfig, dodanie preSelection(), preInputInt() oraz preInputString()\n";

	std::cout<<"\n Wciśnij klawisz, aby kontynuować (ESC, aby pominąć INFO)"<<std::endl;
	if(getch() == 27)
	{
		cls();
		return;
	}
	cls();
	SetConsoleTextAttribute(h, 4);
	std::cout<<" CZERWIEC-LIPIEC"<<std::endl;

	SetConsoleTextAttribute(h, 6);
	std::cout<<" 207_31 Wydanie wersji 20.7"<<std::endl;
	std::cout<<" * 207_5 Konwersja makra na pasteCmd.exe"<<std::endl;
	std::cout<<" 206_28 Dodano tryb automatycznego otwierania bramy, gdy ktoś poprosi o open na PW"<<std::endl;
	std::cout<<" 206_15 Ukryto migający kursor w konsoli"<<std::endl;
	std::cout<<" 206_12.1 Ponowne włączenie bindu na timer wyłącza go (dłuższy Beep)"<<std::endl;
	std::cout<<" * wystarczy zrobić binda /bind <klawisz> xxx(nick, który nie istnieje) msg x"<<std::endl;
	std::cout<<" 206_12 Dodano możliwość ustawienia timera pod bind z mta (pomysł - arki)"<<std::endl;
	std::cout<<" 206_11 Dodano powiadomienia na przelewy od innych graczy"<<std::endl;
	std::cout<<" 206_10 Ping (opcja 'w') dodano możliwość sprawdzenia innego adresu"<<std::endl;
	std::cout<<" * Od teraz Logus uruchomi powiadomienie dźwiękowe tylko wtedy, kiedy wróci internet"<<std::endl;
	std::cout<<" 206_9 Zmieniono system sprawdzania połączenia wi-fi, opcja 'w' z menu"<<std::endl;

	std::cout<<"\n Wciśnij klawisz, aby kontynuować (ESC, aby pominąć INFO)"<<std::endl;
	if(getch() == 27)
	{
		cls();
		return;
	}
	cls();
	SetConsoleTextAttribute(h, 4);
	std::cout<<" MAJ"<<std::endl;

	SetConsoleTextAttribute(h, 6);
	std::cout<<" 205_11.2 Dodano prekonfigurację w przypadku braku pliku logus.ini"<<std::endl;
	std::cout<<" * Teraz nie jest potrzebne restartowanie programu w przypadku pomyłki"<<std::endl;
	std::cout<<" 205_11.1 Zmiana funkcji sprawdzającej podania napisu zamiast liczby"<<std::endl;
	std::cout<<" * Dopóki nie nastąpi połączenie z serwerem, Logus łączy się z nim co 5 sekund"<<std::endl;
	std::cout<<" 205_11 Dodano nową funkcje w LiveChat - [Enter] autoJoin"<<std::endl;
	std::cout<<" 205_10 Rozmiar Logusa jako aplikacji .exe o wiele się zmniejszył"<<std::endl;
	std::cout<<" 205_10 Poprawiono czyszczenie czatu po przeniesieniu logów"<<std::endl;
	std::cout<<" 205_91 Usunięto Logus-pre, od teraz Logus.exe na masterze jest aktualnym wydaniem Pre-Realease"<<std::endl;
	std::cout<<" 205_9 Edytowano zmianę wartości ms dynamicznym odświeżaniu"<<std::endl;
	std::cout<<" * 'set reset', 'set re'"<<std::endl;
	std::cout<<" 205_61 Dodano komendę na reset kursów i $ z poziomu konsoli mta"<<std::endl;
	std::cout<<" * Dodano dźwięki, tekst jest różny w zależności od powodu zamknięcia programu"<<std::endl;
	std::cout<<" 205_6 Zmieniono animacje wyłączenia programu"<<std::endl;
	std::cout<<" * Jeśli takich plików nie ma to Logus sam je zainicjuje (pliki log.1 log.2 itd.)"<<std::endl;
	std::cout<<" 205_6 Naprawiono problem z odczytywaniem plików log, jeśli nie zostały stworzone przez mta"<<std::endl;
	std::cout<<" * Logus wyłączy się automatycznie wraz z grą (zapisując ustawienia)"<<std::endl;
	std::cout<<" 205_6 Przypisano dodatkowe działanie komendzie 'quit' z mta"<<std::endl;
	std::cout<<" * Teraz Logus bierze pod uwagę długość nicku zmniejszając szanse na błędny komunikat"<<std::endl;
	std::cout<<" 205_6 Dodano dodatkowy warunek sprawdzający nick"<<std::endl;

	std::cout<<"\n Wciśnij klawisz, aby kontynuować (ESC, aby pominąć INFO)"<<std::endl;
	if(getch() == 27)
	{
		cls();
		return;
	}
	cls();
	SetConsoleTextAttribute(h, 4);
	std::cout<<" MARZEC"<<std::endl;

	SetConsoleTextAttribute(h, 6);
	std::cout<<" * Dodano też komendę na ustawienie ilości kursów - set c KURSY"<<std::endl;
	std::cout<<" * Wpisując w konsoli 'set m KWOTA', F4 ustawi się na podaną wartość"<<std::endl;
	std::cout<<" 203_3 Dodano nową komendę - ustawienie F4 z poziomu konsoli MTA"<<std::endl;
	std::cout<<" 203_2 Został dodany kolor żółty dla powiadomień zaczynających się od '*'"<<std::endl;
	std::cout<<" * Jak na razie zmiany zostały wprowadzone w trybie bez daty(Timestamps)"<<std::endl;
	std::cout<<" 203_1 Zmieniono kolorystykę czatu w LiveChat oddzielając wiadomość od nazwy gracza"<<std::endl;
	std::cout<<" * Plik znajduje się w folderze logs, logusInfoOutput.log"<<std::endl;
	std::cout<<" * Po wyłączeniu komunikatu dźwiękowego w opcjach linijka z logiem nie pojawi się w tym pliku"<<std::endl;
	std::cout<<" 203_1 Dodano nowy plik .log, aby mieć szybszy dostęp do logów z powiadomień(PW, TEAM, TOWAR, PRZELEWY)"<<std::endl;
	std::cout<<" 203_1 Zmieniono polecenie reconnect z 'r' na 'rr'"<<std::endl;

	std::cout<<"\n Wciśnij klawisz, aby kontynuować (ESC, aby pominąć INFO)"<<std::endl;
	if(getch() == 27)
	{
		cls();
		return;
	}
	cls(); 
	SetConsoleTextAttribute(h, 4);
	std::cout<<" ZMIANY - początek roku"<<std::endl;
	SetConsoleTextAttribute(h, 6);
	std::cout<<" 202_13 Po wciśnięciu entera wraz z uruchomieniem serwera włączy się funkcja LiveChat"<<std::endl;
	std::cout<<" * Jest to kolejna próba testów z serii 'co powoduje pomijanie zapisu niektórych kursów'"<<std::endl;
	std::cout<<" 202_13 Zmodyfikowano sprawdzanie warunków przy dostarczonym towarze"<<std::endl;
	std::cout<<" * Dodatkowo juz nie bedzie wyswietlana wyplata mniejsza niz 0"<<std::endl;
	std::cout<<" 202_13 Poprawiono blad przy wyswietlaniu wyplaty wiekszej niz $1000000 w LiveChat oraz ustawieniach"<<std::endl;
	std::cout<<" * Pozostaje powiadomienie na wejscie i wyjscie z serwera oraz na status AFK danego gracza"<<std::endl;
	std::cout<<" 201_2 Wylaczono powiadomienia na kazda wiadomosc gracza dodanego do Nicknames"<<std::endl;
	std::cout<<" Jeszcze w sierpniu zmieniono system sprawdzania nowych linii"<<std::endl;

	cls();
}
