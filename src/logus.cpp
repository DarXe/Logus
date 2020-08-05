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
	std::cout<<"\n Wybierz opcje (wciśnij klawisz)";
	return getch();
}
void def()
{
	cls();
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