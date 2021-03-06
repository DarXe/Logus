// Copyright © 2020  Niventill, Darxe
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

//standard libraries
#include <iostream>
#include <fstream>
#include <future>

//header includes
#include "common.hpp"
#include "var.hpp"
#include <ver.hpp>
#include "config.hpp"

std::string clearConfigValue(std::string &line, std::string cfgname)
{
  line.erase(0, cfgname.size());
  return removeSpaces(line);
}

void readConfig(bool showInfo)
{
  std::ifstream read;
  std::string templine;
  read.open("logus.ini");
  while (!read.eof())
  {
    getline(read, templine);
    if ((templine.find("//BAZA DANYCH NICKÓW") != std::string::npos) || (templine.find("//NICKNAMES DATABASE") != std::string::npos))
      break;

    else if (templine.find("s_MTA server IP:") != std::string::npos)
      serverIP = clearConfigValue(templine, "s_MTA server IP:");
    else if (templine.find("s_IP serwera MTA:") != std::string::npos)
      serverIP = clearConfigValue(templine, "s_IP serwera MTA:");

    else if (templine.find("s_MTA Path:") != std::string::npos)
      mtaLocation = clearConfigValue(templine, "s_MTA Path:");
    else if (templine.find("s_Ścieżka MTA:") != std::string::npos)
      mtaLocation = clearConfigValue(templine, "s_Ścieżka MTA:");

    else if (templine.find("s_Nickname:") != std::string::npos)
      nick = clearConfigValue(templine, "s_Nickname:");

    else if (templine.find("i_Main sound:") != std::string::npos)
      dzwiekGlowny = stoi(clearConfigValue(templine, "i_Main sound:"));
    else if (templine.find("i_Dźwięk główny:") != std::string::npos)
      dzwiekGlowny = stoi(clearConfigValue(templine, "i_Dźwięk główny:"));

    else if (templine.find("b_Language (0 = POL, 1 = ENG):") != std::string::npos)
      engLang = stoi(clearConfigValue(templine, "b_Language (0 = POL, 1 = ENG):"));
    else if (templine.find("b_Język (0 = POL, 1 = ENG):") != std::string::npos)
      engLang = stoi(clearConfigValue(templine, "b_Język (0 = POL, 1 = ENG):"));

    else if (templine.find("i_Amount of lines displayed:") != std::string::npos)
      lcLines = stoi(clearConfigValue(templine, "i_Amount of lines displayed:"));
    else if (templine.find("i_Liczba wyświetlanych linii:") != std::string::npos)
      lcLines = stoi(clearConfigValue(templine, "i_Liczba wyświetlanych linii:"));

    else if (templine.find("i_Refresh:") != std::string::npos)
      refresh = stoi(clearConfigValue(templine, "i_Refresh:"));
    else if (templine.find("i_Odświeżanie:") != std::string::npos)
      refresh = stoi(clearConfigValue(templine, "i_Odświeżanie:"));

    else if (templine.find("i_Delay between sounds:") != std::string::npos)
      interval = stoi(clearConfigValue(templine, "i_Delay between sounds:"));
    else if (templine.find("i_Odstep między dźwiękami:") != std::string::npos)
      interval = stoi(clearConfigValue(templine, "i_Odstep między dźwiękami:"));

    else if (templine.find("b_Mute team notifications:") != std::string::npos)
      fLockTeam = stoi(clearConfigValue(templine, "b_Mute team notifications:"));
    else if (templine.find("b_Blokada powiadomienia Team:") != std::string::npos)
      fLockTeam = stoi(clearConfigValue(templine, "b_Blokada powiadomienia Team:"));

    else if (templine.find("b_Mute PM notifications:") != std::string::npos)
      fLockPW = stoi(clearConfigValue(templine, "b_Mute PM notifications:"));
    else if (templine.find("b_Blokada powiadomienia PM:") != std::string::npos)
      fLockPW = stoi(clearConfigValue(templine, "b_Blokada powiadomienia PM:"));

    else if (templine.find("b_Mute fraction/cargo notifications:") != std::string::npos)
      fLockReport = stoi(clearConfigValue(templine, "b_Mute fraction/cargo notifications:"));
    else if (templine.find("b_Blokada powiadomienia towaru/frakcji:") != std::string::npos)
      fLockReport = stoi(clearConfigValue(templine, "b_Blokada powiadomienia towaru/frakcji:"));

    else if (templine.find("b_Mute nicknames notifications:") != std::string::npos)
      fLockNick = stoi(clearConfigValue(templine, "b_Mute nicknames notifications:"));
    else if (templine.find("b_Blokada powiadomienia na wybrane nicki:") != std::string::npos)
      fLockNick = stoi(clearConfigValue(templine, "b_Blokada powiadomienia na wybrane nicki:"));

    else if (templine.find("b_Mute phrase notifications:") != std::string::npos)
      fLockPhrase = stoi(clearConfigValue(templine, "b_Mute phrase notifications:"));
    else if (templine.find("b_Blokada powiadomienia na wybrane frazy:") != std::string::npos)
      fLockPhrase = stoi(clearConfigValue(templine, "b_Blokada powiadomienia na wybrane frazy:"));

    else if (templine.find("b_Dynamic refresh:") != std::string::npos)
      dynamicRefresh = stoi(clearConfigValue(templine, "b_Dynamic refresh:"));
    else if (templine.find("b_Odświeżanie dynamiczne:") != std::string::npos)
      dynamicRefresh = stoi(clearConfigValue(templine, "b_Odświeżanie dynamiczne:"));

    else if (templine.find("i_Min dynamic refresh:") != std::string::npos)
      minRefresh = stoi(clearConfigValue(templine, "i_Min dynamic refresh:"));
    else if (templine.find("i_Min dynamiczne odświeżanie:") != std::string::npos)
      minRefresh = stoi(clearConfigValue(templine, "i_Min dynamiczne odświeżanie:"));

    else if (templine.find("i_Max dynamic refresh:") != std::string::npos)
      maxRefresh = stoi(clearConfigValue(templine, "i_Max dynamic refresh:"));
    else if (templine.find("i_Max dynamiczne odświeżanie:") != std::string::npos)
      maxRefresh = stoi(clearConfigValue(templine, "i_Max dynamiczne odświeżanie:"));

    else if (templine.find("i_Unloading time:") != std::string::npos)
      czas = stoi(clearConfigValue(templine, "i_Unloading time:"));
    else if (templine.find("i_Czas rozładunku:") != std::string::npos)
      czas = stoi(clearConfigValue(templine, "i_Czas rozładunku:"));

    else if (templine.find("b_Delivery type:") != std::string::npos)
      random = stoi(clearConfigValue(templine, "b_Delivery type:"));
    else if (templine.find("b_Sposób dostawy:") != std::string::npos)
      random = stoi(clearConfigValue(templine, "b_Sposób dostawy:"));

    else if (templine.find("i_Money:") != std::string::npos)
      money = stoll(clearConfigValue(templine, "i_Money:"));
    else if (templine.find("i_Kasa:") != std::string::npos)
      money = stoll(clearConfigValue(templine, "i_Kasa:"));

    else if (templine.find("i_Courses:") != std::string::npos)
      courses = stoll(clearConfigValue(templine, "i_Courses:"));
    else if (templine.find("i_Kursy:") != std::string::npos)
      courses = stoll(clearConfigValue(templine, "i_Kursy:"));

    else if (templine.find("i_Fast start mode:") != std::string::npos)
      fastStart = stoi(clearConfigValue(templine, "i_Fast start mode:"));
    else if (templine.find("i_Autostart:") != std::string::npos)
      fastStart = stoi(clearConfigValue(templine, "i_Autostart:"));

    else if (templine.find("i_Route:") != std::string::npos)
      trackId = stoi(clearConfigValue(templine, "i_Route:"));
    else if (templine.find("i_Trasa:") != std::string::npos)
      trackId = stoi(clearConfigValue(templine, "i_Trasa:"));

    else if (templine.find("b_Automatic log mover:") != std::string::npos)
      autoMoveLogs = stoi(clearConfigValue(templine, "b_Automatic log mover:"));
    else if (templine.find("b_Automatyczne przenoszenie logów:") != std::string::npos)
      autoMoveLogs = stoi(clearConfigValue(templine, "b_Automatyczne przenoszenie logów:"));

    else if (templine.find("f_Grade:") != std::string::npos)
      grade = stof(clearConfigValue(templine, "f_Grade:"));
    else if (templine.find("f_Płaca w firmie:") != std::string::npos)
      grade = stof(clearConfigValue(templine, "f_Płaca w firmie:"));

    else if (templine.find("f_Komis stawka sprzedaż osobówki:") != std::string::npos)
      base_dealerSellCar = stof(clearConfigValue(templine, "f_Komis stawka sprzedaż osobówki:"));

    else if (templine.find("f_Komis stawka sprzedaż dostawczego:") != std::string::npos)
      base_dealerSellTransport = stof(clearConfigValue(templine, "f_Komis stawka sprzedaż dostawczego:"));

    else if (templine.find("f_Komis stawka skup:") != std::string::npos)
      base_dealerBuy = stof(clearConfigValue(templine, "f_Komis stawka skup:"));

    else if (templine.find("b_Manualna edycja cars.txt:") != std::string::npos)
      dealerManual = stoi(clearConfigValue(templine, "b_Manualna edycja cars.txt:"));

    else if (templine.find("b_Toggle auto gate opening (open at the end of PM):") != std::string::npos)
      autoOpenGate = stoi(clearConfigValue(templine, "b_Toggle auto gate opening (open at the end of PM):"));
    else if (templine.find("b_Włącz automatyczne otwieranie bramy (open na końcu PW):") != std::string::npos)
      autoOpenGate = stoi(clearConfigValue(templine, "b_Włącz automatyczne otwieranie bramy (open na końcu PW):"));

    else if (templine.find("s_Update channel:") != std::string::npos)
      updateChannel = clearConfigValue(templine, "s_Update channel:");
    else if (templine.find("s_Kanał aktualizacji:") != std::string::npos)
      updateChannel = clearConfigValue(templine, "s_Kanał aktualizacji:");

    else if (templine.find("i_Highest salary:") != std::string::npos)
      maxsalary = stoi(clearConfigValue(templine, "i_Highest salary:"));
    else if (templine.find("i_Najwyższy zarobek:") != std::string::npos)
      maxsalary = stoi(clearConfigValue(templine, "i_Najwyższy zarobek:"));

    else if (templine.find("i_Lowest salary:") != std::string::npos)
      minsalary = stoi(clearConfigValue(templine, "i_Lowest salary:"));
    else if (templine.find("i_Najniższy zarobek:") != std::string::npos)
      minsalary = stoi(clearConfigValue(templine, "i_Najniższy zarobek:"));

    else if (templine.find("b_Timestamp:") != std::string::npos)
      timestamp = stoi(clearConfigValue(templine, "b_Timestamp:"));

    else if (templine.find("b_Render engine:") != std::string::npos)
      renderEngine = stoi(clearConfigValue(templine, "b_Render engine:"));
    else if (templine.find("b_Silnik renderowania:") != std::string::npos)
      renderEngine = stoi(clearConfigValue(templine, "b_Silnik renderowania:"));
  }

  consoleLogPath = mtaLocation + "\\MTA\\logs\\console.log";
  consoleLog1Path = mtaLocation + "\\MTA\\logs\\console.log.1";
  consoleLog2Path = mtaLocation + "\\MTA\\logs\\console.log.2";
  consoleLog3Path = mtaLocation + "\\MTA\\logs\\console.log.3";
  consoleLog4Path = mtaLocation + "\\MTA\\logs\\console.log.4";
  consoleLog5Path = mtaLocation + "\\MTA\\logs\\console.log.5";

  getline(read, templine); //jump to actual nicknames
  nicknames.clear();
  while (true)
  {
    getline(read, templine);
    if ((templine.find("//BAZA DANYCH FRAZ") != std::string::npos) || (templine.find("//PHRASE DATABASE") != std::string::npos) || read.eof())
      break;
    nicknames.push_back(templine);
  }
  phrases.clear();
  while (true)
  {
    getline(read, templine);
    if (read.eof())
      break;
    phrases.push_back(templine);
  }
  read.close();
  if (showInfo)
  {
    engLang ? std::cout << " (INFO) Settings has been loaded." : std::cout << " (INFO) Wczytano ustawienia.\n";
  }
}

