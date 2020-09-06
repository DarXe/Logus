// Copyright © 2018-2020  DarXe, Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

#include "livechat.hpp"
#include "../addons/loglookup.hpp"
#include "../addons/dealer.hpp"
#include "../addons/randomLogus.hpp"
#include "settings.hpp"
#include "../config.hpp"
#include "../common.hpp"
#include "../proc.hpp"
#include "../var.hpp"
#include "menu.hpp"

int menu() //con
{
	while(true)
	{
		if(isTimer) delay2 = clock();
		color(kolorGlowny);
		if(engLang) {
			SetConsoleTextAttribute(h, 10);
			std::cout<<" _______________________________________MENU_______________________________________\n";
			SetConsoleTextAttribute(h, 11);
			std::cout<<" [Enter] Run MTA:SA and connect to PTS / reconnect\n";
			std::cout<<" [L] PTS TOTOLOTEK - Lotto Logus\n";
			SetConsoleTextAttribute(h, 12);
			std::cout<<" [s] Faststart PTS + MTA:SA: ";
			switch (fastStart) {
			case 0: std::cout<<"No LiveChat + PTS autostart, but show version info"; break;
			case 1: std::cout<<"LiveChat + PTS autostart, but don't show version info"; break;
			default: std::cout<<"No LiveChat + PTS autostart and no version info"; break;
			}
			std::cout<<"\n";
			std::cout<<" [t] LiveChat - ingame chat with notifications\n";
			std::cout<<" [5] Logus's settings\n";
			SetConsoleTextAttribute(h, 11);
			std::cout<<" [1] Search for team messages in .log files\n";
			std::cout<<" [2] Search for private messages in .log files\n";
			std::cout<<" [3] Search for team messages in all .log files\n";
			std::cout<<" [4] Search for private messages and answers in all .log files\n";
			SetConsoleTextAttribute(h, 12);
			std::cout<<" [p] Search for payments in .log files\n";
			std::cout<<" [o] Search in .log file with date from-to\n";
			SetConsoleTextAttribute(h, 11);
			std::cout<<" [w] Pingtest - check connection to the internet\n";
			std::cout<<" [k] Car Dealer - purchase and selling prices\n";
			std::cout<<" [j] Language - change to Polski\n";
			std::cout<<" [9] Change sound (beep) to random\n";
			std::cout<<" [0] Codepage (legacy): "<<((codePage852)?"852\n":"UTF-8\n");
			std::cout<<" [u] TEST UTF8 - EMOJI\n";
			std::cout<<" [i] INFO\n";
			SetConsoleTextAttribute(h, 10);
			std::cout<<" __________________________________________________________________________________\n";
			std::cout<<"                                [ESC] Quit & save                             \n";
		} else {
			SetConsoleTextAttribute(h, 10);
			std::cout<<" _______________________________________MENU_______________________________________\n";
			SetConsoleTextAttribute(h, 11);
			std::cout<<" [Enter] Uruchom MTA i połącz z PTS / Połącz ponownie\n";
			std::cout<<" [L] PTS TOTOLOTEK - Lotto Logus\n";
			SetConsoleTextAttribute(h, 12);
			std::cout<<" [s] Szybki start LiveChat + PTS: ";
			switch (fastStart) {
			case 0: std::cout<<"Nie, ale wyświetl info o wersji"; break;
			case 1: std::cout<<"Tak, uruchom MTA:PTS przy starcie Logusa"; break;
			default: std::cout<<"Nie uruchamiaj, ani nie wyświetlaj info o wersji"; break;
			}
			std::cout<<std::endl;
			std::cout<<" [t] LiveChat - czat z gry w konsoli z komunikatami dźwiękowymi\n";
			std::cout<<" [5] Ustawienia Logusa\n";
			SetConsoleTextAttribute(h, 11);
			std::cout<<" [1] Szukaj wiadomości teamowych w plikach .log\n";
			std::cout<<" [2] Szukaj PW oraz odpowiedzi w plikach .log\n";
			std::cout<<" [3] Szukaj wiadomości teamowych we wszystkich plikach .log\n";
			std::cout<<" [4] Szukaj PW oraz odpowiedzi we wszystkich plikach .log\n";
			SetConsoleTextAttribute(h, 12);
			std::cout<<" [p] Szukaj przelewów od i do graczy w plikach .log\n";
			std::cout<<" [o] Szukaj w plikach .log po dacie od-do\n";
			SetConsoleTextAttribute(h, 11);
			std::cout<<" [w] Test ping - szybkie sprawdzenie, czy jest internet\n";
			std::cout<<" [k] Komis - ceny skupu i sprzedaży\n";
			std::cout<<" [j] Język - zmień na English\n";
			std::cout<<" [9] Zmiana dźwięku na losowy\n";
			std::cout<<" [0] Kodowanie (legacy): "<<((codePage852)?"852\n":"UTF-8\n");
			std::cout<<" [u] TEST UTF8 - EMOJI\n";
			std::cout<<" [i] INFO\n";
			SetConsoleTextAttribute(h, 10);
			std::cout<<" __________________________________________________________________________________\n";
			std::cout<<"                                [ESC] Wyjście i zapis                              \n";
		}
		Beep(dzwiekGlowny,100);

		switch(wybor()) //set0 MENU
		{
		case 27:
		{
			if(engLang)
			return closeLogus("Closing the program");
			else
			return closeLogus("Zamykanie programu");
		}
		case '1':
		{
			std::string filen = ((engLang)?cfgSelectionStr("Choose file to lookup.", consoleLogPath, consoleLog1Path, consoleLog2Path, consoleLog3Path, consoleLog4Path, consoleLog5Path, "logus.log"):
										cfgSelectionStr("Wybierz nazwę pliku do przeszukania.", consoleLogPath, consoleLog1Path, consoleLog2Path, consoleLog3Path, consoleLog4Path, consoleLog5Path, "logus.log"));
			cls();
			if (filen == "WYJŚCIE")
			{
				cls();
				break;
			}
			checkFileTeam(filen);
			break;
		}
		case '2':
		{
			std::string filen = ((engLang)?cfgSelectionStr("Choose file to lookup.", consoleLogPath, consoleLog1Path, consoleLog2Path, consoleLog3Path, consoleLog4Path, consoleLog5Path, "logus.log"):
										cfgSelectionStr("Wybierz nazwę pliku do przeszukania.", consoleLogPath, consoleLog1Path, consoleLog2Path, consoleLog3Path, consoleLog4Path, consoleLog5Path, "logus.log"));
			cls();
			if (filen == "WYJŚCIE")
			{
				cls();
				break;
			}
			checkFilePM(filen);
			break;
		}
		case '3':
		{
			if (!checkFileTeam(consoleLogPath))
				break;
			if (!checkFileTeam(consoleLog1Path))
				break;
			if (!checkFileTeam(consoleLog2Path))
				break;
			if (!checkFileTeam(consoleLog3Path))
				break;
			if (!checkFileTeam(consoleLog4Path))
				break;
			if (!checkFileTeam(consoleLog5Path))
				break;
			if (!checkFileTeam("logus.log"))
				break;
			break;
		}

		case '4':
		{
			if (!checkFilePM(consoleLogPath))
				break;
			if (!checkFilePM(consoleLog1Path))
				break;
			if (!checkFilePM(consoleLog2Path))
				break;
			if (!checkFilePM(consoleLog3Path))
				break;
			if (!checkFilePM(consoleLog4Path))
				break;
			if (!checkFilePM(consoleLog5Path))
				break;
			if (!checkFilePM("logus.log"))
				break;
			break;
		}
		case 'p':
		{
			std::string filen = ((engLang)?cfgSelectionStr("Choose file to lookup.", consoleLogPath, consoleLog1Path, consoleLog2Path, consoleLog3Path, consoleLog4Path, consoleLog5Path, "logus.log"):
										cfgSelectionStr("Wybierz nazwę pliku do przeszukania.", consoleLogPath, consoleLog1Path, consoleLog2Path, consoleLog3Path, consoleLog4Path, consoleLog5Path, "logus.log"));
			cls();
			if (filen == "WYJŚCIE")
			{
				cls();
				break;
			}
			checkFileTransfers(filen);
			break;
		}
		case 'o':
		{
			dateSelectionMenu();
			break;
		}
		case 't':
		{
			cls();
			if(isTimer) timer -= (clock()-delay2);
			liveChat(); //run LiveChat
			mess = engLang? "Closing MTA and Logus": "Zamykanie MTA i programu";
			if(_quit == 2) return closeLogus(mess); //close Logus
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
			settings();
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
				engLang?std::cout<<"Codepage UTF-8\n":
				std::cout<<"Kodowanie UTF-8\n";
			}
			else
			{
				codePage852 = 1;
				SetConsoleOutputCP(852);
				SetConsoleCP(852); 
				engLang?std::cout<<"Codepage 852\n":
				std::cout<<"Kodowanie 852\n";
			}
			break;
		}
		case 'u':
		{
			cls();
			std::cout << "👌 🤞 🧠 🦷 🦴 ∅ ∈ ∉ ⊂ ⊃ ⊆ ⊇ ⊄ ⋂ ⋃ ≠ ☮😎  𝓌𝐞𝕣ｓנＯη 𝐆έ𝓙  ☞⛵ ≤ ≥ ≈ ≡ ⌈ ⌉ ⌊ ⌋ ∑ ∫ × ⊗ ⊕ ⊙ × ∂ √ ≔ ± ² ℵ ∞ ∎ ′ ° ℓ ∡ ∀ ¬ ∧ ∨ ∃ ∵ ∴  ↖ ↗ ↘ ↙ ☮😎  𝓌𝐞𝕣ｓנＯη 𝐆έ𝓙  ☞⛵  🚃 🚇 🚈 🚊 🚋 🚞 🛤 \n";
			std::cout << ((engLang)? "END. PRESS ESC TO RETURN TO THE MENU\n" : "KONIEC. WCIŚNIJ ESC ABY WRÓCIĆ DO MENU\n"); getch();
			break;
		}
		case 'j':
		{
			cls();
			if(engLang)
			{
				engLang = 0;
				std::cout<<"Menu po polsku\n";
			}
			else
			{
				engLang = 1;
				std::cout<<"Menu in English\n";
			}
			saveConfig(0);
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
			clock_t p = 0;
			std::string host = "";
			std::cout<<"Choose host: \n";
			std::cout<<"1. localhost\n";
			std::cout<<"2. google.pl\n";
			std::cout<<"3. facebook.com\n";
			std::cout<<"4. other\n";
			switch(getch())
			{
				case '1': host = "ping localhost"; break;
				case '2': host = "ping google.pl"; break;
				case '3': host = "ping facebook.com"; break;
				case '4': {
						std::cout<<"Enter host: ";
						std::cin>>host;
						host = "ping "+host; break;
					}
				default: host = "ping google.pl"; break;
			}
			cls();
			while(true)
			{
				if(host == "") break;
				p = clock();
				std::cout<<"Any key - exit. ";
				Sleep(1000);
				system(host.c_str());
				std::cout<<"Delay: "<<clock()-p<<"ms\n";
				if(clock()-p > 4000 && clock()-p < 5000)
					Beep(dzwiekGlowny,333);
				if(kbhit()) {getch(); break;}
			}
			cls();
			break;
		}
		case 'k':
		{
			cls();
			dealer();
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
			runLiveChat();
			mess = engLang? "Closing MTA and Logus": "Zamykanie MTA i programu";
			if(_quit == 2) return closeLogus(mess); //close Logus
			break;
		}
		default:
			def();
		}//switch
	}
	return 0;
}