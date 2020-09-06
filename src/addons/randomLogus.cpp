// Copyright © 2018-2020  DarXe
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.

#include "randomLogus.hpp"

int lottoLogus()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	SetConsoleOutputCP(65001);
	std::vector <std::string> nicknames;
	std::vector <std::string> winners;
	std::vector <short> winnersId;
	std::vector <short> playersId; //lista do tasowania, losowanie wygranych bez powtorzen
	std::string nick = "";
	char wyb = ' ';
	int temp(0);
	
	while(true)
	{
		SetConsoleTextAttribute(h, 112);
		cls();
		std::cout<<" ________________________$ Lotto Logus $________________________"<<std::endl;
		std::cout<<" [1] Dodaj graczy"<<std::endl;
		std::cout<<" [L] Losowanie"<<std::endl;
		std::cout<<" [R] Replay losowania wygranych"<<std::endl;
		std::cout<<" [S] Statystyki, % szansa wygranej"<<std::endl;
		std::cout<<" [Esc] Exit"<<std::endl;
		std::cout<<" _______________________________________________________________\n"<<std::endl;
		wyb = wybor();
		SetConsoleTextAttribute(h, 15);
		switch (wyb)
		{
		case 27:
			cls();
			return 0;
		case 's':
		case 'S':
			lottoLogusStats(nicknames);
			break;

		case '1':
			{
				cls();
				while(true)
				{
					cls();
					playerList(nicknames);
					std::cout<<" [1] Dodawanie..."<<std::endl;
					std::cout<<" [x] Usuń ostatniego gracza"<<std::endl;
					std::cout<<" [a] Usuń wszystkich graczy"<<std::endl;
					std::cout<<" [f] Wypełnij listę literami"<<std::endl;
					std::cout<<" [Esc] Powrót\n"<<std::endl;
					wyb = wybor();
					if(wyb == 27) break;
					switch (wyb)
					{
					case '1':
						{
							while(true)
							{
								cls();
								playerList(nicknames);

								std::cout<<" Podaj nick: "; std::cin>>nick;
								if(nicknames.empty())
								{
									nicknames.push_back("");
									nicknames.push_back(nick);
								}
								else if(!((nicknames.size()+1) % 6))
								{
									nicknames.push_back(nick);
									nicknames.push_back("Pusty los");
								}
								else nicknames.push_back(nick);

								cls();
								playerList(nicknames);
								std::cout<<" [Esc] Zakończ | [Inny klawisz] Następny gracz"<<std::endl;
								if(getch() == 27) break;
							}
							
						}
						break;
					case 'x':
					case 'X':
						{
							if(nicknames.empty())
							{
								std::cout<<" Brak graczy\a";
								Sleep(500);
							}
							else nicknames.pop_back();
						}
						break;
					case 'a':
					case 'A':
						{
							if(nicknames.empty())
							{
								std::cout<<" Brak graczy\a";
								Sleep(500);
							}
							else
							{
								cls();
								std::cout<<" Jesteś tego pewien?\n [Esc] Anuluj | [Inny klawisz] Tak\n";
								if(getch() == 27) break;
								nicknames.clear();
							}
						}
						break;
					case 'f':
					case 'F':
						{
							std::string c;
							for (size_t i = 64; i <=90; i++)
							{
								c = i;
								nicknames.push_back(c);
							}
						}
						break;
					
					default:
						def(); break;
					}
				}
			}
			break;

		case 'l':
		case 'L':
			{
				if(nicknames.size()<=4) {std::cout<<" Za mało graczy!\a"; Sleep(500);}
				else
				{
					cls();
					playerList(nicknames);
					if(winners.empty())
					{
						std::vector <int> tempNum(nicknames.size(),1); //pomocnicza lista przy tasowaniu
						short a = 1, b = nicknames.size()-1; //przedział losowania
						
						temp = 0;
						for(int i(1); i<nicknames.size(); i++) if(!((i-1) % 6)) temp++; //liczba wierszy w liście

						//animacja
						std::cout<<" Wciśnij dowolny klawisz, aby rozpocząć losowanie..."<<std::endl; if(getch() == 27) break;
						pos.X=0; pos.Y=3+temp; SetConsoleCursorPosition(h, pos);
						std::cout<<" Zapisanych na PTS TOTOLOTEK: "<<nicknames.size()-1-((nicknames.size()-1)/6)<<"                           "<<std::endl;
						Sleep(500); std::cout<<" Pustych losów: "<<(nicknames.size()-1)/6<<std::endl;
						Sleep(500); std::cout<<" Komora maszyny losującej jest pusta, zwolnienie blokady za ";
						for(int i(5); i>0; i--)
						{
							pos.X=60; pos.Y=5+temp; SetConsoleCursorPosition(h, pos);
							std::cout<<i<<" "; Sleep(1000);
						}
						pos.X=60; pos.Y=5+temp; SetConsoleCursorPosition(h, pos);
						std::cout<<"0 \n\n";

						playersId.push_back(0);
						do //tasowanie graczy bez powtorzen
						{
							temp = losuj(a, b);
							if(a == temp) a++; if(b == temp) b--; //zawężanie przedziału losowania (na końcach)
							if(tempNum.at(temp))
							{
								playersId.push_back(temp);
								tempNum.at(temp) = 0;
							}
						}while(playersId.size()!=nicknames.size());
						
						//animacja tasowania listy graczy
						for(int i(1); i<playersId.size(); i++)
						{
							if(!((i-1) % 6) && i != 1)
							{
								std::cout<<"\n";
							}
							nick = nicknames.at(playersId.at(i));
							SetConsoleTextAttribute(h, 7);
							std::cout<<" "<<i<<". ";
							if(nick.length() == 9 && nick[5] == ' ')//if "Pusty los" - red color
							{
								SetConsoleTextAttribute(h, 12);
								std::cout<<nick<<"\t";
								SetConsoleTextAttribute(h, 7);
							}
							else
							{
								SetConsoleTextAttribute(h, 10);
								std::cout<<nick<<"\t";
								SetConsoleTextAttribute(h, 7);
							}
							Sleep(300);
						}

						Sleep(500);
						SetConsoleTextAttribute(h, 15);
						std::cout<<"\n\n i rozpoczynamy losowanie czterech wygranych";
						for (size_t i = 0; i < 3; i++)
						{
							Sleep(500);
							std::cout<<".";
						}
						Sleep(1000);
						std::cout<<"\n\n";

						//losowanie wygranych, bez powtórzen
						while(winners.size()<4)
						{
							temp = losuj(1, playersId.size()-1);
							//std::cout<<temp<<" Wylosowano: "<<nicknames.at(playersId.at(temp))<<"\n";
							if(playersId.at(temp))
							{
								winners.push_back(nicknames.at(playersId.at(temp)));
								winnersId.push_back(temp);
								winnersId.push_back(playersId.at(temp));
								playersId.at(temp) = 0;
							}
						}
					} else std::cout<<" Losowanie już się odbyło!\a"<<std::endl;

					SetConsoleTextAttribute(h, 14);
					std::cout<<" 1. Miejsce, 60% puli wygrywa:\t ("<<winnersId.at(0)<<") "<<winners.at(0)<<"!\n\n";
					Sleep(1500);
					SetConsoleTextAttribute(h, 8);
					std::cout<<" 2. Miejsce, 25% puli wygrywa:\t ("<<winnersId.at(2)<<") "<<winners.at(1)<<"!\n\n";
					Sleep(1500);
					SetConsoleTextAttribute(h, 4);
					std::cout<<" 3. Miejsce, 15% puli wygrywa:\t ("<<winnersId.at(4)<<") "<<winners.at(2)<<"!\n\n";
					Sleep(1500);
					SetConsoleTextAttribute(h, 7);
					std::cout<<" 4. Miejsce, +1 los gratis:\t ("<<winnersId.at(6)<<") "<<winners.at(3)<<"!\n\n";
					Sleep(500);
					SetConsoleTextAttribute(h, 15);
					std::cout<<" Gratulacje!"<<std::endl;
					getch();
				}
			}
			break;
		
		case 'r':
		case 'R':
			lottoLogusReplay(nicknames, playersId, winners, winnersId);
			break;

		default:
			def(); break;
		}
	}
	return 0;
}

