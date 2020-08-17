// Copyright (C) 2018-2020  DarXe, Niventill

#include <climits>

void color(std::string value)
{
	std::string value0 = "color 0"+value;
	system(value0.c_str());
}

void serverConnect()//flc
{
	#ifndef dbg
	s_temp = "start mtasa://"+serverIP;
	system(s_temp.c_str());
	#endif
}

bool runLiveChat()//flc
{
	serverConnect();
	cls();
	Beep(dzwiekGlowny,100);
	bool _quit = liveChat(wyswietlaneWiersze);
	if(!_quit) return 0;
	return 1;
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

int cfgInputInt(bool preHead, bool isCls, std::string text = "", std::string inputText = "", std::string errorText = "", std::string minMaxText = "", int min = 0, int max = 0)
{
	if(isCls) cls();
	if(preHead) std::cout<<" _______________________Logus_pre-config_______________________\n";
	std::cout<<" "<<text<<"\n";
	std::cout<<" "<<inputText<<" ";
	std::cin>>temp;
	while (std::cin.fail() || temp < min || temp > max) {
		cls();
		std::cin.clear();
		std::cin.ignore(INT_MAX,'\n');
		SetConsoleTextAttribute(h, 12);
		if(preHead) std::cout<<" _______________________Logus_pre-config_______________________\n";
		SetConsoleTextAttribute(h, 10);
		std::cout<<" "<<errorText<<"\n";
		std::cout<<" "<<minMaxText<<"\n";
		std::cout<<" "<<inputText<<" ";
		std::cin>>temp;
	}
	return temp;
}

std::string cfgInputString(bool preHead, bool isCls, std::string text = "", std::string inputText = "", std::string errorText = "")
{
	std::string temp;
	if(isCls) cls();
	if(preHead) std::cout<<" _______________________Logus_pre-config_______________________\n";
	if(text != "") std::cout<<" "<<text<<"\n";
	std::cout<<" "<<inputText<<" ";
	std::cin>>temp;
	while (std::cin.fail()) {
		cls();
		std::cin.clear();
		std::cin.ignore(INT_MAX,'\n');
		SetConsoleTextAttribute(h, 12);
		if(preHead) std::cout<<" _______________________Logus_pre-config_______________________\n";
		SetConsoleTextAttribute(h, 10);
		std::cout<<" "<<errorText<<"\n";
		std::cout<<" "<<inputText<<" ";
		std::cin>>temp;
	}
	return temp;
}

int cfgSelection(bool preHead, std::string Question = "", std::string Answer = "", std::string Answer2 = "", std::string Answer3 = "", std::string Answer4 = "") // better version of preConfigLegacy i suppose lol
{
		bool sel = 1;
		do {
			cls(); SetConsoleTextAttribute(h, 12);
			if(preHead) std::cout<<" _______________________Logus_pre-config_______________________\n";
			SetConsoleTextAttribute(h, 10);
			if(Question != "") std::cout<<" "<<Question<<"\n";
			if(Answer != "") std::cout<<" [1] "<<Answer<<"\n";
			if(Answer2 != "") std::cout<<" [2] "<<Answer2<<"\n";
			if(Answer3 != "") std::cout<<" [3] "<<Answer3<<"\n";
			if(Answer4 != "") std::cout<<" [4] "<<Answer4<<"\n";

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
				case '4':
				{
					if(Answer4 == "") {
						sel = 0; break;
					} else {
						sel = 1; return 4;
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

	if(cfgSelection(1, "Na poczatek wybierzmy jezyk || Choose your language", "Polski -- wcisnij 1 aby wybrac", "English -- press 2 to select") ==2 ) engLang = 1;

	/* KROKI KONFIGURACJI:
	1. Nick
	2. Czy chcesz ustawic % wyplaty, aktualnie zarobione pieniadze i kursy?
	3. Chcesz wybrac sposob transportu i czas ladowania?
	4. Przenoszenie logów
	5. Autostart

	/* nick */ 

	if(engLang) {
		nick = cfgInputString(1, 1, "Enter your ingame nickname.", "Enter nickname:", "Error. Please enter correct nickname:");
	} else if(codePage852) {
		nick = cfgInputString(1, 1, "Podaj nick w grze.", "Podaj nick:", "Blad. Podaj prawidlowy nick:");
	} else {
		nick = cfgInputString(1, 1, "Podaj nick w grze.", "Podaj nick:", "Błąd. Podaj prawidłowy nick:");
	}

	/* pay wage, money and course */

	if(engLang) {

		if(cfgSelection(1, "Do you want to set pay wage, current courses and earned money?", "Yes, I do", "Not really") == 1 ) {
			switch(cfgSelection(1, "Specify your pay wage.", "I am a trucker/fraction worker, get me out of here", "Press 2 to specify")) {
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
					grade = cfgInputInt(1, 1,  "Specify your pay wage.", "Pay wage:", "Error. Specify correct pay wage:", "Min 50 max 100.", 50, 100);
					grade /= 100;

					courses = cfgInputInt(1, 1,  "Enter courses that you have on your F4.", "Courses:", "Error. Specify correct amount of courses:", "Number cannot be negative.", 0, INT_MAX
					);

					money = cfgInputInt(1, 1,  "Enter money that you have on your F4.", "Money:", "Error. Specify correct amount of money:", "Number cannot be negative.", 0, INT_MAX);
					break;
				}
				default: break;
			}
		}

	} else if(codePage852) {

		if(cfgSelection(1, "Czy chcesz ustawic procent wyplaty, kursy oraz pieniadze?", "Tak, chce", "Nie, nie chce") == 1 ) {
			switch(cfgSelection(1, "Podaj kursy.", "Pracuje we frakcji/jestem truckerem! Zabierz mnie stad", "Wcisnij 2 aby podac")) {
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
					grade = cfgInputInt(1, 1,  "Podaj procent wyplaty.", "Procent wyplaty:", "Blad. Podaj prawidlowy procent wyplaty:", "Min 50 max 100.", 50, 100);
					grade /= 100;

					courses = cfgInputInt(1, 1,  "Podaj kursy ktore masz pod F4.", "Kursy:", "Blad. Podaj prawidlowa ilosc kursow:", "Liczba nie moze byc ujemna.", 0, INT_MAX);

					money = cfgInputInt(1, 1,  "Podaj zarobiona gotówkę pod F4.", "Gotowka:", "Blad. Podaj prawidlowa ilosc gotowki:", "Liczba nie moze byc ujemna.", 0, INT_MAX );
					break;
				}
				default: break;
			}
		}

	} else {

		if(cfgSelection(1, "Czy chcesz ustawić procent wypłaty, kursy oraz pieniędze?", "Tak, chcę", "Nie, nie chcę") == 1 ) {
			switch(cfgSelection(1, "Podaj kursy.", "Pracuję we frakcji/jestem truckerem! Zabierz mnie stąd", "Wciśnij 2 aby podać")) {
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
					grade = cfgInputInt(1, 1,  "Podaj procent wypłaty.", "Procent wypłaty:", "Błąd. Podaj prawidłowy procent wypłaty:", "Min 50 max 100.", 50, 100);
					grade /= 100;

					courses = cfgInputInt(1, 1,  "Podaj kursy które masz pod F4.", "Kursy:", "Błąd. Podaj prawidłową ilość kursów:", "Liczba nie może być ujemna.", 0, INT_MAX);

					money = cfgInputInt(1, 1,  "Podaj zarobioną gotówkę pod F4.", "Gotówka:", "Błąd. Podaj prawidłową ilość kursów:", "Liczba nie może być ujemna.", 0, INT_MAX);
					break;
				}
				default: break;
			}
		}
	}

	/* loading time and transport method */

	if(engLang) {

		if(cfgSelection(1, "Do you want to set loading time and transport method?", "Yes, I do", "Not really") == 1 ) {
			temp2 = cfgInputInt(1, 1,  "Firstly we'll choose loading time.","Enter minutes:", "Error. Enter correct number.", "It has to be a number", 0, INT_MAX);
			temp = cfgInputInt(1, 1,  "Now enter seconds.", "Enter seconds:", "Error. Enter correct number.", "It has to be a number", 0, INT_MAX);
			czas = (temp*60) + temp2;

			if(cfgSelection(1, "Specify loading method.", "Random", """I will choose""") == 1) random = 1;
		}

	} else if(codePage852) {

		if(cfgSelection(1, "Chcesz wybrac sposob transportu i czas ladowania?", "Tak, chce", "Nie, nie chce") == 1 ) {
			temp2 = cfgInputInt(1, 1,  "Na poczatek wybierzmy czas ladowania.", "Podaj minuty:", "Blad. Podaj prawidlowa liczbe.", "To musi byc liczba.", 0, INT_MAX);
			temp = cfgInputInt(1, 1,  "Teraz podaj sekundy.", "Podaj sekundy:", "Blad. Podaj prawidlowa liczbe.", "To musi byc liczba.", 0, INT_MAX);
			czas = (temp*60) + temp2;

			if(cfgSelection(1, "Podaj sposob ladowania.", "Losowy", """Sam wybiore""") == 1) random = 1;
		}

	} else {

		if(cfgSelection(1, "Chcesz wybrać sposób transportu i czas ładowania?", "Tak, chcę", "Nie, nie chcę") == 1 ) {
			temp2 = cfgInputInt(1, 1,  "Na początek wybierzmy czas ładowania.", "Podaj minuty:", "Błąd. Podaj prawidłową liczbę.", "To musi być liczba.", 0, INT_MAX);
			temp = cfgInputInt(1, 1,  "Teraz podaj sekundy.", "Podaj sekundy:", "Błąd. Podaj prawidłową liczbę.", "To musi być liczba.", 0, INT_MAX );
			czas = (temp*60) + temp2;

			if(cfgSelection( "Podaj sposób ładowania.", "Losowy", """Sam wybiorę""") == 1) random = 1;
		}	
	}

	/* auto log mover */

	if(engLang) {

		if(cfgSelection(1, "Do you want to enable automatic log mover?", "Yes, I do", "No, not really") == 1) {
			autoMoveLogs = cfgInputInt(1, 1,  "Enter how many lines of logs are needed to move them.", "Enter amount:", "Error. Please enter correct ammount", "Number cannot be negative.", 0, INT_MAX);
		}

	} else if(codePage852) {

		if(cfgSelection(1, "Czy chcesz wlaczyc automatyczne przenoszenie logow?", "Tak, chce", "Nie, nie chce") == 1) {
			autoMoveLogs = cfgInputInt(1, 1,  "Podaj ilosc linijek do przeniesienia logow", "Podaj ilosc:", "Blad. Podaj prawidlowa ilosc", "Liczba nie moze byc ujemna.", 0, INT_MAX);
		}

	} else {

		if(cfgSelection(1, "Czy chcesz wlączyć automatyczne przenoszenie logów?", "Tak, chcę", "Nie, nie chcę") == 1) {
			autoMoveLogs = cfgInputInt(1, 1,  "Podaj ilość linijek do przeniesienia logów", "Podaj ilość:", "Błąd. Podaj prawidłową ilość", "Liczba nie może być ujemna.", 0, INT_MAX);
		}

	}

	/* fast start */

	if(engLang) {

		switch(cfgSelection(1, "Select Logus' autostart option", "No LiveChat + PTS autostart, but show version info", "LiveChat + PTS autostart, but don't show version info", "No LiveChat + PTS autostart and no version info")) {
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

		switch(cfgSelection(1, "Wybierz autostart Logusa", "Brak szybkiego startu LiveChat + PTS, ale pokaz info o wersji", "Szybki start LiveChat + PTS, nie pokazuj info o wersji", "Brak szybkiego startu LiveChat + PTS i nie pokazuj info o wersji")) {
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

		switch(cfgSelection(1, "Wybierz autostart Logusa", "Brak szybkiego startu LiveChat + PTS, ale pokaż info o wersji", "Szybki start LiveChat + PTS, nie pokazuj info o wersji", "Brak szybkiego startu LiveChat + PTS i nie pokazuj info o wersji")) {
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

	if(engLang) {
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