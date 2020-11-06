// Copyright © 2018-2020  DarXe
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef _COMMON_HPP
#define _COMMON_HPP


//standard libraries
#include <string>
#include <iosfwd>
#define q(var) std::cout << #var << " = " << var << '\n'


//foward declarations
std::string getCurrentTime();

std::string getMTALocation();

std::string getNickFromMTAConfig();

std::string removeSpaces(std::string &line);

std::string round(const long double x, const int dec);

int randomize(int from, int to);

void clslegacy();

void cls();

void clsa();

char wybor();

void def();

void toClipboard(const std::string &s);

int power(int x, int y);

std::string utf8_substr(const std::string &str, int start, int length = INT_MAX);

#endif