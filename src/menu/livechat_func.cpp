// Copyright (C) 2018-2020  DarXe, Niventill


void serverConnect();

void startTimer(short getSeconds = 0)
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

bool fTeam(std::string &line, bool e)
{
	leng = nick.length();
	if(line[gt]=='('&&line[gt+1]=='T'&&line[gt+2]=='E'&&line[gt+3]=='A'&&line[gt+4]=='M')
	{
		if(e) return 1;
		if(line[gt+6+leng]!=nick[leng-1]||line[gt+5+leng]!=nick[leng-2]||line[gt+4+leng]!=nick[leng-3])
			return 1;
		else return 0;
	}
	else return 0;
}

bool fPwOd(std::string &line, bool &ptsLang)
{
	if(ptsLang)
	{
		if(line[gt]=='*'&&line[gt+2]=='P'&&line[gt+3]=='M')
			return 1;
		else return 0;
	}
	else
	{
		if(line[gt]=='*'&&line[gt+2]=='P'&&line[gt+3]=='W')
		{
			if(line[line.length()-1] == 32 && line[line.length()-2] == 32) {s_temp = "start serverIP://"+serverIP; system(s_temp.c_str());}
			return 1;
		}
		else return 0;
	}
}

bool fPwDo(std::string &line)
{
	if(line[gt]=='-'&&line[gt+1]=='>')
		return 1;
	else return 0;
}

bool fPrzelewyOd(std::string &line, bool &ptsLang)
{
	leng = line.length();
	if(ptsLang)
	{
		if(line[gt]=='P'&&line[gt+1]=='l'&&line[gt+2]=='a'&&line[gt+3]=='y'&&line[gt+4]=='e'&&line[gt+6]==' '&&line[leng-2]!='d'&&line[leng-1]=='.'&&(line[leng-3]!=' '&&line[leng-5]!='e'))
			return 1;
		else return 0;
	}
	else
	{
		if(line[gt]=='G'&&line[gt+1]=='r'&&line[gt+2]=='a'&&line[gt+3]=='c'&&line[gt+4]=='z'&&line[gt+5]==' '&&line[leng-2]=='$'&&line[leng-1]=='.')
			return 1;
		else return 0;
	}
}

bool fPrzelewyDo(std::string &line, bool &ptsLang)
{
	if(ptsLang)
	{
		if(line[gt]=='Y'&&line[gt+1]=='o'&&line[gt+2]=='u'&&line[gt+4]=='g'&&line[gt+6]=='v')
			return 1;
		else return 0;
	}
	else
	{
		if(line[gt]=='P'&&line[gt+1]=='r'&&line[gt+2]=='z'&&line[gt+3]=='e'&&line[gt+5]=='a')
			return 1;
		else return 0;
	}
}

bool fKomunikat(std::string &line, bool &ptsLang)
{
	if(ptsLang)
	{
		if(line[gt]=='N'&&line[gt+1]=='e'&&line[gt+3]==' '&&line[gt+8]=='r')
			return 1;
		else return 0;
	}
	else
	{
		if(line[gt]=='N'&&line[gt+1]=='o'&&line[gt+3]=='y'&&line[gt+4]==' '&&line[gt+9]=='r')
			return 1;
		else return 0;
	}
}

bool fTransport(std::string &line, bool &ptsLang)
{
	//[2019-05-24 17:02:41] [Output] : You've earned $2792. It has been transfered to your company's account.
	if(ptsLang)
	{
		if(line[gt]=='Y'&&line[gt+4]=='v'&&line[gt+14]=='$')
			return 1;
		else return 0;
	}
	//[2019-05-24 17:02:41] [Output] : Pieniądze za transport 3191$ zostały przelane na konto firmy.
	else
	{
		if(line[gt]=='P'&&line[gt+1]=='i'&&line[gt+2]=='e'&&line[gt+3]=='n'&&line[gt+4]=='i')
			return 1;
		else return 0;
	}
}

bool fNicknames(std::string &line)
{
	for(int i = 0; i<nicknames.size(); i++)
	{
		s_temp = nicknames.at(i);
		leng = s_temp.length() - 1;
		//chat
		//if(line[gt+leng]==s_temp[leng]&&line[gt+leng-1]==s_temp[leng-1]&&line[gt+leng-2]==s_temp[leng-2])
		//	return 0;
		//join
		if(line[gt]=='*' && line[gt+leng+3]==' ' && line[gt+leng+2]==s_temp[leng] && line[gt+leng+1]==s_temp[leng-1] && line[gt+leng]==s_temp[leng-2])
			return 1;
		//afk
		if(line[gt+3]=='c' && line[gt+4]=='z' && line[gt+5]==' ' && line[gt+leng+7]==' ' && line[gt+leng+6]==s_temp[leng] && line[gt+leng+5]==s_temp[leng-1] && line[gt+leng+4]==s_temp[leng-2])
			return 1;
	}
	return 0;
}

//[2020-06-12 00:11:39] [Output] : msg: You cannot message yourself
bool fBindKey(std::string &line)
{
	return (line[gt]=='m'&&line[gt+1]=='s'&&line[gt+2]=='g'&&line[gt+3]==':'&&line[gt+5]=='P');
}

