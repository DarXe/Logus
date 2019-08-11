// Copyright (C) 2018-2019  DarXe
using namespace std;
#include <string>
#include "..\functions.hpp"
extern int gt;
extern string linia;
extern int leng;
extern string s_temp;
extern string nick;
extern string nicknames;

//(team) [pts]nick
bool fTeam(string &linia, bool e)
{
	leng = nick.length();
	if(linia[gt]=='('&&linia[gt+1]=='T'&&linia[gt+2]=='E'&&linia[gt+3]=='A'&&linia[gt+4]=='M')
	{
		if(e) return 1;
		if(linia[gt+6+leng]!=nick[leng-1]||linia[gt+5+leng]!=nick[leng-2]||linia[gt+4+leng]!=nick[leng-3])
			return 1;
		else return 0;
	}
	else return 0;
}

bool fPwOd(string &linia, bool &ang)
{
	if(ang)
	{
		if(linia[gt]=='*'&&linia[gt+2]=='P'&&linia[gt+3]=='M')
			return 1;
		else return 0;
	}
	else
	{
		if(linia[gt]=='*'&&linia[gt+2]=='P'&&linia[gt+3]=='W')
			return 1;
		else return 0;
	}
}

bool fPwDo(string &linia)
{
	if(linia[gt]=='-'&&linia[gt+1]=='>')
		return 1;
	else return 0;
}

bool fPrzelewyOd(string &linia, bool &ang)
{
	leng = linia.length();
	if(ang)
	{
		if(linia[gt]=='P'&&linia[gt+1]=='l'&&linia[gt+2]=='a'&&linia[gt+3]=='y'&&linia[gt+4]=='e'&&linia[gt+6]==' '&&linia[leng-2]!='d'&&linia[leng-1]=='.'&&(linia[leng-3]!=' '&&linia[leng-5]!='e'))
			return 1;
		else return 0;
	}
	else
	{
		if(linia[gt]=='G'&&linia[gt+1]=='r'&&linia[gt+2]=='a'&&linia[gt+3]=='c'&&linia[gt+4]=='z'&&linia[gt+5]==' '&&linia[leng-2]=='$'&&linia[leng-1]=='.')
			return 1;
		else return 0;
	}
}

bool fPrzelewyDo(string &linia, bool &ang)
{
	if(ang)
	{
		if(linia[gt]=='Y'&&linia[gt+1]=='o'&&linia[gt+2]=='u'&&linia[gt+4]=='g'&&linia[gt+6]=='v')
			return 1;
		else return 0;
	}
	else
	{
		if(linia[gt]=='P'&&linia[gt+1]=='r'&&linia[gt+2]=='z'&&linia[gt+3]=='e'&&linia[gt+5]=='a')
			return 1;
		else return 0;
	}
}

bool fKomunikat(string &linia, bool &ang)
{
	if(ang)
	{
		if(linia[gt]=='N'&&linia[gt+1]=='e'&&linia[gt+3]==' '&&linia[gt+8]=='r')
			return 1;
		else return 0;
	}
	else
	{
		if(linia[gt]=='N'&&linia[gt+1]=='o'&&linia[gt+3]=='y'&&linia[gt+4]==' '&&linia[gt+9]=='r')
			return 1;
		else return 0;
	}
}

bool fTransport(string &linia, bool &ang)
{
	//[2019-05-24 17:02:41] [Output] : You've earned $2792. It has been transfered to your company's account.
	if(ang)
	{
		if(linia[gt]=='Y'&&linia[gt+4]=='v'&&linia[gt+14]=='$')
			return 1;
		else return 0;
	}
	//[2019-05-24 17:02:41] [Output] : Pieniądze za transport 3191$ zostały przelane na konto firmy.
	else
	{
		if(linia[gt]=='P'&&linia[gt+1]=='i'&&linia[gt+2]=='e'&&linia[gt+3]=='n'&&linia[gt+4]=='i')
			return 1;
		else return 0;
	}
}

bool fNicknames(string &linia)
{
	for(int i = 0; i<nicknames.size(); i++)
	{
		s_temp = nicknames.at(i);
		leng = s_temp.length() - 1;
		if(linia[gt+leng]==s_temp[leng]&&linia[gt+leng-1]==s_temp[leng-1]&&linia[gt+leng-2]==s_temp[leng-2])
			return 1;
		if(linia[gt]=='*'&&linia[gt+leng+2]==s_temp[leng]&&linia[gt+leng+1]==s_temp[leng-1]&&linia[gt+leng]==s_temp[leng-2])
			return 1;
		if(linia[gt+5]==' '&&linia[gt+leng+6]==s_temp[leng]&&linia[gt+leng+5]==s_temp[leng-1]&&linia[gt+leng+4]==s_temp[leng-2])
			return 1;
	}
	return 0;
}

/*bool fNick(string &wyraz)
{
	for(int i = 0; i<nicknames.size(); i++)
	{
		s_temp = nicknames.at(i);
		leng = s_temp.length() - 1;
		//<nick>: message
		if(linia[gt+leng]==s_temp[leng]&&linia[gt+leng-1]==s_temp[leng-1]&&linia[gt+leng-2]==s_temp[leng-2])
			return 1;
		//* <nick> joined
		if(linia[gt]=='*'&&linia[gt+leng+2]==s_temp[leng]&&linia[gt+leng+1]==s_temp[leng-1]&&linia[gt+leng]==s_temp[leng-2])
			return 1;
		//Gracz <nick> <action>
		if(linia[gt+5]==' '&&linia[gt+leng+6]==s_temp[leng]&&linia[gt+leng+5]==s_temp[leng-1]&&linia[gt+leng+4]==s_temp[leng-2])
			return 1;
	}
	return 0;
}
*/