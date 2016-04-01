#include "pch.h"
#include "pov.h"
#include <stdio.h>
#include <stdlib.h>

#define COMMANDFILE "H:\\pov-cylinder.txt"

//------------------------------------------------------
    int pov::send(const wchar_t *W) 
//------------------------------------------------------
// Return value:
//	0: SUCCESS
//	1: File open error
//	2: File exists
{
	FILE *fp;
	size_t Size = wcslen(W);
	char *CString = new char[Size + 1];
	CString[Size] = 0;
	for (int y = 0; y<Size; y++)
	{
		CString[y] = (char)W[y];
	}
	fp = fopen(COMMANDFILE, "r");
	if (fp != NULL) {
		fclose(fp);
		return 2;
	}

	fp = fopen(COMMANDFILE, "wt");
	if (fp == NULL) return 1;
	fprintf(fp, "%s\n", CString);
	fclose(fp);
	return 0;
}