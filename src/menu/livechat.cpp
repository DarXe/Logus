// Copyright © 2018-2020  DarXe, Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#include <fstream>
#include <windows.h>
#include <filesystem>
#include <iostream>
#include <conio.h>
#include <thread>

#include "livechat_proc.hpp"
#include "livechat_func.hpp"
#include "..\var.hpp"
#include "..\config.hpp"
#include "..\common.hpp"
#include "..\proc.hpp"
#include "livechat.hpp"

std::deque <std::string> lastLines;
std::vector <std::string> newLines;
int lcLineCount;
bool isNewLine = 0, isNewBeep = 0;
std::ifstream filelc;
std::string linelc;
std::uintmax_t size;

void liveChatHead() //head
{
	std::string sizet; float sizei = size;
	if (size > 1000000)
	{
		sizei /= 1000000;
		sizet = "MB";
	}
	else
	{
		sizei /= 1000;
		sizet = "KB";
	}
	pos.X=0; pos.Y=0; SetConsoleCursorPosition(h, pos);
	SetConsoleTextAttribute(h, 12);
	std::cout<<"###############################LiveChat###############################\n";
	SetConsoleTextAttribute(h, 204); std::cout<<" "; SetConsoleTextAttribute(h, 12);
	std::cout<<" Refresh:"<<refresh<<"ms"<<" # Wierszy:"<<lcLineCount<<" # Rozmiar:"<<std::setprecision(3)<<sizei<<sizet<<" # [Esc] Menu \n";
	if(isTimer)
	{
		SetConsoleTextAttribute(h, 170); std::cout<<" "; SetConsoleTextAttribute(h, 12);
		std::cout<<" Timer "<<timer/1000/60;
		if((timer/1000)%60<10) std::cout<<":0"; else std::cout<<":";
		std::cout<<(timer/1000)%60<<"  [s]Stop Timer # F4 ";
	}
	else
	{
		SetConsoleTextAttribute(h, 204); std::cout<<" "; SetConsoleTextAttribute(h, 12);
		std::cout<<" [t]Timer                  # F4 ";
	}
	std::cout<<"$"<<money<<" # Kursy:"<<courses<<" # Śr $"<<((courses)?money/courses:0)<<"       ";
	SetConsoleTextAttribute(h, 204); std::cout<<"\n "; SetConsoleTextAttribute(h, 12);
	int payment(0); payment = ((money>0)?((money*0.87)-3500)*grade:0);
	std::cout<<track[trackId]<<"              # "<<"Wypłata $"<<payment<<" # Min $"<<minsalary<<" # Max $"<<maxsalary;
	SetConsoleTextAttribute(h, 204);
	pos.X=69; pos.Y=1; SetConsoleCursorPosition(h, pos); std::cout<<" ";
	pos.X=69; pos.Y=2; SetConsoleCursorPosition(h, pos); std::cout<<" ";
	pos.X=69; pos.Y=3; SetConsoleCursorPosition(h, pos); std::cout<<" ";
	SetConsoleTextAttribute(h, 12);
	std::cout<<"\n################################################"<<"#####[m]moveLogs()####\n";
}

void showChat()
{
	std::string nline;
	cls();
	liveChatHead();
	for(int i = 0; i<lastLines.size(); i++)
	{
		nline = lastLines.at(i);
		bool notif = fNicknames(nline)||fTransport(nline)||fKomunikat(nline)||fPrzelewyOd(nline)||fPwOd(nline)||fTeam(nline,0);
		if(notif)
		{
			SetConsoleTextAttribute(h, 160); std::cout<<"=>";
			SetConsoleTextAttribute(h, 10);
			if(nline.length() > gt)
				nline = nline.erase(0, gt);		
			for (size_t i = 0; i < nline.length(); i++)
			{
				if(nline[i] == ':')
				{
					std::cout<<nline[i];
					SetConsoleTextAttribute(h, 15);
					continue;
				}
				std::cout<<nline[i];
			} std::cout<<"\n";
		}
		else
		{
			if(nline.length() > gt)
				nline = nline.erase(0, gt);	
			if(nline[0] == '*')
			{
				SetConsoleTextAttribute(h, 14);
				std::cout<<nline<<std::endl;
			}
			else
			{
				SetConsoleTextAttribute(h, 10);
				for (size_t i = 0; i < nline.length(); i++)
				{
					if(nline[i] == ':')
					{
						std::cout<<nline[i];
						SetConsoleTextAttribute(h, 15);
						continue;
					}
					std::cout<<nline[i];
				} std::cout<<"\n";
			}
		}
	}
}

void getChat(bool init)//gc
{
	if (init) //if it's init, open filelc first
		filelc.open(consoleLogPath, std::ios::in | std::ios::binary);
	while (!filelc.eof()) 
	{	
		getline(filelc, linelc); //get linelc
		if (filelc.eof()) //if above getline returns eof, do break
			break;
		
		if (lastLines.size() >= wyswietlaneWiersze) //if array size exceds wyswietlaneWiersze size remove first element from aray
			lastLines.pop_front();
		lastLines.push_back(linelc); //add element to the end of array
		++lcLineCount;
		if (!init) //if eof isn't present (as there is a new linelc) AND it's not init = 1 save newlines
		{
			newLines.push_back(linelc); //add new lines to another array
			isNewLine = 1;
		}
	}
}

