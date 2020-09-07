// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//standard libraries
#include <filesystem>
#include <iostream>
#include <fstream>


//header includes
#include "config.hpp"
#include "var.hpp"
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
			engLang? std::cout<<"Couldn't find curl, auto-update will be limited.\n":
			std::cout<<"Nie udało się znaleźć curl. Możliwości auto-update będą ograniczone.\n";
	}
}

void checkLogusUpdate()
{
	if (updateChannel == "release")
	{
		system("bin\\curl --silent https://raw.githubusercontent.com/DarXe/Logus/master/version -o version.tmp");
		std::fstream check; std::string versc;
		check.open("version.tmp");
		if (check.good())
		{
			getline(check, versc);
			if (versc.find(":") == std::string::npos && versc != ver)
			{
				rename("Logus.exe", "Logus1.exe");
				system("bin\\curl --silent --location https://github.com/DarXe/Logus/releases/latest/download/Logus.exe -o Logus.exe");
			}
		}
		check.close();
	}
	else if (updateChannel == "nightly")
	{
		system("bin\\curl --silent https://raw.githubusercontent.com/DarXe/Logus/experimental/version -o version.tmp");
		std::fstream check; std::string versc;
		check.open("version.tmp");
		if (check.good())
		{
			check >> versc;
			if (versc != ver)
			{
				rename("Logus.exe", "Logus1.exe");
				system("bin\\curl --silent --location https://raw.githubusercontent.com/DarXe/Logus/experimental/Logus.exe -o Logus.exe");
			}
		}
		check.close();
	}
	else if (updateChannel == "pre-release")
	{
		system("bin\\curl --silent https://raw.githubusercontent.com/DarXe/Logus/master/version -o version.tmp");
		std::fstream check; std::string versc;
		check.open("version.tmp");
		if (check.good())
		{
			check >> versc;
			if (versc != ver)
			{
				rename("Logus.exe", "Logus1.exe");
				system("bin\\curl --silent --location https://raw.githubusercontent.com/DarXe/Logus/master/Logus.exe -o Logus.exe");
			}
		}
		check.close();
	}
	remove("version.tmp");
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