#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

int _tmain() {

	// 1. FindFirstFile
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	/*if (argc != 2)
	{
		_tprintf(TEXT("Usage: %s [target_file]\n"), argv[0]);
		return 0;
	}*/

	//_tprintf(TEXT("Target file is %s\n"), argv[1]);
	//hFind = FindFirstFile(argv[1], &FindFileData);

	hFind = FindFirstFile(_T("\\test"), &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("FindFirstFile failed (%d)\n", GetLastError());
		return 0;
	}
	else
	{
		_tprintf(TEXT("The first file found is %s\n"),
			FindFileData.cFileName);
	}

	// 2. FindNextFile
	DWORD dwError;
	LARGE_INTEGER filesize;

	do
	{
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			_tprintf(TEXT("  %s   <DIR>\n"), FindFileData.cFileName);
		}
		else
		{
			filesize.LowPart = FindFileData.nFileSizeLow;
			filesize.HighPart = FindFileData.nFileSizeHigh;
			_tprintf(TEXT("  %s   %ld bytes\n"), FindFileData.cFileName, filesize.QuadPart);
		}
	} while (FindNextFile(hFind, &FindFileData) != 0);

	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES)
	{
		printf("FindFirstFile failed (%d)\n", GetLastError());
	}

	// 3. FindClose
	FindClose(hFind);

	system("pause");
	return 0;
}