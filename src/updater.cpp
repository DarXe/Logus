// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

//standard libraries
#include <filesystem>
#include <iostream>
#include <fstream>

//header includes
#include <config.hpp>
#include <var.hpp>
#include <common.hpp>
#include <debug.hpp>
#include <stopwatch.hpp>
#include <ver.hpp>
#include "updater.hpp"

void updateDependencies()
{
  if (updateChannel != "disable")
  {
    if (!std::filesystem::exists("bin"))
      std::filesystem::create_directory("bin");
    if (!std::filesystem::exists("bin\\curl.exe"))
    {
      if (std::filesystem::exists("c:\\windows\\system32\\curl.exe"))
        std::filesystem::copy("c:\\windows\\system32\\curl.exe", "bin\\curl.exe");
      if (!std::filesystem::exists("bin\\curl.exe"))
        engLang ? std::cout << " Couldn't find curl, auto-update will be limited.\n" : std::cout << " Nie udało się znaleźć curl. Możliwości auto-update będą ograniczone.\n";
      else
        cls();
    }
    if (!std::filesystem::exists("bin\\pasteCmd.exe"))
    {
      if (system("bin\\curl --progress-bar --fail https://raw.githubusercontent.com/DarXe/Logus/experimental/bin/pasteCmd.exe -o bin\\pasteCmd.exe"))
        remove("bin\\pasteCmd.exe");
      cls();
    }
  }
}

void checkLogusUpdate()
{
  int fail = 0;
  std::fstream check;
  std::string repoVersion;
  engLang ? std::cout << " Checking updates, please wait...\n" : std::cout << " Sprawdzanie aktualizacji. Proszę czekać...\n";
  if (updateChannel == "release")
    fail = system("bin\\curl --progress-bar --fail https://raw.githubusercontent.com/DarXe/Logus/master/version -o version.tmp");
  else if (updateChannel == "experimental" || updateChannel == "nightly")
    fail = system("bin\\curl --progress-bar --fail https://raw.githubusercontent.com/DarXe/Logus/experimental/version_experimental -o version.tmp");

  if (fail)
  {
    remove("version.tmp");
    return;
  }

  cls();
  check.open("version.tmp");

  long long repoVersionNumber = 0;
  if (check.good())
  {
    getline(check, repoVersion);
    try
    {
      repoVersionNumber = stoll(repoVersion);
    }
    catch (...)
    {
      engLang ? std::cout << " Error while checking version \"" << repoVersion << "\".\n" : std::cout << " Błąd podczas sprawdzania wersji \"" << repoVersion << "\".\n";
      return;
    }
    if (repoVersionNumber == getLogusBuildVersion())
    {
      engLang ? std::cout << " Checking successful! Logus is up to date.\n" : std::cout << " Sprawdzanie powiodło się! Posiadasz najnowszą wersję.\n";
      return;
    }
    else if (repoVersionNumber < getLogusBuildVersion())
    {
      engLang ? std::cout << " Checking successful! Logus is newer than the version in the repository.\n" : std::cout << " Sprawdzanie powiodło się! Posiadasz wersją nowszą niż ta obecna w repozytorium.\n";
      return;
    }
  }
  else
  {
    engLang ? std::cout << " Couldn't find curl, auto update will not be possible.\n" : std::cout << " Nie udało się znaleźć curl. Aktualizacja nie będzie możliwa.\n";
    return;
  }

  if (updateChannel == "release" && repoVersionNumber > getLogusBuildVersion())
  {
    engLang ? std::cout << " Updating Logus, please wait...\n" : std::cout << " Aktualizowanie Logusia. Proszę czekać...\n";
    rename("Logus.exe", "Logusold.exe");
    Stopwatch rele;
    fail = system("bin\\curl --progress-bar --fail --location https://github.com/DarXe/Logus/releases/latest/download/Logus.exe -o Logus.exe");
    rele.stop();
    LDebug::DebugOutput("Pobieranie Logus (release): wersja: %s, czas: %s", {repoVersion, rele.pre(ms)});
  }
  else if ((updateChannel == "experimental" || updateChannel == "nightly") && repoVersionNumber > getLogusBuildVersion())
  {
    if (updateChannel == "nightly")
      updateChannel = "experimental";
    engLang ? std::cout << " Updating Logus, please wait...\n" : std::cout << " Aktualizowanie Logusia. Proszę czekać...\n";
    rename("Logus.exe", "Logusold.exe");
    Stopwatch exp;
    fail = system("bin\\curl --progress-bar --fail --location https://raw.githubusercontent.com/DarXe/Logus/experimental/Logus.exe -o Logus.exe");
    exp.stop();
    LDebug::DebugOutput("Pobieranie Logus (experimental): wersja: %s, czas: %s", {repoVersion, exp.pre(ms)});
  }
  if (fail)
  {
    engLang ? std::cout << " Update unsuccessful!\n" : std::cout << " Aktualizacja nie powiodła się!\n";
    remove("Logus.exe");
    rename("Logusold.exe", "Logus.exe");
  }
  else
  {
    engLang ? std::cout << " Update successful! Restart Logus to finish the installation.\n" : std::cout << " Aktualizacja powiodła się! Zrestartuj Logusia aby dokończyć aktualizację.\n";
  }

  check.close();
  remove("version.tmp");
}

void checkUpdates()
{
  SetConsoleTextAttribute(h, 10);
  if (getVer() != getLogusBuildVersion())
  {
    saveConfig(0);
    showUpdateInfo();
    remove("Logusold.exe");
  }
  else
  {
    if (updateChannel != "disable")
      checkLogusUpdate();
  }
}