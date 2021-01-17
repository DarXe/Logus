// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

//standard libraries
#include <iostream>
#include <fstream>
#include <chrono>
#include <conio.h>
#include <thread>
#include <filesystem>

//header includes
#include <common.hpp>
#include <var.hpp>
#include <proc.hpp>
#include <commonConfig.hpp>
#include "../menu/livechat/livechat_events.hpp"
#include <stopwatch.hpp>
#include <debug.hpp>
#include "loglookup.hpp"

bool checkDate(std::string line, const std::string &date, const bool &checkHour)
{
  //used date format (same as in mta logs) [2020-08-28 02:30:15]
  if (!checkHour)
  {
    line = line.substr(1, 10);
    int l_year, l_month, l_day,
        d_year, d_month, d_day;
    sscanf_s(line.c_str(), "%4d-%2d-%2d",
             &l_year, &l_month, &l_day);
    sscanf_s(date.c_str(), "%4d-%2d-%2d",
             &d_year, &d_month, &d_day);

    if (l_year >= d_year)
      if (l_month >= d_month)
        if (l_day >= d_day)
          return 1;
  }
  else
  {
    line = line.substr(1, 16);
    int l_year, l_month, l_day, l_hour, l_minute,
        d_year, d_month, d_day, d_hour, d_minute;
    sscanf_s(line.c_str(), "%4d-%2d-%2d %2d:%2d",
             &l_year, &l_month, &l_day, &l_hour, &l_minute);
    sscanf_s(date.c_str(), "%4d-%2d-%2d %2d:%2d",
             &d_year, &d_month, &d_day, &d_hour, &d_minute);

    if (l_year >= d_year)
      if (l_month >= d_month)
        if (l_day >= d_day)
          if (l_hour >= d_hour)
            if (l_minute >= d_minute)
              return 1;
  }
  return 0;
}

bool showLogContentInLogus(const std::string &filename, const uintmax_t &filesize, std::deque<std::string> &foundLines)
{
  if (foundLines.empty())
  {
    cls();
    std::cout << ((engLang) ? " (INFO) Nothing has been found\n" : " (INFO) Nic nie znaleziono\n");
    return 1;
  }
  int page = 0;
  while (true)
  {
    std::string b;
    SetConsoleTextAttribute(h, 10);
    cls();
    int a = 0;
    for (int i = page * 20; i < foundLines.size(); i++)
    {
      if (std::to_string(++a).size() == 1)
        b = " " + std::to_string(a);
      else
        b = std::to_string(a);

      std::cout << b << foundLines[i] << '\n';
      if (a == 20)
        break;
    }
    if (page * 20 >= foundLines.size())
      break;
    SetConsoleTextAttribute(h, 12);
    std::cout << "<<< ESC - Wyjdź | Każdy inny klawisz - Kontynuuj | Strona: " << ++page << " >>>\n";
    if (getch() == 27)
    {
      cls();
      break;
    }
  }
  return 1;
}

void showLogContentInLiveChat(const std::deque<std::string> &foundLines)
{
  if (foundLines.size() == 0)
    return;
  std::fstream showFile("content.txt", std::ios::out | std::ios::binary);
  Stopwatch showf;
  for (int i = 0; i < foundLines.size(); i++)
  {
    std::string line = foundLines.at(i);
    showFile << line << '\n';
  }
  showf.stop();
  showFile.close();
  LDebug::DebugOutput("showLogContentInLiveChat: czas zapisu: %s (%s)", {showf.pre(ns), showf.pre(ms, 2)});
  ShellExecute(0, 0, "content.txt", 0, 0, SW_SHOW);
}

