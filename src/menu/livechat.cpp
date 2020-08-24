// Copyright (C) 2018-2020  DarXe, Niventill

std::deque <std::string> lastLines, newLines;
int lineCount;
bool isNewLine = 0, isNewBeep = 0;
std::ifstream file;
std::string line;

void liveChatHead() //head
{
	
	pos.X=0; pos.Y=0; SetConsoleCursorPosition(h, pos);
	SetConsoleTextAttribute(h, 12);
	std::cout<<"###############################LiveChat###############################\n";
	SetConsoleTextAttribute(h, 204); std::cout<<" "; SetConsoleTextAttribute(h, 12);
	std::cout<<" Refresh:"<<refresh<<"ms"<<" # Wierszy:"<<lineCount<<" # Errors:"<<errors<<" #  [ESC]Return to MENU    \n";
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
	if(courses) std::cout<<"$"<<money<<" # Courses:"<<courses<<" # Avg $"<<money/courses<<"                  ";
	else      std::cout<<"$"<<0<<" # Courses:"<<0<<" # Avg $"<<0<<"                  ";
	SetConsoleTextAttribute(h, 204); std::cout<<"\n "; SetConsoleTextAttribute(h, 12);
	int payment(0); payment = ((money>0)?((money*0.87)-3500)*grade:0);
	std::cout<<" [Tab]Timestamps #"<<track[trackId]<<" # "<<"Payment $"<<payment;
	SetConsoleTextAttribute(h, 204);
	pos.X=69; pos.Y=1; SetConsoleCursorPosition(h, pos); std::cout<<" ";
	pos.X=69; pos.Y=2; SetConsoleCursorPosition(h, pos); std::cout<<" ";
	pos.X=69; pos.Y=3; SetConsoleCursorPosition(h, pos); std::cout<<" ";
	SetConsoleTextAttribute(h, 12);
	std::cout<<"\n################################################"<<"#####[m]moveLogs()####\n";
}

void moveLogs()//mv clean and move logs from console.log to logus.log
{
	std::fstream from;
	std::fstream to;
	std::string line;
	int count = 0;

	from.open("console.log");
		while(!from.eof())
		{
			getline(from, line);
			count++;
		}
		count--;
		from.clear();
		from.seekg(std::ios::beg);

		std::vector <std::string> logs(count);
		to.open("logus.log", std::ios::app);
			for(std::string line : logs)
			{
				getline(from, line);
				to<<line<<std::endl;
			}
		to.close();
	from.close();

	from.open("console.log", std::ios::out);
	from.close();
	lineCount = 0;
}

void updateLiveChatHead()
{
	tpos = GetConsoleCursorPosition(h);
	liveChatHead();
	SetConsoleCursorPosition(h, tpos);
}

