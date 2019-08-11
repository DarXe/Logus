// Copyright (C) 2018-2019  DarXe
//func

void startTimer(short getSeconds)
{
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
	SetConsoleTextAttribute(h, 170); cout<<" "; SetConsoleTextAttribute(h, 12);
	cout<<" Timer 0:00  [s]Stop Timer   ";
}

//[2019-06-28 11:58:25] [Input]  : test
bool fConsoleInput(string &linia)//fci
{
	if(linia[gt-10]=='I')
	{
		if(linia[gt]=='r'&&linia[gt+1]!='e') //r /reconnect
		{
			s_temp = "start mtasa://"+mtasa;
			system(s_temp.c_str());
			return 1;
		}
		else if(linia[gt]=='t'&&linia[gt+1]!='e') //t START TIMER
		{
			if(linia[gt+1] == 't')//tt START TIMER waga 100%
			{
				startTimer(0);
				int temp;
				temp = czas * 1000 / 1.1;
				temp = czas * 1000 - temp;
				timer -= temp;
			}
			else startTimer(0);
			return 1;
		}
		else if(linia[gt]=='s'&&linia[gt+1]=='e'&&linia[gt+2]=='t')
		{
			if(linia[gt+4]=='t'&&linia[gt+5]=='r') //set tr xx //SET TRACK
			{
				if(linia[gt+7]=='0')
				{
					trackId = 0;
					return 1;
				}
				else if(linia[gt+7]=='a')
				{
					if(linia[gt+8]=='1') trackId = 1;
					else trackId = 3;
					return 1;
				}
				else
				{
					if(linia[gt+8]=='1') trackId = 4;
					else trackId = 2;
					return 1;
				}
				return 0;
			}
			else if(linia[gt+4]=='t') //set t m:ss || set t m ss //SET TIMER
			{
				int liczba; int temp;
				if(linia[gt+5]=='t')
				{
					liczba = linia[gt+7];//min
					liczba -= 48; temp = liczba*600;
					liczba = linia[gt+8];//min
					liczba -= 48; temp += liczba*60;
					liczba = linia[gt+10];//sec
					liczba -= 48; temp += liczba*10;
					liczba = linia[gt+11];//sec
					liczba -= 48; temp += liczba;
				}
				else
				{
					liczba = linia[gt+6];//min
					liczba -= 48; temp = liczba*60;
					liczba = linia[gt+8];//sec
					liczba -= 48; liczba *=10; temp += liczba;
					liczba = linia[gt+9];//sec
					liczba -= 48; temp += liczba;
				}
				startTimer(temp);
				return 1;
			}
			else if(linia[gt+4]=='n')
			{
				if(linia[gt+6]=='a'&&linia[gt+7]=='d'&&linia[gt+8]=='d')
				{
					return 1;
				}
				else if(linia[gt+6]=='d'&&linia[gt+7]=='e'&&linia[gt+8]=='l')
				{
					return 1;
				}
				else return 0;
			}
			else return 0;
		}
		else return 0;
	}
	else return 0;
}

void nrPliku(int nr)
{
	if(nr != 10)
	{
		if(!nr)
			cout<<">>>>>>>>>>>>>>>>>>>> logus.log <<<<<<<<<<<<<<<<<<<<"<<endl;
		else
			cout<<">>>>>>>>>>>>>>>>>>>> Plik nr "<<nr<<" <<<<<<<<<<<<<<<<<<<<"<<endl;
	}
}

int all(string &nazwa, int nr)
{
	int iloscLinijek = 0;
	nrPliku(nr);

	fstream plik;
	plik.open(nazwa.c_str());
		while(!plik.eof())
		{
			getline(plik,linia);
			iloscLinijek++;
		}
	plik.close();

	return iloscLinijek;
}

