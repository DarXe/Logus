// Copyright (C) 2018-2020  DarXe, Niventill


void liveChatHead(int lineCount = 0) //head
{
	pos.X=0; pos.Y=0; SetConsoleCursorPosition(h, pos);
	SetConsoleTextAttribute(h, 12);
	std::cout<<"###############################LiveChat###############################"<<std::endl;
	SetConsoleTextAttribute(h, 204); std::cout<<" "; SetConsoleTextAttribute(h, 12);
	std::cout<<" Refresh:"<<refresh<<"ms"<<" # Wierszy:"<<lineCount-1<<" # Errors:"<<errors<<" #  [ESC]Return to MENU    "<<std::endl;
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
	std::cout<<"\n################################################"<<"#####[m]moveLogs()####"<<std::endl;
}

void getChat(int &lineCount)//gc
{
	std::fstream file;
	std::string line;

	liveChatHead(lineCount);

	file.open("console.log");
		//pobranie linii, które nie mają być wyświetlone
		for(int i = 0; i < lineCount-wyswietlaneWiersze-1; i++)
		{
			getline(file, line);
		}
		//bug fix
		if((lineCount-1)<=wyswietlaneWiersze)
		{
			temp2 = wyswietlaneWiersze;
			wyswietlaneWiersze = lineCount-1;
		}
		//wyświetlenie pozostałych linii
		for(int i = 0; i < wyswietlaneWiersze; i++)
		{
			getline(file, line);
			bool notif = fNicknames(line)||fTransport(line,ptsLang)||fKomunikat(line,ptsLang)||fPrzelewyOd(line,ptsLang)||fPwOd(line,ptsLang)||fTeam(line,0);
			if(notif)
			{
				if(timestamps)
				{
					SetConsoleTextAttribute(h, 160); std::cout<<" "<<line<<std::endl;
				}
				else
				{
					SetConsoleTextAttribute(h, 160); std::cout<<"=>";
					SetConsoleTextAttribute(h, 10);
					if(line.length() > gt)
						line = line.erase(0, gt);		
					for (size_t i = 0; i < line.length(); i++)
					{
						if(line[i] == ':')
						{
							std::cout<<line[i];
							SetConsoleTextAttribute(h, 15);
							continue;
						}
						std::cout<<line[i];
					} std::cout<<"\n";
				}
			}
			else
			{
				if(timestamps)
				{
					SetConsoleTextAttribute(h, 170); std::cout<<" ";
					SetConsoleTextAttribute(h, 10); std::cout<<line<<std::endl;
				}
				else
				{
					if(line.length() > gt)
						line = line.erase(0, gt);	
					if(line[0] == '*')
					{
						SetConsoleTextAttribute(h, 14);
						std::cout<<line<<std::endl;
					}
					else
					{
						SetConsoleTextAttribute(h, 10);
						for (size_t i = 0; i < line.length(); i++)
						{
							if(line[i] == ':')
							{
								std::cout<<line[i];
								SetConsoleTextAttribute(h, 15);
								continue;
							}
							std::cout<<line[i];
						} std::cout<<"\n";
					}
				}
			}
		}
		if((lineCount-1)<=wyswietlaneWiersze) wyswietlaneWiersze = temp2;//bug fix
	file.close();
	pos.X=0; pos.Y=0; SetConsoleCursorPosition(h, pos);
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

	cls();
	liveChatHead();
	pos.X=2; pos.Y=5; SetConsoleCursorPosition(h, pos);
	SetConsoleTextAttribute(h, 15);
	std::cout<<"Brak wierszy po przeniesieniu logow!";
}

