// Copyright © 2020  Niventill
// This file is licensed under ISC License. See "LICENSE" in the top level directory for more info.


//standard libraries
#include <iostream>
#include <fstream>
#include <conio.h>


//header includes
#include <common.hpp>
#include <var.hpp>
#include <proc.hpp>
#include <config.hpp>
#include <commonConfig.hpp>
#include "dealer.hpp"


bool genDealerDatabase(std::string file)
{
	std::fstream cars;
	cars.open(file, std::ios::out);
	if (!cars.good())
	{
		cars.close();
		return 0;
	}
	cars << "Admiral          335000		146 km/h\n";
	cars << "Blade            685000		154 km/h\n";
	cars << "Blista           435000		145 km/h\n";
	cars << "BF_Injection     650000		145 km/h\n";
	cars << "Bobcat           220000		125 km/h\n";
	cars << "Bravura          200000		131 km/h\n";
	cars << "Broadway         320000		141 km/h\n";
	cars << "Buccaneer        330000		146 km/h\n";
	cars << "Cadrona          190000		133 km/h\n";
	cars << "Camper           180000		109 km/h\n";
	cars << "Clover           345000		147 km/h\n";
	cars << "Club             425000		145 km/h\n";
	cars << "Elegant          300000		148 km/h\n";
	cars << "Emperor          385000		136 km/h\n";
	cars << "Esperanto        290000		133 km/h\n";
	cars << "Feltzer          770000		149 km/h\n";
	cars << "Fortune          435000		140 km/h\n";
	cars << "Glendale         200000		131 km/h\n";
	cars << "Greenwood        240000		125 km/h\n";
	cars << "Hermes           300000		133 km/h\n";
	cars << "Huntley          620000		140 km/h\n";
	cars << "Hustler          290000		131 km/h\n";
	cars << "Intruder         200000		133 km/h\n";
	cars << "Journey          170000		 96 km/h\n";
	cars << "Landstalker      300000		140 km/h\n";
	cars << "Majestic         240000		140 km/h\n";
	cars << "Manana           150000		115 km/h\n";
	cars << "Merit            300000		140 km/h\n";
	cars << "Mesa             345000		125 km/h\n";
	cars << "Nebula           180000		140 km/h\n";
	cars << "Oceanic          210000		125 km/h\n";
	cars << "Perennial        170000		118 km/h\n";
	cars << "Picador          290000		134 km/h\n";
	cars << "Premier          670000		154 km/h\n";
	cars << "Previon          210000		133 km/h\n";
	cars << "Primo            200000		127 km/h\n";
	cars << "Rancher          395000		124 km/h\n";
	cars << "Regina           210000		125 km/h\n";
	cars << "Remington        720000		150 km/h\n";
	cars << "Sabre            820000		154 km/h\n";
	cars << "Sadler           170000		134 km/h\n";
	cars << "Savanna          710000		154 km/h\n";
	cars << "Sentinel         720000		146 km/h\n";
	cars << "Slamvan          660000		140 km/h\n";
	cars << "Solair           200000		140 km/h\n";
	cars << "Stafford         260000		136 km/h\n";
	cars << "Stallion         535000		150 km/h\n";
	cars << "Stratum          240000		137 km/h\n";
	cars << "Sunrise          230000		129 km/h\n";
	cars << "Tahoma           280000		142 km/h\n";
	cars << "Tampa            260000		137 km/h\n";
	cars << "Tornado          485000		140 km/h\n";
	cars << "Vincent          190000		133 km/h\n";
	cars << "Virgo            200000		133 km/h\n";
	cars << "Voodoo           435000		150 km/h\n";
	cars << "Walton           120000		105 km/h\n";
	cars << "Willard          160000		133 km/h\n";
	cars << "Windsor          525000		141 km/h\n";
	cars << "Washington       375000		137 km/h\n";
	cars << "Yosemite         445000		128 km/h\n";
	cars << "Uranus           670000		139 km/h\n";
	cars << "Bike              25000		  0 km/h\n";
	cars << "MTB               30000		  0 km/h\n";
	cars << "BMX               30000		  0 km/h\n";
	cars << "Freeway          650000		  0 km/h\n";
	cars << "Wayfarer         500000		  0 km/h\n";
	cars << "Faggio           350000		  0 km/h\n";
	cars << "BF-400           750000		  0 km/h\n";
	cars << "FCR-900          800000		  0 km/h\n";
	cars << "PCJ-600          850000		  0 km/h\n";
	cars << "Sanchez          700000		  0 km/h\n";
	cars << "Dostawcze             0		  0 km/h\n";
	cars << "Benson           200000		109 km/h\n";
	cars << "Berkley          250000		121 km/h\n";
	cars << "Boxville         150000		 96 km/h\n";
	cars << "Burrito          250000		140 km/h\n";
	cars << "Wywrotka_Solo    300000		116 km/h\n";
	cars << "DFT-30           280000		116 km/h\n";
	cars << "Flatbed          350000		140 km/h\n";
	cars << "Mule             160000		 94 km/h\n";
	cars << "Newsvan          280000		121 km/h\n";
	cars << "Packer           350000		112 km/h\n";
	cars << "Pony             120000		 98 km/h\n";
	cars << "Rumpo            160000		121 km/h\n";
	cars << "Trashmaster      250000		 89 km/h\n";
	cars << "Yankee           190000		 94 km/h\n";
	cars << "Bus              250000		  0 km/h\n";
	cars << "Coach            350000		  0 km/h\n";
	cars << "Moonbeam         300000		  0 km/h\n";
	cars << "Utility_Van      230000		  0 km/h\n";
	cars << "Linerunner       250000		 98 km/h\n";
	cars << "Roadtrain        350000		127 km/h\n";
	cars << "Tanker           300000		107 km/h\n";
	cars << "Burtowka         150000		  0 km/h\n";
	cars << "Chlodnia         150000		  0 km/h\n";
	cars << "Cysterna         150000		  0 km/h\n";
	cars << "Wywrotka         150000		  0 km/h\n";
	cars << "Utility_Trailer  150000		  0 km/h\n";
	cars << "Taxi             350000		  0 km/h\n";
	cars << "Cabbie           312500		  0 km/h\n";
	cars.close();
	return 1;
}

