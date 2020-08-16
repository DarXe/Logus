// Copyright (C) 2018-2020  DarXe

//func

//[2020-06-18 13:16:48] [Output] : * player has joined the game
//[2020-06-18 13:19:46] [Output] : * player has left the game (Quit)
//[2020-05-26 05:25:26] [Output] : * player has left the game (Timed out)

/*bool fNick(string &wyraz)
{
	for(int i = 0; i<nicknames.size(); i++)
	{
		s_temp = nicknames.at(i);
		leng = s_temp.length() - 1;
		//<nick>: message
		if(line[gt+leng]==s_temp[leng]&&line[gt+leng-1]==s_temp[leng-1]&&line[gt+leng-2]==s_temp[leng-2])
			return 1;
		//* <nick> joined
		if(line[gt]=='*'&&line[gt+leng+2]==s_temp[leng]&&line[gt+leng+1]==s_temp[leng-1]&&line[gt+leng]==s_temp[leng-2])
			return 1;
		//Gracz <nick> <action>
		if(line[gt+5]==' '&&line[gt+leng+6]==s_temp[leng]&&line[gt+leng+5]==s_temp[leng-1]&&line[gt+leng+4]==s_temp[leng-2])
			return 1;
	}
	return 0;
}
*/

//[2019-06-28 11:58:25] [Input]  : test

void nrPliku(int nr)
{
	if(nr != 10)
	{
		if(!nr)
			std::cout<<">>>>>>>>>>>>>>>>>>>> logus.log <<<<<<<<<<<<<<<<<<<<"<<std::endl;
		else
			std::cout<<">>>>>>>>>>>>>>>>>>>> Plik nr "<<nr<<" <<<<<<<<<<<<<<<<<<<<"<<std::endl;
	}
}

int all(std::string &nazwa, int nr)
{
	std::string line;
	int lineCount = 0;
	nrPliku(nr);

	std::fstream file;
	file.open(nazwa.c_str());
		while(!file.eof())
		{
			getline(file,line);
			lineCount++;
		}
	file.close();

	return lineCount;
}

int teamsay(std::string &nazwa, int nr)
{
	std::string line;
	int lineCount = 0;
	nrPliku(nr);

	std::fstream file;
	file.open(nazwa.c_str());
		while(!file.eof())
		{
			getline(file,line);
			if(fTeam(line, 1))
			{
				std::cout<<++lineCount<<line<<std::endl;
				if(lineCount%30 == 0)
				{
					std::cout<<"PLIK "<<nr<<" [ESC] "<<((!nr)?"Wyjscie":"Nastepny file")<<" | Nastepne 30 wierszy... (dowolny klawisz)"<<std::endl;
					if(getch() == 27)
					{
						cls();
						while(!file.eof())
						{
							getline(file,line);
							if(fTeam(line, 1)) lineCount++;
						}
						break;
					}
					cls();
				}
			}
		}
	file.close();

	return lineCount;
}

int pw(std::string &nazwa, int nr)
{
	std::string line;
	int lineCount = 0;
	nrPliku(nr);

	std::fstream file;
	file.open(nazwa.c_str());
		while(!file.eof())
		{
			getline(file,line);
			if(fPwOd(line, ptsLang)||fPwDo(line))
			{
				std::cout<<++lineCount<<line<<std::endl;
				if(lineCount%30 == 0)
				{
					std::cout<<"PLIK "<<nr<<" [ESC] "<<((!nr)?"Wyjscie":"Nastepny file")<<" | Nastepne 30 wierszy... (dowolny klawisz)"<<std::endl;
					if(getch() == 27)
					{
						cls();
						while(!file.eof())
						{
							getline(file,line);
							if(fPwOd(line, ptsLang)||fPwDo(line)) lineCount++;
						}
						break;
					}
					cls();
				}
			}
		}
	file.close();

	return lineCount;
}

int przelewy(std::string &nazwa, int nr)
{
	std::string line;
	int lineCount = 0;
	nrPliku(nr);

	std::fstream file;
	file.open(nazwa.c_str());
		while(!file.eof())
		{
			getline(file,line);
			if(fPrzelewyOd(line, ptsLang)||fPrzelewyDo(line, ptsLang))
			{
				std::cout<<++lineCount<<line<<std::endl;
				if(lineCount%30 == 0)
				{
					std::cout<<"PLIK "<<nr<<" [ESC] "<<((!nr)?"Wyjscie":"Nastepny file")<<" | Nastepne 30 wierszy... (dowolny klawisz)"<<std::endl;
					if(getch() == 27)
					{
						cls();
						while(!file.eof())
						{
							getline(file,line);
							if(fPrzelewyOd(line, ptsLang)||fPrzelewyDo(line, ptsLang)) lineCount++;
						}
						break;
					}
					cls();
				}
			}
		}
	file.close();

	return lineCount;
}

/*int nickname(string &nazwa, int nr)
{
	string line;
	int lineCount = 0;
	nrPliku(nr);
	fstream file;
	file.open(nazwa.c_str());
		while(!file.eof())
		{
			file>>line>>line>>line>>line; //wyrazy
			if(fNick(line))
			{
				cout<<++lineCount<<line<<endl;
				if(lineCount%30 == 0)
				{
					cout<<"PLIK "<<nr<<" [ESC] "<<((!nr)?"Wyjscie":"Nastepny file")<<" | Nastepne 30 wierszy... (dowolny klawisz)"<<endl;
					if(getch() == 27)
					{
						cls();
						while(!file.eof())
						{
							getline(file,line);
							if(fPrzelewyOd(line, ptsLang)||fPrzelewyDo(line, ptsLang)) lineCount++;
						}
						break;
					}
					cls();
				}
			}
		}
	file.close();

	return lineCount;
}
*/
// HANDLE hIcon = LoadImage(NULL, "icon.ico",IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
// HANDLE hIconSm = LoadImage(NULL, "icon.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
// SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM) hIcon);
// SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM) hIconSm);