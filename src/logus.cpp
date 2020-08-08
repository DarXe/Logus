// Copyright (C) 2018-2020  DarXe

#include "logus.hpp"

int losuj(int od, int doo)
{
	return rand()%(doo - od + 1)+od;
}
void cls()
{
	system("cls");
}
char wybor()
{
	engLang?std::cout<<"\n Choose an option (press a key)":
	std::cout<<"\n Wybierz opcje (wciśnij klawisz)";
	return getch();
}
void def()
{
	cls();
	engLang?std::cout<<"\a (INFO) Option not found!\n":
	std::cout<<"\a (INFO) Nie ma takiej opcji!\n";
}

void toClipboard(const std::string &s)
{
	OpenClipboard(0);
	EmptyClipboard();	
	HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE,s.size()+1);
	if (!hg){
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg),s.c_str(),s.size()+1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT,hg);
	CloseClipboard();
	GlobalFree(hg);
}

int power(int x, int y)
{
	int z = 1;
	for(int i = 0; i < y; i++)
	{
		z*=x;
	}
	return z;
}