void moveLogs()//mv clean and move logs from console.log to logus.log
{
	std::ofstream to;

	//check filelc size and then load filelc content into string
		auto read = std::chrono::high_resolution_clock::now();
	std::ifstream from(consoleLogPath, std::ios::binary);
	std::string fromContent(size,0);
	from.read(&fromContent[0],size);
	from.close();
		auto read1 = std::chrono::high_resolution_clock::now();
		auto readshow = std::chrono::duration_cast<std::chrono::nanoseconds>(read1 - read).count();

	//clear console.log
		auto clearl = std::chrono::high_resolution_clock::now();
	std::ofstream clear;
	clear.open(consoleLogPath, std::ios::out | std::ios::trunc);
	clear.close();
	//goto beginning of the console.log
	filelc.clear();
	filelc.seekg (0, std::ios::beg);
	lcLineCount = 0;
		auto clearl1 = std::chrono::high_resolution_clock::now();
		auto clearlshow = std::chrono::duration_cast<std::chrono::nanoseconds>(clearl1 - clearl).count();

		auto write = std::chrono::high_resolution_clock::now();
	to.open("logus.log", std::ios::binary | std::ios::app);
	to.write(fromContent.c_str(), size);
	to.close();
		auto write1 = std::chrono::high_resolution_clock::now();
		auto writeshow = std::chrono::duration_cast<std::chrono::nanoseconds>(write1 - write).count();

	//save moveLogs time to filelc liveChatInfoOutput.log
	std::ofstream save;
	save.open("debugInfoOutput.log", std::ios::out | std::ios::binary | std::ios::app);
	save << getCurrentTime() <<"moveLogs: wielkość pliku: " << size/1000 << "KB, odczyt: " 
		 << readshow << "ns (" << readshow/1000000 << "ms), czyszczenie: "
		 << clearlshow << "ns (" << clearlshow/1000000 << "ms), zapis: "
		 << writeshow << "ns (" << writeshow/1000000 << "ms), łączny czas: "
		 << readshow+writeshow+clearlshow << "ns ("
		 << std::chrono::duration_cast<std::chrono::milliseconds>(write1 - write).count() +
			std::chrono::duration_cast<std::chrono::milliseconds>(read1 - read).count() + 
			std::chrono::duration_cast<std::chrono::milliseconds>(clearl1 - clearl).count() << "ms)\n";
	save.close();
	size = std::filesystem::file_size(consoleLogPath);
}

void checkNotifications()
{
	if (newLines.size() > 1000)
		for(int i = newLines.size() - 1000; i < newLines.size(); i++)
		{
			liveChatBeep(newLines.at(i));
			if(kbhit())
			{
				if(getch() == 27)
					break;
			}
		}
	else
		for(int i = 0; i < newLines.size(); i++)
		{
			liveChatBeep(newLines.at(i));
			if(kbhit())
			{
				if(getch() == 27)
					break;
			}
		}
}


