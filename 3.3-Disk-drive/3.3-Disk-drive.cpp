#include <Windows.h>
#include <stdio.h>

int main() {
	// 1. GetLogicalDrives
	DWORD drivers = GetLogicalDrives();

	for (int i = 0; i < 26; i++) {
		if (drivers & (1 << i)) {
			printf("Drivers %c found\n", i + 'A');
		}
	}

	// 2. GetDriveType
	CHAR root[4] = "A:";

	for (int i = 0; i < 26; i++)
	{
		if (drivers & (1 << i)) {
			root[0] = i + 'A';
			printf("Drivers %c found, type %d\n", i + 'A', GetDriveTypeA(root));
		}
	}
}