// Copyright © 2018-2020  DarXe, Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//standard libraries
#include <iostream>
#include <conio.h>
#include <windows.h>


//header includes
#include "common.hpp"
#include "commonConfig.hpp"
#include "var.hpp"
#include "config.hpp"
#include "proc.hpp"


//forward declarations
bool liveChat();


void color(std::string value)
{
	std::string value0 = "color 0" + value;
	system(value0.c_str());
}

void serverConnect() //flc
{
#ifndef dbg
	s_temp = "start mtasa://" + serverIP;
	system(s_temp.c_str());
#endif
}

bool runLiveChat() //flc
{
	serverConnect();
	cls();
	Beep(dzwiekGlowny, 100);
	liveChat();
	if (_quit == 2)
		return 0;
	return 1;
}

bool closeLogus(std::string text)
{
	cls();
	saveConfig();
	Beep(dzwiekGlowny - 100, 250);
	std::cout << "\n"
			  << text;
	for (int i = 0; i < 4; i++)
	{
		std::cout << ".";
		if (i == 2)
		{
			Beep(dzwiekGlowny, 200);
			continue;
		}
		Sleep(400);
	}
	Beep(dzwiekGlowny + 100, 250);
	return 0;
}

void dots(short duration, short amount)
{
	for (int i = 0; i < amount; i++)
	{
		std::cout << ".";
		Sleep(duration);
	}
}

