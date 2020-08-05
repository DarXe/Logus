// Copyright (C) 2018-2020  DarXe

#include <climits>

int intError(int &number)
{
	while (!(std::cin>>number))
    {
      std::cout<<"\n\aERRROR! Podales litere/y!"<<std::endl;
			std::cin.clear(); // clear input buffer to restore std::cin to a usable state
			std::cin.ignore(INT_MAX, '\n'); // ignore last input
			std::cout << "Ta opcja wymaga podania liczby..\n";
			std::cout << "Spróbuj ponownie: ";
    }
  return number;
}

void color(std::string value)
{
	std::string value0 = "color 0"+value;
	system(value0.c_str());
}

void infoOuput()
{
	
}

void salaryForTransport(std::string &line, bool &ang)
{
	if(ang)
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
			zapis();
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
			zapis();
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
			zapis();
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
			zapis();
		}
	}
}

bool liveChatBeep(std::string &ostatniaLinia) //bee
{
	//wiadomość pw
	if(!fLockPW){
		if(fPwOd(ostatniaLinia, ang))
		{
			//open the gate
			if(fOpen(ostatniaLinia))
			{
				system("start pasteCmd.exe");
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
		if(fTransport(ostatniaLinia, ang))
		{
			salaryForTransport(ostatniaLinia, ang);
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

		if(fKomunikat(ostatniaLinia, ang))
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
	if(fPrzelewyOd(ostatniaLinia, ang))
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

	return 1;
}

void liveChatHead(int lineCount = 0) //head
{
	pos.X=0; pos.Y=0; SetConsoleCursorPosition(h, pos);
	SetConsoleTextAttribute(h, 12);
	std::cout<<"###############################LiveChat###############################"<<std::endl;
	SetConsoleTextAttribute(h, 204); std::cout<<" "; SetConsoleTextAttribute(h, 12);
	std::cout<<" Refresh:"<<refresh<<"ms"<<" # Wierszy:"<<lineCount-1<<" # Errors:"<<errors<<" #  [ESC]Return to MENU    "<<std::endl;
	if(isTimer)
	{
		SetConsoleTextAttribute(h, 170); std::cout<<" "; SetConsoleTextAttribute(h, 12);
		std::cout<<" Timer "<<timer/1000/60;
		if((timer/1000)%60<10) std::cout<<":0"; else std::cout<<":";
		std::cout<<(timer/1000)%60<<"  [s]Stop Timer # F4 ";
	}
	else
	{
		SetConsoleTextAttribute(h, 204); std::cout<<" "; SetConsoleTextAttribute(h, 12);
		std::cout<<" [t]Timer                  # F4 ";
	}
	if(courses) std::cout<<"$"<<money<<" # Courses:"<<courses<<" # Avg $"<<money/courses<<"                  ";
	else      std::cout<<"Dostarczone kursy: "<<courses<<"                                             ";
	SetConsoleTextAttribute(h, 204); std::cout<<"\n "; SetConsoleTextAttribute(h, 12);
	int payment(0); payment = ((money>0)?((money*0.87)-3500)*grade:0);
	std::cout<<" [Tab]Timestamps #"<<track[trackId]<<" # "<<"Payment $"<<payment;
	SetConsoleTextAttribute(h, 204);
	pos.X=69; pos.Y=1; SetConsoleCursorPosition(h, pos); std::cout<<" ";
	pos.X=69; pos.Y=2; SetConsoleCursorPosition(h, pos); std::cout<<" ";
	pos.X=69; pos.Y=3; SetConsoleCursorPosition(h, pos); std::cout<<" ";
	SetConsoleTextAttribute(h, 12);
	std::cout<<"\n################################################"<<"#####[m]moveLogs()####"<<std::endl;
}

void getChat(int &lineCount)//gc
{
	std::fstream file;
	std::string line;

	liveChatHead(lineCount);

	file.open("console.log");
		//pobranie linii, które nie mają być wyświetlone
		for(int i = 0; i < lineCount-wyswietlaneWiersze-1; i++)
		{
			getline(file, line);
		}
		//bug fix
		if((lineCount-1)<=wyswietlaneWiersze)
		{
			temp2 = wyswietlaneWiersze;
			wyswietlaneWiersze = lineCount-1;
		}
		//wyświetlenie pozostałych linii
		for(int i = 0; i < wyswietlaneWiersze; i++)
		{
			getline(file, line);
			bool notif = fNicknames(line)||fTransport(line,ang)||fKomunikat(line,ang)||fPrzelewyOd(line,ang)||fPwOd(line,ang)||fTeam(line,0);
			if(notif)
			{
				if(timestamps)
				{
					SetConsoleTextAttribute(h, 160); std::cout<<" "<<line<<std::endl;
				}
				else
				{
					SetConsoleTextAttribute(h, 160); std::cout<<"=>";
					SetConsoleTextAttribute(h, 10);
					if(line.length() > gt)
						line = line.erase(0, gt);		
					for (size_t i = 0; i < line.length(); i++)
					{
						if(line[i] == ':')
						{
							std::cout<<line[i];
							SetConsoleTextAttribute(h, 15);
							continue;
						}
						std::cout<<line[i];
					} std::cout<<"\n";
				}
			}
			else
			{
				if(timestamps)
				{
					SetConsoleTextAttribute(h, 170); std::cout<<" ";
					SetConsoleTextAttribute(h, 10); std::cout<<line<<std::endl;
				}
				else
				{
					if(line.length() > gt)
						line = line.erase(0, gt);	
					if(line[0] == '*')
					{
						SetConsoleTextAttribute(h, 14);
						std::cout<<line<<std::endl;
					}
					else
					{
						SetConsoleTextAttribute(h, 10);
						for (size_t i = 0; i < line.length(); i++)
						{
							if(line[i] == ':')
							{
								std::cout<<line[i];
								SetConsoleTextAttribute(h, 15);
								continue;
							}
							std::cout<<line[i];
						} std::cout<<"\n";
					}
				}
			}
		}
		if((lineCount-1)<=wyswietlaneWiersze) wyswietlaneWiersze = temp2;//bug fix
	file.close();
	pos.X=0; pos.Y=0; SetConsoleCursorPosition(h, pos);
}

void moveLogs()//mv clean and move logs mtasarom console.log to logus.log
{
	std::fstream from;
	std::fstream to;
	std::string line;
	int count = 0;

	from.open("console.log");
		while(!from.eof())
		{
			getline(from, line);
			count++;
		}
		count--;
		from.clear();
		from.seekg(std::ios::beg);

		std::vector <std::string> logs(count);
		to.open("logus.log", std::ios::app);
			for(std::string line : logs)
			{
				getline(from, line);
				to<<line<<std::endl;
			}
		to.close();
	from.close();

	from.open("console.log", std::ios::out);
	from.close();

	cls();
	liveChatHead();
	pos.X=2; pos.Y=5; SetConsoleCursorPosition(h, pos);
	SetConsoleTextAttribute(h, 15);
	std::cout<<"Brak wierszy po przeniesieniu logow!";
}

bool runLiveChat()//flc
{
	s_temp = "start mtasa://"+mtasa;
	system(s_temp.c_str());
	cls();
	Beep(dzwiekGlowny,100);
	bool _quit = liveChat(wyswietlaneWiersze);
	if(!_quit) return 0;
	return 1;
}

void serverConnect()//flc
{
	s_temp = "start mtasa://"+mtasa;
	system(s_temp.c_str());
}

void stopAutoJoin(bool &isAutoJoin)
{
	isAutoJoin = false;
	pos.X=3; pos.Y=4; SetConsoleCursorPosition(h, pos);
	SetConsoleTextAttribute(h, 12); std::cout<<"       CONNECTED!       ";
	Beep(dzwiekGlowny, 500);
}

bool closeLogus(std::string text = "Bye bye")
{
	cls();
	zapis();
	Beep(dzwiekGlowny-100,250);
	std::cout<<"\n"<<text;
	for(int i = 0; i<4; i++){
		std::cout<<".";
		if(i == 2) {Beep(dzwiekGlowny,200); continue;}
		Sleep(400);
	}
	Beep(dzwiekGlowny+100,250);
	return 0;
}

void dots(short duration, short amount)
{
	for (int i = 0;i<amount; i++) {
		std::cout<<".";
		Sleep(duration);
	}
}

int preInputInt(std::string text = "", std::string inputText = "", std::string errorText = "", std::string minMaxText = "", int min = 0, int max = 0)
{
	int temp;
	cls(); std::cout<<" _______________________Logus_pre-config_______________________\n";
	std::cout<<" "<<text<<"\n";
	std::cout<<" "<<inputText<<" ";
	std::cin>>temp;
	while (std::cin.fail() || temp < min || temp > max) {
		cls();
		std::cin.clear();
		std::cin.ignore(INT_MAX,'\n');
		SetConsoleTextAttribute(h, 12);
		std::cout<<" _______________________Logus_pre-config_______________________\n";
		SetConsoleTextAttribute(h, 10);
		std::cout<<" "<<errorText<<"\n";
		std::cout<<" "<<minMaxText<<"\n";
		std::cout<<" "<<inputText<<" ";
		std::cin>>temp;
	}
	return temp;
}

std::string preInputString(std::string text = "", std::string inputText = "", std::string errorText = "")
{
	std::string temp;
	cls(); std::cout<<" _______________________Logus_pre-config_______________________\n";
	std::cout<<" "<<text<<"\n";
	std::cout<<" "<<inputText<<" ";
	std::cin>>temp;
	while (std::cin.fail()) {
		cls();
		std::cin.clear();
		std::cin.ignore(INT_MAX,'\n');
		SetConsoleTextAttribute(h, 12);
		std::cout<<" _______________________Logus_pre-config_______________________\n";
		SetConsoleTextAttribute(h, 10);
		std::cout<<" "<<errorText<<"\n";
		std::cout<<" "<<inputText<<" ";
		std::cin>>temp;
	}
	return temp;
}

int preSelection(std::string Question = "", std::string Answer = "", std::string Answer2 = "", std::string Answer3 = "") // better version of preConfigLegacy i suppose lol
{
		bool sel = 1;
		do {
			cls(); SetConsoleTextAttribute(h, 12);
			std::cout<<" _______________________Logus_pre-config_______________________\n";
			SetConsoleTextAttribute(h, 10);
			if(Question != "") std::cout<<" "<<Question<<"\n";
			if(Answer != "") std::cout<<" [1] "<<Answer<<"\n";
			if(Answer2 != "") std::cout<<" [2] "<<Answer2<<"\n";
			if(Answer3 != "") std::cout<<" [3] "<<Answer3<<"\n";

			switch(getch()) {
				case '1':
				{
					if(Answer == "") {
						sel = 0; break;
					} else {
						sel = 1; return 1;
					}
				}
				case '2':
				{
					if(Answer2 == "") {
						sel = 0; break;
					} else {
						sel = 1; return 2;
					}
				}
				case '3':
				{
					if(Answer3 == "") {
						sel = 0; break;
					} else {
						sel = 1; return 3;
					}
				}
				default:
				{
					sel = 0; break;
				}
			}
		} while(!sel);
		return 0;
}

void preConfig()
{
	SetConsoleOutputCP(65001); // hard-coding ftw
	SetConsoleCP(65001); // should work on Win 7
	std::string _versionName_ = "Logus - preconfig";
	SetConsoleTitleA(_versionName_.c_str());
	SetConsoleTextAttribute(h, 10);
	std::cout<<" Witaj w Logusiu || Welcome to Logus\n";
	std::cout<<" Przechodze do prekonfiguracji || Going to preconfiguration"; dots(50,3); Sleep(5000);

	if(preSelection("Na poczatek wybierzmy jezyk || At the beginning, choose your language", "Polski -- wcisnij 1 aby wybrac", "English -- press 2 to select") ==2 ) ang = 1;

	/* KROKI KONFIGURACJI:
	1. Nick
	2. Czy chcesz ustawic % wyplaty, aktualnie zarobione pieniadze i kursy?
	3. Chcesz wybrac sposob transportu i czas ladowania?
	4. Przenoszenie logów
	5. Autostart

	/* nick */ 

	if(ang) {
		nick = preInputString("Enter your ingame nickname.", "Enter nickname:", "Error. Please enter correct nickname:");
	} else if(codePage852) {
		nick = preInputString("Podaj nick w grze.", "Podaj nick:", "Blad. Podaj prawidlowy nick:");
	} else {
		nick = preInputString("Podaj nick w grze.", "Podaj nick:", "Błąd. Podaj prawidłowy nick:");
	}

	/* pay wage, money and course */

	if(ang) {

		if(preSelection("Do you want to set pay wage, current courses and earned money?", "Yes, I do", "Not really") == 1 ) {
			switch(preSelection("Specify your pay wage.", "I am a trucker/fraction worker, get me out of here", "Press 2 to specify")) {
				case 1:
				{
					grade = 1; cls();
					std::cout<<" _______________________Logus_pre-config_______________________\n";
					std::cout<<" No worries, we set your pay wage to 100%.\n";
					std::cout<<" Press any key to continue..."; getch();
					break;
				}
				case 2:
				{
					grade = preInputInt("Specify your pay wage.", "Pay wage:", "Error. Specify correct pay wage:", "Min 50 max 100.", 50, 100);
					grade /= 100;

					courses = preInputInt("Enter courses that you have on your F4.", "Courses:", "Error. Specify correct amount of courses:", "Number cannot be negative.", 0, INT_MAX
					);

					money = preInputInt("Enter money that you have on your F4.", "Money:", "Error. Specify correct amount of money:", "Number cannot be negative.", 0, INT_MAX);
					break;
				}
				default: break;
			}
		}

	} else if(codePage852) {

		if(preSelection("Czy chcesz ustawic procent wyplaty, kursy oraz pieniadze?", "Tak, chce", "Nie, nie chce") == 1 ) {
			switch(preSelection("Podaj kursy.", "Pracuje we frakcji/jestem truckerem! Zabierz mnie stad", "Wcisnij 2 aby podac")) {
				case 1:
				{
					grade = 1; cls();
					std::cout<<" _______________________Logus_pre-config_______________________\n";
					std::cout<<" Chill utopia, ustawilismy procent wyplaty na 100%.\n";
					std::cout<<" Wcisnij dowolny klawisz aby kontynuowac..."; getch();
					break;
				}
				case 2:
				{				
					grade = preInputInt("Podaj procent wyplaty.", "Procent wyplaty:", "Blad. Podaj prawidlowy procent wyplaty:", "Min 50 max 100.", 50, 100);
					grade /= 100;

					courses = preInputInt("Podaj kursy ktore masz pod F4.", "Kursy:", "Blad. Podaj prawidlowa ilosc kursow:", "Liczba nie moze byc ujemna.", 0, INT_MAX);

					money = preInputInt("Podaj zarobiona gotówkę pod F4.", "Gotowka:", "Blad. Podaj prawidlowa ilosc gotowki:", "Liczba nie moze byc ujemna.", 0, INT_MAX );
					break;
				}
				default: break;
			}
		}

	} else {

		if(preSelection("Czy chcesz ustawić procent wypłaty, kursy oraz pieniędze?", "Tak, chcę", "Nie, nie chcę") == 1 ) {
			switch(preSelection("Podaj kursy.", "Pracuję we frakcji/jestem truckerem! Zabierz mnie stąd", "Wciśnij 2 aby podać")) {
				case 1:
				{
					grade = 1; cls();
					std::cout<<" _______________________Logus_pre-config_______________________\n";
					std::cout<<" Chill utopia, ustawiliśmy procent wypłaty na 100%.\n";
					std::cout<<" Wciśnij dowolny klawisz aby kontynuować..."; getch();
					break;
				}
				case 2:
				{
					grade = preInputInt("Podaj procent wypłaty.", "Procent wypłaty:", "Błąd. Podaj prawidłowy procent wypłaty:", "Min 50 max 100.", 50, 100);
					grade /= 100;

					courses = preInputInt("Podaj kursy które masz pod F4.", "Kursy:", "Błąd. Podaj prawidłową ilość kursów:", "Liczba nie może być ujemna.", 0, INT_MAX);

					money = preInputInt("Podaj zarobioną gotówkę pod F4.", "Gotówka:", "Błąd. Podaj prawidłową ilość kursów:", "Liczba nie może być ujemna.", 0, INT_MAX);
					break;
				}
				default: break;
			}
		}
	}

	/* loading time and transport method */

	if(ang) {

		if(preSelection("Do you want to set loading time and transport method?", "Yes, I do", "Not really") == 1 ) {
			temp2 = preInputInt("Firstly we'll choose loading time.","Enter minutes:", "Error. Enter correct number.", "It has to be a number", 0, INT_MAX);
			temp = preInputInt("Now enter seconds.", "Enter seconds:", "Error. Enter correct number.", "It has to be a number", 0, INT_MAX);
			czas = (temp*60) + temp2;

			if(preSelection("Specify loading method.", "Random", """I will choose""") == 1) random = 1;
		}

	} else if(codePage852) {

		if(preSelection("Chcesz wybrac sposob transportu i czas ladowania?", "Tak, chce", "Nie, nie chce") == 1 ) {
			temp2 = preInputInt("Na poczatek wybierzmy czas ladowania.", "Podaj minuty:", "Blad. Podaj prawidlowa liczbe.", "To musi byc liczba.", 0, INT_MAX);
			temp = preInputInt("Teraz podaj sekundy.", "Podaj sekundy:", "Blad. Podaj prawidlowa liczbe.", "To musi byc liczba.", 0, INT_MAX);
			czas = (temp*60) + temp2;

			if(preSelection("Podaj sposob ladowania.", "Losowy", """Sam wybiore""") == 1) random = 1;
		}

	} else {

		if(preSelection("Chcesz wybrać sposób transportu i czas ładowania?", "Tak, chcę", "Nie, nie chcę") == 1 ) {
			temp2 = preInputInt("Na poczętek wybierzmy czas ładowania.", "Podaj minuty:", "Błąd. Podaj prawidłową liczbę.", "To musi być liczba.", 0, INT_MAX);
			temp = preInputInt("Teraz podaj sekundy.", "Podaj sekundy:", "Błąd. Podaj prawidłową liczbę.", "To musi być liczba.", 0, INT_MAX );
			czas = (temp*60) + temp2;

			if(preSelection( "Podaj sposób ładowania.", "Losowy", """Sam wybiorę""") == 1) random = 1;
		}	
	}

	/* auto log mover */

	if(ang) {

		if(preSelection("Do you want to enable automatic log mover?", "Yes, I do", "No, not really") == 1) {
			autoMoveLogs = preInputInt("Enter how many lines of logs are needed to move them.", "Enter amount:", "Error. Please enter correct ammount", "Number cannot be negative.", 0, INT_MAX);
		}

	} else if(codePage852) {

		if(preSelection("Czy chcesz wlaczyc automatyczne przenoszenie logow?", "Tak, chce", "Nie, nie chce") == 1) {
			autoMoveLogs = preInputInt("Podaj ilosc linijek do przeniesienia logow", "Podaj ilosc:", "Blad. Podaj prawidlowa ilosc", "Liczba nie moze byc ujemna.", 0, INT_MAX);
		}

	} else {

		if(preSelection("Czy chcesz wlączyć automatyczne przenoszenie logów?", "Tak, chcę", "Nie, nie chcę") == 1) {
			autoMoveLogs = preInputInt("Podaj ilość linijek do przeniesienia logów", "Podaj ilość:", "Błąd. Podaj prawidłową ilość", "Liczba nie może być ujemna.", 0, INT_MAX);
		}

	}

	/* fast start */

	if(ang) {

		switch(preSelection("Select Logus' autostart option", "No LiveChat + PTS autostart, but show version info", "LiveChat + PTS autostart, but don't show version info", "No LiveChat + PTS autostart and no version info")) {
			case 1:
			{
				fastStart = 0;
				break;
			}
			case 2:
			{
				fastStart = 1;
				break;
			}
			case 3:
			{
				fastStart = 2;
				break;
			}
			default: break;
		}

	} else if(codePage852) {

		switch(preSelection("Wybierz autostart Logusa", "Brak szybkiego startu LiveChat + PTS, ale pokaz info o wersji", "Szybki start LiveChat + PTS, nie pokazuj info o wersji", "Brak szybkiego startu LiveChat + PTS i nie pokazuj info o wersji")) {
			case 1:
			{
				fastStart = 0;
				break;
			}
			case 2:
			{
				fastStart = 1;
				break;
			}
			case 3:
			{
				fastStart = 2;
				break;
			}
			default: break;
		}

	} else {

		switch(preSelection("Wybierz autostart Logusa", "Brak szybkiego startu LiveChat + PTS, ale pokaż info o wersji", "Szybki start LiveChat + PTS, nie pokazuj info o wersji", "Brak szybkiego startu LiveChat + PTS i nie pokazuj info o wersji")) {
			case 1:
			{
				fastStart = 0;
				break;
			}
			case 2:
			{
				fastStart = 1;
				break;
			}
			case 3:
			{
				fastStart = 2;
				break;
			}
			default: break;
		}

	}

	/* end of preconfig */

	if(ang) {
		cls();
		std::cout<<" Preconfiguration ended succesfully."; dots(100,3);
		std::cout<<"\n You can always change settings in main menu! \n";
		std::cout<<" Press any key to continue.\n"; getch();

	} else if(codePage852) {

		cls();
		std::cout<<" Prekonfiguracja ukonczona pomyslnie."; dots(100,3);
		std::cout<<"\n Ustawienia mozesz w kazdej chwili zmienic w menu glownym!\n";
		std::cout<<" Wcisnij dowolny klawisz aby kontynuowac.\n"; getch();

	} else {

		cls();
		std::cout<<" Prekonfiguracja ukończona pomyślnie."; dots(100,3);
		std::cout<<"\n Ustawienia możesz w każdej chwili zmienić w menu glównym!\n";
		std::cout<<" Wciśnij dowolny klawisz aby kontynuować.\n"; getch();
	}
}