// Copyright (C) 2018-2019  DarXe

//func
//(team) [pts]nick
bool fTeam(string &linia, bool e) //e - uwzglednianie wlasnego nicku(wspolna funkcja, dlatego wyjatek)
{
	leng = nick.length();
	if(linia[gt]=='('&&linia[gt+1]=='T'&&linia[gt+2]=='E'&&linia[gt+3]=='A'&&linia[gt+4]=='M')
	{
		if(e) return 1;
		if(linia[gt+6+leng]!=nick[leng-1]||linia[gt+5+leng]!=nick[leng-2]||linia[gt+4+leng]!=nick[leng-3])
			return 1;
		else return 0;
	}
	else return 0;
}

bool fPwOd(string &linia, bool &ang)
{
	if(ang)
	{
		if(linia[gt]=='*'&&linia[gt+2]=='P'&&linia[gt+3]=='M')
			return 1;
		else return 0;
	}
	else
	{
		if(linia[gt]=='*'&&linia[gt+2]=='P'&&linia[gt+3]=='W')
			return 1;
		else return 0;
	}
}

bool fPwDo(string &linia)
{
	if(linia[gt]=='-'&&linia[gt+1]=='>')
		return 1;
	else return 0;
}

bool fPrzelewyOd(string &linia, bool &ang)
{
	leng = linia.length();
	if(ang)
	{
		if(linia[gt]=='P'&&linia[gt+1]=='l'&&linia[gt+2]=='a'&&linia[gt+3]=='y'&&linia[gt+4]=='e'&&linia[gt+6]==' '&&linia[leng-2]!='d'&&linia[leng-1]=='.'&&(linia[leng-3]!=' '&&linia[leng-5]!='e'))
			return 1;
		else return 0;
	}
	else
	{
		if(linia[gt]=='G'&&linia[gt+1]=='r'&&linia[gt+2]=='a'&&linia[gt+3]=='c'&&linia[gt+4]=='z'&&linia[gt+5]==' '&&linia[leng-2]=='$'&&linia[leng-1]=='.')
			return 1;
		else return 0;
	}
}

bool fPrzelewyDo(string &linia, bool &ang)
{
	if(ang)
	{
		if(linia[gt]=='Y'&&linia[gt+1]=='o'&&linia[gt+2]=='u'&&linia[gt+4]=='g'&&linia[gt+6]=='v')
			return 1;
		else return 0;
	}
	else
	{
		if(linia[gt]=='P'&&linia[gt+1]=='r'&&linia[gt+2]=='z'&&linia[gt+3]=='e'&&linia[gt+5]=='a')
			return 1;
		else return 0;
	}
}

bool fKomunikat(string &linia, bool &ang)
{
	if(ang)
	{
		if(linia[gt]=='N'&&linia[gt+1]=='e'&&linia[gt+3]==' '&&linia[gt+8]=='r')
			return 1;
		else return 0;
	}
	else
	{
		if(linia[gt]=='N'&&linia[gt+1]=='o'&&linia[gt+3]=='y'&&linia[gt+4]==' '&&linia[gt+9]=='r')
			return 1;
		else return 0;
	}
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

bool fTransport(string &linia, bool &ang)
{
	//[2019-05-24 17:02:41] [Output] : You've earned $2792. It has been transfered to your company's account.
	if(ang)
	{
		if(linia[gt]=='Y'&&linia[gt+4]=='v'&&linia[gt+14]=='$')
			return 1;
		else return 0;
	}
	//[2019-05-24 17:02:41] [Output] : Pieniądze za transport 3191$ zostały przelane na konto firmy.
	else
	{
		if(linia[gt]=='P'&&linia[gt+1]=='i'&&linia[gt+2]=='e'&&linia[gt+3]=='n'&&linia[gt+4]=='i')
			return 1;
		else return 0;
	}
}

bool fNicknames(string &linia)
{
	for(int i = 0; i<nicknames.size(); i++)
	{
		s_temp = nicknames.at(i);
		leng = s_temp.length() - 1;
		if(linia[gt+leng]==s_temp[leng]&&linia[gt+leng-1]==s_temp[leng-1]&&linia[gt+leng-2]==s_temp[leng-2])
			return 1;
		if(linia[gt]=='*'&&linia[gt+leng+2]==s_temp[leng]&&linia[gt+leng+1]==s_temp[leng-1]&&linia[gt+leng]==s_temp[leng-2])
			return 1;
		if(linia[gt+5]==' '&&linia[gt+leng+6]==s_temp[leng]&&linia[gt+leng+5]==s_temp[leng-1]&&linia[gt+leng+4]==s_temp[leng-2])
			return 1;
	}
	return 0;
}

bool fNick(string &wyraz)
{
	for(int i = 0; i<nicknames.size(); i++)
	{
		s_temp = nicknames.at(i);
		leng = s_temp.length() - 1;
		//<nick>: message
		if(linia[gt+leng]==s_temp[leng]&&linia[gt+leng-1]==s_temp[leng-1]&&linia[gt+leng-2]==s_temp[leng-2])
			return 1;
		//* <nick> joined
		if(linia[gt]=='*'&&linia[gt+leng+2]==s_temp[leng]&&linia[gt+leng+1]==s_temp[leng-1]&&linia[gt+leng]==s_temp[leng-2])
			return 1;
		//Gracz <nick> <action>
		if(linia[gt+5]==' '&&linia[gt+leng+6]==s_temp[leng]&&linia[gt+leng+5]==s_temp[leng-1]&&linia[gt+leng+4]==s_temp[leng-2])
			return 1;
	}
	return 0;
}

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

// HANDLE hIcon = LoadImage(NULL, "icon.ico",IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
// HANDLE hIconSm = LoadImage(NULL, "icon.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
// SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM) hIcon);
// SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM) hIconSm);