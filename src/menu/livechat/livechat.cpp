// Copyright © 2018-2020  DarXe, Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//standard libraries
#include <fstream>
#include <filesystem>
#include <iostream>
#include <conio.h>
#include <thread>
#include <string_view>
#include <future>


//header includes
#include "livechat_eventhandlers.hpp"
#include "livechat_events.hpp"
#include "livechat_cmd.hpp"
#include "livechat_format.hpp"
#include <var.hpp>
#include <config.hpp>
#include <cpu.hpp>
#include <common.hpp>
#include <proc.hpp>
#include <stopwatch.hpp>
#include <debug.hpp>
#include "livechat.hpp"


//variable declarations
static std::deque <std::string> lastLines;
static std::deque <int> lastLinesSize;
static std::vector <std::string> newLines;
static int lcLineCount;
static bool isNewLine = 0;
static std::ifstream filelc;
static std::string linelc;
static std::uintmax_t size;
static bool isAutoJoin;
static CpuUsage cpu;
static Status st;
static int head1 = 0, head2 = 0, head3 = 0;
static int status = 0;
static bool forceRedraw = 0;

std::string Status::get()
{
	if (pos < 7)
		pos++;
	else
		pos = 0;
	return stat[pos];
}

void liveChatHead() //head
{
	std::string sizet; float sizei = size; COORD pos;
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
	std::cout<<"##########################################LiveChat##########################################\n";
	cpuMeter(1);

	pos.X=0; pos.Y=1; SetConsoleCursorPosition(h, pos);
	SetConsoleTextAttribute(h, 204); std::cout<<" "; SetConsoleTextAttribute(h, 12);
	std::cout<<" ["<<st.get()<<"]Refresh:"<<refresh<<"ms # Wierszy:"<<lcLineCount<< " # Rozmiar: "<< std::setprecision(2)<<sizei<<sizet<<" # [Esc] Menu ";
	if (head1-GetCursorPosX() > 0) {std::string h1(head1-GetCursorPosX(), ' '); std::cout << h1;} head1 = GetCursorPosX();
	if(mainTimer.running)
	{
		SetConsoleTextAttribute(h, 170); std::cout<<"\n "; SetConsoleTextAttribute(h, 12);
		std::cout<<" Timer "<<mainTimer.getTime()<<" [s]Stop Timer ";
	}
	else
	{
		SetConsoleTextAttribute(h, 204); std::cout<<"\n "; SetConsoleTextAttribute(h, 12);
		std::cout<<" [t]Timer                  ";
	}

	long long payment = 0; payment = ((money>0)?((money*0.9)-3500)*grade:0);
	std::cout<<"# Zarobek: $"<<money<<" # Kursy: "<<courses<<" # Wypłata: $"<<payment;
	if (head2-GetCursorPosX() > 0){std::string h2(head2-GetCursorPosX(), ' '); std::cout << h2;} head2 = GetCursorPosX();

	SetConsoleTextAttribute(h, 204); std::cout<<"\n "; SetConsoleTextAttribute(h, 12);
	std::cout<<track[trackId]<<"              # "<<"Średnia: $"<<((courses)?money/courses:0)<<" # Min: $"<<minsalary<<" # Max: $"<<maxsalary;
	if (head3-GetCursorPosX() > 0){std::string h3(head3-GetCursorPosX(), ' '); std::cout << h3;} head3 = GetCursorPosX();
	
	SetConsoleTextAttribute(h, 204);
	pos.X=91; pos.Y=1; SetConsoleCursorPosition(h, pos); std::cout<<" ";
	pos.X=91; pos.Y=2; SetConsoleCursorPosition(h, pos); std::cout<<" ";
	pos.X=91; pos.Y=3; SetConsoleCursorPosition(h, pos); std::cout<<" ";
	SetConsoleTextAttribute(h, 12);
	if (renderEngine)
		 std::cout<<"\n####engine:experimental###################################################[m]moveLogs#######\n";
	else std::cout<<"\n####engine:stable#########################################################[m]moveLogs#######\n";
	
}

void cpuMeter(const bool &bypass)
{
	if (cpu.ready() || bypass)
	{
		SetConsoleTextAttribute(h, 12);
		SetConsoleCursorPosition(h, {5, 0});
		std::cout << std::fixed << std::setprecision(2) << "CPU:" << cpu.getCpuUsage() << "%#AVG:" << cpu.getCpuAvg() << '%';
		if (status-GetCursorPosX() > 0)
		{
			std::string s1(status-GetCursorPosX(), '#'); std::cout << s1;
		}
		status = GetCursorPosX();
	}
}

void statusMeter()
{
	cpuMeter();
	SetConsoleTextAttribute(h, 4);
	SetConsoleCursorPosition(h, {3, 1});
	std::cout << st.get();
}

void showChat()
{
	auto f = std::async(std::launch::async, []()
	{
		if (!renderEngine)
			cls();
		liveChatHead();
		LCFormat::ParseLines(lastLines, lastLinesSize, timestamp);
	});
}

