// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef LC_HPP_INCLUDED
#define LC_HPP_INCLUDED


//standard libraries
#include <deque>
#include <vector>
#include <string>


//foward variable declarations
extern std::deque <std::string> lastLines;
extern std::vector <std::string> newLines;
extern int lcLineCount;
extern bool isNewLine, isNewBeep;
extern std::ifstream filelc;
extern std::string linelc;
extern std::uintmax_t size;


//forward function declarations
void liveChatHead();
void showChat();
void getChat(bool init = 0);
void moveLogs();
void checkNotifications();
bool liveChat();


#endif