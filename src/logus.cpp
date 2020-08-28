// Copyright (C) 2018-2020  DarXe

#include "logus.hpp"
#include <chrono>
#include <iomanip>

int losuj(int od, int doo)
{
	return rand()%(doo - od + 1)+od;
}

#ifdef _WIN32
	#define CLS "cls"
#elif __linux__
	#define CLS "clear"

int kbhit(void)
{
    int ch, r;

    nodelay(stdscr, TRUE);
    noecho();

    ch = getch();
    if( ch == ERR)
            r = FALSE;
    else
    {
            r = TRUE;
            ungetch(ch);
    }

    echo();
    nodelay(stdscr, FALSE);
    return(r);
}

SetConsoleTitleA(std::string title)
{
	std::cout << "\033]0;" << title << "\007";
}

SetConsoleCursorPosition(int temp, )

#endif
void cls()
{
	system(CLS);
}

std::string getCurrentTime()
{
	auto in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "[%Y-%m-%d %H:%M:%S] ");
	return ss.str();
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
