// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef LC_HPP_INCLUDED
#define LC_HPP_INCLUDED


//standard libraries
#include <deque>
#include <vector>
#include <string>


//forward function declarations

class Status
{
	const std::string stat[8] = {"―", "\\", "|", "/", "―", "\\", "|", "/"};
	short pos = 0;
public:
	std::string get();
};

void liveChatHead();
void cpuMeter(const bool &bypass = false);
void statusMeter();
void showChat();
void forceLiveChatReload();
void getChat(const bool &init = false);
void moveLogs();
void checkMessages(const bool &pre);
bool liveChatInput();
bool liveChat();


#endif