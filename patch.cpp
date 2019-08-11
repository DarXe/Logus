// Copyright (C) 2018-2019  DarXe
//#include "..\patch.hpp"

int getVer()
{
	fstream plik;
	plik.open("logus.ini");
		for(int i(0); i<6; i++) getline(plik,s_temp);
		plik>>s_temp>>temp;
	plik.close();
	return temp;
}

void zapis()
{ //saa save
	fstream plik;
	plik.open("logus.ini", ios::out);
		plik<<"////////////////////////////////////////////////////////////////////////////////////////////////\n";
		plik<<"//Witaj w pliku konfiguracyjnym. Aby ręcznie skonfigurować ustawienia, podmień liczbę na inną.\n";
		plik<<"//Pomiędzy nazwą ustawienia a wartością musi być odstęp spacji, np. nazwa_ustawienia: wartość.\n";
		plik<<"//Nie edytuj linii posiadających komentarz '//', w ustawieniach edytuj tylko wartosci\n";
		plik<<"//0 - fałsz, 1 - prawda, kolory: 1-9, A-F"<<endl;
		plik<<"////////////////////////////////////////////////////////////////////////////////////////////////\n";
		plik<<"wersja(nie_edytować): "<<ver<<"\n";
		plik<<"IP_serwera_MTA: "<<mtasa<<"\n";
		plik<<"język_ang_na_pts(0/1): "<<ang<<"\n";
		plik<<"nick_na_pts: "<<nick<<"\n";
		plik<<"dzwięk_główny: "<<dzwiekGlowny<<"\n";
		plik<<"kolor_główny: "<<kolorGlowny<<"\n";
		plik<<"menu_glówne_bez_polskich_znaków(0/1): "<<menuGlowne<<"\n";
		plik<<"wyświetlane_wiersze: "<<wyswietlaneWiersze<<"\n";
		plik<<"odświeżanie: "<<refresh<<"\n";
		plik<<"przerwa_między_dźwiękami: "<<interval<<"\n";
		plik<<"wyciszenie_komunikatu_team(0/1): "<<fLockTeam<<"\n";
		plik<<"wyciszenie_komunikatu_pw(0/1): "<<fLockPW<<"\n";
		plik<<"wyciszenie_komunikatu_raport(0/1): "<<fLockKomunikat<<"\n";
		plik<<"wyciszenie_komunikatu_nick(0/1): "<<fLockNick<<"\n";
		plik<<"dźwięk_każdej_nowej_wiadomości_czatu: "<<chatSound<<"\n";
		plik<<"dynamiczne_odświeżanie: "<<dynamicRefresh<<"\n";
		plik<<"czas_rozładowywania_towaru: "<<czas<<"\n";
		plik<<"cel_trasy_skrypt: "<<random<<"\n";
		plik<<"f4: "<<money<<"\n";
		plik<<"ilość_kursów: "<<courses<<"\n";
		plik<<"szybki_start: "<<fastStart<<"\n";
		plik<<"kodowanie852: "<<codePage852<<"\n";
		plik<<"trasa: "<<trackId<<"\n";
		plik<<"automatyczne_przenoszenie_logów: "<<autoMoveLogs<<"\n";
		plik<<"ranga(50%=0.5): "<<grade<<"\n";
		plik<<"////////////////////////////////////////////////////////////////////////////////////////////////\n";
		plik<<"//W tym miejscu znajduje sie lista zapisanych graczy."<<endl;
		plik<<"//Aby poprawnie dodać gracza przez plik należy ustalić też ilość graczy."<<endl;
		plik<<"//Zapisana jest ona po napisie 'ilość_graczy: ', po dwukropku musi być spacja."<<endl;
		plik<<"//Przykład:"<<endl;
		plik<<"//ilość_graczy: 2"<<endl;
		plik<<"//1 ASL|DarXe"<<endl;
		plik<<"//2 MERO4k"<<endl;
		plik<<"////////////////////////////////////////////////////////////////////////////////////////////////\n";
		plik<<"Lista zapisanych graczy: "<<endl;
		plik<<"ilość_graczy: "<<nicknames.size()<<endl;
		for(int i = 0; i < nicknames.size(); i++)
		{
			plik<<i+1<<" "<<nicknames.at(i)<<endl;
		}
	plik.close();
	cout<<"(INFO) Ustawienia zostaly zapisane."<<endl;
}

