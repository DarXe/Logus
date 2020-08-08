// Copyright (C) 2018-2020  DarXe
//#include "..\patch.hpp"

std::string getVer()
{
	std::fstream file;
	file.open("logus.ini");
		for(int i(0); i<6; i++) getline(file,s_temp);
		file>>s_temp>>tempVer;
	file.close();
	return tempVer;
}

void zapis(bool showInfo = true)
{ //saa save
	std::fstream file;
	file.open("logus.ini", std::ios::out);
		file<<"////////////////////////////////////////////////////////////////////////////////////////////////\n";
		file<<"//Witaj w pliku konfiguracyjnym. Aby ręcznie skonfigurować ustawienia, podmień liczbę na inną.\n";
		file<<"//Pomiędzy nazwą ustawienia a wartością musi być odstęp spacji, np. nazwa_ustawienia: wartość.\n";
		file<<"//Nie edytuj linii posiadających komentarz '//', w ustawieniach edytuj tylko wartosci\n";
		file<<"//0 - fałsz, 1 - prawda, kolory: 1-9, A-F"<<std::endl;
		file<<"////////////////////////////////////////////////////////////////////////////////////////////////\n";
		file<<"wersja(nie_edytować): "<<ver<<"\n";
		file<<"IP_serwera_MTA: "<<mtasa<<"\n";
		file<<"język_ang_na_pts(0/1): "<<ang<<"\n";
		file<<"nick_na_pts: "<<nick<<"\n";
		file<<"dzwięk_główny: "<<dzwiekGlowny<<"\n";
		file<<"kolor_główny: "<<kolorGlowny<<"\n";
		file<<"menu_glówne_bez_polskich_znaków(0/1): "<<engLang<<"\n";
		file<<"wyświetlane_wiersze: "<<wyswietlaneWiersze<<"\n";
		file<<"odświeżanie: "<<refresh<<"\n";
		file<<"przerwa_między_dźwiękami: "<<interval<<"\n";
		file<<"wyciszenie_komunikatu_team(0/1): "<<fLockTeam<<"\n";
		file<<"wyciszenie_komunikatu_pw(0/1): "<<fLockPW<<"\n";
		file<<"wyciszenie_komunikatu_raport(0/1): "<<fLockKomunikat<<"\n";
		file<<"wyciszenie_komunikatu_nick(0/1): "<<fLockNick<<"\n";
		file<<"dźwięk_każdej_nowej_wiadomości_czatu: "<<chatSound<<"\n";
		file<<"dynamiczne_odświeżanie: "<<dynamicRefresh<<"\n";
		file<<"czas_rozładowywania_towaru: "<<czas<<"\n";
		file<<"cel_trasy_skrypt: "<<random<<"\n";
		file<<"f4: "<<money<<"\n";
		file<<"ilość_kursów: "<<courses<<"\n";
		file<<"szybki_start: "<<fastStart<<"\n";
		file<<"kodowanie852: "<<codePage852<<"\n";
		file<<"trasa: "<<trackId<<"\n";
		file<<"automatyczne_przenoszenie_logów: "<<autoMoveLogs<<"\n";
		file<<"ranga(50%=0.5): "<<grade<<"\n";
		file<<"////////////////////////////////////////////////////////////////////////////////////////////////\n";
		file<<"//W tym miejscu znajduje sie lista zapisanych graczy."<<std::endl;
		file<<"//Aby poprawnie dodać gracza przez plik należy ustalić też ilość graczy."<<std::endl;
		file<<"//Zapisana jest ona po napisie 'ilość_graczy: ', po dwukropku musi być spacja."<<std::endl;
		file<<"//Przykład:"<<std::endl;
		file<<"//ilość_graczy: 2"<<std::endl;
		file<<"//1 ASL|DarXe"<<std::endl;
		file<<"//2 MERO4k"<<std::endl;
		file<<"////////////////////////////////////////////////////////////////////////////////////////////////\n";
		file<<"Lista zapisanych graczy: "<<std::endl;
		file<<"ilość_graczy: "<<nicknames.size()<<std::endl;
		for(int i = 0; i < nicknames.size(); i++)
		{
			file<<i+1<<" "<<nicknames.at(i)<<std::endl;
		}
	file.close();
	if(showInfo)
	engLang?std::cout<<"(INFO) Settings has been saved.\n":
	std::cout<<"(INFO) Ustawienia zostaly zapisane.\n";
}