void preConfig()
{
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001); // should work on Win 7
	std::string _versionName_ = "Logus - preconfig";
	SetConsoleTitleA(_versionName_.c_str());
	SetConsoleTextAttribute(h, 10);
	std::cout << ((engLang) ? " Welcome to Logus!\n" : " Witaj w Logusiu!\n");
	std::cout << ((engLang) ? " Going to preconfiguration" : " Przechodzę do prekonfiguracji");
	dots(50, 3);
	Sleep(5000);

	/* KROKI KONFIGURACJI:
	1. Czy chcesz ustawic % wyplaty, aktualnie zarobione pieniadze i kursy?
	2. Chcesz wybrac sposob transportu i czas ladowania?
	3. Przenoszenie logów
	4. Autostart

	/* pay wage, money and course */

	if (engLang)
	{

		if (cfgSelection(1, "Do you want to set pay wage, current courses and earned money?", "Yes, I do", "Not really") == 1)
		{
			switch (cfgSelection(1, "Specify your pay wage.", "I am a trucker/fraction worker, get me out of here", "Press 2 to specify"))
			{
			case 1:
			{
				grade = 1;
				cls();
				std::cout << " _______________________Logus_pre-config_______________________\n";
				std::cout << " No worries, we set your pay wage to 100%.\n";
				std::cout << " Press any key to continue...";
				getch();
				break;
			}
			case 2:
			{
				grade = cfgInput(1, 1, "Specify your pay wage.", "Pay wage:", "Error. Specify correct pay wage:", "Min 50 max 100.", 50, 100);
				grade /= 100;

				courses = cfgInput(1, 1, "Enter courses that you have on your F4.", "Courses:", "Error. Specify correct amount of courses:", "Number cannot be negative.", 0, INT_MAX);

				money = cfgInput(1, 1, "Enter money that you have on your F4.", "Money:", "Error. Specify correct amount of money:", "Number cannot be negative.", 0, INT_MAX);
				break;
			}
			default:
				break;
			}
		}
	}
	else if (codePage852)
	{

		if (cfgSelection(1, "Czy chcesz ustawic procent wyplaty, kursy oraz pieniadze?", "Tak, chce", "Nie, nie chce") == 1)
		{
			switch (cfgSelection(1, "Podaj kursy.", "Pracuje we frakcji/jestem truckerem! Zabierz mnie stad", "Wcisnij 2 aby podac"))
			{
			case 1:
			{
				grade = 1;
				cls();
				std::cout << " _______________________Logus_pre-config_______________________\n";
				std::cout << " Chill utopia, ustawilismy procent wyplaty na 100%.\n";
				std::cout << " Wcisnij dowolny klawisz aby kontynuowac...";
				getch();
				break;
			}
			case 2:
			{
				grade = cfgInput(1, 1, "Podaj procent wyplaty.", "Procent wyplaty:", "Blad. Podaj prawidlowy procent wyplaty:", "Min 50 max 100.", 50, 100);
				grade /= 100;

				courses = cfgInput(1, 1, "Podaj kursy ktore masz pod F4.", "Kursy:", "Blad. Podaj prawidlowa ilosc kursow:", "Liczba nie moze byc ujemna.", 0, INT_MAX);

				money = cfgInput(1, 1, "Podaj zarobiona gotówkę pod F4.", "Gotowka:", "Blad. Podaj prawidlowa ilosc gotowki:", "Liczba nie moze byc ujemna.", 0, INT_MAX);
				break;
			}
			default:
				break;
			}
		}
	}
	else
	{

		if (cfgSelection(1, "Czy chcesz ustawić procent wypłaty, kursy oraz pieniędze?", "Tak, chcę", "Nie, nie chcę") == 1)
		{
			switch (cfgSelection(1, "Podaj kursy.", "Pracuję we frakcji/jestem truckerem! Zabierz mnie stąd", "Wciśnij 2 aby podać"))
			{
			case 1:
			{
				grade = 1;
				cls();
				std::cout << " _______________________Logus_pre-config_______________________\n";
				std::cout << " Chill utopia, ustawiliśmy procent wypłaty na 100%.\n";
				std::cout << " Wciśnij dowolny klawisz aby kontynuować...";
				getch();
				break;
			}
			case 2:
			{
				grade = cfgInput(1, 1, "Podaj procent wypłaty.", "Procent wypłaty:", "Błąd. Podaj prawidłowy procent wypłaty:", "Min 50 max 100.", 50, 100);
				grade /= 100;

				courses = cfgInput(1, 1, "Podaj kursy które masz pod F4.", "Kursy:", "Błąd. Podaj prawidłową ilość kursów:", "Liczba nie może być ujemna.", 0, INT_MAX);

				money = cfgInput(1, 1, "Podaj zarobioną gotówkę pod F4.", "Gotówka:", "Błąd. Podaj prawidłową ilość kursów:", "Liczba nie może być ujemna.", 0, INT_MAX);
				break;
			}
			default:
				break;
			}
		}
	}

	/* loading time and transport method */

	if (engLang)
	{

		if (cfgSelection(1, "Do you want to set loading time and transport method?", "Yes, I do", "Not really") == 1)
		{
			temp2 = cfgInput(1, 1, "Firstly we'll choose loading time.", "Enter minutes:", "Error. Enter correct number.", "It has to be a number", 0, INT_MAX);
			temp = cfgInput(1, 1, "Now enter seconds.", "Enter seconds:", "Error. Enter correct number.", "It has to be a number", 0, INT_MAX);
			czas = (temp * 60) + temp2;

			if (cfgSelection(1, "Specify loading method.", "Random", ""
																	 "I will choose"
																	 "") == 1)
				random = 1;
		}
	}
	else if (codePage852)
	{

		if (cfgSelection(1, "Chcesz wybrac sposob transportu i czas ladowania?", "Tak, chce", "Nie, nie chce") == 1)
		{
			temp2 = cfgInput(1, 1, "Na poczatek wybierzmy czas ladowania.", "Podaj minuty:", "Blad. Podaj prawidlowa liczbe.", "To musi byc liczba.", 0, INT_MAX);
			temp = cfgInput(1, 1, "Teraz podaj sekundy.", "Podaj sekundy:", "Blad. Podaj prawidlowa liczbe.", "To musi byc liczba.", 0, INT_MAX);
			czas = (temp * 60) + temp2;

			if (cfgSelection(1, "Podaj sposob ladowania.", "Losowy", "Sam wybiore") == 1)
				random = 1;
		}
	}
	else
	{

		if (cfgSelection(1, "Chcesz wybrać sposób transportu i czas ładowania?", "Tak, chcę", "Nie, nie chcę") == 1)
		{
			temp2 = cfgInput(1, 1, "Na początek wybierzmy czas ładowania.", "Podaj minuty:", "Błąd. Podaj prawidłową liczbę.", "To musi być liczba.", 0, INT_MAX);
			temp = cfgInput(1, 1, "Teraz podaj sekundy.", "Podaj sekundy:", "Błąd. Podaj prawidłową liczbę.", "To musi być liczba.", 0, INT_MAX);
			czas = (temp * 60) + temp2;

			if (cfgSelection(1, "Podaj sposób ładowania.", "Losowy", "Sam wybiorę") == 1)
				random = 1;
		}
	}

	/* auto log mover */

	if (engLang)
	{

		if (cfgSelection(1, "Do you want to enable automatic log mover?", "Yes, I do", "No, not really") == 1)
			autoMoveLogs = 1;
	}
	else if (codePage852)
	{

		if (cfgSelection(1, "Czy chcesz wlaczyc automatyczne przenoszenie logow?", "Tak, chce", "Nie, nie chce") == 1)
			autoMoveLogs = 1;
	}
	else
	{

		if (cfgSelection(1, "Czy chcesz wlączyć automatyczne przenoszenie logów?", "Tak, chcę", "Nie, nie chcę") == 1)
			autoMoveLogs = 1;
	}

	/* fast start */

	if (engLang)
	{

		switch (cfgSelection(1, "Select Logus' autostart option", "No LiveChat + PTS autostart, but show version info", "LiveChat + PTS autostart, but don't show version info", "No LiveChat + PTS autostart and no version info"))
		{
		case 1:
		{
			fastStart = 0;
			break;
		}
		case 2:
		{
			fastStart = 1;
			break;
		}
		case 3:
		{
			fastStart = 2;
			break;
		}
		default:
			break;
		}
	}
	else if (codePage852)
	{

		switch (cfgSelection(1, "Wybierz autostart Logusa", "Brak szybkiego startu LiveChat + PTS, ale pokaz info o wersji", "Szybki start LiveChat + PTS, nie pokazuj info o wersji", "Brak szybkiego startu LiveChat + PTS i nie pokazuj info o wersji"))
		{
		case 1:
		{
			fastStart = 0;
			break;
		}
		case 2:
		{
			fastStart = 1;
			break;
		}
		case 3:
		{
			fastStart = 2;
			break;
		}
		default:
			break;
		}
	}
	else
	{

		switch (cfgSelection(1, "Wybierz autostart Logusa", "Brak szybkiego startu LiveChat + PTS, ale pokaż info o wersji", "Szybki start LiveChat + PTS, nie pokazuj info o wersji", "Brak szybkiego startu LiveChat + PTS i nie pokazuj info o wersji"))
		{
		case 1:
		{
			fastStart = 0;
			break;
		}
		case 2:
		{
			fastStart = 1;
			break;
		}
		case 3:
		{
			fastStart = 2;
			break;
		}
		default:
			break;
		}
	}

	/* end of preconfig */

	if (engLang)
	{
		cls();
		std::cout << " Preconfiguration ended succesfully.";
		dots(100, 3);
		std::cout << "\n You can always change settings in main menu! \n";
		std::cout << " Press any key to continue.\n";
		getch();
	}
	else if (codePage852)
	{

		cls();
		std::cout << " Prekonfiguracja ukonczona pomyslnie.";
		dots(100, 3);
		std::cout << "\n Ustawienia mozesz w kazdej chwili zmienic w menu glownym!\n";
		std::cout << " Wcisnij dowolny klawisz aby kontynuowac.\n";
		getch();
	}
	else
	{

		cls();
		std::cout << " Prekonfiguracja ukończona pomyślnie.";
		dots(100, 3);
		std::cout << "\n Ustawienia możesz w każdej chwili zmienić w menu glównym!\n";
		std::cout << " Wciśnij dowolny klawisz aby kontynuować.\n";
		getch();
	}
}