void playerList(std::vector <std::string> &nicknames)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout<<" _________________________________________PTS TOTOLOTEK - lista zapisanych_________________________________________"<<std::endl;
	if(nicknames.empty()) std::cout<<" Brak graczy";
	else
	{
		SetConsoleTextAttribute(h, 10);
		for(int i(1); i<nicknames.size(); i++)
		{
			if(!((i-1) % 6) && i != 1)
			{
				std::cout<<"\n";
			}
			if(!(i%6))
			{
				SetConsoleTextAttribute(h, 12);
				std::cout<<" "<<i<<". "<<nicknames.at(i)<<"\t";
				SetConsoleTextAttribute(h, 10);
			}else std::cout<<" "<<i<<". "<<nicknames.at(i)<<"\t";
		}
		SetConsoleTextAttribute(h, 15);
	}
	std::cout<<"\n __________________________________________________________________________________________________________________\n"<<std::endl;
}

void lottoLogusReplay(std::vector <std::string> &nicknames, std::vector <short> &playersId, std::vector <std::string> &winners, std::vector <short> &winnersId)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	if(winners.empty()) {std::cout<<"Brak zapisu losowania!\a"; Sleep(500);}
	else if(nicknames.size() != playersId.size()) {std::cout<<"Dokonano zmian w liście zapisanych!\a"; Sleep(500);} //fix crash program
	else
	{
		cls();
		playerList(nicknames);
		
		int temp = 0;
		std::string nick = "";
		for(int i(1); i<nicknames.size(); i++) if(!((i-1) % 6)) temp++;

		std::cout<<" Wciśnij dowolny klawisz, aby rozpocząć losowanie..."<<std::endl;
		pos.X=0; pos.Y=3+temp; SetConsoleCursorPosition(h, pos);
		std::cout<<" Zapisanych na PTS TOTOLOTEK: "<<nicknames.size()-1-((nicknames.size()-1)/6)<<"                           "<<std::endl;
		Sleep(500); std::cout<<" Pustych losów: "<<(nicknames.size()-1)/6<<std::endl;
		Sleep(500); std::cout<<" Komora maszyny losującej jest pusta, zwolnienie blokady za ";
		for(int i(5); i>0; i--)
		{
			pos.X=60; pos.Y=5+temp; SetConsoleCursorPosition(h, pos);
			std::cout<<i<<" "; Sleep(1000);
		}
		pos.X=60; pos.Y=5+temp; SetConsoleCursorPosition(h, pos);
		std::cout<<"0 \n\n";

		//fix
		for(int i(0); i<winnersId.size(); i++)
			if(i%2 == 1) playersId.at(winnersId.at(i-1)) = winnersId.at(i);
		
		for(int i(1); i<playersId.size(); i++)
		{
			if(!((i-1) % 6) && i != 1)
			{
				std::cout<<"\n";
			}
			nick = nicknames.at(playersId.at(i));
			SetConsoleTextAttribute(h, 7);
			std::cout<<" "<<i<<". ";
			if(nick.length() == 9 && nick[5] == ' ')
			{
				SetConsoleTextAttribute(h, 12);
				std::cout<<nick<<"\t";
				SetConsoleTextAttribute(h, 7);
			}
			else
			{
				SetConsoleTextAttribute(h, 10);
				std::cout<<nick<<"\t";
				SetConsoleTextAttribute(h, 7);
			}
			Sleep(300);
		}

		Sleep(500);
		SetConsoleTextAttribute(h, 15);
		std::cout<<"\n\n i rozpoczynamy losowanie czterech wygranych";
		for (size_t i = 0; i < 3; i++)
		{
			Sleep(500);
			std::cout<<".";
		}
		Sleep(1000);
		std::cout<<"\n\n";
		
		SetConsoleTextAttribute(h, 14);
		std::cout<<" 1. Miejsce, 60% puli wygrywa:\t ("<<winnersId.at(0)<<") "<<winners.at(0)<<"!\n\n";
		Sleep(1500);
		SetConsoleTextAttribute(h, 8);
		std::cout<<" 2. Miejsce, 25% puli wygrywa:\t ("<<winnersId.at(2)<<") "<<winners.at(1)<<"!\n\n";
		Sleep(1500);
		SetConsoleTextAttribute(h, 4);
		std::cout<<" 3. Miejsce, 15% puli wygrywa:\t ("<<winnersId.at(4)<<") "<<winners.at(2)<<"!\n\n";
		Sleep(1500);
		SetConsoleTextAttribute(h, 7);
		std::cout<<" 4. Miejsce, +1 los gratis:\t ("<<winnersId.at(6)<<") "<<winners.at(3)<<"!\n\n";
		Sleep(500);
		SetConsoleTextAttribute(h, 15);
		std::cout<<" Gratulacje!"<<std::endl;
		getch();
	}
}

