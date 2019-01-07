// pulse-filetree-generator.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
// include <windows.h>
#include <stdio.h>
#include <shlobj.h>
#include <tchar.h>
#include <locale.h>

WIN32_FIND_DATA data;

void listdir(const wchar_t dir[], FILE * fp) {
	wchar_t nom[MAX_PATH];
	wcscpy_s(nom, dir);
	wcscat_s(nom, L"\\*");
	wchar_t espacea[5];
	wcscpy_s(espacea, L" {");
	HANDLE h = FindFirstFile(nom, &data);
	if (h == INVALID_HANDLE_VALUE) { fwprintf_s(stderr, L" Error %s", nom); return; }
	h = FindFirstFile(nom, &data);
	do { // folders
		if (FILE_ATTRIBUTE_DIRECTORY&data.dwFileAttributes) {
			if (data.cFileName[0] == '.') continue; // évite "." et ".."
			//SetConsoleTextAttribute(hConsole, 12);
			//wprintf(L"%s\"text\" : \"%s\", \"children\" : [", espacea, data.cFileName);
			fwprintf_s(fp, L"%s\"text\" : \"%s\", \"children\" : [", espacea, data.cFileName);
			wcscpy_s(espacea, L",{");
			//wprintf(L"%s\\\n",  data.cFileName);
			wcscpy_s(nom, dir);
			wcscat_s(nom, L"\\");
			wcscat_s(nom, data.cFileName);
			if (wcsncmp(nom, L"c:\\\\Windows\\\\", 8) != 0)
				listdir(nom, fp); // folder
			//wprintf( L"]" );
			fwprintf_s(fp, L"]}");
		}
	} while (FindNextFile(h, &data));
	FindClose(h);
}

bool dirExists(_TCHAR* dirName_in)
{
	DWORD dwAttrib = GetFileAttributes((LPCWSTR)dirName_in);
	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}
int _tmain(int argc, _TCHAR* argv[])
{
	
	wchar_t drive[_MAX_DRIVE];
	wchar_t dir[_MAX_DIR];
	wchar_t file[_MAX_FNAME];
	wchar_t ext[_MAX_EXT];
	size_t driveNumberOfElements = _MAX_DRIVE, dirNumberOfElements= _MAX_DIR, nameNumberOfElements=_MAX_FNAME, extNumberOfElements= _MAX_PATH;
	size_t ReturnValue;

	char outfilename[MAX_PATH];
	char envnom[MAX_PATH];
	FILE * fp;

	setlocale(LC_ALL, "en_US.utf8");

	if (argc == 1) {
		fwprintf_s(stderr, L"usage : %s \"dir_start\" [file result json]", argv[0]);
		return -1;
	}

	if (!dirExists(argv[1])) {
		fwprintf(stderr, L"\nerror arg1 (%s) is not folder\n", argv[1]);
		return -1;
	}

	if (argc < 3) {
		getenv_s(&ReturnValue, envnom, MAX_PATH, "TMP");
		strcpy_s(outfilename, MAX_PATH, envnom);
		strcat_s(outfilename, MAX_PATH, "\\file.txt");
	}
	else {
		char buffer[MAX_PATH];
		int ret = wcstombs_s(&ReturnValue, buffer, MAX_PATH, argv[2], MAX_PATH);
		strcpy_s(outfilename, MAX_PATH, buffer);
	}

	_wsplitpath_s(argv[1], drive,driveNumberOfElements, dir,dirNumberOfElements, file,nameNumberOfElements,  ext,extNumberOfElements);
	

	printf("\file result in %s", outfilename);
	errno_t err = fopen_s(&fp, (char*)outfilename, "w+");

	fwprintf_s(fp, L"{\"text\" : \"%s\", \"children\" : [", file);
	listdir(argv[1], fp);
	fprintf(fp, "]}");
	fclose(fp);
	//fwprintf(stderr, L"\n arg1 (%s)\n", file);

}
