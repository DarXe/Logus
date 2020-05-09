// Copyright (C) 2018-2019  DarXe
//#include "..\patch.hpp"

int getVer()
{
	fstream file;
	file.open("logus.ini");
		for(int i(0); i<6; i++) getline(file,s_temp);
		file>>s_temp>>temp;
	file.close();
	return temp;
}

void zapis()
{ //saa save
	fstream file;
	file.open("logus.ini", ios::out);
		file<<"////////////////////////////////////////////////////////////////////////////////////////////////\n";
		file<<"//Witaj w pliku konfiguracyjnym. Aby ręcznie skonfigurować ustawienia, podmień liczbę na inną.\n";
		file<<"//Pomiędzy nazwą ustawienia a wartością musi być odstęp spacji, np. nazwa_ustawienia: wartość.\n";
		file<<"//Nie edytuj linii posiadających komentarz '//', w ustawieniach edytuj tylko wartosci\n";
		file<<"//0 - fałsz, 1 - prawda, kolory: 1-9, A-F"<<endl;
		file<<"////////////////////////////////////////////////////////////////////////////////////////////////\n";
		file<<"wersja(nie_edytować): "<<ver<<"\n";
		file<<"IP_serwera_MTA: "<<mtasa<<"\n";
		file<<"język_ang_na_pts(0/1): "<<ang<<"\n";
		file<<"nick_na_pts: "<<nick<<"\n";
		file<<"dzwięk_główny: "<<dzwiekGlowny<<"\n";
		file<<"kolor_główny: "<<kolorGlowny<<"\n";
		file<<"menu_glówne_bez_polskich_znaków(0/1): "<<menuGlowne<<"\n";
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
		file<<"//W tym miejscu znajduje sie lista zapisanych graczy."<<endl;
		file<<"//Aby poprawnie dodać gracza przez plik należy ustalić też ilość graczy."<<endl;
		file<<"//Zapisana jest ona po napisie 'ilość_graczy: ', po dwukropku musi być spacja."<<endl;
		file<<"//Przykład:"<<endl;
		file<<"//ilość_graczy: 2"<<endl;
		file<<"//1 ASL|DarXe"<<endl;
		file<<"//2 MERO4k"<<endl;
		file<<"////////////////////////////////////////////////////////////////////////////////////////////////\n";
		file<<"Lista zapisanych graczy: "<<endl;
		file<<"ilość_graczy: "<<nicknames.size()<<endl;
		for(int i = 0; i < nicknames.size(); i++)
		{
			file<<i+1<<" "<<nicknames.at(i)<<endl;
		}
	file.close();
	cout<<"(INFO) Ustawienia zostaly zapisane."<<endl;
}

void odczyt() //re read
{	
	int temp;
	fstream file;
	file.open("logus.ini");
		for(int i(0); i<6; i++) getline(file,s_temp);
		file>>s_temp>>temp;
		file>>s_temp>>mtasa;
		file>>s_temp>>ang;
		file>>s_temp>>nick;
		file>>s_temp>>dzwiekGlowny;
		file>>s_temp>>kolorGlowny;
		file>>s_temp>>menuGlowne;
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
		cout<<"(INFO) Wczytano ustawienia."<<endl;
	file.close();
}

void patch() //pat
{
	fstream file;
	file.open("logus.ini");
		for(int i(0); i<6; i++) getline(file,s_temp);
		file>>s_temp>>temp;
		file>>s_temp>>mtasa;
		file>>s_temp>>ang;
		file>>s_temp>>nick;
		file>>s_temp>>dzwiekGlowny;
		file>>s_temp>>kolorGlowny;
		file>>s_temp>>menuGlowne;
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
		cout<<"(INFO) Wczytano ustawienia. Wykonano aktualizacje do wersji "<<ver<<"."<<endl;
	file.close();
	zapis();
}

void patch_190622()
{
	fstream file;
	file.open("logus.ini");
		for(int i(0); i<6; i++) getline(file,s_temp);
		file>>s_temp>>ang;
		file>>s_temp>>nick;
		file>>s_temp>>dzwiekGlowny;
		file>>s_temp>>kolorGlowny;
		file>>s_temp>>menuGlowne;
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
		cout<<"(INFO) Wczytano ustawienia. Wykonano aktualizacje do wersji 190622."<<endl;
	file.close();
	zapis();
}

void readDefault()
{
	dzwiekGlowny = 1777;
	fLockTeam = 0;
	fLockPW = 0;
	fLockKomunikat = 0;
	fLockNick = 0;
	menuGlowne = 0;
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