bool liveChat() //lc
{
	//reset some things
	lastLines.clear();
	lastLines.shrink_to_fit();
	lcLineCount = 0;
	bool isAutoJoin = false;
	//load logs without checking notifications
	auto initspeed = std::chrono::high_resolution_clock::now();
	getChat(1);
	auto initspeed1 = std::chrono::high_resolution_clock::now();
	auto initspeedshow = std::chrono::duration_cast<std::chrono::nanoseconds>(initspeed1 - initspeed).count();

	auto initshowspeed = std::chrono::high_resolution_clock::now();
	size = std::filesystem::file_size(consoleLogPath);
	showChat();
	auto initshowspeed1 = std::chrono::high_resolution_clock::now();
	auto initshowspeedshow = std::chrono::duration_cast<std::chrono::nanoseconds>(initshowspeed1 - initshowspeed).count();

	std::ofstream save;
	save.open("debugInfoOutput.log", std::ios::out | std::ios::binary | std::ios::app);
	save << getCurrentTime() <<"initLiveChat: wielkość pliku: " << size/1000 
		<< "KB, linie: " << lcLineCount << ", odczyt: " 
		<< initspeedshow << "ns (" << initspeedshow/1000000 << "ms), wyświetlanie: "
		<< initshowspeedshow << "ns (" << initshowspeedshow/1000000 << "ms), łączny czas: "
		<< initspeedshow+initshowspeedshow << "ns ("
		<< std::chrono::duration_cast<std::chrono::milliseconds>(initspeed1 - initspeed).count() +
			std::chrono::duration_cast<std::chrono::milliseconds>(initshowspeed1 - initshowspeed).count() << "ms)\n";
	save.close();
	//end

	if(isTimer)
	{
		delay = clock();
		timer -= (clock()-delay);
	}

	while(true) //actual livechat infinite loop
	{
		if(isTimer) delay = clock();

		getChat();
		if (isNewLine)
		{
			isNewLine = 0;
			if(dynamicRefresh)
			{
				for(int i = 0; i<newLines.size(); i++)
				{
					if(refresh <= minRefresh)
					{
						refresh = minRefresh;
						break;
					}
					refresh -= 50;
				}
			}
			std::ifstream refreshf(consoleLogPath, std::ios::in | std::ios::binary);
			refreshf.close();
			size = std::filesystem::file_size(consoleLogPath);
			showChat();
			checkNotifications();
			if (_quit == 2)
			{
				filelc.close();
				return 0;
			}
		}
		else
		{
			if(dynamicRefresh)
			{
				if(refresh < maxRefresh)
				{
					refresh += 25;
					liveChatHead();
				}
				else if (refresh != maxRefresh)
				{
					refresh = maxRefresh;
					liveChatHead();
				}
				else if ((refresh == maxRefresh) && isTimer)
					liveChatHead();
			}
			else
				liveChatHead();
		}

		if(autoMoveLogs)
			{
				if (size >= 99000)
					moveLogs();
			}

		//darxe's shit
		if(!isAutoJoin)
		{
			for(int i(0); i<20; i++) //wait time
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(refresh/20));
				if(kbhit()) break;
			}
		}
		else
		{
			serverConnect();
			for(int i(5); i>0; i--) //wait 5s
			{
				pos.X=3; pos.Y=4; SetConsoleCursorPosition(h, pos);
				SetConsoleTextAttribute(h, 12); std::cout<<" autoJoin: trying to connect in "<<i<<"s ";
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				if(kbhit()) break;
			}
		}

		//if key pressed
		if (kbhit())
		{
			switch (getch())
			{
			case 27:
			{
				cls();
				filelc.close();
				return 1;
			}
			case 't':
				startTimer();
				break;
			case 's':
				stopTimer();
				liveChatHead();
				break;
			case 'm':
			{
				cls();
				std::cout << "CZY NA PEWNO CHCESZ PRZENIESC LOGI z console.log DO PLIKU logus.log?\nESC - Anuluj | Inny klawisz - zgoda\n";
				if (getch() == 27)
					break;
				showChat();
				moveLogs();
			}
			break;
			case 48: //48? it's funny, because it's 0 :D //clear track
			{
				trackId = trackId ? 0 : 1;
				liveChatHead();
				break;
			}
			case 13: //enter start autoJoin
			{
				isAutoJoin = true;
				pos.X = 3;
				pos.Y = 4;
				SetConsoleCursorPosition(h, pos);
				SetConsoleTextAttribute(h, 12);
				std::cout << "    START autoJoin    ";
				Beep(dzwiekGlowny, 750);
			}
			break;
			case 'v': //save
			{
				pos.X = 10;
				pos.Y = 0;
				SetConsoleCursorPosition(h, pos);
				Beep(dzwiekGlowny, 100);
				std::cout << "ZAPISANO!";
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				saveConfig(0);
			}
			break;
			case 'r': //read
			{
				pos.X = 10;
				pos.Y = 0;
				SetConsoleCursorPosition(h, pos);
				Beep(dzwiekGlowny, 100);
				std::cout << "WCZYTANO!";
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				readConfig(0);
			}
			break;
			default:
			{
				std::cout << '\a';
				break;
			}
			}
		}

		//timer countdown
		if(isTimer)
		{
			if(timer>0)
			{
				timer -= (clock()-delay);
				delay = clock();
				if(isCzas)
				{
					if(random)
					{
						if(timer<300000)
						{
							Beep(dzwiekGlowny,150);
							Beep(0,interval);
							Beep(dzwiekGlowny+50,150);
							Beep(0,interval);
							Beep(dzwiekGlowny+100,150);
							Beep(0,interval);
							isCzas = 0;
						}
					}
					else
					{
						if(timer<360000)
						{
							Beep(dzwiekGlowny,150);
							Beep(0,interval);
							Beep(dzwiekGlowny+50,150);
							Beep(0,interval);
							Beep(dzwiekGlowny+100,150);
							Beep(0,interval);
							isCzas = 0;
						}
					}
				}
			}
			else
			{
				Beep(dzwiekGlowny-100,150);
				Beep(0,interval);
				Beep(dzwiekGlowny-50,150);
				Beep(0,interval);
				Beep(dzwiekGlowny,150);
				Beep(0,interval);
				isTimer = 0;
				pos.X=0; pos.Y=2; SetConsoleCursorPosition(h, pos);
				std::cout<<"  [t]Timer                     ";
			}
		}

		//end of darxe's shit
		if (isAutoJoin)
		{
			std::string tempLine;
			for(int i = 0; i<newLines.size(); i++)
			{
				tempLine = newLines.at(i);
				if(tempLine[gt] != 'c')
				{
					stopAutoJoin(isAutoJoin);
				}
			}
		}
		newLines.clear();
		if (newLines.capacity() > 100000)
			newLines.shrink_to_fit();
		filelc.clear();
		filelc.sync();
		if(isTimer) timer -= (clock()-delay);
	}
	filelc.close();
	return 1;
}//liveChat()