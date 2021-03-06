// Copyright © 2018-2020  DarXe
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#ifndef _COMMON_HPP
#define _COMMON_HPP

//standard libraries
#include <string>
#include <deque>
#include <iosfwd>
#include <string_view>
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
char wybor();
void def();
void toClipboard(const std::string &s);
int power(int x, int y);
std::string_view utf8_substr(const std::string_view str, int start, int length = INT_MAX);
int GetCursorPosX();
short GetConsoleRows();
int utf8_size(const std::string &line);
int utf8_size(const std::string_view line);
bool lcompare(std::string_view line, std::string_view value);

#endif