void getChat(const bool &init) //gc
{
	if (lastLines.size() > wyswietlaneWiersze) //checks if user bruteforced lower "wyswietlaneWiersze" than is saved in deque
	{
		cls(); //do a full console clean
		forceRedraw = true; //tell livechat to redraw
	}
	else if (wyswietlaneWiersze > 50) //check if user bruteforced higher "wyswietlaneWiersze" than is supported
	{
		cls(); //do a full console clean
		forceRedraw = true; //tell livechat to redraw
		wyswietlaneWiersze = 50; //set "wyswietlaneWiersze" to max supported value
	}
	else if (wyswietlaneWiersze < 10) //check if user bruteforced lower "wyswietlaneWiersze" than is supported
	{
		forceRedraw = true; //tell livechat to redraw
		wyswietlaneWiersze = 10; //set "wyswietlaneWiersze" to max supported value
	}

	while (!filelc.eof())
	{
		getline(filelc, linelc); //get linelc
		if (filelc.eof())
			break;				 //if above getline returns eof, do a break

		std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv; 
		int utfsize = linelc.size()-conv.from_bytes(linelc).size(); //get real string size (utf8)
		if (linelc.size() > 92 + gt + utfsize) //split string to next line if it's too long
		{
			int notif = 0;
			if (notifCheck(linelc)) //offset if "beepable" message is present (as it occupies 2 chars)
				notif = 2;
			lastLines.emplace_back(utf8_substr(linelc, 0, 92 + gt - notif)); 
			lastLines.emplace_back(utf8_substr(linelc, 92 + gt - notif));
		}
		else if (linelc.size() > gt) //if line is fine and isn't too long, just emplace it all
		{
			lastLines.emplace_back(linelc); //add element to the end of array
		}
		while (lastLines.size() > wyswietlaneWiersze)
		{
			lastLines.pop_front();
			++lcLineCount;
		}
		if (!init) //if eof isn't present (as there is a new linelc) AND it's not init = 1 save newlines
		{
			newLines.emplace_back(linelc); //add new lines to another array
			isNewLine = 1;
		}
	}

	if((lastLines.size()+5) > GetConsoleRows())
	{
		clslegacy();
		forceRedraw = true;
	}
}

void moveLogs() //mv clean and move logs from console.log to logus.log
{
	if (size < 1073741824)
	{
		//read console.log
		Stopwatch read;
		size = std::filesystem::file_size(consoleLogPath);
		std::ifstream from(consoleLogPath, std::ios::binary);
		std::string fromContent(size, 0);
		from.read(&fromContent[0], size);
		from.close();
		read.stop();
		//asynchronously write to logus.log
		auto f = std::async(std::launch::async, [&read, &fromContent]
		{
			Stopwatch write;
			std::ofstream to("logus.log", std::ios::binary | std::ios::app);
			to.write(fromContent.c_str(), size);
			to.close();
			write.stop();

			//save moveLogs time to filelc liveChatInfoOutput.log
			LDebug::DebugOutput("moveLogs: wielkość pliku: %sKB, odczyt: %s (%s), zapis: %s (%s), łącznie: %sns (%sms)", 
			{std::to_string(size/1000), read.pre(ns), read.pre(ms, 2), write.pre(ns), write.pre(ms, 2),
			round(read.get(ns) + + write.get(ns), 0), round(read.get(ms) + write.get(ms), 2)});
		});

	}
	else
	{
		Stopwatch copy;
		std::ifstream from(consoleLogPath, std::ios::binary);
		std::ofstream to("logus.log", std::ios::binary | std::ios::app);
		while(true)
		{
			std::string content;
			getline(from, content);
			if (from.eof())
				break;
			to << content << '\n';
		}
		copy.stop();
		//save moveLogs time to filelc liveChatInfoOutput.log
		LDebug::DebugOutput("moveLogs: wielkość pliku: %sKB, łącznie: %s (%s)", {std::to_string(size), copy.pre(ns), copy.pre(ms, 2)});
	}

	//clear console.log
	std::ofstream clear;
	clear.open(consoleLogPath, std::ios::out | std::ios::trunc);
	clear.close();
	//goto beginning of the console.log
	filelc.clear();
	filelc.seekg(0, std::ios::beg);
	lcLineCount = 0;

	size = std::filesystem::file_size(consoleLogPath);
}

void checkMessages(const bool &pre)
{
	if (pre)
	{
		if (newLines.size() > 1000)
			for (int i = newLines.size() - 1000; i < newLines.size(); i++)
			{
				LCCommand::PreCheckCommandInput(newLines[i]);
				if (kbhit())
				{
					if (getch() == 27)
						break;
				}
			}
		else
			for (int i = 0; i < newLines.size(); i++)
			{
				LCCommand::PreCheckCommandInput(newLines[i]);
				if (kbhit())
				{
					if (getch() == 27)
						break;
				}
			}
	}
	else
	{
		if (newLines.size() > 1000)
			for (int i = newLines.size() - 1000; i < newLines.size(); i++)
			{
				LCEventHandler::CheckEventHandlers(newLines[i]);
				if (kbhit())
				{
					if (getch() == 27)
						break;
				}
			}
		else
			for (int i = 0; i < newLines.size(); i++)
			{
				LCEventHandler::CheckEventHandlers(newLines[i]);
				if (kbhit())
				{
					if (getch() == 27)
						break;
				}
			}
	}
}

