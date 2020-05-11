// Copyright (C) 2018-2019  DarXe
#include <climits>

int intError(int &number)
{
	while (!(cin>>number))
    {
      std::cout<<"\n\aERRROR! Podales litere/y!"<<std::endl;
			cin.clear(); // clear input buffer to restore cin to a usable state
			cin.ignore(INT_MAX, '\n'); // ignore last input
			cout << "Ta opcja wymaga podania liczby..\n";
			cout << "Spróbuj ponownie: ";
    }
  return number;
}

void color(string value)
{
	string value0 = "color 0"+value;
	system(value0.c_str());
}

void infoOuput()
{
	
}

void salaryForTransport(string &line, bool &ang)
{
	if(ang)
	{
		if(line[gt+19] == '.')
		{
			int liczba, mnoz=1000;
			for(int i = 48; i<52; i++)//57 58 59 60 61 $xxxx
			{
				liczba = line[i];
				liczba -= 48;
				money += liczba*mnoz;
				mnoz /= 10;
			}
			courses++;
			zapis();
		}
		else if(line[gt+18] == '.')
		{
			int liczba, mnoz=100;
			for(int i = 48; i<51; i++)//57 58 59 60 $xxx
			{
				liczba = line[i];
				liczba -= 48;
				money += liczba*mnoz;
				mnoz /= 10;
			}
			courses++;
			zapis();
		}
	}
	else
	{
		if(line[61] == '$')
		{
			int liczba, mnoz=1000;
			for(int i = 57; i<61; i++)//57 58 59 60 61 xxxx$
			{
				liczba = line[i];
				liczba -= 48;
				money += liczba*mnoz;
				mnoz /= 10;
			}
			courses++;
			zapis();
		}
		else if(line[60] == '$')
		{
			int liczba, mnoz=100;
			for(int i = 57; i<60; i++)//57 58 59 60 xxx$
			{
				liczba = line[i];
				liczba -= 48;
				money += liczba*mnoz;
				mnoz /= 10;
			}
			courses++;
			zapis();
		}
	}
}

bool liveChatBeep(string &ostatniaLinia) //bee
{
	//wiadomość pw
	if(!fLockPW){
		if(fPwOd(ostatniaLinia, ang))
		{
			Beep(dzwiekGlowny,300);
			Beep(0,interval);
			Beep(dzwiekGlowny,300);
			Beep(0,interval);

			fstream info;
			info.open("logusInfoOutput.log", ios::app);
				info<<ostatniaLinia<<std::endl;
			info.close();
		}
	}

	//wiadomość teamowa
	if(!fLockTeam)
	{
		if(fTeam(ostatniaLinia, 0))
		{
			Beep(dzwiekGlowny,150);
			Beep(0,interval);
			Beep(dzwiekGlowny,150);
			Beep(0,interval);
			
			fstream info;
			info.open("logusInfoOutput.log", ios::app);
				info<<ostatniaLinia<<std::endl;
			info.close();
		}
	}

	//dostarczenie towaru, raport z frakcji
	if(!fLockKomunikat)
	{
		if(fTransport(ostatniaLinia, ang))
		{
			salaryForTransport(ostatniaLinia, ang);
			if(trackId)
			{
				if(trackId == 4) trackId = 1;
				else trackId++;
			}
			Beep(dzwiekGlowny,150);
			Beep(0,interval);
			Beep(dzwiekGlowny,150);
			Beep(0,interval);
			Beep(dzwiekGlowny,150);
			Beep(0,interval);
			
			fstream info;
			info.open("logusInfoOutput.log", ios::app);
				info<<ostatniaLinia<<std::endl;
			info.close();
		}
		else if(fKomunikat(ostatniaLinia, ang))
		{
			Beep(dzwiekGlowny,150);
			Beep(0,interval);
			Beep(dzwiekGlowny,150);
			Beep(0,interval);
			Beep(dzwiekGlowny,150);
			Beep(0,interval);
			
			fstream info;
			info.open("logusInfoOutput.log", ios::app);
				info<<ostatniaLinia<<std::endl;
			info.close();
		}
	}

	//nick z czatu dodany do ulubionych
	if(!fLockNick)
	{
		if(fNicknames(ostatniaLinia))
		{
			Beep(dzwiekGlowny,300);
			Beep(0,interval);
		}
	}

	char _quit = fConsoleInput(ostatniaLinia);
	if(_quit)
	{
		Beep(dzwiekGlowny,100);
		Beep(0,interval);
		if(_quit == 2) return 0; //close Logus
	}

	return 1;
}

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
	else      std::cout<<"Dostarczone kursy: "<<courses<<"                                             ";
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
	fstream file;
	string line;

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
			if(fNicknames(line)||fTransport(line,ang)||fKomunikat(line,ang)||fPrzelewyOd(line,ang)||fPwOd(line,ang)||fTeam(line,0))
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

void moveLogs()//mv clean and move logs mtasarom console.log to logus.log
{
	fstream from;
	fstream to;
	string line;
	int count = 0;

	from.open("console.log");
		while(!from.eof())
		{
			getline(from, line);
			count++;
		}
		count--;
		from.clear();
		from.seekg(ios::beg);

		vector <string> logs(count);
		to.open("logus.log", ios::app);
			for(string line : logs)
			{
				getline(from, line);
				to<<line<<std::endl;
			}
		to.close();
	from.close();

	from.open("console.log", ios::out);
	from.close();

	cls();
	liveChatHead();
	pos.X=2; pos.Y=5; SetConsoleCursorPosition(h, pos);
	SetConsoleTextAttribute(h, 15);
	std::cout<<"Brak wierszy po przeniesieniu logow!";
}

bool runLiveChat()//flc
{
	s_temp = "start mtasa://"+mtasa;
	system(s_temp.c_str());
	cls();
	Beep(dzwiekGlowny,100);
	bool _quit = liveChat(wyswietlaneWiersze);
	if(!_quit) return 0;
	return 1;
}

void serverConnect()//flc
{
	s_temp = "start mtasa://"+mtasa;
	system(s_temp.c_str());
}

void stopAutoJoin(bool &isAutoJoin)
{
	isAutoJoin = false;
	pos.X=3; pos.Y=4; SetConsoleCursorPosition(h, pos);
	SetConsoleTextAttribute(h, 12); std::cout<<"       CONNECTED!       ";
	Beep(dzwiekGlowny, 500);
}

bool closeLogus(string text = "Bye bye")
{
	cls();
	zapis();
	Beep(dzwiekGlowny-100,250);
	std::cout<<"\n"<<text;
	for(int i = 0; i<4; i++){
		std::cout<<".";
		if(i == 2) {Beep(dzwiekGlowny,200); continue;}
		Sleep(400);
	}
	Beep(dzwiekGlowny+100,250);
	return 0;
}