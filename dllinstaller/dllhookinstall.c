#include <windows.h>
#include <stdio.h>
typedef struct _kbhookinfo{
	HHOOK hook;
}KBHOOKINFO;

typedef KBHOOKINFO *PKBHOOKINFO;

typedef LRESULT (WINAPI* LPFHOOKFUNC)(int, WPARAM, LPARAM);
typedef PKBHOOKINFO (*LPFKBWNDHOOK)(void);

LPFKBWNDHOOK lpfkbhook;
LPFHOOKFUNC lpfHookFunc;
char *hfname = "KBHookFunc";
char *imports[] = { 0 };
char *dlls[] = { 0 };

int main(){
	HMODULE hdll = LoadLibrary("klogtest.dll");
	if (hdll == NULL){
		printf("Could not load dll\n");
		system("pause");
		return EXIT_FAILURE;
	}

	lpfHookFunc = (LPFHOOKFUNC)GetProcAddress(hdll, "KBHookFunc");
	lpfkbhook = (LPFKBWNDHOOK)GetProcAddress(hdll, "kbWindowHook");

	if (!lpfHookFunc && !lpfkbhook){
		FreeLibrary(hdll);
		system("pause");
		return EXIT_FAILURE;
	}
	KBHOOKINFO *kbHook = lpfkbhook();
	system("pause");
	return 0;
}