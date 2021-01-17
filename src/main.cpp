// Copyright © 2018-2020  DarXe
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

//standard libraries
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <vector>
#include <thread>

//header includes
#include <common.hpp>
#include <var.hpp>
#include "ver.hpp"
#include "updater.hpp"
#include <config.hpp>
#include <proc.hpp>
#include "menu/menu.hpp"
#include "main.hpp"

static void hideConsoleCursor()
{
  while (true)
  {
    CONSOLE_CURSOR_INFO CURSOR;
    CURSOR.dwSize = 1;
    CURSOR.bVisible = FALSE;
    SetConsoleCursorInfo(h, &CURSOR);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

static bool init(const int &argc)
{
  if (argc != 1)
  {
    std::fstream file;
    file.open("version", std::ios::out);
    file << genVer();
    file.close();
    return 0;
  }
  std::fstream inifile;
  inifile.open("logus.ini");
  if (inifile.good())
  {
    readConfig(0);
  }
  else
  {

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

  SetConsoleOutputCP(65001); //code page utf-8
  SetConsoleCP(65001);

  std::ifstream test;
  while (true)
  {
    test.open(mtaLocation + "\\MTA\\logs\\console.log");
    if (!test.good() && mtaLocation != "ERROR")
    {
      cls();
      std::string temploc;
      std::cout << ((engLang) ? " Found MTA Path: " : " Znaleziona ścieżka MTA: ");
      std::cout << mtaLocation << '\n';
      std::cout << ((engLang) ? " MTA directory found, but console.log file couldn't been found\n" : " Udało się znaleźć lokalizację MTA, ale nie znaleziono pliku console.log\n");
      std::cout << ((engLang) ? " Make sure you ran MTA after it's installation. If you did so and it's still not working, pray and blame your computer\n Press any key to try find MTA path again" : " Upewnij się, że MTA zostało uruchomione po jego zainstalowaniu.\n Jeśli poblem nadal występuje, pomódl się i poprzeklinaj na kąkuter\n Wciśnij dowolny klawisz aby spróbować znaleźć lokalizację MTA ponownie");
      getch();
      mtaLocation = getMTALocation();
    }
    else if (!test.good() && mtaLocation == "ERROR")
    {
      cls();
      std::string temploc;
      std::cout << ((engLang) ? " MTA directory not found. Please enter path manually\n" : " Nie udało się znaleźć lokalizacji MTA. Proszę podaj lokalizację manualnie\n");
      std::cout << ((engLang) ? " It has to be the main directory, eg. C:\\Program Files (x86)\\MTA San Andreas 1.5\n" : " Ścieżka musi być ścieżką główną, np. C:\\Program Files (x86)\\MTA San Andreas 1.5\n");
      std::cout << ((engLang) ? " Enter path: " : " Podaj ścieżkę: ");
      getline(std::cin, mtaLocation);
    }
    else
    {
      cls();
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
  return 1;
}

int main(int argc, char **argv) //maa main
{

  //init check if config exists, search for mta path etc
  if (!init(argc))
    return 0;

  std::thread con(hideConsoleCursor);
  con.detach();

  //q(mtaLocation); q(consoleLogPath); q(consoleLog1Path); q(consoleLog2Path); q(consoleLog3Path); q(consoleLog4Path); q(consoleLog5Path); getch(); return 0;
  std::fstream fileInit;
  fileInit.open(consoleLogPath, std::ios::app);
  fileInit.close();
  fileInit.open(consoleLog1Path, std::ios::app);
  fileInit.close();
  fileInit.open(consoleLog2Path, std::ios::app);
  fileInit.close();
  fileInit.open(consoleLog3Path, std::ios::app);
  fileInit.close();
  fileInit.open(consoleLog4Path, std::ios::app);
  fileInit.close();
  fileInit.open(consoleLog5Path, std::ios::app);
  fileInit.close();
  fileInit.open("liveChatInfoOutput.log", std::ios::app);
  fileInit.close();
  fileInit.open("logus.log", std::ios::app);
  fileInit.close();
  updateDependencies();

  std::string _versionName_ = "Logus " + titleVer;
  SetConsoleTitleA(_versionName_.c_str()); //verr
  std::srand(time(NULL));

  checkUpdates();

  switch (fastStart)
  {
  case 0:
    wersja();
    break;
  case 1:
  {
    runLiveChat();
    break;
  }
  default:
    break;
  }

  menu();

  return 0;
}

void wersja()
{
  std::cout << "  Witaj " << nick << " !" << std::endl;
  Sleep(300);
  std::cout << "  ___________________" << std::endl;
  std::cout << " |      Autorzy      |" << std::endl;
  std::cout << " |       DarXe       |" << std::endl;
  std::cout << " |     Niventill     |" << std::endl;
  std::cout << " |___________________|" << std::endl;
  std::cout << " |   Wersja " << relVer << "    |" << std::endl; //verr
  /*Sleep(300); std::cout<<std::endl;
	std::cout<<" PLANY: "<<std::endl;
	std::cout<<" Kreator wlasnych powiadomien"<<std::endl;
	std::cout<<" Wyszukiwanie wiadomosci tylko wybranych przez siebie graczy"<<std::endl;
	std::cout<<" Wyszukiwanie po tagach, ktore bedzie sie tworzylo(wysylalo) w konsoli mta"<<std::endl;
	std::cout<<" Naprawienie problemu z polskimi znakami na systemach win7"<<std::endl;*/
  Sleep(300);
  std::cout << std::endl;
  std::cout << " Nie zapomnij zajrzeć na GitHub'a - znajdziesz tam informacje o tym" << std::endl;
  std::cout << " jak korzystać z programu (są tam opisane wszystkie opcje)" << std::endl;
  std::cout << " https://github.com/DarXe/Logus/blob/master/README.md\n"
            << std::endl;
  Sleep(500);
  Beep(dzwiekGlowny, 150);
  std::cout << " Wciśnij klawisz, aby wyswietlić nowości" << std::endl;
  getch();
  cls();

  ////////////////////////////////////////////////////////////////// news goes here ////////////////////////////

  SetConsoleTextAttribute(h, 4);
  std::cout << " LISTOPAD\n";

  SetConsoleTextAttribute(h, 6);
  std::cout << " 2011_11 Nowa komenda "
               "set l <0:00>"
               " - ustawianie czasu załadunku\n";
  std::cout << " 2011_11 Komendy "
               "find cfg"
               ", "
               "find console.log"
               " i "
               "find logus.log"
               " zmieniły nazwę na:\n";
  std::cout << " * "
               "open cfg"
               ", "
               "open console.log"
               " oraz "
               "open logus.log"
               ", aby lepiej wskazać zastosowanie komendy\n";
  std::cout << " 2011_09 Nowa komenda - "
               "autorr"
               ", która włącza autoJoin - tj. próbuje połączyć się z serwerem co 10 sekund\n";
  std::cout << " * Komenda zastapiła klawisz Enter, który wcześniej robił to samo co teraz robi autorr\n";
  std::cout << " 2011_07 Nowa komenda - "
               "set minr <liczba>"
               " i "
               "set maxr <liczba>"
               ", które ustawiają min i max dynamicznego odświeżania\n";
  std::cout << " 2011_07 Nowa komenda - "
               "set dyn"
               ", która przełącza dynamiczne odświeżanie\n";
  std::cout << " 2011_07 Nowa komenda - "
               "set refr <liczba>"
               ", która ustawia odświeżanie liveChat\n";
  std::cout << " 2011_06 Nowa komenda - "
               "cls"
               ", czyli czyszczenie "
               "buforu"
               " czatu\n";
  std::cout << " 2011_06 Od teraz LiveChat zawija zbyt długie wiersze\n";
  std::cout << " 2011_06 Nowa komenda - "
               "set engine"
               ", która zmienia tryb renderowania czatu\n";
  std::cout << " 2011_04 Udoskonalono moduł automatycznej aktualizacji\n";
  std::cout << " 2011_04 Dodano komendę "
               "set ts"
               ", która przełącza widoczność timestampów\n";
  std::cout << " 2011_04 Przebudowano system wyświetlania w liveChat, czego rezultatem jest przyśpieszenie programu o 3,5 raza!\n";
  std::cout << " * Oprócz przyśpieszenia Logusia, po krótkim czasie nieobecności do Logusia wracają timestampy\n";
  std::cout << " * Parser LCFormat z biegiem czasu będzie uzupełniany o nowe formatowanie\n";
  std::cout << "\n Wciśnij klawisz, aby kontynuować (ESC, aby pominąć INFO)\n";
  if (getch() == 27)
  {
    cls();
    return;
  }
  cls();
  SetConsoleTextAttribute(h, 4);
  std::cout << " PAŹDZIERNIK\n";

  SetConsoleTextAttribute(h, 6);
  std::cout << " 2010_29 Dodano komendę "
               "find console.log"
               " oraz "
               "find logus.log"
               ", które otwierają plik z logami\n";
  std::cout << " 2010_29 Dodano komendę "
               "find cfg"
               ", która otwiera plik konfiguracyjny\n";
  std::cout << " 2010_29 Dodano komendę "
               "find tf"
               ", która otwiera domyślny edytor z wszystkimi przelewami\n";
  std::cout << " 2010_29 Dodano (a raczej przywrócono) opcję sprawdzenia ostatnich 20 przelewów\n";
  std::cout << " 2010_28 Dodano bazę fraz - tj. listę wyrazów do szukania w wiadomości gracza\n";
  std::cout << " * Główne zastosowanie to zapis wariantów nicku użytkownika Logusia\n";
  std::cout << " * Np.: Dar, dar, darXe, Darks itp. itd.\n";
  std::cout << " 2010_18 Dodano komendę set hre (hard reset), która poza resetowaniem kursów i gotówki resetuje także min i max zarobek\n";
  std::cout << " 2010_18 Komendy set n add i set n del zmieniły nazwę na nickdb add i nickdb del\n";
  std::cout << " 209_06 Przebudowa kodu... (znowu)\n";
  std::cout << "\n Wciśnij klawisz, aby kontynuować (ESC, aby pominąć INFO)\n";
  if (getch() == 27)
  {
    cls();
    return;
  }
  cls();
  SetConsoleTextAttribute(h, 4);
  std::cout << " WRZESIEŃ\n";

  SetConsoleTextAttribute(h, 6);
  std::cout << " 209_06 Min i max zarobek (resetowalny przez ustawienia lub komendę set re)\n";
  std::cout << " 209_06 Przebudowa kodu... (znowu)\n";
  std::cout << " 209_06 Auto-updater i wybór kanału aktualizacji!\n";
  std::cout << " 209_02-06 Poprawki błędów (znowu)\n";
  std::cout << " 209_01 Wykrycie wypadku uruchomi teraz także timer (resetując przy okazji inne timery)\n";
  std::cout << " 209_01 Dodano nowe ustawienie - automatyczne otwieranie bramy po otrzymaniu PW kończącego się na "
               "open"
               "\n";
  std::cout << " 209_01 Poprawiono kilka błędów powstałych po optymalizacji liveChat, teraz powinno być git\n";

  std::cout << "\n Wciśnij klawisz, aby kontynuować (ESC, aby pominąć INFO)\n";
  if (getch() == 27)
  {
    cls();
    return;
  }
  cls();
  SetConsoleTextAttribute(h, 4);
  std::cout << " SIERPIEŃ\n";

  SetConsoleTextAttribute(h, 6);
  std::cout << " 208_31 Wyszukiwanie logów (przelewów, wiadomości teamowych itp) działa teraz tak jak nigdy dotąd\n";
  std::cout << " 208_31 Dalsza optymalizacja liveChat - chodzi naprawdę szybko :-)\n";
  std::cout << " 208_31 Nowe ustawienie - maksymalny i minimalny dynamiczny refresh\n";
  std::cout << " 208_31 Dodano także nowe bugi, tj. brak kompatybilności ustawień z poprzednimi wersjami...\n";
  std::cout << " * Kosztem tego jest config v2, czyli 57 biednych else ifów pracujących na czarno\n";
  std::cout << " 208_31 Przebudowa niektórych komend w taki sposób, aby przyjmowały dowolne wartości\n";
  std::cout << " 208_31 Nowe komendy w LiveChat - set n add nick i set n del nick (usuwa lub dodaje nick do bazy nicków)\n";
  std::cout << " 208_31 Automatyczne wyszukiwanie nicku i lokalizacji MTA\n";
  std::cout << " * Dodatkowo zmiana nicku przed konsolę lub czat także zmieni nick (w przypadku zmiany nicku z poziomu czatu\n"
            << " * pomyślność zmiany nicku zależy od tego czy nick obecny w configu Logusia pokrywa się z tym w MTA\n";
  std::cout << " 208_25 Gruntowna przebudowa LiveChat, w końcu mniejsze zużycie I/O i brak pomijania logów!\n";
  std::cout << " 208_17 Dodanie integracji z komisem, tj. możliwość sprawdzenia cen pojazdów w komisie\n";
  std::cout << " * Niebawem zrobione będzie pełnoprawne wsparcie dla Win 7 (z pomocą conEmu)\n";
  std::cout << " 208_06.1 Częściowe wsparcie dla języka angielskiego (jak widać nowości dalej sa po polsku Xd)\n";
  std::cout << " 208_06 Uporządkowanie kodu i refaktoryzacja\n";
  std::cout << " 208_04 Poprawienie funkcji preConfig, dodanie preSelection(), preInputInt() oraz preInputString()\n";

  std::cout << "\n Wciśnij klawisz, aby kontynuować (ESC, aby pominąć INFO)\n";
  if (getch() == 27)
  {
    cls();
    return;
  }
  cls();
  SetConsoleTextAttribute(h, 4);
  std::cout << " CZERWIEC-LIPIEC\n";

  SetConsoleTextAttribute(h, 6);
  std::cout << " 207_31 Wydanie wersji 20.7\n";
  std::cout << " * 207_5 Konwersja makra na pasteCmd.exe\n";
  std::cout << " 206_28 Dodano tryb automatycznego otwierania bramy, gdy ktoś poprosi o open na PW\n";
  std::cout << " 206_15 Ukryto migający kursor w konsoli\n";
  std::cout << " 206_12.1 Ponowne włączenie bindu na timer wyłącza go (dłuższy Beep)\n";
  std::cout << " * wystarczy zrobić binda /bind <klawisz> xxx(nick, który nie istnieje) msg x\n";
  std::cout << " 206_12 Dodano możliwość ustawienia timera pod bind z mta (pomysł - arki)\n";
  std::cout << " 206_11 Dodano powiadomienia na przelewy od innych graczy\n";
  std::cout << " 206_10 Ping (opcja 'w') dodano możliwość sprawdzenia innego adresu\n";
  std::cout << " * Od teraz Logus uruchomi powiadomienie dźwiękowe tylko wtedy, kiedy wróci internet\n";
  std::cout << " 206_9 Zmieniono system sprawdzania połączenia wi-fi, opcja 'w' z menu\n";

  std::cout << "\n Wciśnij klawisz, aby kontynuować (ESC, aby pominąć INFO)\n";
  if (getch() == 27)
  {
    cls();
    return;
  }
  cls();
  SetConsoleTextAttribute(h, 4);
  std::cout << " MAJ\n";

  SetConsoleTextAttribute(h, 6);
  std::cout << " 205_11.2 Dodano prekonfigurację w przypadku braku pliku logus.ini\n";
  std::cout << " * Teraz nie jest potrzebne restartowanie programu w przypadku pomyłki\n";
  std::cout << " 205_11.1 Zmiana funkcji sprawdzającej podania napisu zamiast liczby\n";
  std::cout << " * Dopóki nie nastąpi połączenie z serwerem, Logus łączy się z nim co 5 sekund\n";
  std::cout << " 205_11 Dodano nową funkcje w LiveChat - [Enter] autoJoin\n";
  std::cout << " 205_10 Rozmiar Logusa jako aplikacji .exe o wiele się zmniejszył\n";
  std::cout << " 205_10 Poprawiono czyszczenie czatu po przeniesieniu logów\n";
  std::cout << " 205_91 Usunięto Logus-pre, od teraz Logus.exe na masterze jest aktualnym wydaniem Pre-Realease\n";
  std::cout << " 205_9 Edytowano zmianę wartości ms dynamicznym odświeżaniu\n";
  std::cout << " * 'set reset', 'set re'\n";
  std::cout << " 205_61 Dodano komendę na reset kursów i $ z poziomu konsoli mta\n";
  std::cout << " * Dodano dźwięki, tekst jest różny w zależności od powodu zamknięcia programu\n";
  std::cout << " 205_6 Zmieniono animacje wyłączenia programu\n";
  std::cout << " * Jeśli takich plików nie ma to Logus sam je zainicjuje (pliki log.1 log.2 itd.)\n";
  std::cout << " 205_6 Naprawiono problem z odczytywaniem plików log, jeśli nie zostały stworzone przez mta\n";
  std::cout << " * Logus wyłączy się automatycznie wraz z grą (zapisując ustawienia)\n";
  std::cout << " 205_6 Przypisano dodatkowe działanie komendzie 'quit' z mta\n";
  std::cout << " * Teraz Logus bierze pod uwagę długość nicku zmniejszając szanse na błędny komunikat\n";
  std::cout << " 205_6 Dodano dodatkowy warunek sprawdzający nick\n";

  std::cout << "\n Wciśnij klawisz, aby kontynuować (ESC, aby pominąć INFO)\n";
  if (getch() == 27)
  {
    cls();
    return;
  }
  cls();
  SetConsoleTextAttribute(h, 4);
  std::cout << " MARZEC\n";

  SetConsoleTextAttribute(h, 6);
  std::cout << " * Dodano też komendę na ustawienie ilości kursów - set c KURSY\n";
  std::cout << " * Wpisując w konsoli 'set m KWOTA', F4 ustawi się na podaną wartość\n";
  std::cout << " 203_3 Dodano nową komendę - ustawienie F4 z poziomu konsoli MTA\n";
  std::cout << " 203_2 Został dodany kolor żółty dla powiadomień zaczynających się od '*'\n";
  std::cout << " * Jak na razie zmiany zostały wprowadzone w trybie bez daty(Timestamps)\n";
  std::cout << " 203_1 Zmieniono kolorystykę czatu w LiveChat oddzielając wiadomość od nazwy gracza\n";
  std::cout << " * Plik znajduje się w folderze logs, logusInfoOutput.log\n";
  std::cout << " * Po wyłączeniu komunikatu dźwiękowego w opcjach linijka z logiem nie pojawi się w tym pliku\n";
  std::cout << " 203_1 Dodano nowy plik .log, aby mieć szybszy dostęp do logów z powiadomień(PW, TEAM, TOWAR, PRZELEWY)\n";
  std::cout << " 203_1 Zmieniono polecenie reconnect z 'r' na 'rr'\n";

  std::cout << "\n Wciśnij klawisz, aby kontynuować (ESC, aby pominąć INFO)\n";
  if (getch() == 27)
  {
    cls();
    return;
  }
  cls();
  SetConsoleTextAttribute(h, 4);
  std::cout << " ZMIANY - początek roku\n";
  SetConsoleTextAttribute(h, 6);
  std::cout << " 202_13 Po wciśnięciu entera wraz z uruchomieniem serwera włączy się funkcja LiveChat\n";
  std::cout << " * Jest to kolejna próba testów z serii 'co powoduje pomijanie zapisu niektórych kursów'\n";
  std::cout << " 202_13 Zmodyfikowano sprawdzanie warunków przy dostarczonym towarze\n";
  std::cout << " * Dodatkowo juz nie bedzie wyswietlana wyplata mniejsza niz 0\n";
  std::cout << " 202_13 Poprawiono blad przy wyswietlaniu wyplaty wiekszej niz $1000000 w LiveChat oraz ustawieniach\n";
  std::cout << " * Pozostaje powiadomienie na wejscie i wyjscie z serwera oraz na status AFK danego gracza\n";
  std::cout << " 201_2 Wylaczono powiadomienia na kazda wiadomosc gracza dodanego do Nicknames\n";
  std::cout << " Jeszcze w sierpniu zmieniono system sprawdzania nowych linii\n";

  cls();
}
