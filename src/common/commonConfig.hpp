// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


#ifndef COMMONCONFIG_HPP_INCLUDED
#define COMMONCONFIG_HPP_INCLUDED


//standard libraries
#include <string>


int cfgInput(bool preHead, bool isCls, std::string text, std::string inputText, std::string errorText, std::string minMaxText, int min = 0, int max = 0);

std::string cfgInput(bool preHead, bool isCls, std::string text, std::string inputText, std::string errorText);

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


#endif