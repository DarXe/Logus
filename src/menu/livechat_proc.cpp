// Copyright (C) 2018-2020  DarXe, Niventill

void startTimer(short getSeconds)
{
	Beep(dzwiekGlowny, 100);
	delay = clock();
	if(getSeconds)
	{
		timer = getSeconds*1000;
	}
	else
	{
		timer = czas*1000;
		if(random) timer += 300000; else timer += 360000;
		isCzas = 1;
	}
	isTimer = 1;
	pos.X=0; pos.Y=2; SetConsoleCursorPosition(h, pos);
	SetConsoleTextAttribute(h, 170); std::cout<<" "; SetConsoleTextAttribute(h, 12);
	std::cout<<" Timer 0:00  [s]Stop Timer   ";
}

void stopTimer()
{
	Beep(dzwiekGlowny, 500);
	isTimer = 0;
	isCzas = 0;
	timer = 0;
	pos.X=0; pos.Y=2; SetConsoleCursorPosition(h, pos);
	SetConsoleTextAttribute(h, 204); std::cout<<" "; SetConsoleTextAttribute(h, 12);
}

void salaryForTransport(std::string &line, bool &ptsLang)
{
	if(ptsLang)
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
			zapis(0);
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
			zapis(0);
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
			zapis(0);
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
			zapis(0);
		}
	}
}

bool liveChatBeep(std::string &ostatniaLinia) //bee
{
	//wiadomość pw
	if(!fLockPW){
		if(fPwOd(ostatniaLinia, ptsLang))
		{
			//open the gate
			if(fOpen(ostatniaLinia))
			{
				system("start bin\\pasteCmd.exe");
				toClipboard("open");
				
				Beep(dzwiekGlowny,400);
				Beep(0,interval);

				std::fstream info;
				info.open("logusInfoOutput.log", std::ios::app);
					info<<ostatniaLinia<<std::endl;
				info.close();
				return 1;
			}
			//other PM
			Beep(dzwiekGlowny,300);
			Beep(0,interval);
			Beep(dzwiekGlowny,300);
			Beep(0,interval);

			std::fstream info;
			info.open("logusInfoOutput.log", std::ios::app);
				info<<ostatniaLinia<<std::endl;
			info.close();
			return 1;
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
			
			std::fstream info;
			info.open("logusInfoOutput.log", std::ios::app);
				info<<ostatniaLinia<<std::endl;
			info.close();
			return 1;
		}
	}

	//nick z czatu dodany do ulubionych
	if(!fLockNick)
	{
		if(fNicknames(ostatniaLinia))
		{
			Beep(dzwiekGlowny,300);
			Beep(0,interval);
			return 1;
		}
	}

	//dostarczenie towaru, raport z frakcji
	if(!fLockKomunikat)
	{
		if(fTransport(ostatniaLinia, ptsLang))
		{
			salaryForTransport(ostatniaLinia, ptsLang);
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
			
			std::fstream info;
			info.open("logusInfoOutput.log", std::ios::app);
				info<<ostatniaLinia<<std::endl;
			info.close();
			return 1;
		}

		if(fKomunikat(ostatniaLinia, ptsLang))
		{
			Beep(dzwiekGlowny,150);
			Beep(0,interval);
			Beep(dzwiekGlowny,150);
			Beep(0,interval);
			Beep(dzwiekGlowny,150);
			Beep(0,interval);
			
			std::fstream info;
			info.open("logusInfoOutput.log", std::ios::app);
				info<<ostatniaLinia<<std::endl;
			info.close();
			return 1;
		}
	}

	//przelewy
	if(fPrzelewyOd(ostatniaLinia, ptsLang))
	{
		Beep(dzwiekGlowny,400);
		Beep(0,interval);

		std::fstream info;
		info.open("logusInfoOutput.log", std::ios::app);
			info<<ostatniaLinia<<std::endl;
		info.close();
		return 1;
	}
	
	//klawisz zbindowany pod błąd /bind <key> <your_nick> msg x
	//aktualna funkcja - start timera
	if(fBindKey(ostatniaLinia))
	{
		if(isTimer)
		{
			stopTimer();
			std::fstream info;
			info.open("logusInfoOutput.log", std::ios::app);
				info<<ostatniaLinia.substr(0, 33)<<"Timer - STOP"<<std::endl;
			info.close();
		}
		else
		{
			startTimer();
			std::fstream info;
			info.open("logusInfoOutput.log", std::ios::app);
				info<<ostatniaLinia.substr(0, 33)<<"Timer - START"<<std::endl;
			info.close();
		}
		return 1;
	}

	char _quit = fConsoleInput(ostatniaLinia);
	if(_quit)
	{
		Beep(dzwiekGlowny,100);
		Beep(0,interval);
		if(_quit == 2) return 0; //close Logus
	}

	if(chatSound) 
	{
		Beep(750,50);
		timer -= 50; //darxe po co to?
	}

	return 1;
}