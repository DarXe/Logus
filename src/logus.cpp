#include <iostream>
#include <conio.h>
#include "..\logus.hpp"

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
	std::cout<<" Wybierz opcje : ";
	return getch();
}
void def()
{
	cls();
	std::cout<<"\a (INFO) Nie ma takiej opcji!\n";
}