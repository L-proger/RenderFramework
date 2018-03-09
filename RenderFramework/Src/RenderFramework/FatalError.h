#ifndef FatalError_h__
#define FatalError_h__

#include <Windows.h>

inline void FatalError(const TCHAR* message) {
	int b1 = 12750;
	int b2 = 4750;
	int len = 80;

	for(int i = 0; i < 2; ++i) {
		Beep(b1, len);
		Beep(b2, len);
	}

	MessageBox(NULL, message, TEXT("Error"), MB_OK);
	exit(0);
}
#endif // FatalError_h__