void odczyt() //re read
{	
	std::fstream file;
	file.open("logus.ini");
		for(int i(0); i<6; i++) getline(file,s_temp);
		file>>s_temp>>tempVer;
		file>>s_temp>>mtasa;
		file>>s_temp>>ang;
		file>>s_temp>>nick;
		file>>s_temp>>dzwiekGlowny;
		file>>s_temp>>kolorGlowny;
		file>>s_temp>>engLang;
		file>>s_temp>>wyswietlaneWiersze;
		file>>s_temp>>refresh;
		file>>s_temp>>interval;
		file>>s_temp>>fLockTeam;
		file>>s_temp>>fLockPW;
		file>>s_temp>>fLockKomunikat;
		file>>s_temp>>fLockNick;
		file>>s_temp>>chatSound;
		file>>s_temp>>dynamicRefresh;
		file>>s_temp>>czas;
		file>>s_temp>>random;
		file>>s_temp>>money;
		file>>s_temp>>courses;
		file>>s_temp>>fastStart;
		file>>s_temp>>codePage852;
		file>>s_temp>>trackId;
		file>>s_temp>>autoMoveLogs;
		file>>s_temp>>grade;
	file.close();

	file.open("logus.ini");
		do //naprawa błędu po aktualizacji (błędne wczytanie z listy Nicknames)
		{
			getline(file,s_temp);
		} while (s_temp[0]!='L');
		
		file>>s_temp;
		file>>leng;
		nicknames.clear();
		for(int i = 0; i < leng; i++)
		{
			file>>temp>>s_temp;
			nicknames.push_back(s_temp);
		}
		engLang?std::cout<<"(INFO) Settings has been loaded.":
		std::cout<<"(INFO) Wczytano ustawienia.\n";
	file.close();
}

void patch() //pat
{
	std::fstream file;
	file.open("logus.ini");
		for(int i(0); i<6; i++) getline(file,s_temp);
		file>>s_temp>>tempVer;
		file>>s_temp>>mtasa;
		file>>s_temp>>ang;
		file>>s_temp>>nick;
		file>>s_temp>>dzwiekGlowny;
		file>>s_temp>>kolorGlowny;
		file>>s_temp>>engLang;
		file>>s_temp>>wyswietlaneWiersze;
		file>>s_temp>>refresh;
		file>>s_temp>>interval;
		file>>s_temp>>fLockTeam;
		file>>s_temp>>fLockPW;
		file>>s_temp>>fLockKomunikat;
		file>>s_temp>>fLockNick;
		file>>s_temp>>chatSound;
		file>>s_temp>>dynamicRefresh;
		file>>s_temp>>czas;
		file>>s_temp>>random;
		file>>s_temp>>money;
		file>>s_temp>>courses;
		file>>s_temp>>fastStart;
		file>>s_temp>>codePage852;
		file>>s_temp>>trackId;
		file>>s_temp>>autoMoveLogs;
		file>>s_temp>>grade;
	file.close();

	file.open("logus.ini");
		do 
		{
			getline(file,s_temp);
		} while (s_temp[0]!='L');
		
		file>>s_temp;
		file>>leng;
		nicknames.clear();
		for(int i = 0; i < leng; i++)
		{
			file>>temp>>s_temp;
			nicknames.push_back(s_temp);
		}
		engLang?std::cout<<"(INFO) Settings loaded. Succesfully updated do "<<ver<<std::endl:
		std::cout<<"(INFO) Wczytano ustawienia. Wykonano aktualizacje do wersji "<<ver<<std::endl;
	file.close();
	zapis(0);
}

void readDefault()
{
	dzwiekGlowny = 1777;
	fLockTeam = 0;
	fLockPW = 0;
	fLockKomunikat = 0;
	fLockNick = 0;
	engLang = 0;
	chatSound = 0;
	kolorGlowny = "A";
	wyswietlaneWiersze = 15;
	refresh = 300;
	ang = 0;
	interval = 50;
	nick = "PodajSwojNick";
	dynamicRefresh = 0;
	czas = 90;
	random = 0;
	mtasa = "185.62.189.174:22003";
	money = 0;
	courses = 0;
	fastStart = 0;
	codePage852 = 0;
	trackId = 0;
	autoMoveLogs = 0;
	grade = 0.5;
}