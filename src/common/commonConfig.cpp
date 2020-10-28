// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//standard libraries
#include <iostream>
#include <windows.h>
#include <conio.h>


//header includes
#include "common.hpp"
#include "var.hpp"
#include "commonConfig.hpp"


int cfgInput(bool preHead, bool isCls, std::string text, std::string inputText, std::string errorText, std::string minMaxText, int min, int max)
{
	int temp;
	if (isCls)
		cls();
	if (preHead)
		std::cout << " _______________________Logus_pre-config_______________________\n";
	std::cout << " " << text << "\n";
	std::cout << " " << inputText << " ";
	std::cin >> temp;
	while (std::cin.fail() || temp < min || temp > max)
	{
		cls();
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		SetConsoleTextAttribute(h, 12);
		if (preHead)
			std::cout << " _______________________Logus_pre-config_______________________\n";
		SetConsoleTextAttribute(h, 10);
		std::cout << " " << errorText << "\n";
		std::cout << " " << minMaxText << "\n";
		std::cout << " " << inputText << " ";
		std::cin >> temp;
	}
	return temp;
}

std::string cfgInput(bool preHead, bool isCls, std::string text, std::string inputText, std::string errorText)
{
	std::string temp;
	if (isCls)
		cls();
	if (preHead)
		std::cout << " _______________________Logus_pre-config_______________________\n";
	if (text != "")
		std::cout << " " << text << "\n";
	std::cout << " " << inputText << " ";
	getline(std::cin, temp);
	while (std::cin.fail())
	{
		cls();
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		SetConsoleTextAttribute(h, 12);
		if (preHead)
			std::cout << " _______________________Logus_pre-config_______________________\n";
		SetConsoleTextAttribute(h, 10);
		std::cout << " " << errorText << "\n";
		std::cout << " " << inputText << " ";
		std::cin >> temp;
	}
	return temp;
}

int cfgSelection(bool preHead,
				 std::string Question,
				 std::string Answer,
				 std::string Answer2,
				 std::string Answer3,
				 std::string Answer4)
{
	bool sel = 1;
	do
	{
		cls();
		SetConsoleTextAttribute(h, 12);
		if (preHead)
			std::cout << " _______________________Logus_pre-config_______________________\n";
		SetConsoleTextAttribute(h, 10);
		if (Question != "")
			std::cout << " " << Question << "\n";
		if (Answer != "")
			std::cout << " [1] " << Answer << "\n";
		if (Answer2 != "")
			std::cout << " [2] " << Answer2 << "\n";
		if (Answer3 != "")
			std::cout << " [3] " << Answer3 << "\n";
		if (Answer4 != "")
			std::cout << " [4] " << Answer4 << "\n";

		switch (getch())
		{
		case '1':
		{
			if (Answer == "")
			{
				sel = 0;
				break;
			}
			else
			{
				sel = 1;
				return 1;
			}
		}
		case '2':
		{
			if (Answer2 == "")
			{
				sel = 0;
				break;
			}
			else
			{
				sel = 1;
				return 2;
			}
		}
		case '3':
		{
			if (Answer3 == "")
			{
				sel = 0;
				break;
			}
			else
			{
				sel = 1;
				return 3;
			}
		}
		case '4':
		{
			if (Answer4 == "")
			{
				sel = 0;
				break;
			}
			else
			{
				sel = 1;
				return 4;
			}
		}
		default:
		{
			sel = 0;
			break;
		}
		}
	} while (!sel);
	return 0;
}

std::string cfgSelectionStr(std::string Question,
							std::string Answer,
							std::string Answer2,
							std::string Answer3,
							std::string Answer4,
							std::string Answer5,
							std::string Answer6,
							std::string Answer7)
{
	bool sel = 1;
	cls();
	do
	{
		SetConsoleTextAttribute(h, 12);
		SetConsoleTextAttribute(h, 10);
		if (Question != "")
			std::cout << " " << Question << "\n";
		if (Answer != "")
			std::cout << " [1] " << Answer << "\n";
		if (Answer2 != "")
			std::cout << " [2] " << Answer2 << "\n";
		if (Answer3 != "")
			std::cout << " [3] " << Answer3 << "\n";
		if (Answer4 != "")
			std::cout << " [4] " << Answer4 << "\n";
		if (Answer5 != "")
			std::cout << " [5] " << Answer5 << "\n";
		if (Answer6 != "")
			std::cout << " [6] " << Answer6 << "\n";
		if (Answer7 != "")
			std::cout << " [7] " << Answer7 << "\n";

		switch (getch())
		{
		case '1':
		{
			if (Answer == "")
			{
				sel = 0;
				break;
			}
			else
			{
				sel = 1;
				return Answer;
			}
		}
		case '2':
		{
			if (Answer2 == "")
			{
				sel = 0;
				break;
			}
			else
			{
				sel = 1;
				return Answer2;
			}
		}
		case '3':
		{
			if (Answer3 == "")
			{
				sel = 0;
				break;
			}
			else
			{
				sel = 1;
				return Answer3;
			}
		}
		case '4':
		{
			if (Answer4 == "")
			{
				sel = 0;
				break;
			}
			else
			{
				sel = 1;
				return Answer4;
			}
		}
		case '5':
		{
			if (Answer5 == "")
			{
				sel = 0;
				break;
			}
			else
			{
				sel = 1;
				return Answer5;
			}
		}
		case '6':
		{
			if (Answer6 == "")
			{
				sel = 0;
				break;
			}
			else
			{
				sel = 1;
				return Answer6;
			}
		}
		case '7':
		{
			if (Answer7 == "")
			{
				sel = 0;
				break;
			}
			else
			{
				sel = 1;
				return Answer7;
			}
		}
		default:
		{
			return "WYJŚCIE";
		}
		}
	} while (!sel);
	return 0;
}