void databaseCheckout()
{
	SetConsoleTextAttribute(h, 6); //set info text to yellow
	std::fstream cars, f1, f2;
	char c1, c2;
	cars.open("cars.txt");
	if (!cars.good())
	{
		std::cout << " NIE ZNALEZIONO BAZY DANYCH! TWORZENIE.\n";
		genDealerDatabase() ? std::cout << " POMYŚLNIE UTWORZONO BAZĘ DANYCH.\n" : std::cout << " BŁĄD PODCZAS TWORZENIA BAZY DANYCH!\n";
		cars.close();
	}
	else
	{
		if (dealerManual)
		{
			std::cout << " MANUALNA EDYCJA BAZY DANYCH. POMIJANIE SPRAWDZANIA BAZY DANYCH!\n";
			return;
		}
		f1.open("cars.txt", std::ios::in);
		if (!genDealerDatabase("cars.tmp"))
			std::cout << " BŁĄD PODCZAS PORÓWNYWANIA BAZY DANYCH!\n";
		f2.open("cars.tmp", std::ios::in);
		while (true)
		{
			c1 = f1.get();
			c2 = f2.get();
			if (c1 != c2)
			{
				std::cout << " LOKALNA BAZA DANYCH RÓŻNI SIĘ WZGLĘDEM ORYGINAŁU. NADPISYWANIE.\n";
				genDealerDatabase() ? std::cout << " POMYŚLNIE NADPISANO BAZĘ DANYCH.\n" : std::cout << " BŁĄD PODCZAS NADPISYWANIA BAZY DANYCH!\n";
				break;
			}
			if ((c1 == EOF) || (c2 == EOF))
				break;
		}
		f1.close();
		f2.close();
		remove("cars.tmp");
	}
}

