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
	std::filesystem::create_directory("bin");
	if (!std::filesystem::exists("bin\\curl.exe"))
	{
		std::filesystem::copy("c:\\windows\\system32\\curl.exe", "bin\\curl.exe");
		system("bin\\curl --silent https://raw.githubusercontent.com/DarXe/Logus/master/pasteCmd.exe -o bin\\pasteCmd.exe");
		if (!std::filesystem::exists("bin\\curl.exe"))
			engLang ? std::cout << " Couldn't find curl, auto-update will be limited.\n" : std::cout << " Nie udało się znaleźć curl. Możliwości auto-update będą ograniczone.\n";
		else
			cls();
	}
	else
		cls();
}

void checkLogusUpdate()
{
	if (updateChannel == "release")
	{
		system("bin\\curl --silent https://raw.githubusercontent.com/DarXe/Logus/master/version -o version.tmp");
		std::fstream check;
		std::string versc;
		check.open("version.tmp");
		if (check.good())
		{
			getline(check, versc);
			if (versc != ver)
			{
				engLang ? std::cout << " Updating Logus, please wait...\n" : std::cout << " Aktualizowanie Logusia. Proszę czekać...\n";
				remove("version.tmp");
				rename("Logus.exe", "Logus1.exe");
				if (system("bin\\curl --silent --fail --location https://github.com/DarXe/Logus/releases/latest/download/Logus.exe -o Logus.exe"))
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
		}
		check.close();
	}
	else if (updateChannel == "nightly")
	{
		system("bin\\curl --silent https://raw.githubusercontent.com/DarXe/Logus/experimental/version -o version.tmp");
		std::fstream check;
		std::string versc;
		check.open("version.tmp");
		if (check.good())
		{
			check >> versc;
			if (versc != ver)
			{
				engLang ? std::cout << " Updating Logus, please wait...\n" : std::cout << " Aktualizowanie Logusia. Proszę czekać...\n";
				rename("Logus.exe", "Logus1.exe");
				remove("version.tmp");
				if (system("bin\\curl --silent --fail --location https://raw.githubusercontent.com/DarXe/Logus/experimental/Logus.exe -o Logus.exe"))
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
		}
		check.close();
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