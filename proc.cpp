// Copyright (C) 2018-2019  DarXe
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
	for (int i = 0;i<amount; i++)
	{
		std::cout<<".";
		Sleep(duration);
	}
}

void preConfig()
{
	SetConsoleOutputCP(65001); // hard-coding ftw
	SetConsoleCP(65001); // i believe that it should work on Win 7
	std::string _versionName_ = "Logus - preconfig";
	SetConsoleTitleA(_versionName_.c_str());
	SetConsoleTextAttribute(h, 10);
	std::cout<<" Witaj w Logusiu"<<std::endl;
	std::cout<<" Przechodze do prekonfiguracji"; dots(50,3); Sleep(5000);
	cls();
	std::cout<<" Welcome to Logus"<<std::endl;
	std::cout<<" Going to preconfiguration"; dots(50,3); Sleep(5000); cls();
	SetConsoleTextAttribute(h, 12);
	std::cout<<" _______________________Logus pre config_______________________"<<std::endl;
	SetConsoleTextAttribute(h, 10);
	std::cout<<" Na poczatek wybierzmy jezyk"; dots(50,3); std::cout<<std::endl;
	std::cout<<" At the beginning, choose your language"; dots(50,3); std::cout<<"      "<<std::endl; Sleep(5000);
	bool sel = 1;
	do // wybor jezyka
	{
		cls(); SetConsoleTextAttribute(h, 12);
		std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
		SetConsoleTextAttribute(h, 10);
		if(sel)
		{
			std::cout<<" [1] Polski -- wcisnij 1 aby wybrac"<<std::endl;
			std::cout<<" [2] English -- press 2 to select"<<std::endl;
		}
		else
		{
			std::cout<<" [1] Polski -- wcisnij 1 aby wybrac!"<<std::endl;
			std::cout<<" [2] English -- press 2 to select!"<<std::endl;
		}
		switch(getch())
		{
			case '1':
			{
				ang = 0;
				do // system selection to minimize good old Win7 bugs
				{
					cls(); SetConsoleTextAttribute(h, 12);
					std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
					SetConsoleTextAttribute(h, 10);
						std::cout<<" Jaki system operacyjny posiadasz?"<<std::endl;
						std::cout<<" [1] Windows 10"<<std::endl;
						std::cout<<" [2] Windows 7 lub nizej"<<std::endl;
					switch(getch())
					{
						case '1':
						{
							codePage852 = 0;
							sel = 1;
							cls();
							SetConsoleTextAttribute(h, 12);
							std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
							SetConsoleTextAttribute(h, 10);
							std::cout<<" Podaj swój nick: ";
							std::cin>>nick;
							break;
						}
						case '2':
						{
							codePage852 = 1;
							menuGlowne = 1;
							SetConsoleOutputCP(852); // hard-coding ftw
							SetConsoleCP(852); // i believe that it should work on Win 7
							cls();
							SetConsoleTextAttribute(h, 12);
							std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
							SetConsoleTextAttribute(h, 10);
							std::cout<<" UWAGA! Krzaczki podczas korzystania z LiveChat sa nie do unikniecia (chyba, ze zainstalujesz Windows 10)."<<std::endl;
							std::cout<<" Istnieje szansa na naprawienie bledu w przyszlosci."<<std::endl;
							std::cout<<"Wcisnij dowolny klawisz aby kontynuowac."; getch();
							sel = 1;
							cls();
							SetConsoleTextAttribute(h, 12);
							std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
							SetConsoleTextAttribute(h, 10);
							std::cout<<" Podaj swoj nick: ";
							std::cin>>nick;
							break;
						}
						default:
						{
							sel = 0; break;
						}
					}
				} while(!sel);
				break;
			}
			case '2':
			{
				ang = 1;
				sel = 1;
				cls();
				SetConsoleTextAttribute(h, 12);
				std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
				SetConsoleTextAttribute(h, 10);
				std::cout<<" Enter your nickname: ";
				std::cin>>nick;
				break;
			}
			default:
			{
				sel = 0; break;
			}
		}
	} while(!sel);
	do // choose fraction/company
	{
		cls(); SetConsoleTextAttribute(h, 12);
		std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
		SetConsoleTextAttribute(h, 10);
		if(ang)
		{
			std::cout<<" Do you work in a company or a fraction?"<<std::endl;
			std::cout<<" [1] I work in a company"<<std::endl;
			std::cout<<" [2] I work in a fraction"<<std::endl;
			std::cout<<" [3] I dont work anywhere"<<std::endl;
		}
		else
		{
			if(codePage852)
			{
				std::cout<<" Pracujesz we frakcji czy w firmie?"<<std::endl;
				std::cout<<" [1] Pracuje w firmie"<<std::endl;
				std::cout<<" [2] Pracuje we frakcji"<<std::endl;
				std::cout<<" [3] Nigdzie nie pracuje"<<std::endl;
			}
			else
			{
				std::cout<<" Pracujesz we frakcji czy w firmie?"<<std::endl;
				std::cout<<" [1] Pracuję w firmie"<<std::endl;
				std::cout<<" [2] Pracuję we frakcji"<<std::endl;
				std::cout<<" [3] Nigdzie nie pracuję"<<std::endl;
			}
		}
		switch(getch())
		{
			case '1':
			case '2':
			case '3':
			{
				do // money and courses
				{
					cls(); SetConsoleTextAttribute(h, 12);
					std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
					SetConsoleTextAttribute(h, 10);
					if(ang)
					{
						std::cout<<" Do you want to set pay wage, current courses and earned money?"<<std::endl;
						std::cout<<" [1] I do"<<std::endl;
						std::cout<<" [2] Not really"<<std::endl;
					}
					else
					{
						if(codePage852)
						{
						std::cout<<" Czy chcesz ustawic % wyplaty, aktualnie zarobione pieniadze i kursy?"<<std::endl;
						std::cout<<" [1] Tak, chce"<<std::endl;
						std::cout<<" [2] Nie, nie chce"<<std::endl;
						}
						else
						{
						std::cout<<" Czy chcesz ustawić % wyplaty, aktualnie zarobione pieniędze i kursy?"<<std::endl;
						std::cout<<" [1] Tak, chcę"<<std::endl;
						std::cout<<" [2] Nie, nie chcę"<<std::endl;
						}
					}
					switch(getch())
					{
						case '1':
						{
								cls();
								do // pay wage if in a company
								{
									cls(); SetConsoleTextAttribute(h, 12);
									std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
									SetConsoleTextAttribute(h, 10);
									if(ang)
									{
										std::cout<<" Specify your pay wage."<<std::endl;
										std::cout<<" [1] But... I'm a trucker/fraction worker..."<<std::endl;
										std::cout<<" [2] Press 2 to specify your pay wage"<<std::endl;
									}
									else
									{
										if(codePage852)
										{
											std::cout<<" Podaj % wyplaty w firmie."<<std::endl;
											std::cout<<" [1] Ale ja jestem truckerem/pracownikiem frakcji..."<<std::endl;
											std::cout<<" [2] Wcisnij 2 aby podac"<<std::endl;
										}
										else
										{
											std::cout<<" Podaj % wypłaty w firmie."<<std::endl;
											std::cout<<" [1] Ale ja jestem truckerem/pracownikiem frakcji..."<<std::endl;
											std::cout<<" [2] Wciśnij 2 aby podać"<<std::endl;
										}
										
									}
									switch(getch())
									{
										case '1':
										{
											cls();
											SetConsoleTextAttribute(h, 12);
											std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
											SetConsoleTextAttribute(h, 10);
											if(ang)
											{
												std::cout<<" Don't panic, we set your pay wage to 100%."<<std::endl;
												std::cout<<" Press any key to continue..."; getch(); cls();
											}
											else
											{
												if(codePage852)
												{
													std::cout<<" Nie panikuj, ustawilismy % wyplaty na 100%."<<std::endl;
													std::cout<<" Wcisnij dowolny klawisz aby kontynuowac..."; getch(); cls();
												}
												else
												{
													std::cout<<" Nie panikuj, ustawiliśmy % wypłaty na 100%."<<std::endl;
													std::cout<<" Wciśnij dowolny klawisz aby kontynuować..."; getch(); cls();
												}
											}
											
											sel = 1;
											grade = 1;
											break;
										}
										case '2':
										{
											cls(); SetConsoleTextAttribute(h, 12);
											std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
											SetConsoleTextAttribute(h, 10);
											if(ang)
											{
												std::cout<<" Enter your pay wage."<<std::endl;
												std::cout<<" Enter a number (without %): "; std::cin>>grade; std::cout<<std::endl;
												while (std::cin.fail() && grade < 50 || grade > 100)
												{
													cls();
													std::cin.clear();
													std::cin.ignore(INT_MAX,'\n');
													SetConsoleTextAttribute(h, 12);
													std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
													SetConsoleTextAttribute(h, 10);
													std::cout<<" You can only enter numbers!\n";
													std::cout<<" Number can't be below 50 or above 100!"<<std::endl;
													std::cout<<" Enter a number: "<<std::endl;
													std::cin>>grade;
												}
												grade /= 100;
											}
											else
											{
												if(codePage852)
												{
													std::cout<<" Podaj % wyplaty."<<std::endl;
													std::cout<<" Podaj liczbe (bez %): "; std::cin>>grade; std::cout<<std::endl;
												}
												else
												{
													std::cout<<" Podaj % wypłaty."<<std::endl;
													std::cout<<" Podaj liczbę (bez %): "; std::cin>>grade; std::cout<<std::endl;
												}
												while (std::cin.fail() && grade < 50 || grade > 100)
												{
													cls();
													std::cin.clear();
													std::cin.ignore(INT_MAX,'\n');
													SetConsoleTextAttribute(h, 12);
													std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
													SetConsoleTextAttribute(h, 10);
													if(codePage852)
													{
														std::cout<<" Mozesz podac tylko liczbe!\n";
														std::cout<<" Liczba nie moze byc mniejsza niz 50 i wieksza niz 100!"<<std::endl;
														std::cout<<" Podaj liczbe: "<<std::endl;
													}
													else
													{
														std::cout<<" Możesz podać tylko liczbę!\n";
														std::cout<<" Liczba nie może być mniejsza niż 50 i większa niż 100!"<<std::endl;
														std::cout<<" Podaj liczbę: "<<std::endl;
													}
													std::cin>>grade;
												}
												grade /= 100;
											}
											sel = 1;
											break;
										}
										default:
										{
											sel = 0; break;
										}
									}

								} while(!sel);
								cls();
								SetConsoleTextAttribute(h, 12);
								std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
								SetConsoleTextAttribute(h, 10);
								if(ang)
								{
									std::cout<<" Enter courses that you have on your F4."<<std::endl;
									std::cout<<" Enter a number: "; std::cin>>courses; std::cout<<std::endl;
									while (std::cin.fail() && courses < 0 || courses > 9999)
									{
										cls();
										std::cin.clear();
										std::cin.ignore(INT_MAX,'\n');
										SetConsoleTextAttribute(h, 12);
										std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
										SetConsoleTextAttribute(h, 10);
										std::cout<<" You can only enter numbers!\n";
										std::cout<<" Number can't be below 0 or above 9999!"<<std::endl;
										std::cout<<" Enter a number: "<<std::endl;
										std::cin>>courses;
									}
									cls();
									SetConsoleTextAttribute(h, 12);
									std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
									SetConsoleTextAttribute(h, 10);
									std::cout<<" Enter money that you have on your F4."<<std::endl;
									std::cout<<" Enter a number: "; std::cin>>money; std::cout<<std::endl;
									while (std::cin.fail() && money < 0 || money > 9999999)
									{
										cls();
										std::cin.clear();
										std::cin.ignore(INT_MAX,'\n');
										SetConsoleTextAttribute(h, 12);
										std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
										SetConsoleTextAttribute(h, 10);
										std::cout<<" You can only enter numbers!\n";
										std::cout<<" Number can't be below 0 or above 9999999!"<<std::endl;
										std::cout<<" Enter a number: "<<std::endl;
										std::cin>>money;
									}
									sel = 1;
								}
								else
								{
									if(codePage852)
									{
										std::cout<<" Podaj kursy ktore masz pod F4."<<std::endl;
										std::cout<<" Podaj liczbe: "; std::cin>>courses; std::cout<<std::endl;
									}
									else
									{
										std::cout<<" Podaj kursy które masz pod F4."<<std::endl;
										std::cout<<" Podaj liczbę: "; std::cin>>courses; std::cout<<std::endl;
									}
									
									while (std::cin.fail() && courses < 0 || courses > 9999)
									{
										cls();
										std::cin.clear();
										std::cin.ignore(INT_MAX,'\n');
										SetConsoleTextAttribute(h, 12);
										std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
										SetConsoleTextAttribute(h, 10);
										if(codePage852)
										{
											std::cout<<" Musisz podac liczbe!\n";
											std::cout<<" Liczba nie moze byc negatywna lub powyzej 9999!\n";
											std::cout<<" Wpisz liczbe: ";
										}
										else
										{
											std::cout<<" Musisz podać liczbę!\n";
											std::cout<<" Liczba nie może byc negatywna lub powyżej 9999!\n";
											std::cout<<" Wpisz liczbę: ";
										}
										std::cin>>courses;
									}
										cls();
										SetConsoleTextAttribute(h, 12);
										std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
										SetConsoleTextAttribute(h, 10);
										if(codePage852)
										{
											std::cout<<" Podaj zarobek ktory masz pod F4."<<std::endl;
											std::cout<<" Wpisz liczbe: "; std::cin>>money; std::cout<<std::endl;
										}
										else
										{
											std::cout<<" Podaj zarobek który masz pod F4."<<std::endl;
											std::cout<<" Wpisz liczbę: "; std::cin>>money; std::cout<<std::endl;
										}
									while (std::cin.fail() && money < 0 || money > 9999999)
									{
										cls();
										std::cin.clear();
										std::cin.ignore(INT_MAX,'\n');
										SetConsoleTextAttribute(h, 12);
										std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
										SetConsoleTextAttribute(h, 10);
										if(codePage852)
										{
											std::cout<<" Musisz podac liczbe!\n";
											std::cout<<" Liczba nie moze byc negatywna lub powyzej 9999999!\n";
											std::cout<<" Wpisz liczbe: "<<std::endl;
										}
										else
										{
											std::cout<<" Musisz podać liczbę!\n";
											std::cout<<" Liczba nie może być negatywna lub powyżej 9999999!\n";
											std::cout<<" Wpisz liczbę: "<<std::endl;
										}
										std::cin>>money;
									}
									sel = 1;
								}
						}
						case '2':
						{
							sel = 1; break;
						}
						default:
						{
							sel = 0; break;
						}
					}
				} while(!sel);
				break;
			}
			default:
			{
				sel = 0; break;
			}
		}
	} while(!sel);
	do // selection of loading time and transport method
	{
		cls(); SetConsoleTextAttribute(h, 12);
		std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
		SetConsoleTextAttribute(h, 10);
		if(ang)
		{
			std::cout<<" Do you want to set loading time and transport method?"<<std::endl;
			std::cout<<" [1] Sure"<<std::endl;
			std::cout<<" [2] I don't want to"<<std::endl;
		}
		else
		{
			if(codePage852)
			{
				std::cout<<" Chcesz wybrac sposob transportu i czas ladowania?"<<std::endl;
				std::cout<<" [1] Pewnie"<<std::endl;
				std::cout<<" [2] Nie, nie chce"<<std::endl;
			}
			else
			{
				std::cout<<" Chcesz wybrać sposób transportu i czas ładowania?"<<std::endl;
				std::cout<<" [1] Pewnie"<<std::endl;
				std::cout<<" [2] Nie, nie chcę"<<std::endl;
			}
		}
		switch(getch())
		{
			case '1':
			{
				do 
				{
					cls(); SetConsoleTextAttribute(h, 12);
					std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
					SetConsoleTextAttribute(h, 10);
					if(ang)
					{
						std::cout<<" First, we will choose loading time."<<std::endl;
						std::cout<<"Enter minutes: "; std::cin>>temp2; std::cout<<std::endl;
						while (std::cin.fail())
						{
							cls(); SetConsoleTextAttribute(h, 12);
							std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
							SetConsoleTextAttribute(h, 10);
							std::cin.clear();
							std::cin.ignore(INT_MAX,'\n');
							std::cout<<"You can only enter numbers!\n";
							std::cout<<"Enter minutes: "<<std::endl;
							std::cin>>temp2;
						}
							cls();
							std::cout<<" Now enter seconds."<<std::endl;
							std::cout<<"Enter seconds: "; std::cin>>temp; std::cout<<std::endl;
						while (std::cin.fail())
						{
							cls(); SetConsoleTextAttribute(h, 12);
							std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
							SetConsoleTextAttribute(h, 10);
							std::cin.clear();
							std::cin.ignore(INT_MAX,'\n');
							std::cout<<"You can only enter numbers!\n";
							std::cout<<"Enter seconds: "<<std::endl;
							std::cin>>money;
						}
						czas = (temp*60) + temp2;
						sel = 1;
					}
					else
					{
						if(codePage852)
						{
							std::cout<<" Na poczatek wybierzmy czas ladowania towaru."<<std::endl;
							std::cout<<"Podaj minuty: "; std::cin>>temp2; std::cout<<std::endl;
						}
						else
						{
							std::cout<<" Na początek wybierzmy czas ładowania towaru."<<std::endl;
							std::cout<<"Podaj minuty: "; std::cin>>temp2; std::cout<<std::endl;
						}
						while (std::cin.fail())
						{
							cls(); SetConsoleTextAttribute(h, 12);
							std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
							SetConsoleTextAttribute(h, 10);
							std::cin.clear();
							std::cin.ignore(INT_MAX,'\n');
							if(codePage852)
							{
								std::cout<<"Mozesz podac tylko liczby!\n";
								std::cout<<"Podaj minuty: "<<std::endl;
							}
							else
							{
								std::cout<<"Możesz podać tylko liczby!\n";
								std::cout<<"Podaj minuty: "<<std::endl;
							}
							std::cin>>temp2;
						}
							cls(); SetConsoleTextAttribute(h, 12);
							std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
							SetConsoleTextAttribute(h, 10);
							std::cout<<" Teraz podaj sekundy."<<std::endl;
							std::cout<<"Podaj sekundy: "; std::cin>>temp; std::cout<<std::endl;
						while (std::cin.fail())
						{
							cls(); SetConsoleTextAttribute(h, 12);
							std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
							SetConsoleTextAttribute(h, 10);
							std::cin.clear();
							std::cin.ignore(INT_MAX,'\n');
							if(codePage852)
							{
								std::cout<<"Mozesz podac tylko liczby!\n";
								std::cout<<"Podaj sekundy: "<<std::endl;
							}
							else
							{
								std::cout<<"Możesz podać tylko liczby!\n";
								std::cout<<"Podaj sekundy: "<<std::endl;
							}
							std::cin>>money;
						}
						czas = (temp*60) + temp2;
						sel = 1;
					}
				} while(!sel);
				break;
			}
			case '2':
			{
				sel = 1;
				break;
			}
			default:
			{
				sel = 0; break;
			}
		}
	} while(!sel);
	do // fast start selection
	{
		cls(); SetConsoleTextAttribute(h, 12);
		std::cout<<" _______________________Logus_pre-config_______________________"<<std::endl;
		SetConsoleTextAttribute(h, 10);
		if(ang)
		{
			std::cout<<" Select Logus' autostart option"<<std::endl;
			std::cout<<" [1] No LiveChat + PTS autostart, but show version info"<<std::endl;
			std::cout<<" [2] LiveChat + PTS autostart, but don't show version info"<<std::endl;
			std::cout<<" [3] No LiveChat + PTS autostart and no version info"<<std::endl;
		}
		else
		{
			std::cout<<" Wybierz tryb autostartu Logusa"<<std::endl;
			if(codePage852)
			{
				std::cout<<" [1] Brak szybkiego startu LiveChat + PTS, ale pokaz info o wersji"<<std::endl;
			}
			else
			{
				std::cout<<" [1] Brak szybkiego startu LiveChat + PTS, ale pokaż info o wersji"<<std::endl;
			}
			std::cout<<" [2] Szybki start LiveChat + PTS, nie pokazuj info o wersji"<<std::endl;
			std::cout<<" [3] Brak szybkiego startu LiveChat + PTS i nie pokazuj info o wersji"<<std::endl;
		}
		switch(getch())
		{
			case '1':
			{
				sel = 1;
				fastStart = 0;
				break;
			}
			case '2':
			{
				sel = 1;
				fastStart = 1;
				break;
			}
			case '3':
			{
				sel = 1;
				fastStart = 2;
				break;
			}
			default:
			{
				sel = 0; break;
			}
		}
	} while(!sel);
	if(ang)
	{
		cls();
		std::cout<<" Preconfiguration ended succesfully."; dots(100,3); std::cout<<std::endl;
		std::cout<<" You can always change settings in main menu! \n";
		std::cout<<" Press any key to continue."; getch();
	}
	if(codePage852)
	{
		cls();
		std::cout<<" Prekonfiguracja ukonczona pomyslnie."; dots(100,3); std::cout<<std::endl;
		std::cout<<" Ustawienia mozesz w kazdej chwili zmienic w menu glownym!\n";
		std::cout<<" Wcisnij dowolny klawisz aby kontynuowac."; getch();
	}
	else
	{
		cls();
		std::cout<<" Prekonfiguracja ukończona pomyślnie."; dots(100,3); std::cout<<std::endl;
		std::cout<<" Ustawienia możesz w każdej chwili zmienić w menu glównym!\n";
		std::cout<<" Wciśnij dowolny klawisz aby kontynuować."; getch();
	}
}