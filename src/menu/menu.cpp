// Copyright (C) 2018-2020  DarXe, Niventill


#include "livechat.cpp"
#include "settings.cpp"

int menu() //con
{
	int lineCount = 0;
	int lineCountAll = 0;
	while(true)
	{
		if(isTimer) delay2 = clock();
		color(kolorGlowny);
		if(engLang) {
			SetConsoleTextAttribute(h, 10);
			std::cout<<" _______________________________________MENU_______________________________________\n";
			SetConsoleTextAttribute(h, 11);
			std::cout<<" [Enter] Run MTA:SA and connect to PTS / reconnect\n";
			std::cout<<" [L] PTS TOTOLOTEK - Lotto Logus\n";
			SetConsoleTextAttribute(h, 12);
			std::cout<<" [s] Faststart PTS + MTA:SA: ";
			switch (fastStart) {
			case 0: std::cout<<"No LiveChat + PTS autostart, but show version info"; break;
			case 1: std::cout<<"LiveChat + PTS autostart, but don't show version info"; break;
			default: std::cout<<"No LiveChat + PTS autostart and no version info"; break;
			}
			std::cout<<"\n";
			std::cout<<" [t] LiveChat - ingame chat with notifications\n";
			std::cout<<" [5] Logus's settings\n";
			SetConsoleTextAttribute(h, 11);
			std::cout<<" [1] Search for team messages in console.log\n";
			std::cout<<" [2] Search for private messages in console.log\n";
			std::cout<<" [3] Search for team messages in all .log files\n";
			std::cout<<" [4] Search for private messages and answers in all .log files\n";
			SetConsoleTextAttribute(h, 12);
			std::cout<<" [p] Search for payments in all .log files\n";
			std::cout<<" [n] Amount of lines in all .log files\n";
			SetConsoleTextAttribute(h, 11);
			std::cout<<" [w] Pingtest - check connection to the internet\n";
			std::cout<<" [k] Car Dealer - purchase and selling prices\n";
			std::cout<<" [j] Language - change to Polski\n";
			std::cout<<" [9] Change sound (beep) to random\n";
			std::cout<<" [0] Codepage (legacy): "<<((codePage852)?"852":"UTF-8")<<std::endl;
			std::cout<<" [i] INFO\n";
			SetConsoleTextAttribute(h, 10);
			std::cout<<" __________________________________________________________________________________\n";
			std::cout<<"                                [ESC] Quit & save                             \n";
		} else {
			SetConsoleTextAttribute(h, 10);
			std::cout<<" _______________________________________MENU_______________________________________\n";
			SetConsoleTextAttribute(h, 11);
			std::cout<<" [Enter] Uruchom MTA i połącz z PTS / Połącz ponownie\n";
			std::cout<<" [L] PTS TOTOLOTEK - Lotto Logus\n";
			SetConsoleTextAttribute(h, 12);
			std::cout<<" [s] Szybki start LiveChat + PTS: ";
			switch (fastStart) {
			case 0: std::cout<<"Nie, ale wyświetl info o wersji"; break;
			case 1: std::cout<<"Tak, uruchom MTA:PTS przy starcie Logusa"; break;
			default: std::cout<<"Nie uruchamiaj, ani nie wyświetlaj info o wersji"; break;
			}
			std::cout<<std::endl;
			std::cout<<" [t] LiveChat - czat z gry w konsoli z komunikatami dźwiękowymi\n";
			std::cout<<" [5] Ustawienia Logusa\n";
			SetConsoleTextAttribute(h, 11);
			std::cout<<" [1] Szukaj wiadomości teamowych w console.log\n";
			std::cout<<" [2] Szukaj PW oraz odpowiedzi w console.log\n";
			std::cout<<" [3] Szukaj wiadomości teamowych we wszystkich plikach .log\n";
			std::cout<<" [4] Szukaj PW oraz odpowiedzi we wszystkich plikach .log\n";
			SetConsoleTextAttribute(h, 12);
			std::cout<<" [p] Szukaj przelewów od i do graczy we wszystkich plikach\n";
			std::cout<<" [n] Ilość wierszy w plikach\n";
			SetConsoleTextAttribute(h, 11);
			std::cout<<" [w] Test ping - szybkie sprawdzenie, czy jest internet\n";
			std::cout<<" [k] Komis - ceny skupu i sprzedaży\n";
			std::cout<<" [j] Język - zmień na English\n";
			std::cout<<" [9] Zmiana dźwięku na losowy\n";
			std::cout<<" [0] Kodowanie (legacy): "<<((codePage852)?"852":"UTF-8")<<std::endl;
			std::cout<<" [i] INFO\n";
			SetConsoleTextAttribute(h, 10);
			std::cout<<" __________________________________________________________________________________\n";
			std::cout<<"                                [ESC] Wyjście i zapis                              \n";
		}
		Beep(dzwiekGlowny,100);

		switch(wybor()) //set0 MENU
		{
		case 27:
		{
			if(engLang)
			return closeLogus("Closing the program");
			else
			return closeLogus("Zamykanie programu");
		}
		case '1':
		{
			cls();
			teamsay(a,1);
			break;
		}
		case '2':
		{
			cls();
			pw(a,1);
			break;
		}
		case '3':
		{
			cls();
			lineCount = 0;
			lineCountAll = 0;
			lineCountAll+=teamsay(f,6);
			lineCountAll+=teamsay(e,5);
			lineCountAll+=teamsay(d,4);
			lineCountAll+=teamsay(c,3);
			lineCountAll+=teamsay(b,2);
			lineCountAll+=teamsay(a,1);
			lineCount=teamsay(L,0);
			if(engLang) {
				std::cout<<"Lines in MTA logs: "<<lineCountAll<<std::endl;
				std::cout<<"Lines in logus.log: "<<lineCount<<std::endl;
			} else {
				std::cout<<"Wierszy w plikach MTA: "<<lineCountAll<<std::endl;
				std::cout<<"Wierszy w logus.log: "<<lineCount<<std::endl;
			}
			break;
		}

		case '4':
		{
			cls();
			lineCount = 0;
			lineCountAll = 0;
			lineCountAll+=pw(f,6);
			lineCountAll+=pw(e,5);
			lineCountAll+=pw(d,4);
			lineCountAll+=pw(c,3);
			lineCountAll+=pw(b,2);
			lineCountAll+=pw(a,1);
			lineCount=pw(L,0);
			if(engLang) {
				std::cout<<"Lines in MTA logs: "<<lineCountAll<<std::endl;
				std::cout<<"Lines in logus.log: "<<lineCount<<std::endl;
			} else {
				std::cout<<"Wierszy w plikach MTA: "<<lineCountAll<<std::endl;
				std::cout<<"Wierszy w logus.log: "<<lineCount<<std::endl;
			}
			break;
		}
		case 'p':
		{
			cls();
			lineCountAll = 0;
			lineCountAll+=przelewy(f,6);
			lineCountAll+=przelewy(e,5);
			lineCountAll+=przelewy(d,4);
			lineCountAll+=przelewy(c,3);
			lineCountAll+=przelewy(b,2);
			lineCountAll+=przelewy(a,1);
			lineCountAll+=przelewy(L,0);
			if(engLang) {
				std::cout<<"Lines: "<<lineCountAll<<std::endl;
			} else {
				std::cout<<"Wierszy: "<<lineCountAll<<std::endl;
			}
			break;
		}
		case 'n':
		{
			cls();
			lineCountAll = 0;
			lineCount = 0;
			lineCount=all(f,6);
			lineCountAll+=lineCount;
			if(engLang) {
				std::cout<<"Lines: "<<lineCountAll<<std::endl;
			} else {
				std::cout<<"Wierszy: "<<lineCountAll<<std::endl;
			}
			lineCount=all(e,5);
			lineCountAll+=lineCount;
			if(engLang) {
				std::cout<<"Lines: "<<lineCountAll<<std::endl;
			} else {
				std::cout<<"Wierszy: "<<lineCountAll<<std::endl;
			}
			lineCount=all(d,4);
			lineCountAll+=lineCount;
			if(engLang) {
				std::cout<<"Lines: "<<lineCountAll<<std::endl;
			} else {
				std::cout<<"Wierszy: "<<lineCountAll<<std::endl;
			}
			lineCount=all(c,3);
			lineCountAll+=lineCount;
			if(engLang) {
				std::cout<<"Lines: "<<lineCountAll<<std::endl;
			} else {
				std::cout<<"Wierszy: "<<lineCountAll<<std::endl;
			}
			lineCount=all(b,2);
			lineCountAll+=lineCount;
			if(engLang) {
				std::cout<<"Lines: "<<lineCountAll<<std::endl;
			} else {
				std::cout<<"Wierszy: "<<lineCountAll<<std::endl;
			}
			lineCount=all(a,1);
			lineCountAll+=lineCount;
			if(engLang) {
				std::cout<<"Lines: "<<lineCountAll<<std::endl;
			} else {
				std::cout<<"Wierszy: "<<lineCountAll<<std::endl;
			}
			std::cout<<std::endl;
			if(engLang) {
				std::cout<<"Lines in MTA logs: "<<lineCountAll<<std::endl;
				std::cout<<"Lines in logus.log: "<<lineCount<<std::endl;
			} else {
				std::cout<<"Wierszy w plikach MTA: "<<lineCountAll<<std::endl;
				std::cout<<"Wierszy w logus.log: "<<lineCount<<std::endl;
			}
			break;
		}
		case 't':
		{
			cls();
			if(isTimer) timer -= (clock()-delay2);
			liveChat(); //run LiveChat
			mess = engLang? "Closing MTA and Logus": "Zamykanie MTA i programu";
			if(_quit == 2) return closeLogus(mess); //close Logus
			break;
		} 
		case 'l':
		case 'L':
		{
			cls();
			lottoLogus(); //run Lotto Logus
			break;
		}
		case '5': //set1    SETTINGS one
		{
			cls();
			settings();
			break;
		}
		case '0':
		{
			cls();
			if(codePage852)
			{
				codePage852 = 0;
				SetConsoleOutputCP(65001);
				SetConsoleCP(65001); 
				engLang?std::cout<<"Codepage UTF-8\n":
				std::cout<<"Kodowanie UTF-8\n";
			}
			else
			{
				codePage852 = 1;
				SetConsoleOutputCP(852);
				SetConsoleCP(852); 
				engLang?std::cout<<"Codepage 852\n":
				std::cout<<"Kodowanie 852\n";
			}
			break;
		}
		case 'j':
		{
			cls();
			if(engLang)
			{
				engLang = 0;
				std::cout<<"Menu po polsku\n";
			}
			else
			{
				engLang = 1;
				std::cout<<"Menu in English\n";
			}
			break;
		}
		case '9':
		{
			cls();
			dzwiekGlowny = losuj(50,10000);
			std::cout<<dzwiekGlowny<<std::endl;
			break;
		}

		case 'w':
		{
			cls();
			clock_t p = 0;
			std::string host = "";
			std::cout<<"Choose host: \n";
			std::cout<<"1. localhost\n";
			std::cout<<"2. google.pl\n";
			std::cout<<"3. facebook.com\n";
			std::cout<<"4. other\n";
			switch(getch())
			{
				case '1': host = "ping localhost"; break;
				case '2': host = "ping google.pl"; break;
				case '3': host = "ping facebook.com"; break;
				case '4': {
						std::cout<<"Enter host: ";
						std::cin>>host;
						host = "ping "+host; break;
					}
				default: host = "ping google.pl"; break;
			}
			cls();
			while(true)
			{
				if(host == "") break;
				p = clock();
				std::cout<<"Any key - exit. ";
				Sleep(1000);
				system(host.c_str());
				std::cout<<"Delay: "<<clock()-p<<"ms\n";
				if(clock()-p > 4000 && clock()-p < 5000)
					Beep(dzwiekGlowny,333);
				if(kbhit()) {getch(); break;}
			}
			cls();
			break;
		}
		case 'k':
		{
			cls();
			dealer();
			break;
		}
		case 'i':
		{
			cls();
			wersja();
			break;
		}
		case 's':
		{
			cls();
			switch (fastStart)
			{
			case 0:
				fastStart = 1;
				break;
			case 1:
				fastStart = 2;
				break;
			default:
				fastStart = 0;
			break;
			}
			break;
		}
		case 13:
		{
			cls();
			runLiveChat();
			mess = engLang? "Closing MTA and Logus": "Zamykanie MTA i programu";
			if(_quit == 2) return closeLogus(mess); //close Logus
			break;
		}
		default:
			def();
		}//switch
	}
	return 0;
}