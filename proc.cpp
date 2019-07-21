// Copyright (C) 2018-2019  DarXe

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

void co(string s, int n) //aux void
{
	cout<<s<<": "<<n<<endl;
}

void cls()
{
	system("cls");
}

char wybor()
{
	cout<<" Wybierz opcje : ";
	return getch();
}

void def()
{
	cls();
	cout<<"\a (INFO) Nie ma takiej opcji!"<<endl;
}

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

void playerList(vector <string> &nicknames)
{
	cout<<" _________________________________________PTS TOTOLOTEK - lista zapisanych_________________________________________"<<endl;
	if(nicknames.empty()) cout<<" Brak graczy";
	else
	{
		SetConsoleTextAttribute(h, 10);
		for(int i(1); i<nicknames.size(); i++)
		{
			if(!((i-1) % 6) && i != 1)
			{
				cout<<"\n";
			}
			if(!(i%6))
			{
				SetConsoleTextAttribute(h, 12);
				cout<<" "<<i<<". "<<nicknames.at(i)<<"\t";
				SetConsoleTextAttribute(h, 10);
			}else cout<<" "<<i<<". "<<nicknames.at(i)<<"\t";
		}
		SetConsoleTextAttribute(h, 15);
	}
	cout<<"\n __________________________________________________________________________________________________________________\n"<<endl;
}

void lottoLogusReplay(vector <string> &nicknames, vector <short> &playersId, vector <string> &winners, vector <short> &winnersId)
{
	
	if(winners.empty()) {cout<<"Brak zapisu losowania!\a"; Sleep(500);}
	else if(nicknames.size() != playersId.size()) {cout<<"Dokonano zmian w liście zapisanych!\a"; Sleep(500);} //fix crash program
	else
	{
		cls();
		playerList(nicknames);
		
		int temp = 0;
		string nick = "";
		for(int i(1); i<nicknames.size(); i++) if(!((i-1) % 6)) temp++;

		cout<<" Wciśnij dowolny klawisz, aby rozpocząć losowanie..."<<endl;
		pos.X=0; pos.Y=3+temp; SetConsoleCursorPosition(h, pos);
		cout<<" Zapisanych na PTS TOTOLOTEK: "<<nicknames.size()-1-((nicknames.size()-1)/6)<<"                           "<<endl;
		Sleep(500); cout<<" Pustych losów: "<<(nicknames.size()-1)/6<<endl;
		Sleep(500); cout<<" Tasowanie uczestników za 5"; Sleep(1000);
		for(int i(4); i>0; i--)
		{
			pos.X=26; pos.Y=5+temp; SetConsoleCursorPosition(h, pos);
			cout<<i<<" "; Sleep(1000);
		}
		pos.X=26; pos.Y=5+temp; SetConsoleCursorPosition(h, pos);
		cout<<"0 \n\n";

		//fix
		for(int i(0); i<winnersId.size(); i++)
			if(i%2 == 1) playersId.at(winnersId.at(i-1)) = winnersId.at(i);
		
		for(int i(1); i<playersId.size(); i++)
		{
			if(!((i-1) % 6) && i != 1)
			{
				cout<<"\n";
			}
			nick = nicknames.at(playersId.at(i));
			SetConsoleTextAttribute(h, 7);
			cout<<" "<<i<<". ";
			if(nick.length() == 9 && nick[5] == ' ')
			{
				SetConsoleTextAttribute(h, 12);
				cout<<nick<<"\t";
				SetConsoleTextAttribute(h, 7);
			}
			else
			{
				SetConsoleTextAttribute(h, 10);
				cout<<nick<<"\t";
				SetConsoleTextAttribute(h, 7);
			}
			Sleep(250);
		}

		Sleep(500);
		SetConsoleTextAttribute(h, 15);
		cout<<"\n\n Losowanie wygranych...\n\n";
		Sleep(1500);

		SetConsoleTextAttribute(h, 14);
		cout<<" 1. Miejsce, 60% puli wygrywa:\t ("<<winnersId.at(0)<<") "<<winners.at(0)<<"!\n\n";
		Sleep(1000);
		SetConsoleTextAttribute(h, 8);
		cout<<" 2. Miejsce, 25% puli wygrywa:\t ("<<winnersId.at(2)<<") "<<winners.at(1)<<"!\n\n";
		Sleep(1000);
		SetConsoleTextAttribute(h, 4);
		cout<<" 3. Miejsce, 15% puli wygrywa:\t ("<<winnersId.at(4)<<") "<<winners.at(2)<<"!\n\n";
		Sleep(1000);
		SetConsoleTextAttribute(h, 7);
		cout<<" 4. Miejsce, +1 los gratis:\t ("<<winnersId.at(6)<<") "<<winners.at(3)<<"!\n\n";
		Sleep(1000);
		SetConsoleTextAttribute(h, 15);
		cout<<" Gratulacje!"<<endl;
		getch();
	}
}