void lottoLogusStats(std::vector <std::string> &nicknames)
{
	if(nicknames.size()<=4) {std::cout<<" Za mało graczy!\a"; Sleep(500);}
	else
	{
		std::vector <std::string> winners;
		std::vector <int> playersId;
		std::vector <short> randoms;
		std::vector <float> randomsC(5,0); //randoms count {nazwa, nazwa, nazwa, nazwa, pusty}0-4
		std::fstream log;
		std::string nick = "";
		int temp = 0;
		cls();
		log.open("lottoLogus.log", std::ios::out);

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
		t = clock();
		int count = 10000;

		while(licznik<=count)
		{
			if(winners.empty())
			{
				std::vector <int> tempNum(nicknames.size(),1);
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
						log<<nick<<std::endl;
					}
					playersId.at(temp) = 0;
				}
			}
			if(licznik>start) log<<std::endl;
			licznik++;
			winners.clear();
			playersId.clear();
		}

		std::cout<<"Losowań: "<<count<<std::endl;
		std::cout<<"Ilość wygranych:"<<std::endl;
		std::cout<<nicknames.at(randoms[0])<<": "<<randomsC[0]<<std::endl;
		std::cout<<nicknames.at(randoms[1])<<": "<<randomsC[1]<<std::endl;
		std::cout<<nicknames.at(randoms[2])<<": "<<randomsC[2]<<std::endl;
		std::cout<<nicknames.at(randoms[3])<<": "<<randomsC[3]<<std::endl;
		std::cout<<"Pusty Los: "<<randomsC[4]<<std::endl;
		std::cout<<"TIME: "<<clock()-t<<"ms\n\n";

		std::cout<<"Zapisanych na PTS TOTOLOTEK: "<<nicknames.size()-1-((nicknames.size()-1)/6)<<std::endl;
		std::cout<<"Pustych losów: "<<(nicknames.size()-1)/6<<std::endl;
		for (size_t i = 0; i < 4; i++)
		{
			std::cout<<nicknames.at(randoms[i])<<": "<<randomsC[i]/licznik*100<<"%\n";
		}
		std::cout<<"Pusty: "<<srednia*100<<"%\n\n";

		std::cout<<"MaxWin: "<<Msrednia2*100<<"%\n";
		std::cout<<"minWin: "<<msrednia2*100<<"%\n";
		std::cout<<"MaxPusty: "<<Msrednia*100<<"%\n";
		std::cout<<"minPusty: "<<msrednia*100<<"%\n";


		log<<"Losowań: "<<count<<std::endl;
		log<<"Ilość wygranych:"<<std::endl;
		log<<nicknames.at(randoms[0])<<": "<<randomsC[0]<<std::endl;
		log<<nicknames.at(randoms[1])<<": "<<randomsC[1]<<std::endl;
		log<<nicknames.at(randoms[2])<<": "<<randomsC[2]<<std::endl;
		log<<nicknames.at(randoms[3])<<": "<<randomsC[3]<<std::endl;
		log<<"Pusty Los: "<<randomsC[4]<<std::endl;
		log<<"TIME: "<<clock()-t<<"ms\n\n";

		log<<"Zapisanych na PTS TOTOLOTEK: "<<nicknames.size()-1-((nicknames.size()-1)/6)<<std::endl;
		log<<"Pustych losów: "<<(nicknames.size()-1)/6<<std::endl;
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

		std::cout<<"\nRozszerzone informacje zostaly wygenerowane w pliku lottoLogus.log";
		std::cout<<"\nZnajduje sie on tam, gdzie wklejany jest program - w logach MTA";
		std::cout<<"\n\nWciśnij dowolny klawisz...";
		getch();
	}
}