void showChat()
{
	
	std::string nline;
	cls();
	liveChatHead();
	for(int i = 0; i<lastLines.size(); i++)
	{
		nline = lastLines.at(i);
		bool notif = fNicknames(nline)||fTransport(nline,ptsLang)||fKomunikat(nline,ptsLang)||fPrzelewyOd(nline,ptsLang)||fPwOd(nline,ptsLang)||fTeam(nline,0);
		if(notif)
		{
			if(timestamps)
			{
				SetConsoleTextAttribute(h, 160); std::cout<<" "<<nline<<std::endl;
			}
			else
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
		}
		else
		{
			if(timestamps)
			{
				SetConsoleTextAttribute(h, 170); std::cout<<" ";
				SetConsoleTextAttribute(h, 10); std::cout<<nline<<std::endl;
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
}

void getChat(bool init = 0)//gc
{
	
	if (init) //if it's init, open file first
		file.open("console.log", std::ios::in);
	while (!file.eof()) 
	{	
		getline(file, line); //get line
		if (file.eof()) //if above getline returns eof, do break
			break;
		if (lastLines.size() >= wyswietlaneWiersze) //if array size exceds wyswietlaneWiersze size remove first element from aray
			lastLines.pop_front();
		lastLines.push_back(line); //add element to the end of array
		++lineCount;
		if (!init) //if eof isn't present (as there is a new line) AND it's not init = 1 save newlines
		{
			newLines.push_back(line); //add new lines to another array
			isNewLine = 1;
		}
	}
}

void checkNotifications()
{
	for(int i = 0; i<newLines.size(); i++)
	{
		liveChatBeep(newLines.at(i));
	}
}

bool liveChat() //lc
{
	bool isAutoJoin = false;
	//load logs without checking notifications
	getChat(1);
	showChat();
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
					if(refresh <= 10)
					{
						refresh = 10;
						break;
					}
					refresh -= 5;
				}
			}
			std::thread chknotifs(checkNotifications);
			showChat();
			chknotifs.join();
			showChat();
		}
		else
		{
			if(dynamicRefresh)
			{
			if(refresh < 1000)
				refresh += 25;
			else
				refresh = 1000;
			}
			updateLiveChatHead();
		}

		//darxe's shit

		if(!isAutoJoin)
		{
			for(int i(0); i<20; i++) //wait time
			{
				Sleep(refresh/20);
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
				Sleep(5000/5);
				if(kbhit()) break;
			}
		}

		//if key pressed
		if(kbhit())
		{
			switch (getch())
			{
			case 27: cls(); return 1;
			case 't': startTimer(); break;
			case 's': stopTimer(); break;
			case 'm':
				{
					cls();
					std::cout<<"CZY NA PEWNO CHCESZ PRZENIESC LOGI z console.log DO PLIKU logus.log?\nESC - Anuluj | Inny klawisz - zgoda\n";
					if(getch() == 27) {getChat(lineCount); break;}
					moveLogs();
				}
				break;
			case '\t':
				{
					timestamps = ((timestamps)?0:1);
					pos.X=0; pos.Y=4; SetConsoleCursorPosition(h, pos);
					cls(); getChat(lineCount);
				}
				break;
			case 48: //48? it's funny, because it's 0 :D //clear track
				{
					trackId = ((trackId)?0:1);
				}
				break;
			case 13: //enter start autoJoin
			{
				isAutoJoin = true;
				pos.X=3; pos.Y=4; SetConsoleCursorPosition(h, pos);
				SetConsoleTextAttribute(h, 12); std::cout<<"    START autoJoin    ";
				Beep(dzwiekGlowny, 750);
			}
				break;
			case 'v': //save
				{
					pos.X=10; pos.Y=0; SetConsoleCursorPosition(h, pos);
					Beep(dzwiekGlowny, 100);
					std::cout<<"ZAPISANO!"; Sleep(500);
					zapis();
				}
				break;
			case 'r': //read
				{
					pos.X=10; pos.Y=0; SetConsoleCursorPosition(h, pos);
					Beep(dzwiekGlowny, 100);
					std::cout<<"WCZYTANO!"; Sleep(500);
					odczyt();
				}
				break;
			
			default:
				{
					def();
					getChat(lineCount);
				}
				break;
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
		Sleep(refresh);

		if (isAutoJoin)
		{
			std::string tempLine;
			for(int i = 0; i<newLines.size(); i++)
			{
				tempLine = newLines.at(i);
				if(tempLine[gt] != 'c')
				{
					tpos = GetConsoleCursorPosition(h);
					stopAutoJoin(isAutoJoin);
					SetConsoleCursorPosition(h, tpos);
				}
			}
		}
		newLines.clear();
		file.clear();
		file.sync();
		if(autoMoveLogs && (lineCount > autoMoveLogs)) 
		{
			moveLogs();
			file.close();
			file.open("console.log", std::ios::in);
		}
		if(isTimer) timer -= (clock()-delay);
	}
	file.close();
	return 1;
}//liveChat()