int teamsay(string &nazwa, int nr)
{
	//randomColor();
	int iloscLinijek = 0;
	nrPliku(nr);

	fstream plik;
	plik.open(nazwa.c_str());
		while(!plik.eof())
		{
			getline(plik,linia);
			if(fTeam(linia, 1))
			{
				cout<<++iloscLinijek<<linia<<endl;
				if(iloscLinijek%30 == 0)
				{
					cout<<"PLIK "<<nr<<" [ESC] "<<((!nr)?"Wyjscie":"Nastepny plik")<<" | Nastepne 30 wierszy... (dowolny klawisz)"<<endl;
					if(getch() == 27)
					{
						cls();
						while(!plik.eof())
						{
							getline(plik,linia);
							if(fTeam(linia, 1)) iloscLinijek++;
						}
						break;
					}
					cls();
				}
			}
		}
	plik.close();

	return iloscLinijek;
}

int pw(string &nazwa, int nr)
{
	//randomColor();
	int iloscLinijek = 0;
	nrPliku(nr);

	fstream plik;
	plik.open(nazwa.c_str());
		while(!plik.eof())
		{
			getline(plik,linia);
			if(fPwOd(linia, ang)||fPwDo(linia))
			{
				cout<<++iloscLinijek<<linia<<endl;
				if(iloscLinijek%30 == 0)
				{
					cout<<"PLIK "<<nr<<" [ESC] "<<((!nr)?"Wyjscie":"Nastepny plik")<<" | Nastepne 30 wierszy... (dowolny klawisz)"<<endl;
					if(getch() == 27)
					{
						cls();
						while(!plik.eof())
						{
							getline(plik,linia);
							if(fPwOd(linia, ang)||fPwDo(linia)) iloscLinijek++;
						}
						break;
					}
					cls();
				}
			}
		}
	plik.close();

	return iloscLinijek;
}

int przelewy(string &nazwa, int nr)
{
	//randomColor();
	int iloscLinijek = 0;
	nrPliku(nr);

	fstream plik;
	plik.open(nazwa.c_str());
		while(!plik.eof())
		{
			getline(plik,linia);
			if(fPrzelewyOd(linia, ang)||fPrzelewyDo(linia, ang))
			{
				cout<<++iloscLinijek<<linia<<endl;
				if(iloscLinijek%30 == 0)
				{
					cout<<"PLIK "<<nr<<" [ESC] "<<((!nr)?"Wyjscie":"Nastepny plik")<<" | Nastepne 30 wierszy... (dowolny klawisz)"<<endl;
					if(getch() == 27)
					{
						cls();
						while(!plik.eof())
						{
							getline(plik,linia);
							if(fPrzelewyOd(linia, ang)||fPrzelewyDo(linia, ang)) iloscLinijek++;
						}
						break;
					}
					cls();
				}
			}
		}
	plik.close();

	return iloscLinijek;
}

/*int nickname(string &nazwa, int nr)
{
	//randomColor();
	int iloscLinijek = 0;
	nrPliku(nr);
	fstream plik;
	plik.open(nazwa.c_str());
		while(!plik.eof())
		{
			plik>>linia>>linia>>linia>>linia; //wyrazy
			if(fNick(linia))
			{
				cout<<++iloscLinijek<<linia<<endl;
				if(iloscLinijek%30 == 0)
				{
					cout<<"PLIK "<<nr<<" [ESC] "<<((!nr)?"Wyjscie":"Nastepny plik")<<" | Nastepne 30 wierszy... (dowolny klawisz)"<<endl;
					if(getch() == 27)
					{
						cls();
						while(!plik.eof())
						{
							getline(plik,linia);
							if(fPrzelewyOd(linia, ang)||fPrzelewyDo(linia, ang)) iloscLinijek++;
						}
						break;
					}
					cls();
				}
			}
		}
	plik.close();

	return iloscLinijek;
}
*/
// HANDLE hIcon = LoadImage(NULL, "icon.ico",IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
// HANDLE hIconSm = LoadImage(NULL, "icon.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
// SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM) hIcon);
// SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM) hIconSm);