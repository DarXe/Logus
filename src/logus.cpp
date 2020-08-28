// Copyright © 2018-2020  DarXe

#include "logus.hpp"
#include <chrono>
#include <iomanip>

int losuj(int od, int doo)
{
	return rand()%(doo - od + 1)+od;
}

#ifdef __linux__

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
	#ifdef _WIN32
	system("cls");
	#elif __linux__
	system("clear");
	#endif
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

/*
bool fNick(string &wyraz)
{
	for(int i = 0; i<nicknames.size(); i++)
	{
		s_temp = nicknames.at(i);
		leng = s_temp.length() - 1;
		//<nick>: message
		if(line[gt+leng]==s_temp[leng]&&line[gt+leng-1]==s_temp[leng-1]&&line[gt+leng-2]==s_temp[leng-2])
			return 1;
		//* <nick> joined
		if(line[gt]=='*'&&line[gt+leng+2]==s_temp[leng]&&line[gt+leng+1]==s_temp[leng-1]&&line[gt+leng]==s_temp[leng-2])
			return 1;
		//Gracz <nick> <action>
		if(line[gt+5]==' '&&line[gt+leng+6]==s_temp[leng]&&line[gt+leng+5]==s_temp[leng-1]&&line[gt+leng+4]==s_temp[leng-2])
			return 1;
	}
	return 0;
}
*/
