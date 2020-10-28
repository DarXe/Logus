// Copyright © 2018-2020  DarXe, Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

//standard libraries
#include <iostream>
#include <conio.h>


//header includes
#include <var.hpp>
#include <common.hpp>
#include <proc.hpp>
#include <config.hpp>
#include <commonConfig.hpp>
#include "livechat/livechat_events.hpp"
#include "settings.hpp"

void settings()
{
	while (true)
	{
		if (engLang)
		{
			SetConsoleTextAttribute(h, 10);
			std::cout << " __________________________Settings - Logus___________________________\n";
			SetConsoleTextAttribute(h, 7);
			std::cout << " [r] Reset settings to default\n";
			SetConsoleTextAttribute(h, 14);
			std::cout << " [p] Notify on private message: " << ((!fLockPW) ? "YES" : "NO") << "\n";
			std::cout << " [t] Notify on team message: " << ((!fLockTeam) ? "YES" : "NO") << "\n";
			std::cout << " [s] Notify on report or transport message: " << ((!fLockReport) ? "YES" : "NO") << "\n";
			std::cout << " [k] Chat notifications - choosen nicknames: " << ((!fLockNick) ? "YES" : "NO") << "\n";
			std::cout << " [c] Notify on any message: " << ((chatSound) ? "YES" : "NO") << "\n";
			std::cout << " [a] Update channel: " << updateChannel << "\n";
			SetConsoleTextAttribute(h, 7);
			std::cout << " [1] Amount of lines displayed: " << wyswietlaneWiersze << "\n";
			std::cout << " [2] Refresh rate (100-5000): " << refresh << "\n";
			std::cout << " [3] Dynamic refresh: " << ((dynamicRefresh) ? "YES" : "NO") << "\n";
			std::cout << " [4] Notify' beep length(50-10000): " << dzwiekGlowny << "\n";
			std::cout << " [5] Notify' beep delay(50-1000): " << interval << "\n";
			std::cout << " [u] Min dynamic refresh in LiveChat: " << minRefresh << "\n";
			std::cout << " [o] Max dynamic refresh in LiveChat: " << maxRefresh << "\n";
			std::cout << " [m] Automatic log mover: ";
			if (autoMoveLogs)
				std::cout << "YES, at " << autoMoveLogs << " lines";
			else
				std::cout << "NO";
			std::cout << "\n";
			std::cout << " [d] Auto gate open (open at the end of PM): " << autoOpenGate << "\n";
			SetConsoleTextAttribute(h, 14);
			std::cout << " [6] Cargo unload time - " << czas / 60 << ((czas % 60 < 10) ? ":0" : ":") << czas % 60 << "\n";
			std::cout << " [7] I will choose / Random: " << ((random) ? "5min - Random" : "6min - I will choose") << "\n";
			SetConsoleTextAttribute(h, 7);
			std::cout << " [8] F4 / earned money from last reset: $" << money << "\n";
			std::cout << " [9] Amount of delivered courses: " << courses << "\n";
			std::cout << " [0] Pay wage: " << grade * 100 << "%\n";
			int payment(0);
			payment = ((money * 0.87) - 3500) * grade;
			std::cout << " # # Payment is "
					  << "$" << payment << "\n";
			std::cout << " [x] Reset money and courses state\n";
			SetConsoleTextAttribute(h, 14);
			std::cout << " [b] Players - database of chosen players\n";
			std::cout << " [v] Phrase database - database of phrases to look for in messages\n";
			std::cout << " [n] Nickname: " << nick << "\n";
			SetConsoleTextAttribute(h, 10);
			std::cout << " _____________________________________________________________________\n";
			std::cout << "                         [ESC] Return & Save                          \n";
		}
		else
		{
			SetConsoleTextAttribute(h, 10);
			std::cout << " _________________________Ustawienia - Logus__________________________\n";
			SetConsoleTextAttribute(h, 7);
			std::cout << " [r] Przywróć ustawienia domyślne\n";
			SetConsoleTextAttribute(h, 14);
			std::cout << " [p] Dźwięk wiadomości PW: " << ((!fLockPW) ? "TAK" : "NIE") << "\n";
			std::cout << " [t] Dźwięk wiadomości teamowych: " << ((!fLockTeam) ? "TAK" : "NIE") << "\n";
			std::cout << " [s] Dźwięk komunikatów(raport, transport): " << ((!fLockReport) ? "TAK" : "NIE") << "\n";
			std::cout << " [k] Powiadomienia na czacie - wybrane nicki: " << ((!fLockNick) ? "TAK" : "NIE") << "\n";
			std::cout << " [c] Dźwięk każdej wiadomości na czacie: " << ((chatSound) ? "TAK" : "NIE") << "\n";
			std::cout << " [a] Kanał aktualizacji: " << updateChannel << "\n";
			SetConsoleTextAttribute(h, 7);
			std::cout << " [1] Liczba wyświetlanych wierszy: " << wyswietlaneWiersze << "\n";
			std::cout << " [2] Częstotliwość odświeżania(100-5000): " << refresh << "\n";
			std::cout << " [3] Dynamiczne odświeżanie: " << ((dynamicRefresh) ? "TAK" : "NIE") << "\n";
			std::cout << " [4] Częstotliwość dźwięku(50-10000): " << dzwiekGlowny << "\n";
			std::cout << " [5] Przerwa między dźwiękami(50-1000): " << interval << "\n";
			std::cout << " [u] Minimalny dynamiczny refresh w LiveChat: " << minRefresh << "\n";
			std::cout << " [o] Maksymalny dynamiczny refresh w LiveChat: " << maxRefresh << "\n";
			std::cout << " [m] Automatyczne przenoszenie logów: ";
			if (autoMoveLogs)
				std::cout << "TAK";
			else
				std::cout << "NIE";
			std::cout << "\n";
			std::cout << " [d] Automatyczne otwieranie bramy (open na końcu PW): " << autoOpenGate << "\n";
			SetConsoleTextAttribute(h, 14);
			std::cout << " [6] Czas rozładowywania towaru - " << czas / 60 << ((czas % 60 < 10) ? ":0" : ":") << czas % 60 << "\n";
			std::cout << " [7] Sam wybiorę / Losowy: " << ((random) ? "5min - Losowy" : "6min - Sam wybiorę") << "\n";
			SetConsoleTextAttribute(h, 7);
			std::cout << " [8] F4 / zarobione pieniądze od ostatniego wyzerowania: $" << money << "\n";
			std::cout << " [9] Liczba dostarczonych kursów: " << courses << "\n";
			std::cout << " [0] Ranga w firmie: " << grade * 100 << "%\n";
			int payment(0);
			payment = ((money * 0.87) - 3500) * grade;
			std::cout << " # # Wyplata wynosi "
					  << "$" << payment << "\n";
			std::cout << " [x] Wyzeruj stan F4 i kursów\n";
			SetConsoleTextAttribute(h, 14);
			std::cout << " [b] Gracze - baza danych wybranych graczy\n";
			std::cout << " [v] Baza fraz do szukania w wiadomości\n";
			std::cout << " [n] Nickname: " << nick << "\n";
			SetConsoleTextAttribute(h, 10);
			std::cout << " _____________________________________________________________________\n";
			std::cout << "                         [ESC] Powrót i zapis                         \n";
		}
		Beep(dzwiekGlowny, 100);

		switch (wybor())
		{
		case 27:
		{
			cls();
			saveConfig();
			return;
		}
		case 'r':
		{
			cls();
			engLang ? std::cout << "ARE YOU SURE? Enter - Accept | Any other key - Cancel\n" : std::cout << "CZY NA PEWNO CHCESZ TO ZROBIĆ? Enter - Akceptuj | Inny klawisz - Anuluj\n";
			if (getch() != 13)
				break;
			readDefault();
			engLang ? std::cout << "Settings has been succesfully reset to default!\n" : std::cout << "Ustawienia domyślne programu zostały przywrócone!\n";
		}
		break;
		case 'p':
		{
			cls();
			fLockPW = (fLockPW) ? 0 : 1;
			break;
		}
		case 't':
		{
			cls();
			fLockTeam = (fLockTeam) ? 0 : 1;
			break;
		}
		case 's':
		{
			cls();
			fLockReport = (fLockReport) ? 0 : 1;
			break;
		}
		case 'k':
		{
			cls();
			fLockNick = (fLockNick) ? 0 : 1;
			break;
		}
		case 'c':
		{
			cls();
			chatSound = (chatSound) ? 0 : 1;
			break;
		}
		case 'a':
		{
			cls();
			if (updateChannel == "release")
				updateChannel = "nightly";
			else if (updateChannel == "nightly")
				updateChannel = "disable";
			else if (updateChannel == "disable")
				updateChannel = "release";
			break;
		}
		case '1':
		{
			wyswietlaneWiersze = (engLang ? cfgInput(0, 1, "Enter amount of displayed lines", "Enter amount:", "Error. Entered wrong value", "Min 0, Max 100", 0, 100) :
			cfgInput(0, 1, "Podaj ilość wyświetlanych wierszy", "Podaj liczbę:", "Błąd. Podano błędną wartość", "Min 0, Max 100", 0, 100));
			cls();
			break;
		}
		case '2':
		{
			refresh = (engLang ? cfgInput(0, 1, "Enter new refresh rate", "Enter amount:", "Error. Entered wrong value", "Min 0, Max 1000", 0, 1000) :
			cfgInput(0, 1, "Podaj nową częstotliwość odświeżania", "Podaj liczbę:", "Błąd. Podano błędną wartość", "Min 0, Max 1000", 0, 1000));
			cls();
			break;
		}
		case '3':
		{
			cls();
			dynamicRefresh = (dynamicRefresh) ? 0 : 1;
			break;
		}
		case '4':
		{
			dzwiekGlowny = (engLang ? cfgInput(0, 1, "Enter new sound frequency", "Enter amount:", "Error. Entered wrong value", "Min 0, Max 10000", 0, 10000) :
			cfgInput(0, 1, "Podaj nową częstotliwość dźwięku", "Podaj liczbę:", "Błąd. Podano błędną wartość", "Min 0, Max 10000", 0, 10000));
			cls();
			break;
		}
		case '5':
		{
			interval = (engLang ? cfgInput(0, 1, "Enter new delay between sounds", "Enter amount:", "Error. Entered wrong value", "Min 0, Max 1000", 0, 1000) :
			cfgInput(0, 1, "Podaj nowy odstęp między dźwiękami", "Podaj liczbę:", "Błąd. Podano błędną wartość", "Min 0, Max 1000", 0, 1000));
			cls();
			break;
		}
		case 'u':
		{
			minRefresh = (engLang ? cfgInput(0, 1, "Enter new refresh rate", "Enter amount:", "Error. Entered wrong value", "Min 1, Max 2000", 1, 2000) :
			cfgInput(0, 1, "Podaj nową częstotliwość odświeżania", "Podaj liczbę:", "Błąd. Podano błędną wartość", "Min 1, Max 2000", 1, 2000));
			cls();
			break;
		}
		case 'o':
		{
			maxRefresh = (engLang ? cfgInput(0, 1, "Enter new refresh rate", "Enter amount:", "Error. Entered wrong value", "Min 1, Max 2000", 1, 2000) :
			cfgInput(0, 1, "Podaj nową częstotliwość odświeżania", "Podaj liczbę:", "Błąd. Podano błędną wartość", "Min 1, Max 2000", 1, 2000));
			cls();
			break;
		}
		case 'm':
		{
			cls();
			autoMoveLogs = autoMoveLogs ? 0 : 1;
			break;
		}
		case 'd':
		{
			cls();
			autoOpenGate = autoOpenGate ? 0 : 1;
			break;
		}
		case '6':
		{
			int temp2 = (engLang ? cfgInput(0, 1, "", "Enter minutes:", "Error. Entered wrong value", "Min 0, Max 10", 0, 10) :
			cfgInput(0, 1, "", "Podaj minuty:", "Błąd. Podano błędną wartość", "Min 0, Max 10", 0, 10));
			int temp = (engLang ? cfgInput(0, 1, "", "Enter seconds:", "Error. Entered wrong value", "Min 0, Max 59", 0, 59) :
			cfgInput(0, 1, "", "Podaj sekundy:", "Błąd. Podano błędną wartość", "Min 0, Max 59", 0, 59));
			czas = (temp2 * 60) + temp;
			cls();
			break;
		}
		case '7':
		{
			cls();
			random = (random) ? 0 : 1;
			break;
		}
		case '8':
		{
			money = (engLang ? cfgInput(0, 1, "Enter new amount of money (without $ etc)", "Enter a number:", "Error. Entered wrong value", "It has to be a number", 0, INT_MAX) :
			cfgInput(0, 1, "Podaj nową ilość $ (sama liczba)", "Podaj liczbę:", "Błąd. Podano błędną wartość", "To musi być liczba", 0, INT_MAX));
			cls();
			break;
		}
		case '9':
		{
			courses = (engLang ? cfgInput(0, 1, "Enter new amount of courses", "Enter amount:", "Error. Entered wrong value", "It has to be a number", 0, INT_MAX) :
			cfgInput(0, 1, "Podaj nową ilość kursów", "Podaj ilość:", "Błąd. Podano błędną wartość", "To musi być liczba", 0, INT_MAX));
			cls();
			break;
		}
		case '0':
		{
			grade = (engLang ? cfgInput(0, 1, "Enter new pay wage", "Enter amount:", "Error. Entered wrong value", "Min 50, Max 100", 50, 100) :
			cfgInput(0, 1, "Podaj nowy procent wypłaty", "Podaj ilość:", "Błąd. Podano błędną wartość", "Min 50, Max 100", 50, 100));
			grade /= 100;
			cls();
			break;
		}
		case 'x':
		{
			cls();
			engLang ? std::cout << "ARE YOU SURE? Enter - Accept | Any other key - Cancel\n" : std::cout << "CZY NA PEWNO CHCESZ TO ZROBIĆ? Enter - Akceptuj | Inny klawisz - Anuluj\n";
			if (getch() != 13)
				break;
			money = 0;
			courses = 0;
			minsalary = 0;
			maxsalary = 0;
			cls();
			engLang ? std::cout << "(INFO) Money and courses has been cleared.\n" : std::cout << "(INFO) Wyzerowano.\n";
			break;
		}
		case 'v':
		{
			cls();
			while (true)
			{
				SetConsoleTextAttribute(h, 10);
				Beep(dzwiekGlowny, 100);
				if (engLang)
				{
					std::cout << " ____________________Settings - Phrase database__________________\n";
					std::cout << " (INFO) You can also enter phrases manually in logus.ini\n";
					SetConsoleTextAttribute(h, 14);
					std::cout << " [1] Add new phrase\n";
					std::cout << " [2] Remove last phrase\n";
					std::cout << " [3] Show list of added phrases\n";
					std::cout << " [4] Delete phrase by ID\n";
					SetConsoleTextAttribute(h, 7);
					std::cout << " [r] Read from file\n";
					std::cout << " [x] Remove all phrases\n";
					SetConsoleTextAttribute(h, 10);
					std::cout << " ________________________________________________________________\n";
					std::cout << "                        [ESC] Return & Save                      \n";
				}
				else
				{
					std::cout << " _____________________Ustawienia - Baza fraz_____________________\n";
					std::cout << " (INFO) Możesz też wpisywać frazy ręcznie w pliku logus.ini\n";
					SetConsoleTextAttribute(h, 14);
					std::cout << " [1] Dodaj nową frazę\n";
					std::cout << " [2] Usuń ostatnio dodaną frazę\n";
					std::cout << " [3] Wyświetl listę dodanych fraz\n";
					std::cout << " [4] Usuń frazę o danym id z listy\n";
					SetConsoleTextAttribute(h, 7);
					std::cout << " [r] Wykonaj odczyt z pliku, jeśli fraza został dodany w logus.ini\n";
					std::cout << " [x] Usuń wszystkie frazy\n";
					SetConsoleTextAttribute(h, 10);
					std::cout << " ________________________________________________________________\n";
					std::cout << "                       [ESC] Powrót i zapis                      \n";
				}
				char wyb = wybor();
				switch (wyb)
				{
				case 27:
				{
					cls();
					saveConfig();
					break;
				}
				case '1': //set2 SETTINGS two
				{
					cls();
					while (true)
					{
						engLang ? std::cout << " Enter exact phrase: " : std::cout << " Podaj dokładną frazę: ";
						std::string s_temp;
						std::cin >> s_temp;
						if (s_temp.length() < 2)
							engLang ? std::cout << " Phrase has to be at least 2 characters long!\n" : std::cout << " Minimum 2 znaki!\n";
						else
						{
							cls();
							phrases.push_back(s_temp);
							engLang ? std::cout << " Added phrase " << s_temp << "\n" : std::cout << " Dodano frazę " << s_temp << "\n";
							break;
						}
					}
					break;
				}
				case '2':
				{
					cls();
					if (phrases.empty())
						engLang ? std::cout << " (INFO) Phrase list is empty\n" : std::cout << " (INFO) Lista fraz jest pusta\n";
					else
					{
						engLang? std::cout << " Removed phrase " << phrases.back() << "\n" : std::cout << " Usunięto frazę " << phrases.back() << "\n";
						phrases.pop_back();
					}
					break;
				}
				case '3':
				{
					cls();
					if (phrases.empty())
						engLang ? std::cout << " (INFO) Phrase list is empty\n" : std::cout << " (INFO) Lista fraz jest pusta\n";
					else
					{
						for (int i = 0; i < phrases.size(); i++)
						{
							std::cout << " " << i + 1 << ". " << phrases.at(i) << "\n";
						}
					}
					break;
				}
				case '4':
				{
					cls();
					if (phrases.empty())
						engLang ? std::cout << " (INFO) Phrase list is empty\n" : std::cout << " (INFO) Lista fraz jest pusta\n";
					else
					{
						cls();
						for (int i = 0; i < phrases.size(); i++)
						{
							std::cout << " " << i + 1 << ". " << phrases.at(i) << "\n";
						}
						int result;
						engLang ? result = cfgInput(0, 0, "Enter phrase's ID that you want to remove", "Enter ID:", "Error. Entered wrong value", "It has to be a number", 0, phrases.size()) :
						result = cfgInput(0, 0, "Podaj ID frazy którą chcesz usunąć", "Podaj ID:", "Błąd. Podaną błędną wartość", "To musi być liczba", 0, phrases.size());
						cls();
						engLang ? std::cout << " Removed phrase " << phrases.at(result - 1) << "\n" : std::cout << " Usunieto frazę " << phrases.at(result - 1) << "\n";
						phrases.erase(phrases.begin() + result - 1);
					}
					break;
				}
				case 'r':
				{
					cls();
					readDefault();
					saveConfig();
					break;
				}
				case 'x':
				{
					cls();
					engLang ? std::cout << "ARE YOU SURE? Enter - Accept | Any other key - Cancel\n" : std::cout << "CZY NA PEWNO CHCESZ TO ZROBIĆ? Enter - Akceptuj | Inny klawisz - Anuluj\n";
					if (getch() != 13)
						break;
					nicknames.clear();
					engLang ? std::cout << " Removed all phrases\n" : std::cout << " Usunięto wszystkie frazy\n";
					break;
				}
				default:
					def();
				}
				if (wyb == 27)
					break;
			}
			break;
		}
		case 'b':
		{
			cls();
			while (true)
			{
				SetConsoleTextAttribute(h, 10);
				Beep(dzwiekGlowny, 100);
				if (engLang)
				{
					std::cout << " ______________________Settings - Nicknames______________________\n";
					std::cout << " (INFO) You can also enter nicknames manually in logus.ini\n";
					SetConsoleTextAttribute(h, 14);
					std::cout << " [1] Add new player\n";
					std::cout << " [2] Remove last player\n";
					std::cout << " [3] Show list of added players\n";
					std::cout << " [4] Delete player by ID\n";
					SetConsoleTextAttribute(h, 7);
					std::cout << " [r] Read from file\n";
					std::cout << " [x] Remove all players\n";
					SetConsoleTextAttribute(h, 10);
					std::cout << " ________________________________________________________________\n";
					std::cout << "                        [ESC] Return & Save                      \n";
				}
				else
				{
					std::cout << " _____________________Ustawienia - Nicknames_____________________\n";
					std::cout << " (INFO) Możesz też wpisywać nazwy ręcznie w pliku logus.ini\n";
					SetConsoleTextAttribute(h, 14);
					std::cout << " [1] Dodaj nowego gracza\n";
					std::cout << " [2] Usuń ostatnio dodanego gracza\n";
					std::cout << " [3] Wyświetl listę dodanych graczy\n";
					std::cout << " [4] Usuń gracza o danym id z listy\n";
					SetConsoleTextAttribute(h, 7);
					std::cout << " [r] Wykonaj odczyt z pliku, jeśli gracz został dodany w logus.ini\n";
					std::cout << " [x] Usuń wszystkich graczy\n";
					SetConsoleTextAttribute(h, 10);
					std::cout << " ________________________________________________________________\n";
					std::cout << "                       [ESC] Powrót i zapis                      \n";
				}
				char wyb = wybor();
				switch (wyb)
				{
				case 27:
				{
					cls();
					saveConfig();
					break;
				}
				case '1': //set2 SETTINGS two
				{
					cls();
					while (true)
					{
						engLang ? std::cout << " Enter exact player name: " : std::cout << " Podaj dokładną nazwę gracza: ";
						std::string s_temp;
						std::cin >> s_temp;
						if (s_temp.length() < 3)
							engLang ? std::cout << " Nickname has to be at least 3 characters long!\n" : std::cout << " Minimum 3 znaki!\n";
						else
						{
							cls();
							nicknames.push_back(s_temp);
							engLang ? std::cout << " Added player " << s_temp << "\n" : std::cout << " Dodano gracza " << s_temp << "\n";
							break;
						}
					}
					break;
				}
				case '2':
				{
					cls();
					if (nicknames.empty())
						engLang ? std::cout << " (INFO) Player list is empty\n" : std::cout << " (INFO) Lista graczy jest pusta\n";
					else
					{
						engLang ? std::cout << " Removed player " << nicknames.back() << '\n' : std::cout << " Usunięto gracza " << nicknames.back() << "\n";
						nicknames.pop_back();
					}
					break;
				}
				case '3':
				{
					cls();
					if (nicknames.empty())
						engLang ? std::cout << " (INFO) Player list is empty\n" : std::cout << " (INFO) Lista graczy jest pusta\n";
					else
					{
						for (int i = 0; i < nicknames.size(); i++)
						{
							std::cout << " " << i + 1 << ". " << nicknames.at(i) << "\n";
						}
					}
					break;
				}
				case '4':
				{
					cls();
					if (nicknames.empty())
						engLang ? std::cout << " (INFO) Player list is empty\n" : std::cout << " (INFO) Lista graczy jest pusta\n";
					else
					{
						cls();
						for (int i = 0; i < nicknames.size(); i++)
						{
							std::cout << " " << i + 1 << ". " << nicknames.at(i) << "\n";
						}
						int result;
						engLang ? result = cfgInput(0, 0, "Enter player's ID that you want to remove", "Enter ID:", "Error. Entered wrong value", "It has to be a number", 0, nicknames.size()) :
						result = cfgInput(0, 0, "Podaj ID gracza którego chcesz usunąć", "Podaj ID:", "Błąd. Podaną błędną wartość", "To musi być liczba", 0, nicknames.size());
						cls();
						engLang ? std::cout << " Removed player " << nicknames.at(result - 1) << "\n" : std::cout << " Usunieto gracza " << nicknames.at(result - 1) << "\n";
						nicknames.erase(nicknames.begin() + result - 1);
					}
					break;
				}
				case 'r':
				{
					cls();
					readDefault();
					saveConfig();
					break;
				}
				case 'x':
				{
					cls();
					engLang ? std::cout << "ARE YOU SURE? Enter - Accept | Any other key - Cancel\n" : std::cout << "CZY NA PEWNO CHCESZ TO ZROBIĆ? Enter - Akceptuj | Inny klawisz - Anuluj\n";
					if (getch() != 13)
						break;
					nicknames.clear();
					engLang ? std::cout << " Removed all players\n" : std::cout << " Usunięto wszystkich graczy\n";
					break;
				}
				default:
					def();
				}
				if (wyb == 27)
					break;
			}
			break;
		}
		case 'n':
		{
			cls();
			engLang ? std::cout << "Nickname is required to proper work of LiveChat\n" : std::cout << "Nazwa nicku potrzebna jest do poprawnego dzialania LiveChat\n";
			while (true)
			{
				engLang ? std::cout << "Enter your new nickname: " : std::cout << "Podaj swoj nowy nick: ";
				std::cin >> nick;
				if (nick.length() < 3)
				{
					engLang ? std::cout << "Nickname has to be at least 3 characters long!\n" : std::cout << "Minimum 3 znaki!\n";
				}
				else
					break;
			}
			cls();
			break;
		}
		default:
			def();
		}
	}
}
