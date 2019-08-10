// Copyright (C) 2018-2019  DarXe

void intError()
{
	cerr<<"\n\aERRROR! Podales litere/y!"<<endl;
	cout<<"Program wylaczy sie, uruchom go ponownie"<<endl;
	if(fastStart == 1)
	{
		cout<<"\nMasz wlaczona funkcje fastStart!"<<endl;
		cout<<"Program automatycznie wylaczy funkcje 'szybki start' w celu uniknienia"<<endl;
		cout<<"ponownego polaczenia ze serwerem"<<endl;
		fastStart = 0;
		zapis();
	}
	getch();
}

void color(string value)
{
	string value0 = "color 0"+value;
	system(value0.c_str());
}

void salaryForTransport(string &linia, bool &ang)
{
	if(ang)
	{
		if(linia[gt+19] == '.')
		{
			int liczba, mnoz=1000;
			for(int i = 48; i<52; i++)//57 58 59 60 61 $xxxx
			{
				liczba = linia[i];
				liczba -= 48;
				money += liczba*mnoz;
				mnoz /= 10;
			}
			courses++;
			zapis();
		}
		else if(linia[gt+18] == '.')
		{
			int liczba, mnoz=100;
			for(int i = 48; i<51; i++)//57 58 59 60 $xxx
			{
				liczba = linia[i];
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
		if(linia[61] == '$')
		{
			int liczba, mnoz=1000;
			for(int i = 57; i<61; i++)//57 58 59 60 61 xxxx$
			{
				liczba = linia[i];
				liczba -= 48;
				money += liczba*mnoz;
				mnoz /= 10;
			}
			courses++;
			zapis();
		}
		else if(linia[60] == '$')
		{
			int liczba, mnoz=100;
			for(int i = 57; i<60; i++)//57 58 59 60 xxx$
			{
				liczba = linia[i];
				liczba -= 48;
				money += liczba*mnoz;
				mnoz /= 10;
			}
			courses++;
			zapis();
		}
	}
}

void liveChatBeep(string &ostatniaLinia) //bee
{
	//wiadomość pw
	if(!fLockPW){
		if(fPwOd(ostatniaLinia, ang))
		{
			Beep(dzwiekGlowny,300);
			Beep(0,interval);
			Beep(dzwiekGlowny,300);
			Beep(0,interval);
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
		}
	}

	//dostarczenie towaru, raport z frakcji
	if(!fLockKomunikat)
	{
		if(fTransport(ostatniaLinia, ang)||fKomunikat(ostatniaLinia, ang))
		{
			if(fTransport(ostatniaLinia, ang))
			{
				salaryForTransport(ostatniaLinia, ang);
				if(trackId)
				{
					if(trackId == 4) trackId = 1;
					else trackId++;
				}
			}
			Beep(dzwiekGlowny,150);
			Beep(0,interval);
			Beep(dzwiekGlowny,150);
			Beep(0,interval);
			Beep(dzwiekGlowny,150);
			Beep(0,interval);
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

	if(fConsoleInput(ostatniaLinia))
	{
		Beep(dzwiekGlowny,100);
		Beep(0,interval);
	}
}

void getChat(int &iloscLinijek)//gc
{
	pos.X=0; pos.Y=0; SetConsoleCursorPosition(h, pos);
	SetConsoleTextAttribute(h, 12);
	cout<<"###############################LiveChat###############################"<<endl;
	SetConsoleTextAttribute(h, 204); cout<<" "; SetConsoleTextAttribute(h, 12);
	cout<<" Refresh:"<<refresh<<"ms"<<" # Wierszy:"<<iloscLinijek-1<<" # Errors:"<<errors<<" #  [ESC]Return to MENU    "<<endl;
	if(isTimer)
	{
		SetConsoleTextAttribute(h, 170); cout<<" "; SetConsoleTextAttribute(h, 12);
		cout<<" Timer "<<timer/1000/60;
		if((timer/1000)%60<10) cout<<":0"; else cout<<":";
		cout<<(timer/1000)%60<<"  [s]Stop Timer # F4 ";
	}
	else 
	{
		SetConsoleTextAttribute(h, 204); cout<<" "; SetConsoleTextAttribute(h, 12);
		cout<<" [t]Timer                  # F4 ";
	}
	if(courses) cout<<"$"<<money<<" # Courses:"<<courses<<" # Avg $"<<money/courses<<"                  ";
	else      cout<<"Dostarczone kursy: "<<courses<<"                                             ";
	SetConsoleTextAttribute(h, 204); cout<<"\n "; SetConsoleTextAttribute(h, 12);
	cout<<" [Tab]Timestamps #"<<track[trackId]<<" # "<<"Payment $"<<((money)?((money*0.87)-3500)*grade:0);
	SetConsoleTextAttribute(h, 204);
	pos.X=69; pos.Y=1; SetConsoleCursorPosition(h, pos); cout<<" ";
	pos.X=69; pos.Y=2; SetConsoleCursorPosition(h, pos); cout<<" ";
	pos.X=69; pos.Y=3; SetConsoleCursorPosition(h, pos); cout<<" ";
	SetConsoleTextAttribute(h, 12);
	cout<<"\n################################################"<<"#####[m]moveLogs()####"<<endl;

	plik.open("console.log");
		//pobranie linii, które nie mają być wyświetlone
		for(int i = 0; i < iloscLinijek-wyswietlaneWiersze-1; i++)
		{
			getline(plik, linia);
		}
		//bug fix
		if((iloscLinijek-1)<=wyswietlaneWiersze)
		{
			temp2 = wyswietlaneWiersze;
			wyswietlaneWiersze = iloscLinijek-1;
		}
		//wyświetlenie pozostałych linii
		for(int i = 0; i < wyswietlaneWiersze; i++)
		{
			getline(plik, linia);
			if(fNicknames(linia)||fTransport(linia,ang)||fKomunikat(linia,ang)||fPrzelewyOd(linia,ang)||fPwOd(linia,ang)||fTeam(linia,0))
			{
				if(timestamps)
				{
					SetConsoleTextAttribute(h, 160); cout<<" "<<linia<<endl;
				}
				else
				{
					SetConsoleTextAttribute(h, 10); cout<<"# ";
					SetConsoleTextAttribute(h, 160); cout<<linia.substr(gt)<<endl;
				}
			}
			else
			{
				if(timestamps)
				{
					SetConsoleTextAttribute(h, 170); cout<<" ";
					SetConsoleTextAttribute(h, 10); cout<<linia<<endl;
				}
				else
				{
					SetConsoleTextAttribute(h, 10); cout<<"# "<<linia.substr(gt)<<endl;
				}
			}
		}
		if((iloscLinijek-1)<=wyswietlaneWiersze) wyswietlaneWiersze = temp2;//bug fix
	plik.close();
}

void moveLogs()//mv clean and move logs from console.log to logus.log
{
	fstream from;
	fstream to;
	int count = 0;

	from.open("console.log");
		while(!from.eof())
		{
			getline(from, linia);
			count++;
		}
		count--;
	from.close();

	vector <string> logs(count);
	from.open("console.log");
	to.open("logus.log", ios::app);
		for(string linia : logs)
		{
			getline(from, linia);
			to<<linia<<endl;
		}
	to.close();
	from.close();

	from.open("console.log", ios::out);
	from.close();

	pos.X=2; pos.Y=5; SetConsoleCursorPosition(h, pos);
	SetConsoleTextAttribute(h, 15);
	cout<<"Brak wierszy po przeniesieniu logow!";
}