bool liveChat(int &wyswietlaneWiersze) //lc
{
	bool isAutoJoin = false;
	std::string ostatniaLinia[11]; //ostatnie linie
	int lineCount = 0;
	std::fstream file;
	std::string line;

	if(isTimer) delay = clock();

	file.open("console.log");
		while(!file.eof())
		{
			getline(file,line);
			++lineCount;
		}
		file.close();
	getChat(lineCount);

	if(isTimer) timer -= (clock()-delay);
	while(true)
	{   
		if(isTimer) delay = clock();
		
		lineCount = 0;
		//counting lines in a log file
		file.open("console.log");
			while(!file.eof())
			{
				getline(file,line);
				++lineCount;
			}
		file.close();
		//saving information about the number of lines in an auxiliary variable
		temp = lineCount;

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

		if(dynamicRefresh && refresh<950 && !kbhit()) refresh+=5;

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
					std::cout<<"CZY NA PEWNO CHCESZ PRZENIESC LOGI z console.log DO PLIKU logus.log?\nESC - Anuluj | Inny klawisz - zgoda"<<std::endl;
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

		liveChatHead(lineCount);
		pos.X=0; pos.Y=0; SetConsoleCursorPosition(h, pos);
		
		lineCount = 0;
		//counting lines in a log file after a time interval
		file.open("console.log");
			while(!file.eof())
			{
				getline(file,line);
				++lineCount;
			}
			file.clear();
			file.seekg(std::ios::beg); //instead of file.close() and file.open() go to begin line

		temp = lineCount-temp; //difference in the number of lines
		//if it is different, it means that a new message has appeared

		if(isTimer) timer -= (clock()-delay);

		if(temp > 0)
		{
			if(isTimer) delay = clock();

				if(lineCount <= 10)
				{
					switch (lineCount) //bug fix
					{
					case 10:
						getline(file, ostatniaLinia[9]);
					case 9:
						getline(file, ostatniaLinia[8]);
					case 8:
						getline(file, ostatniaLinia[7]);
					case 7:
						getline(file, ostatniaLinia[6]);
					case 6:
						getline(file, ostatniaLinia[5]);
					case 5:
						getline(file, ostatniaLinia[4]);
					case 4:
						getline(file, ostatniaLinia[3]);
					case 3:
						getline(file, ostatniaLinia[2]);
					case 2:
						getline(file, ostatniaLinia[1]);
					case 1: //tests
					{
						std::fstream error;
						error.open("logusErrors.log", std::ios::app);
							error<<">>>>>>>>>>ERROR NR "<<errors<<"<<<<<<<<<<"<<std::endl;
							error<<"TYPE: ???\n";
					}
						break;
					default:
						{
							errors++;
							//saving errors
							std::fstream error;
							error.open("logusErrors.log", std::ios::app);
								error<<">>>>>>>>>>ERROR NR "<<errors<<"<<<<<<<<<<"<<std::endl;
								error<<"TYPE: PRE\n";
								error<<"ROWS: "<<lineCount<<"\n";
								error<<"Refresh: "<<refresh<<"\n";
								error<<"Temp: "<<temp<<"\n";
								error<<"Lck: "<<fLockTeam<<fLockPW<<fLockKomunikat<<fLockNick<<chatSound<<"\n";
								error<<"LAST(9)\n";
								for (size_t i = 9; i >= 1; i--)
								{
									error<<i<<". "<<ostatniaLinia[i]<<std::endl;
								}
								std::cout<<std::endl;
							error.close();
						}
						break;
					}
				}
				else
				{
					for(int i = 0; i < lineCount-10; i++) getline(file, ostatniaLinia[10]);
					//capturing last lines
					for(int i = 9; i > 0; i--) {getline(file, ostatniaLinia[i]);}
				}
			file.close();

			if(chatSound) {Beep(750,50); timer -= 50;} //the sound of each new chat message
			if(dynamicRefresh && refresh > 300) refresh-=50; //if a new message appears, reduce the refresh rate by 100ms

			cls(); getChat(lineCount); //chat display

			//19.07.21 loops removed, only cases
			switch (temp)
			{
			case 10:
				if(!liveChatBeep(ostatniaLinia[10])) return 0;
			case 9:
				if(!liveChatBeep(ostatniaLinia[9])) return 0;
			case 8:
				if(!liveChatBeep(ostatniaLinia[8])) return 0;
			case 7:
				if(!liveChatBeep(ostatniaLinia[7])) return 0;
			case 6:
				if(!liveChatBeep(ostatniaLinia[6])) return 0;
			case 5:
				if(!liveChatBeep(ostatniaLinia[5])) return 0;
			case 4:
				if(!liveChatBeep(ostatniaLinia[4])) return 0;
			case 3:
				if(!liveChatBeep(ostatniaLinia[3])) return 0;
			case 2:
				if(!liveChatBeep(ostatniaLinia[2])) return 0;
			case 1:
				if(!liveChatBeep(ostatniaLinia[1])) return 0;
				break;
			default:
				{
					errors++;
					std::fstream error;
					error.open("logusErrors.log", std::ios::app);
						error<<">>>>>>>>>>ERROR NR "<<errors<<"<<<<<<<<<<"<<std::endl;
						error<<"TYPE: POST\n";
						error<<"ROWS: "<<lineCount<<"\n";
						error<<"Refresh: "<<refresh<<"\n";
						error<<"Temp: "<<temp<<"\n";
						error<<"Lck: "<<fLockTeam<<fLockPW<<fLockKomunikat<<fLockNick<<chatSound<<"\n";
						error<<"LAST(10)\n";
						for (size_t i = 10; i >= 1; i--)
						{
							error<<i<<". "<<ostatniaLinia[i]<<std::endl;
						}
						std::cout<<std::endl;
					error.close();
				}
				break;
			}

			if(isAutoJoin)
			{
				switch (temp)
				{
				case 10:
					if(ostatniaLinia[10][gt] != 'c') stopAutoJoin(isAutoJoin);
				case 9:
					if(ostatniaLinia[9][gt] != 'c') stopAutoJoin(isAutoJoin);
				case 8:
					if(ostatniaLinia[8][gt] != 'c') stopAutoJoin(isAutoJoin);
				case 7:
					if(ostatniaLinia[7][gt] != 'c') stopAutoJoin(isAutoJoin);
				case 6:
					if(ostatniaLinia[6][gt] != 'c') stopAutoJoin(isAutoJoin);
				case 5:
					if(ostatniaLinia[5][gt] != 'c') stopAutoJoin(isAutoJoin);
				case 4:
					if(ostatniaLinia[4][gt] != 'c') stopAutoJoin(isAutoJoin);
				case 3:
					if(ostatniaLinia[3][gt] != 'c') stopAutoJoin(isAutoJoin);
				case 2:
					if(ostatniaLinia[2][gt] != 'c') stopAutoJoin(isAutoJoin);
				case 1:
					if(ostatniaLinia[1][gt] != 'c') stopAutoJoin(isAutoJoin);
					break;
				
				default:
					break;
				}
			}

			if(autoMoveLogs && (lineCount > autoMoveLogs)) moveLogs();
			if(isTimer) timer -= (clock()-delay);
		}//if
		else file.close(); //fix
	}//while
	return 1;
}//liveChat()