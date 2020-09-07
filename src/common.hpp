// Copyright © 2018-2020  DarXe
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef _COMMON_HPP
#define _COMMON_HPP


//standard libraries
#include <string>


//foward declarations
std::string getCurrentTime();

std::string getMTALocation();

std::string getNickFromMTAConfig();

std::string removeSpaces(std::string &line);

int losuj(int from, int to);

void cls();

char wybor();

void def();

void toClipboard(const std::string &s);

int power(int x, int y);


#endif