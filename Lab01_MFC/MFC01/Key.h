#pragma once
#include "pch.h"

#define str_length  12
#define Score_aChar 10
#define Score_aString 100
#define Rect_wildth 20

TCHAR  Traget_str[str_length + 1];
UINT   GameScore = 0;
bool gStart = false;


void InitLetter(CString& randString )
{
	SYSTEMTIME systime;
	GetSystemTime(&systime); 
	//为rand()得到随机数作准备;
	srand(systime.wMilliseconds);
	for (int i = 0; i < str_length; i++)
	{		
		randString+= (TCHAR)('A' + rand() % 26);
	}
}