bool liveChatInput()
{
	if (kbhit())
	{
		COORD pos;
		switch (getch())
		{
		case 27:
		{
			clslegacy();
			filelc.close();
			return 1;
		}
		case 't':
			mainTimer.startCounter();
			break;
		case 's':
			mainTimer.stopCounter();
			liveChatHead();
			break;
		case 'm':
		{
			cls();
			std::cout << "CZY NA PEWNO CHCESZ PRZENIESC LOGI z console.log DO PLIKU logus.log?\nENTER - Zgoda | Inny klawisz - anuluj\n";
			if (getch() != 13)
			{
				forceRedraw = true;
				break;
			}
			forceRedraw = true;
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
			cls();
			std::cout << "CZY NA PEWNO CHCESZ WŁĄCZYĆ AUTO RECONNECT?\nENTER - Zgoda | Inny klawisz - anuluj\n";
			if (getch() != 13)
			{
				forceRedraw = true;
				break;
			}
			forceRedraw = true;
			isAutoJoin = true;
			pos.X = 3;
			pos.Y = 4;
			SetConsoleCursorPosition(h, pos);
			SetConsoleTextAttribute(h, 12);
			std::cout << "####START autoJoin####";
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
	return 0;
}

bool liveChat() //lc
{
	//reset some things
	lastLines.clear();
	lastLines.shrink_to_fit();
	for (int i = 0; i < 50; i++)
		lastLinesSize[i] = 0;
	lcLineCount = 0;
	cpu.clear();
	isAutoJoin = false;
	//init file stream
	filelc.open(consoleLogPath, std::ios::in | std::ios::binary);
	//load logs without checking notifications
	Stopwatch init;
	getChat(1);
	init.stop();

	Stopwatch initshow;
	size = std::filesystem::file_size(consoleLogPath);
	mainTimer.update();
	cls();
	showChat();
	initshow.stop();

	LDebug::DebugOutput("initLiveChat: wielkość pliku: %sKB, linie: %s, odczyt: %s (%s), wyświetlanie: %s (%s), łącznie: %sns (%sms)", 
	{std::to_string(size/1000), std::to_string(lcLineCount), init.pre(ns), init.pre(ms, 2), initshow.pre(ns), initshow.pre(ms, 2),
	round(init.get(ns) + initshow.get(ns), 0), round(init.get(ms) + initshow.get(ms), 2)});
	//end

	while (true) //actual livechat infinite loop
	{
		mainTimer.update();

		getChat();
		if (isNewLine)
		{
			isNewLine = false;
			forceRedraw = false;
			if (dynamicRefresh)
			{
				for (int i = 0; i < newLines.size(); i++)
				{
					if (refresh <= minRefresh)
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
			checkMessages(true);
			showChat();
			checkMessages(false);
		}
		else if (forceRedraw)
		{
			forceRedraw = false;
			showChat();
		}
		else
		{
			if (dynamicRefresh)
			{
				if (refresh < maxRefresh)
				{
					refresh += 25;
					liveChatHead();
				}
				else if (refresh != maxRefresh)
				{
					refresh = maxRefresh;
					liveChatHead();
				}
				else if ((refresh == maxRefresh) && mainTimer.running)
					liveChatHead();
				else
					statusMeter();
			}
			else
				liveChatHead();
		}

		if (autoMoveLogs)
		{
			if (size >= 99000)
				moveLogs();
		}

		if (isAutoJoin)
		{
			std::string tempLine;
			for (int i = 0; i < newLines.size(); i++)
			{
				tempLine = newLines.at(i);
				if (tempLine[gt] != 'c')
				{
					stopAutoJoin(isAutoJoin);
				}
			}
		}

		if (!isAutoJoin)
		{
			for (int i(0); i < 20; i++) //wait time
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(refresh / 20));
				if (kbhit())
					break;
			}
		}
		else
		{
			serverConnect();
			for (int i(15); i > 0; i--) //wait 5s
			{
				SetConsoleCursorPosition(h, {0, 0});
				SetConsoleTextAttribute(h, 12);
				std::cout << "#autoJoin: trying to connect in " << i << "s#";
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				if (kbhit())
					break;
			}
		}

		//if key pressed
		if (liveChatInput())
			return 1;

		mainTimer.beep();

		newLines.clear();
		if (newLines.capacity() > 100000)
		{
			LDebug::DebugOutput("newLinesCapacity: wielkość pliku: %sKB, newLines.capacity() = %s",
			{std::to_string(size / 1000), std::to_string(newLines.capacity())});
			newLines.shrink_to_fit();
		}
		filelc.clear();
		filelc.sync();
	}
	filelc.close();
	return 1;
} //liveChat()