bool showLogContentInDefEditor(const std::string &filename, const uintmax_t &filesize, const std::deque<std::string> &foundLines)
{
  if (foundLines.size() == 0)
  {
    cls();
    std::cout << ((engLang) ? " (INFO) Nothing has been found\n" : " (INFO) Nic nie znaleziono\n");
    return 1;
  }
  std::fstream showFile("content.txt", std::ios::out | std::ios::binary);
  Stopwatch showf;
  for (int i = 0; i < foundLines.size(); i++)
  {
    showFile << foundLines[i] << '\n';
  }
  showf.stop();
  LDebug::DebugOutput("showLogContentInDefEditor: plik: %s, wielkość pliku: %sKB, czas zapisu: %s (%s)", {filename, std::to_string(filesize / 1000),
                                                                                                          showf.pre(ns), showf.pre(ms, 2)});
  showFile.close();
  cls();
  std::cout << ((engLang) ? "Current file: " : "Aktualny plik: ") << filename << ((engLang) ? "\nFound content will be shown in default program associated with .txt extension\nPress ESC to return to menu or any other key to continue" : "\nZnaleziona zawartość pokaże się w edytorze domyślnie ustalonym dla rozszerzenia .txt\nWciśnij klawisz ESC aby powrócić do MENU lub inny żeby kontynuować");
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  ShellExecute(0, 0, "content.txt", 0, 0, SW_SHOW);
  if (getch() == 27)
  {
    ;
    cls();
    return 0;
  }
  cls();
  return 1;
}

bool checkLogNicknames(const std::string &filename)
{
  std::ifstream fileCheck;
  std::string line;
  std::deque<std::string> foundLines;
  auto filesize = std::filesystem::file_size(filename);
  if (filesize > 1000000000)
  {
    std::cout << ((engLang) ? " (INFO) File is to big\n" : " (INFO) Plik jest za duży\n");
    return 1;
  }

  fileCheck.open(filename, std::ios::in | std::ios::binary);
  while (!fileCheck.eof())
  {
    getline(fileCheck, line);
    if (LCEvent::Nicknames(line))
      foundLines.push_back(line);
  }
  fileCheck.close();

  if (!showLogContentInDefEditor(filename, filesize, foundLines))
    return 0;
  return 1;
}

bool checkLogPM(const std::string &filename, const Editor &editor)
{
  std::ifstream fileCheck;
  std::string line;
  std::deque<std::string> foundLines;
  auto filesize = std::filesystem::file_size(filename);
  if (filesize > 1000000000)
  {
    std::cout << ((engLang) ? " (INFO) File is to big\n" : " (INFO) Plik jest za duży\n");
    return 1;
  }

  fileCheck.open(filename, std::ios::in | std::ios::binary);
  while (!fileCheck.eof())
  {
    getline(fileCheck, line);
    if (LCEvent::PmFrom(line) || LCEvent::PmTo(line))
      foundLines.push_back(line);
  }
  fileCheck.close();
  switch (editor)
  {
  case DefEditor:
  {
    if (!showLogContentInDefEditor(filename, filesize, foundLines))
      return 0;
    break;
  }
  case Logus:
  {
    if (!showLogContentInLogus(filename, filesize, foundLines))
      return 0;
    break;
  }
  default:
  {
    break;
  }
  }
  return 1;
}

bool checkLogTransfersAll(const Editor &editor)
{
  std::ifstream fileCheck;
  std::string line;
  std::deque<std::string> foundLines;
  auto filesize = std::filesystem::file_size("logus.log");
  if (filesize > 1000000000 && editor != LiveChat)
  {
    std::cout << ((engLang) ? " (INFO) File is to big\n" : " (INFO) Plik jest za duży\n");
    return 1;
  }

  fileCheck.open("logus.log", std::ios::in | std::ios::binary);
  while (!fileCheck.eof())
  {
    getline(fileCheck, line);
    if (LCEvent::TransfersFrom(line) || LCEvent::TransfersTo(line))
      foundLines.push_front(line);
  }
  fileCheck.close();
  fileCheck.open(consoleLogPath, std::ios::in | std::ios::binary);
  while (!fileCheck.eof())
  {
    getline(fileCheck, line);
    if (LCEvent::TransfersFrom(line) || LCEvent::TransfersTo(line))
      foundLines.push_front(line);
  }
  fileCheck.close();

  switch (editor)
  {
  case DefEditor:
  case Logus:
  {
    if (!showLogContentInLogus("console.log", filesize, foundLines))
      return 0;
    break;
  }
  case LiveChat:
  {
    showLogContentInLiveChat(foundLines);
    return 0;
  }
  default:
  {
    break;
  }
  }
  return 1;
}