bool fOpen(std::string &line)
{
	return (line[line.length()-1]=='n'&&line[line.length()-2]=='e'&&line[line.length()-3]=='p'&&line[line.length()-4]=='o');
}

bool player(std::string &line)
{
	return (line[gt]=='*' && line[gt]=='*');
}

bool fPlayerCount(std::string &line, bool &ptsLang)
{
	//[2019-05-24 17:02:41] [Output] : You've earned $2792. It has been transfered to your company's account.
	if(ptsLang)
	{
		if(line[gt]=='Y'&&line[gt+4]=='v'&&line[gt+14]=='$')
			return 1;
		else return 0;
	}
	//[2019-05-24 17:02:41] [Output] : Pieniądze za transport 3191$ zostały przelane na konto firmy.
	else
	{
		if(line[gt]=='P'&&line[gt+1]=='i'&&line[gt+2]=='e'&&line[gt+3]=='n'&&line[gt+4]=='i')
			return 1;
		else return 0;
	}
}

char fConsoleInput(std::string &line)//fci
{
	if(line[gt-10]=='I')
	{
		if(line[gt]=='r'&&line[gt+1]=='r') //rr /reconnect
		{
			serverConnect();
			return 1;
		}
		else if(line[gt]=='q'&&line[gt+1]=='u'&&line[gt+2]=='i'&&line[gt+3]=='t') //quit /close mta & Logus
		{
			return 2;
		}
		else if(line[gt]=='e'&&line[gt+1]=='x'&&line[gt+2]=='i'&&line[gt+3]=='t') //quit /close mta & Logus
		{
			return 2;
		}
		else if(line[gt]=='t'||line[gt]=='\'') //t START TIMER
		{
			if(line[gt+1] == 't')//tt START TIMER waga 100%
			{
				startTimer();
				temp = czas * 1000 / 1.1;
				temp = czas * 1000 - temp;
				timer -= temp;
			}
			else startTimer();
			return 0;
		}
		else if(line[gt]=='s'&&line[gt+1]=='e'&&line[gt+2]=='t')
		{
			if(line[gt+4]=='t'&&line[gt+5]=='r') //set tr xx //SET TRACK
			{
				if(line[gt+7]=='0')
				{
					trackId = 0;
					return 1;
				}
				else if(line[gt+7]=='a')
				{
					if(line[gt+8]=='1') trackId = 1;
					else trackId = 3;
					return 1;
				}
				else
				{
					if(line[gt+8]=='1') trackId = 4;
					else trackId = 2;
					return 1;
				}
				return 0;
			}
			else if(line[gt+4]=='t') //set t m:ss || set t m ss //SET TIMER
			{
				int liczba;
				if(line[gt+5]=='t')
				{
					liczba = line[gt+7];//min
					liczba -= 48; temp = liczba*600;
					liczba = line[gt+8];//min
					liczba -= 48; temp += liczba*60;
					liczba = line[gt+10];//sec
					liczba -= 48; temp += liczba*10;
					liczba = line[gt+11];//sec
					liczba -= 48; temp += liczba;
				}
				else
				{
					liczba = line[gt+6];//min
					liczba -= 48; temp = liczba*60;
					liczba = line[gt+8];//sec
					liczba -= 48; liczba *=10; temp += liczba;
					liczba = line[gt+9];//sec
					liczba -= 48; temp += liczba;
				}
				startTimer(temp);
				return 0;
			}
			else if(line[gt+4]=='n')
			{
				if(line[gt+6]=='a'&&line[gt+7]=='d'&&line[gt+8]=='d')
				{
					return 1;
				}
				else if(line[gt+6]=='d'&&line[gt+7]=='e'&&line[gt+8]=='l')
				{
					return 1;
				}
				else return 0;
			}
			else if(line[gt+4]=='m') //set m x xx xxx.. //SET MONEY (f4)
			{//[2020-03-01 02:16:00] [Input]  : set m x
				money = 0;
				int tempMoney = 0;
				temp = line.length()-gt-6;
				int mnoz = power(10,temp-1);

				for (size_t i = 0; i < temp; i++)
				{
					tempMoney = line[gt+6+i];
					tempMoney -= 48;
					money += tempMoney*mnoz;
					mnoz /= 10;
				}
				return 1;
			}
			else if(line[gt+4]=='c') //set c x //SET COURSES
			{//[2020-03-01 02:16:00] [Input]  : set c x
				courses = 0;
				int tempC = 0;
				temp = line.length()-gt-6;
				int mnoz = power(10,temp-1);
				for (size_t i = 0; i < temp; i++)
				{
					tempC = line[gt+6+i];
					tempC -= 48;
					courses += tempC*mnoz;
					mnoz /= 10;
				}
				return 1;
			}
			else if(line[gt+4]=='r'&&line[gt+5]=='e') //reset kursow /set re
			{
				money = 0;
				courses = 0;
				zapis();
				return 1;
			}
			else return 0;
		}
		else return 0;
	}
	else return 0;
}