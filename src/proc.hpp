// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef PROC_HPP_INCLUDED
#define PROC_HPP_INCLUDED


//standard libraries
#include <string>


//forward declarations
void color(std::string value);

void serverConnect();

bool runLiveChat();

bool closeLogus(std::string text = "Bye bye");

void dots(short duration, short amount);

int cfgInputInt(bool preHead, bool isCls, std::string text = "", std::string inputText = "", std::string errorText = "", std::string minMaxText = "", int min = 0, int max = 0);

std::string cfgInputString(bool preHead, bool isCls, std::string text = "", std::string inputText = "", std::string errorText = "");

int cfgSelection(bool preHead,
				std::string Question = "",
				std::string Answer = "",
				std::string Answer2 = "",
				std::string Answer3 = "",
				std::string Answer4 = "");

std::string cfgSelectionStr(std::string Question = "",
			std::string Answer = "",
			std::string Answer2 = "",
			std::string Answer3 = "",
			std::string Answer4 = "",
			std::string Answer5 = "",
			std::string Answer6 = "",
			std::string Answer7 = "");

void preConfig();


#endif