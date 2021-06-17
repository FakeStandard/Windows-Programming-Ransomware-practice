
#include <iostream>
#include <Windows.h>
#include <tchar.h>

BOOL UpdateFileAttributes(LPCTSTR lpFileName, DWORD dwFileAttributes, BOOL bFlag) {
	BOOL bResult = TRUE;
	DWORD dwAttrs = GetFileAttributes(lpFileName);
	if (dwAttrs == INVALID_FILE_ATTRIBUTES) {
		return FALSE;
	}

	if (bFlag) {
		if (!(dwAttrs & dwFileAttributes)) {
			bResult = SetFileAttributes(lpFileName, dwAttrs | dwFileAttributes);
		}
		else {
			if (dwAttrs & dwFileAttributes) {
				DWORD dwNewAttrs = dwAttrs & ~dwFileAttributes;
				bResult = SetFileAttributes(lpFileName, dwNewAttrs);
			}
		}
	}

	return bResult;
}

int main()
{
	// 1. CopyFile
	if (!CopyFile(
		_T("D:\\testSource.txt"),
		_T("D:\\testTarget.txt"),
		false))
	{
		printf("CopyFile() Error %d\n", GetLastError());
	}

	// 2. DeleteFile
	if (!DeleteFile(_T("D:\\testTarget.txt"))) {
		printf("DeleteFile() Error %d\n", GetLastError());
	}

	// 3. MoveFile
	if (!MoveFile(
		_T("D:\\testSource.txt"),
		_T("D:\\test\\testSourceNew.txt"))) {
		printf("MoveFile() Error %d\n", GetLastError());
	}

	// 4. GetFileAttributes & SetFileAttributes
	BOOL b = UpdateFileAttributes(_T("D:\\test\\testSourceNew.txt"), FILE_ATTRIBUTE_HIDDEN, TRUE);
	if (!b) {
		printf("UpdateFileAttributes() Error %d\n", GetLastError());
	}

	return 0;
}