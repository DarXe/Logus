// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#ifndef CONFIG_HPP_INCLUDED
#define CONFIG_HPP_INCLUDED

//standard libraries
#include <string>

//foward declarations
std::string clearConfigValue(std::string &line, std::string cfgname);

void readConfig(bool showInfo = true);

std::string getVer();

void showUpdateInfo();

void saveConfig(bool showInfo = true);

void readDefault();

#endif