bool checkLogTransfers(const std::string &filename, const Editor &editor)
{
  std::ifstream fileCheck;
  std::string line;
  std::deque<std::string> foundLines;
  auto filesize = std::filesystem::file_size(filename);
  if (filesize > 1000000000)
  {
    std::cout << ((engLang) ? " (INFO) File is to big\n" : " (INFO) Plik jest za duży\n");
    return 1;
  }

  fileCheck.open(filename, std::ios::in | std::ios::binary);
  while (!fileCheck.eof())
  {
    getline(fileCheck, line);
    if (LCEvent::TransfersFrom(line) || LCEvent::TransfersTo(line))
      foundLines.push_back(line);
  }
  fileCheck.close();

  switch (editor)
  {
  case DefEditor:
  {
    if (!showLogContentInDefEditor(filename, filesize, foundLines))
      return 0;
    break;
  }
  case Logus:
  {
    if (!showLogContentInLogus(filename, filesize, foundLines))
      return 0;
    break;
  }
  default:
  {
    break;
  }
  }
  return 1;
}

bool checkLogTeam(const std::string &filename)
{
  std::ifstream fileCheck;
  std::string line;
  std::deque<std::string> foundLines;
  auto filesize = std::filesystem::file_size(filename);
  if (filesize > 1000000000)
  {
    std::cout << ((engLang) ? " (INFO) File is to big\n" : " (INFO) Plik jest za duży\n");
    return 1;
  }

  fileCheck.open(filename, std::ios::in | std::ios::binary);
  while (!fileCheck.eof())
  {
    getline(fileCheck, line);
    if (LCEvent::Team(line, 1))
      foundLines.push_back(line);
  }
  fileCheck.close();

  if (!showLogContentInDefEditor(filename, filesize, foundLines))
    return 0;
  return 1;
}

bool CheckLogContentDateFromTo(const std::string &filename, const std::string &date, const std::string &dateEnd, const bool &checkHour)
{
  std::ifstream fileCheck;
  std::string line;
  std::deque<std::string> foundLines;
  auto filesize = std::filesystem::file_size(filename);
  if (filesize > 1000000000)
  {
    std::cout << ((engLang) ? " (INFO) File is to big\n" : " (INFO) Plik jest za duży\n");
    return 1;
  }

  fileCheck.open(filename, std::ios::in | std::ios::binary);
  while (true)
  {
    getline(fileCheck, line);
    if (fileCheck.eof())
      break;
    if (checkDate(line, date, checkHour))
    {
      foundLines.push_back(line);
      break;
    }
  }
  while (true)
  {
    getline(fileCheck, line);
    if (fileCheck.eof())
      break;
    foundLines.push_back(line);
    if (checkDate(line, dateEnd, checkHour))
      break;
  }
  fileCheck.close();

  showLogContentInDefEditor(filename, filesize, foundLines);
  return 1;
}