void testLos()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	int temp;
	int a = 0;
	int b5=0,b6=0,b7=0,b8=0,b9=0;
	cls();
	while(true)
	{
		a = losuj(1000,6000);
		//getch();
		Sleep(5);
		pos.X=0; pos.Y=0; SetConsoleCursorPosition(h, pos); std::cout<<a<<std::endl;
		if(a >= 1000 && a < 2000) b5++;
		else if(a >= 2000 && a < 3000) b6++;
		else if(a >= 3000 && a < 4000) b7++;
		else if(a >= 4000 && a < 5000) b8++;
		else b9++;
		pos.X=0; pos.Y=1; SetConsoleCursorPosition(h, pos);
		temp = b5;
		if(b6>temp) temp=b6;
		if(b7>temp) temp=b7;
		if(b8>temp) temp=b8;
		if(b9>temp) temp=b9;
		if(temp==b5)
		{
			SetConsoleTextAttribute(h, 4);
			std::cout<<b5<<std::endl;
			SetConsoleTextAttribute(h, 15);
			std::cout<<b6<<std::endl;
			std::cout<<b7<<std::endl;
			std::cout<<b8<<std::endl;
			std::cout<<b9<<std::endl;
		}
		else if(temp==b6)
		{
			std::cout<<b5<<std::endl;
			SetConsoleTextAttribute(h, 4);
			std::cout<<b6<<std::endl;
			SetConsoleTextAttribute(h, 15);
			std::cout<<b7<<std::endl;
			std::cout<<b8<<std::endl;
			std::cout<<b9<<std::endl;
		}
		else if(temp==b7)
		{
			std::cout<<b5<<std::endl;
			std::cout<<b6<<std::endl;
			SetConsoleTextAttribute(h, 4);
			std::cout<<b7<<std::endl;
			SetConsoleTextAttribute(h, 15);
			std::cout<<b8<<std::endl;
			std::cout<<b9<<std::endl;
		}
		else if(temp==b8)
		{
			std::cout<<b5<<std::endl;
			std::cout<<b6<<std::endl;
			std::cout<<b7<<std::endl;
			SetConsoleTextAttribute(h, 4);
			std::cout<<b8<<std::endl;
			SetConsoleTextAttribute(h, 15);
			std::cout<<b9<<std::endl;
		}
		else
		{
			std::cout<<b5<<std::endl;
			std::cout<<b6<<std::endl;
			std::cout<<b7<<std::endl;
			std::cout<<b8<<std::endl;
			SetConsoleTextAttribute(h, 4);
			std::cout<<b9<<std::endl;
			SetConsoleTextAttribute(h, 15);
		}
		if(kbhit())
			break;
	}
	system("pause");
}

/*

std::string randomColor()
{
	int los = 0;
	std::string zwroc = " ";
	los = rand()%15;
	switch(los)
	{
	case 0:
		color("1");
		zwroc = "1";
		break;
	case 1:
		color("2");
		zwroc = "2";
		break;
	case 2:
		color("3");
		zwroc = "3";
		break;
	case 3:
		color("4");
		zwroc = "4";
		break;
	case 4:
		color("5");
		zwroc = "5";
		break;
	case 5:
		color("6");
		zwroc = "6";
		break;
	case 6:
		color("7");
		zwroc = "7";
		break;
	case 7:
		color("8");
		zwroc = "8";
		break;
	case 8:
		color("9");
		zwroc = "9";
		break;
	case 9:
		color("A");
		zwroc = "A";
		break;
	case 10:
		color("B");
		zwroc = "B";
		break;
	case 11:
		color("C");
		zwroc = "C";
		break;
	case 12:
		color("D");
		zwroc = "D";
		break;
	case 13:
		color("E");
		zwroc = "E";
		break;
	case 14:
		color("F");
		zwroc = "F";
		break;
	default:
		def();
	}
	return zwroc;
}
*/