void odczyt() //re read
{	
	int temp;
	fstream plik;
	plik.open("logus.ini");
		for(int i(0); i<6; i++) getline(plik,s_temp);
		plik>>s_temp>>temp;
		plik>>s_temp>>mtasa;
		plik>>s_temp>>ang;
		plik>>s_temp>>nick;
		plik>>s_temp>>dzwiekGlowny;
		plik>>s_temp>>kolorGlowny;
		plik>>s_temp>>menuGlowne;
		plik>>s_temp>>wyswietlaneWiersze;
		plik>>s_temp>>refresh;
		plik>>s_temp>>interval;
		plik>>s_temp>>fLockTeam;
		plik>>s_temp>>fLockPW;
		plik>>s_temp>>fLockKomunikat;
		plik>>s_temp>>fLockNick;
		plik>>s_temp>>chatSound;
		plik>>s_temp>>dynamicRefresh;
		plik>>s_temp>>czas;
		plik>>s_temp>>random;
		plik>>s_temp>>money;
		plik>>s_temp>>courses;
		plik>>s_temp>>fastStart;
		plik>>s_temp>>codePage852;
		plik>>s_temp>>trackId;
		plik>>s_temp>>autoMoveLogs;
		plik>>s_temp>>grade;
	plik.close();

	plik.open("logus.ini");
		do //naprawa błędu po aktualizacji (błędne wczytanie z listy Nicknames)
		{
			getline(plik,s_temp);
		} while (s_temp[0]!='L');
		
		plik>>s_temp;
		plik>>leng;
		nicknames.clear();
		for(int i = 0; i < leng; i++)
		{
			plik>>temp>>s_temp;
			nicknames.push_back(s_temp);
		}
		cout<<"(INFO) Wczytano ustawienia."<<endl;
	plik.close();
}

void patch() //pat
{
	fstream plik;
	plik.open("logus.ini");
		for(int i(0); i<6; i++) getline(plik,s_temp);
		plik>>s_temp>>temp;
		plik>>s_temp>>mtasa;
		plik>>s_temp>>ang;
		plik>>s_temp>>nick;
		plik>>s_temp>>dzwiekGlowny;
		plik>>s_temp>>kolorGlowny;
		plik>>s_temp>>menuGlowne;
		plik>>s_temp>>wyswietlaneWiersze;
		plik>>s_temp>>refresh;
		plik>>s_temp>>interval;
		plik>>s_temp>>fLockTeam;
		plik>>s_temp>>fLockPW;
		plik>>s_temp>>fLockKomunikat;
		plik>>s_temp>>fLockNick;
		plik>>s_temp>>chatSound;
		plik>>s_temp>>dynamicRefresh;
		plik>>s_temp>>czas;
		plik>>s_temp>>random;
		plik>>s_temp>>money;
		plik>>s_temp>>courses;
		plik>>s_temp>>fastStart;
		plik>>s_temp>>codePage852;
		plik>>s_temp>>trackId;
		plik>>s_temp>>autoMoveLogs;
		plik>>s_temp>>grade;
	plik.close();

	plik.open("logus.ini");
		do 
		{
			getline(plik,s_temp);
		} while (s_temp[0]!='L');
		
		plik>>s_temp;
		plik>>leng;
		nicknames.clear();
		for(int i = 0; i < leng; i++)
		{
			plik>>temp>>s_temp;
			nicknames.push_back(s_temp);
		}
		cout<<"(INFO) Wczytano ustawienia. Wykonano aktualizacje do wersji "<<ver<<"."<<endl;
	plik.close();
	zapis();
}

void patch_190622()
{
	fstream plik;
	plik.open("logus.ini");
		for(int i(0); i<6; i++) getline(plik,s_temp);
		plik>>s_temp>>ang;
		plik>>s_temp>>nick;
		plik>>s_temp>>dzwiekGlowny;
		plik>>s_temp>>kolorGlowny;
		plik>>s_temp>>menuGlowne;
		plik>>s_temp>>wyswietlaneWiersze;
		plik>>s_temp>>refresh;
		plik>>s_temp>>interval;
		plik>>s_temp>>fLockTeam;
		plik>>s_temp>>fLockPW;
		plik>>s_temp>>fLockKomunikat;
		plik>>s_temp>>fLockNick;
		plik>>s_temp>>chatSound;
		plik>>s_temp>>dynamicRefresh;
		plik>>s_temp>>czas;
		plik>>s_temp>>random;
	plik.close();

	plik.open("logus.ini");
		do 
		{
			getline(plik,s_temp);
		} while (s_temp[0]!='L');
		
		plik>>s_temp;
		plik>>leng;
		nicknames.clear();
		for(int i = 0; i < leng; i++)
		{
			plik>>temp>>s_temp;
			nicknames.push_back(s_temp);
		}
		cout<<"(INFO) Wczytano ustawienia. Wykonano aktualizacje do wersji 190622."<<endl;
	plik.close();
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