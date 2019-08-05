// Copyright (C) 2018-2019  DarXe

void co(string s, int n) //aux void
{
	cout<<s<<": "<<n<<endl;
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
		Sleep(500); cout<<" Komora maszyny losującej jest pusta, zwolnienie blokady za ";
		for(int i(5); i>0; i--)
		{
			pos.X=60; pos.Y=5+temp; SetConsoleCursorPosition(h, pos);
			cout<<i<<" "; Sleep(1000);
		}
		pos.X=60; pos.Y=5+temp; SetConsoleCursorPosition(h, pos);
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
			Sleep(300);
		}

		Sleep(500);
		SetConsoleTextAttribute(h, 15);
		cout<<"\n\n i rozpoczynamy losowanie czterech wygranych";
		for (size_t i = 0; i < 3; i++)
		{
			Sleep(500);
			cout<<".";
		}
		Sleep(1000);
		cout<<"\n\n";
		
		SetConsoleTextAttribute(h, 14);
		cout<<" 1. Miejsce, 60% puli wygrywa:\t ("<<winnersId.at(0)<<") "<<winners.at(0)<<"!\n\n";
		Sleep(1500);
		SetConsoleTextAttribute(h, 8);
		cout<<" 2. Miejsce, 25% puli wygrywa:\t ("<<winnersId.at(2)<<") "<<winners.at(1)<<"!\n\n";
		Sleep(1500);
		SetConsoleTextAttribute(h, 4);
		cout<<" 3. Miejsce, 15% puli wygrywa:\t ("<<winnersId.at(4)<<") "<<winners.at(2)<<"!\n\n";
		Sleep(1500);
		SetConsoleTextAttribute(h, 7);
		cout<<" 4. Miejsce, +1 los gratis:\t ("<<winnersId.at(6)<<") "<<winners.at(3)<<"!\n\n";
		Sleep(500);
		SetConsoleTextAttribute(h, 15);
		cout<<" Gratulacje!"<<endl;
		getch();
	}
}

int losuj(int od, int doo)
{
	return rand()%(doo - od + 1)+od;
}

