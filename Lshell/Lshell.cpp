#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <Windows.h>
#include <direct.h>
#include <stdlib.h>
#include <processthreadsapi.h>
#include <cprintf_m.h>
#include <processid_m.h>
using namespace std;
char inputstr[256] = { 0 };
char bufferstr[256] = { 0 };
char* bufferstr_ = NULL;

static int inputstrcmp(const char* command, char* _args) {
	bufferstr[255] = { 0 };
	for (int fis = 0; fis != sizeof(command); fis++) {
		bufferstr[fis] = inputstr[fis];
		if (strcmp(bufferstr, command) == 0) {
			bufferstr[255] = { 0 };
			for (int fiss = fis; fiss != sizeof(inputstr); fiss++)
			{
				_args[fiss - fis] = inputstr[fiss+2];
			}
			return TRUE;
		}
	}
	return FALSE;
}

int main() {

	char PathName[MAX_PATH] = { 0 };
	getcwd(PathName, sizeof(PathName));
	for (int szpn = strlen(PathName); 1; szpn--) {
		char* bj = &PathName[szpn - 1];
		if (strcmp(bj, "\\")) {
			break;
		}
		PathName[szpn - 1] = NULL;
	}
	//获得主机，用户名
	WCHAR PCName[256];
	WCHAR UserName[256];
	unsigned long size = 256;
	GetComputerName(PCName, &size);
	GetEnvironmentVariable(L"USERNAME", UserName, sizeof UserName);

	printf("-----Lshell,垃圾的不能再垃圾的工具，仅供测试-----\n");
	printf("Lshell - 垃圾玩意[版本 Beta 1.0]\n(c) L Corporation。不保留所有权利。\n");

	while (1) {
		colorful_printf(RED, "[Lshell]");
		printf("%S@%S:~%s", UserName, PCName, PathName);
		if (IsRunningAsAdmin(GetCurrentProcessId()) == true) {
			printf("#");
		}
		else
		{
			printf("$");
		}
		gets_s(inputstr, sizeof inputstr);
		char returnstr[256] = { 0 };
		int text = NULL;
		text = inputstrcmp("help", returnstr);
		cout << "text:" << text << "returnstr=" << returnstr;

	}
}