void dealerInfo(bool isBuy)
{
	std::string searchedVehicle, vehicle, kmph;
	std::fstream cars;
	int price, vmax;
	bool isTransport = 0;
	while (true)
	{
		cls();
		std::cout << " Podaj DOKŁADNĄ nazwę pojazdu: ";
		getline(std::cin, searchedVehicle);
		for (int i = 0; i < searchedVehicle.length(); i++)
		{
			if (isspace(searchedVehicle[i]))
				searchedVehicle[i] = '_';
			if (isupper(searchedVehicle[i]))
				searchedVehicle[i] = tolower(searchedVehicle[i]);
		}
		isTransport = 0;
		cars.open("cars.txt", std::ios::in);
		while (!cars.eof())
		{
			cars >> vehicle >> price >> vmax >> kmph;
			for (int i = 0; i < vehicle.length(); i++)
			{
				if (isupper(vehicle[i]))
					vehicle[i] = tolower(vehicle[i]);
			}
			if (vehicle == "dostawcze")
				isTransport = 1;
			if (vehicle.find(searchedVehicle) != std::string::npos)
			{
				vehicle[0] = toupper(vehicle[0]);
				if (isBuy)
				{
					cls();
					std::cout << " Stawka bazowa: " << base_dealerBuy * 100 << "%, " << vehicle << ", $" << price * base_dealerBuy << ", " << vmax << " km/h\n";
					std::cout << " ESC - wyjście | Inny klawisz, wyszukaj ponownie\n";
				}
				else
				{
					if (!isTransport)
					{
						cls();
						std::cout << " Stawka bazowa: " << base_dealerSellCar * 100 << "%, " << vehicle << ", $" << price * base_dealerSellCar << ", " << vmax << " km/h\n";
						std::cout << " ESC - wyjście | Inny klawisz, wyszukaj ponownie\n";
					}
					else
					{
						cls();
						std::cout << " Stawka bazowa: " << base_dealerSellTransport * 100 << "%, " << vehicle << ", $" << price * base_dealerSellTransport << ", " << vmax << " km/h\n";
						if (vehicle == "Roadtrain" && vehicle == "Tanker" && vehicle == "Linerunner")
							std::cout << " Z naczepą ($" << base_dealerSellTransport * 150000 << "): $" << (price + 150000) * base_dealerSellTransport << '\n';
						std::cout << " ESC - wyjście | Inny klawisz, wyszukaj ponownie\n";
					}
				}
				if (getch() == 27)
				{
					cls();
					return;
				}
				else
					break;
			}
		}
		cars.close();
	}
}

void printDatabase(bool showDiff)
{
	std::string line;
	std::fstream cars;
	char dL, dO;
	if (showDiff == 0)
	{
		cars.open("cars.txt");
		while (!cars.eof())
		{
			getline(cars, line);
			std::cout << line << "\n";
		}
		cars.close();
	}
	else
	{
		std::fstream diL, diO;
		diL.open("cars.txt", std::ios::in);
		genDealerDatabase("cars.tmp");
		diO.open("cars.tmp", std::ios::in);
		while (true)
		{
			dL = diL.get();
			dO = diO.get();
			if ((dL == EOF) || (dO == EOF))
				break;
			if (dL != dO)
				SetConsoleTextAttribute(h, 12);
			else
				SetConsoleTextAttribute(h, 7);
			std::cout << dL;
		}
		diL.close();
		diO.close();
		remove("cars.tmp");
	}
	SetConsoleTextAttribute(h, 7);
	std::cout << "\nDowolny klawisz - kontynuuj\n";
	getch();
	cls();
}