void lottoLogusStats(vector <string> &nicknames)
{
    if(nicknames.size()<=4) {cout<<" Za mało graczy!\a"; Sleep(500);}
    else
    {
		vector <string> winners;
		vector <int> playersId;
		vector <short> randoms;
		vector <float> randomsC(5,0); //randoms count {nazwa, nazwa, nazwa, nazwa, pusty}0-4
		fstream log;
		string nick = "";
		cls();
		log.open("lottoLogus.log", ios::out);

        int licznik = 1;
        const int start = 1000;
		int los;
		
		while(randoms.size()<4)
		{
			los = losuj(1, nicknames.size()-1);
			for (int i : randoms)
			{
				if(i == los) los = 0;
			}
			if(los%6 != 0 && los)
				randoms.push_back(los);
		}
		randoms.push_back(6); //"pusty los"

        float srednia; float Msrednia=0; float msrednia=1000;
        float srednia2; float Msrednia2=0; float msrednia2=1000;
        clock_t t = clock();
        int count = 10000;

        while(licznik<=count)
        {
            if(winners.empty())
            {
                vector <int> tempNum(nicknames.size(),1);
				short a = 1, b = nicknames.size()-1;
                playersId.push_back(0);
                do
                {
                    temp = losuj(a, b);
					if(a == temp) a++; if(b == temp) b--;
                    if(tempNum.at(temp))
                    {
                        playersId.push_back(temp);
                        tempNum.at(temp) = 0;
                    }
                }while(playersId.size()!=nicknames.size());
            }

            while(winners.size()<4)
            {
                temp = losuj(1, playersId.size()-1);
                if(playersId.at(temp))
                {   
                    nick = nicknames.at(playersId.at(temp));
                    winners.push_back(nick);
                    if(playersId.at(temp) == randoms.at(0)) randomsC[0]++;
                    if(playersId.at(temp) == randoms.at(1)) randomsC[1]++;
                    if(playersId.at(temp) == randoms.at(2)) randomsC[2]++;
                    if(playersId.at(temp) == randoms.at(3)) randomsC[3]++;
                    if(playersId.at(temp)%6 == 0) randomsC[4]++; //pusty los

                    if(licznik>start)
                    {
                        log<<"Licz="<<licznik<<"\t ";
						for (size_t i = 0; i < 4; i++)
						{
							srednia2 = randomsC[i]/licznik;
							if(srednia2<msrednia2) msrednia2 = srednia2;
                        	if(srednia2>Msrednia2) Msrednia2 = srednia2;
							log<<nicknames.at(randoms[i])<<"="<<srednia2*100<<"%\t ";
						}
						srednia = randomsC[4]/licznik;
						if(srednia<msrednia) msrednia = srednia;
						if(srednia>Msrednia) Msrednia = srednia;
						log<<"Pusty los"<<"="<<srednia*100<<"%\t ";
                        log<<nick<<endl;
                    }
                    playersId.at(temp) = 0;
                }
            }
            if(licznik>start) log<<endl;
            licznik++;
            winners.clear();
            playersId.clear();
        }

        cout<<"Losowań: "<<count<<endl;
        cout<<"Ilość wygranych:"<<endl;
        cout<<nicknames.at(randoms[0])<<": "<<randomsC[0]<<endl;
        cout<<nicknames.at(randoms[1])<<": "<<randomsC[1]<<endl;
        cout<<nicknames.at(randoms[2])<<": "<<randomsC[2]<<endl;
        cout<<nicknames.at(randoms[3])<<": "<<randomsC[3]<<endl;
        cout<<"Pusty Los: "<<randomsC[4]<<endl;
        cout<<"TIME: "<<clock()-t<<"ms\n\n";

        cout<<"Zapisanych na PTS TOTOLOTEK: "<<nicknames.size()-1-((nicknames.size()-1)/6)<<endl;
        cout<<"Pustych losów: "<<(nicknames.size()-1)/6<<endl;
		for (size_t i = 0; i < 4; i++)
		{
			cout<<nicknames.at(randoms[i])<<": "<<randomsC[i]/licznik*100<<"%\n";
		}
        cout<<"Pusty: "<<srednia*100<<"%\n\n";

        cout<<"MaxWin: "<<Msrednia2*100<<"%\n";
        cout<<"minWin: "<<msrednia2*100<<"%\n";
        cout<<"MaxPusty: "<<Msrednia*100<<"%\n";
        cout<<"minPusty: "<<msrednia*100<<"%\n";


        log<<"Losowań: "<<count<<endl;
        log<<"Ilość wygranych:"<<endl;
        log<<nicknames.at(randoms[0])<<": "<<randomsC[0]<<endl;
        log<<nicknames.at(randoms[1])<<": "<<randomsC[1]<<endl;
        log<<nicknames.at(randoms[2])<<": "<<randomsC[2]<<endl;
        log<<nicknames.at(randoms[3])<<": "<<randomsC[3]<<endl;
        log<<"Pusty Los: "<<randomsC[4]<<endl;
        log<<"TIME: "<<clock()-t<<"ms\n\n";

        log<<"Zapisanych na PTS TOTOLOTEK: "<<nicknames.size()-1-((nicknames.size()-1)/6)<<endl;
        log<<"Pustych losów: "<<(nicknames.size()-1)/6<<endl;
		for (size_t i = 0; i < 4; i++)
		{
			log<<nicknames.at(randoms[i])<<": "<<randomsC[i]/licznik*100<<"%\n";
		}
        log<<"Pusty: "<<srednia*100<<"%\n\n";

        log<<"MaxWin: "<<Msrednia2*100<<"%\n";
        log<<"minWin: "<<msrednia2*100<<"%\n";
        log<<"MaxPusty: "<<Msrednia*100<<"%\n";
        log<<"minPusty: "<<msrednia*100<<"%\n";

        log.close();

		cout<<"\nRozszerzone informacje zostaly wygenerowane w pliku lottoLogus.log";
		cout<<"\nZnajduje sie on tam, gdzie wklejany jest program - w logach MTA";
		cout<<"\n\nWciśnij dowolny klawisz...";
		getch();
    }
}