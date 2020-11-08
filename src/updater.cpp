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
#include "ver.hpp"
#include "updater.hpp"


void updateDependencies()
{
	if (!std::filesystem::exists("bin")) std::filesystem::create_directory("bin");
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

void checkLogusUpdate()
{
	if (updateChannel == "release")
	{
		engLang? std::cout << " Checking updates, please wait...\n" : std::cout << " Sprawdzanie aktualizacji. Proszę czekać...\n";
		system("bin\\curl --progress-bar https://raw.githubusercontent.com/DarXe/Logus/master/version -o version.tmp");
		std::fstream check;
		std::string versc;
		check.open("version.tmp");
		if (check.good())
		{
			getline(check, versc);
			if (versc != ver)
			{
				engLang ? std::cout << " Updating Logus, please wait...\n" : std::cout << " Aktualizowanie Logusia. Proszę czekać...\n";
				rename("Logus.exe", "Logus1.exe");
				if (system("bin\\curl --progress-bar --fail --location https://github.com/DarXe/Logus/releases/latest/download/Logus.exe -o Logus.exe"))
				{
					engLang ? std::cout << " Update unsuccessful!\n" : std::cout << " Aktualizacja nie powiodła się!\n";
					remove("Logus.exe");
					rename("Logus1.exe", "Logus.exe");
				}
				else
				{
					engLang ? std::cout << " Update successful! Restart Logus to finish the installation.\n" :
					std::cout << " Aktualizacja powiodła się! Zrestartuj Logusia aby dokończyć aktualizację.\n";
				}
			}
			else
			{
				engLang ? std::cout << " Checking successful! Logus is up to date.\n" :
					std::cout << " Sprawdzanie powiodło się! Posiadasz najnowszą wersję.\n";
			}
		}
		check.close();
		remove("version.tmp");
	}
	else if (updateChannel == "experimental" || updateChannel == "nightly")
	{
		if (updateChannel == "nightly")
			updateChannel = "experimental";
		engLang? std::cout << " Checking updates, please wait...\n" : std::cout << " Sprawdzanie aktualizacji. Proszę czekać...\n";
		system("bin\\curl --progress-bar https://raw.githubusercontent.com/DarXe/Logus/experimental/version -o version.tmp");
		std::fstream check;
		std::string versc;
		check.open("version.tmp");
		if (check.good())
		{
			getline(check, versc);
			if (versc != ver)
			{
				engLang ? std::cout << " Updating Logus, please wait...\n" : std::cout << " Aktualizowanie Logusia. Proszę czekać...\n";
				rename("Logus.exe", "Logus1.exe");
				if (system("bin\\curl --progress-bar --fail --location https://raw.githubusercontent.com/DarXe/Logus/experimental/Logus.exe -o Logus.exe"))
				{
					engLang ? std::cout << " Update unsuccessful!\n" : std::cout << " Aktualizacja nie powiodła się!\n";
					remove("Logus.exe");
					rename("Logus1.exe", "Logus.exe");
				}
				else
				{
					engLang ? std::cout << " Update successful! Restart Logus to finish the installation.\n" :
					std::cout << " Aktualizacja powiodła się! Zrestartuj Logusia aby dokończyć aktualizację.\n";
				}
				
			}
			else
			{
				engLang ? std::cout << " Checking successful! Logus is up to date.\n" :
					std::cout << " Sprawdzanie powiodło się! Posiadasz najnowszą wersję.\n";
			}
		}
		check.close();
		remove("version.tmp");
	}
}

void checkUpdates()
{
	if (getVer() != ver)
	{
		saveConfig(0);
		showUpdateInfo();
		remove("Logus1.exe");
	}
	else
	{
		if (updateChannel != "disable")
			checkLogusUpdate();
	}
}