long long getVer()
{
  std::fstream file;
  std::string templine;
  file.open("logus.ini");
  while (!file.eof())
  {
    getline(file, templine);
    if (templine.find("s_version:") != std::string::npos)
    {
      clearConfigValue(templine, "s_version:");
      return stoll(templine);
    }
    else if (templine.find("s_wersja:") != std::string::npos)
    {
      clearConfigValue(templine, "s_wersja:");
      return stoll(templine);
    }
  }
  return -1;
}

void showUpdateInfo()
{
  engLang ? std::cout << " (INFO) Settings loaded. Succesfully updated from " << getHumanReadableVersion(0, getVer() / 1000) << " to " << getHumanReadableVersion(0) << '\n' : std::cout << " (INFO) Wczytano ustawienia. Wykonano aktualizację z " << getHumanReadableVersion(0, getVer() / 1000) << " do " << getHumanReadableVersion(0) << '\n';
}

void saveConfig(bool showInfo)
{ //saa save
  auto f = std::async(std::launch::async, [] {
    std::fstream file;
    if (engLang)
    {
      file.open("logus.ini", std::ios::out);
      file << "////////////////////////////////////////////////////////////////////////////////////////////////\n";
      file << "//Welcome to the config file. Feel free to change settings as you like (don't edit version tho)\n";
      file << "//Setting prefixes: s = text variable, i = integer variable, f = float, b = 0/1 variable (bool)\n";
      file << "//Colors: 1-9, A-F" << std::endl;
      file << "////////////////////////////////////////////////////////////////////////////////////////////////\n";
      file << "s_version: " << getLogusBuildVersion() << "\n";
      file << "s_Update channel: " << updateChannel << '\n';
      file << "s_MTA server IP: " << serverIP << "\n";
      file << "s_MTA Path: " << mtaLocation << "\n";
      file << "s_Nickname: " << nick << "\n";
      file << "i_Main sound: " << dzwiekGlowny << "\n";
      file << "b_Language (0 = POL, 1 = ENG): " << engLang << "\n";
      file << "i_Amount of lines displayed: " << lcLines << "\n";
      file << "i_Refresh: " << refresh << "\n";
      file << "i_Delay between sounds: " << interval << "\n";
      file << "b_Mute team notifications: " << fLockTeam << "\n";
      file << "b_Mute PM notifications: " << fLockPW << "\n";
      file << "b_Mute fraction/cargo notifications: " << fLockReport << "\n";
      file << "b_Mute nicknames notifications: " << fLockNick << "\n";
      file << "b_Mute phrase notifications: " << fLockPhrase << '\n';
      file << "b_Toggle auto gate opening (open at the end of PM): " << autoOpenGate << "\n";
      file << "b_Timestamp: " << timestamp << '\n';
      file << "b_Render engine: " << renderEngine << '\n';
      file << "b_Dynamic refresh: " << dynamicRefresh << "\n";
      file << "i_Min dynamic refresh: " << minRefresh << "\n";
      file << "i_Max dynamic refresh: " << maxRefresh << "\n";
      file << "i_Unloading time: " << czas << "\n";
      file << "b_Delivery type: " << random << "\n";
      file << "i_Money: " << money << "\n";
      file << "i_Courses: " << courses << "\n";
      file << "i_Lowest salary: " << minsalary << "\n";
      file << "i_Highest salary: " << maxsalary << "\n";
      file << "i_Fast start mode: " << fastStart << "\n";
      file << "i_Route: " << trackId << "\n";
      file << "b_Automatic log mover: " << autoMoveLogs << "\n";
      file << "f_Grade: " << grade << "\n";
      file << "f_Komis stawka sprzedaż osobówki: " << base_dealerSellCar << "\n";
      file << "f_Komis stawka sprzedaż dostawczego: " << base_dealerSellTransport << "\n";
      file << "f_Komis stawka skup: " << base_dealerBuy << "\n";
      file << "b_Manualna edycja cars.txt: " << dealerManual << "\n";
      file << "//NICKNAMES DATABASE////////////////////////////////////////////////////////////////////////////\n";
      file << "Nicknames in database: " << nicknames.size() << '\n';
      for (int i = 0; i < nicknames.size(); i++)
        file << nicknames.at(i) << '\n';
      file << "//PHRASE DATABASE///////////////////////////////////////////////////////////////////////////////\n";
      for (int i = 0; i < phrases.size(); i++)
        file << phrases.at(i) << '\n';
    }
    else
    {
      file.open("logus.ini", std::ios::out);
      file << "////////////////////////////////////////////////////////////////////////////////////////////////\n";
      file << "//Witaj w pliku konfiguracyjnym. Edytuj go do woli, ale używaj poprawnych typów wartości\n";
      file << "//Typy wartości: s = tekst, i = liczba, f = liczba zmiennoprzecinkowa, b = 0/1 (bool)\n";
      file << "//Kolory: 1-9, A-F" << std::endl;
      file << "////////////////////////////////////////////////////////////////////////////////////////////////\n";
      file << "s_wersja: " << getLogusBuildVersion() << "\n";
      file << "s_IP serwera MTA: " << serverIP << "\n";
      file << "s_Kanał aktualizacji: " << updateChannel << '\n';
      file << "s_Ścieżka MTA: " << mtaLocation << "\n";
      file << "s_Nickname: " << nick << "\n";
      file << "i_Dźwięk główny: " << dzwiekGlowny << "\n";
      file << "b_Język (0 = POL, 1 = ENG): " << engLang << "\n";
      file << "i_Liczba wyświetlanych linii: " << lcLines << "\n";
      file << "i_Odświeżanie: " << refresh << "\n";
      file << "i_Odstep między dźwiękami: " << interval << "\n";
      file << "b_Blokada powiadomienia Team: " << fLockTeam << "\n";
      file << "b_Blokada powiadomienia PM: " << fLockPW << "\n";
      file << "b_Blokada powiadomienia towaru/frakcji: " << fLockReport << "\n";
      file << "b_Blokada powiadomienia na wybrane nicki: " << fLockNick << "\n";
      file << "b_Blokada powiadomienia na wybrane frazy: " << fLockPhrase << '\n';
      file << "b_Włącz automatyczne otwieranie bramy (open na końcu PW): " << autoOpenGate << "\n";
      file << "b_Timestamp: " << timestamp << '\n';
      file << "b_Silnik renderowania: " << renderEngine << '\n';
      file << "b_Odświeżanie dynamiczne: " << dynamicRefresh << "\n";
      file << "i_Min dynamiczne odświeżanie: " << minRefresh << "\n";
      file << "i_Max dynamiczne odświeżanie: " << maxRefresh << "\n";
      file << "i_Czas rozładunku: " << czas << "\n";
      file << "b_Sposób dostawy: " << random << "\n";
      file << "i_Kasa: " << money << "\n";
      file << "i_Kursy: " << courses << "\n";
      file << "i_Najniższy zarobek: " << minsalary << "\n";
      file << "i_Najwyższy zarobek: " << maxsalary << "\n";
      file << "i_Autostart: " << fastStart << "\n";
      file << "i_Trasa: " << trackId << "\n";
      file << "b_Automatyczne przenoszenie logów: " << autoMoveLogs << "\n";
      file << "f_Płaca w firmie: " << grade << "\n";
      file << "f_Komis stawka sprzedaż osobówki: " << base_dealerSellCar << "\n";
      file << "f_Komis stawka sprzedaż dostawczego: " << base_dealerSellTransport << "\n";
      file << "f_Komis stawka skup: " << base_dealerBuy << "\n";
      file << "b_Manualna edycja cars.txt: " << dealerManual << "\n";
      file << "//BAZA DANYCH NICKÓW////////////////////////////////////////////////////////////////////////////\n";
      file << "Nicki w bazie danych: " << nicknames.size() << '\n';
      for (int i = 0; i < nicknames.size(); i++)
        file << nicknames.at(i) << '\n';
      file << "//BAZA DANYCH FRAZ//////////////////////////////////////////////////////////////////////////////\n";
      for (int i = 0; i < phrases.size(); i++)
        file << phrases.at(i) << '\n';
    }
    file.close();
  });
  if (showInfo)
  {
    f.wait();
    engLang ? std::cout << " (INFO) Settings has been saved.\n" : std::cout << " (INFO) Ustawienia zostaly zapisane.\n";
  }
}

void readDefault()
{
  dzwiekGlowny = 1777;
  fLockTeam = 0;
  fLockPW = 0;
  fLockReport = 0;
  fLockNick = 0;
  fLockPhrase = 0;
  engLang = 0;
  lcLines = 15;
  refresh = 300;
  interval = 50;
  nick = getNickFromMTAConfig();
  dynamicRefresh = 0;
  czas = 90;
  random = 0;
  serverIP = "185.62.189.174:22003";
  money = 0;
  courses = 0;
  fastStart = 0;
  trackId = 0;
  autoMoveLogs = 1;
  grade = 0.5;
  base_dealerBuy = 0.4;
  base_dealerSellCar = 0.65;
  base_dealerSellTransport = 0.8;
  dealerManual = 0;
  minRefresh = 250;
  maxRefresh = 1250;
  timestamp = 0;
  renderEngine = 1;
}