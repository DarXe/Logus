// Copyright (C) 2018-2019  DarXe
#include <iostream>
#include <conio.h>
#include "..\logus.hpp"
using namespace std;

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
	cout<<"\n Wybierz opcje (wciśnij klawisz)";
	return getch();
}
void def()
{
	cls();
	cout<<"\a (INFO) Nie ma takiej opcji!\n";
}