void dealer()
{
	databaseCheckout();

	while (true)
	{
		SetConsoleTextAttribute(h, 15);
		std::cout << " _______________________________________MENU_______________________________________\n";
		SetConsoleTextAttribute(h, 7);
		std::cout << " [1] (" << base_dealerBuy * 100 << "%) Skup do komisu - podaj dokładną nazwę pojazdu\n";
		std::cout << " [2] (osobówka: " << base_dealerSellCar * 100 << "%, dostawczy: " << base_dealerSellTransport * 100 << "%) Sprzedaż z komisu - podaj dokładną nazwę pojazdu\n";
		std::cout << " [3] Lista pojazdów\n";
		std::cout << " [4] Ustaw stawkę bazową\n";
		std::cout << " [0] Manualna edycja cars.txt: ";
		dealerManual ? std::cout << "TAK\n" : std::cout << "NIE\n";
		std::cout << " [f] Ghetto diff tool\n";
		std::cout << " [r] Reset bazy danych\n";
		SetConsoleTextAttribute(h, 15);
		std::cout << " __________________________________________________________________________________\n";
		std::cout << "                                [ESC] Wyjście i zapis                              \n";
		char wyb = wybor();
		SetConsoleTextAttribute(h, 7);
		switch (wyb)
		{
		case 27:
		{
			cls();
			return;
		}
		case '1':
		{
			cls();
			dealerInfo(1);
			break;
		}
		case '2':
		{
			cls();
			dealerInfo(0);
			break;
		}
		case '3':
		{
			cls();
			printDatabase();
			break;
		}
		case '4':
		{
			while (true)
			{
				cls();
				SetConsoleTextAttribute(h, 15);
				std::cout << " _____________________________________CENA_BAZOWA__________________________________\n";
				SetConsoleTextAttribute(h, 7);
				std::cout << " [1] Stawka skupu do komisu: " << base_dealerBuy * 100 << "%\n";
				std::cout << " [2] Stawka sprzedaży osobówki z komisu: " << base_dealerSellCar * 100 << "%\n";
				std::cout << " [3] Stawka sprzedaży dostawczego z komisu: " << base_dealerSellTransport * 100 << "%\n";
				SetConsoleTextAttribute(h, 15);
				std::cout << " __________________________________________________________________________________\n";
				std::cout << "                                [ESC] Wyjście i zapis                              \n";
				wyb = wybor();
				SetConsoleTextAttribute(h, 7);
				switch (wyb)
				{
				case 27:
					break;
				case '1':
				{
					base_dealerBuy = cfgInput(0, 1, "Podaj nową cenę skupu do komisu", "Podaj stawkę w procentach:", "Dupa, coś zrobiłeś źle", "Min 25% max 100%", 25, 100);
					base_dealerBuy /= 100;
					break;
				}
				case '2':
				{
					base_dealerSellCar = cfgInput(0, 1, "Podaj nową cenę sprzedaży osobówki z komisu", "Podaj stawkę w procentach:", "Dupa, coś zrobiłeś źle", "Min 25% max 100%", 25, 100);
					base_dealerSellCar /= 100;
					break;
				}
				case '3':
				{
					base_dealerSellTransport = cfgInput(0, 1, "Podaj nową cenę sprzedaży dostawczego z komisu", "Podaj stawkę w procentach:", "Dupa, coś zrobiłeś źle", "Min 25% max 100%", 25, 100);
					base_dealerSellTransport /= 100;
					break;
				}
				default:
					break;
				}
				if (wyb == 27)
				{
					saveConfig(0);
					cls();
					break;
				}
			}
		}
		case '0':
		{
			dealerManual = dealerManual ? 0 : 1;
			cls();
			saveConfig(0);
			break;
		}
		case 'f':
		{
			cls();
			printDatabase(1);
			break;
		}
		case 'r':
		{
			cls();
			std::cout << " CZY NA PEWNO CHCESZ ZRESETOWAĆ BAZĘ DANYCH? TEJ AKCJI NIE MOŻNA COFNĄĆ\n ENTER - Reset, INNY KLAWISZ - Anuluj\n";
			if (getch() != 13)
				break;
			genDealerDatabase();
			cls();
			break;
		}
		default:
			cls();
			break;
		}
	}
}