// Copyright © 2018-2020  DarXe, Niventill



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

void stopAutoJoin(bool &isAutoJoin)
{
	isAutoJoin = false;
	pos.X=3; pos.Y=4; SetConsoleCursorPosition(h, pos);
	SetConsoleTextAttribute(h, 12); std::cout<<"       CONNECTED!       ";
	Beep(dzwiekGlowny, 500);
}