void dateSelectionMenu()
{
  std::string date, dateEnd, filename;
  cls();
  filename = ((engLang) ? cfgSelectionStr("Choose file to lookup.", consoleLogPath, consoleLog1Path, consoleLog2Path, consoleLog3Path, consoleLog4Path, consoleLog5Path, "logus.log") : cfgSelectionStr("Wybierz nazwę pliku do przeszukania.", consoleLogPath, consoleLog1Path, consoleLog2Path, consoleLog3Path, consoleLog4Path, consoleLog5Path, "logus.log"));
  if (filename == "WYJŚCIE")
  {
    cls();
    return;
  }
  cls();
  if (engLang)
  {
    if (cfgSelection("Do you want to also include the time in the search?", "Yes", "No") == 1)
    {
      date = cfgInput(1, "Enter the starting date (for example 2020-08-28 21:37)", "Enter date: (must be format RRRR-MM-DD HH:MM):", "You did something wrong");
      dateEnd = cfgInput(1, "Enter the ending date (for example 2020-08-28 21:37)", "Enter date: (must be format RRRR-MM-DD HH:MM):", "You did something wrong");
      if (date.size() > 16 || dateEnd.size() > 16)
        return;
      CheckLogContentDateFromTo(filename, date, dateEnd, 1);
      return;
    }
    else
    {
      date = cfgInput(1, "Enter the starting date (for example 2020-08-28)", "Enter date: (must be format RRRR-MM-DD HH:MM):", "You did something wrong");
      dateEnd = cfgInput(1, "Enter the ending date (for example 2020-08-28)", "Enter date: (must be format RRRR-MM-DD HH:MM):", "You did something wrong");
      if (date.size() > 10 || dateEnd.size() > 10)
        return;
      CheckLogContentDateFromTo(filename, date, dateEnd, 0);
      return;
    }
  }
  else
  {
    if (cfgSelection("Czy chcesz uwzględnić w wyszukiwaniu także godzinę?", "Tak", "Nie") == 1)
    {
      date = cfgInput(1, "Podaj datę początkową (przykładowo 2020-08-28 21:37)", "Podaj datę (obowiązkowo format RRRR-MM-DD HH:MM):", "Nie wiem jak, ale coś podałeś źle");
      dateEnd = cfgInput(1, "Podaj datę końcową (przykładowo 2020-08-29 21:37)", "Podaj datę (obowiązkowo format RRRR-MM-DD HH:MM):", "Nie wiem jak, ale coś podałeś źle");
      if (date.size() > 16 || dateEnd.size() > 16)
        return;
      CheckLogContentDateFromTo(filename, date, dateEnd, 1);
      return;
    }
    else
    {
      date = cfgInput(1, "Podaj datę początkową (przykładowo 2020-08-28)", "Podaj datę (obowiązkowo format RRRR-MM-DD):", "Nie wiem jak, ale coś podałeś źle");
      dateEnd = cfgInput(1, "Podaj datę końcową (przykładowo 2020-08-29)", "Podaj datę (obowiązkowo format RRRR-MM-DD):", "Nie wiem jak, ale coś podałeś źle");
      if (date.size() > 10 || dateEnd.size() > 10)
        return;
      CheckLogContentDateFromTo(filename, date, dateEnd, 0);
      return;
    }
  }
}

void findWordAll_NonCaseSensitive(std::string &word)
{
  std::ifstream fileCheck;
  std::string line, newline;
  for (int i = 0; i < word.size(); i++)
  {
    if (isupper(word[i]))
      word[i] = std::tolower(word[i]);
  }
  std::deque<std::string> foundLines;

  fileCheck.open("logus.log", std::ios::in | std::ios::binary);
  while (!fileCheck.eof())
  {
    getline(fileCheck, line);
    newline = line;
    for (int i = 0; i < line.size(); i++)
    {
      if (isupper(line[i]))
        newline[i] = std::tolower(line[i]);
    }
    if (newline.find(word, gt) != std::string::npos && line.find("[Input]  : ") == std::string::npos)
      foundLines.push_front(line);
  }
  fileCheck.close();
  fileCheck.open(consoleLogPath, std::ios::in | std::ios::binary);
  while (!fileCheck.eof())
  {
    getline(fileCheck, line);
    newline = line;
    for (int i = 0; i < line.size(); i++)
    {
      if (isupper(line[i]))
        newline[i] = std::tolower(line[i]);
    }
    if (newline.find(word, gt) != std::string::npos && line.find("[Input]  : ") == std::string::npos)
      foundLines.push_front(line);
  }
  fileCheck.close();

  showLogContentInLiveChat(foundLines);
  return;
}

void findWordAll_CaseSensitive(std::string &word)
{
  std::ifstream fileCheck;
  std::string line;
  std::deque<std::string> foundLines;

  fileCheck.open("logus.log", std::ios::in | std::ios::binary);
  while (!fileCheck.eof())
  {
    getline(fileCheck, line);
    if (line.find(word, gt) != std::string::npos && line.find("[Input]  : ") == std::string::npos)
      foundLines.push_front(line);
  }
  fileCheck.close();
  fileCheck.open(consoleLogPath, std::ios::in | std::ios::binary);
  while (!fileCheck.eof())
  {
    getline(fileCheck, line);
    if (line.find(word, gt) != std::string::npos && line.find("[Input]  : ") == std::string::npos)
      foundLines.push_front(line);
  }
  fileCheck.close();

  showLogContentInLiveChat(foundLines);
  return;
}