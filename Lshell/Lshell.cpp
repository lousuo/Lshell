// Lshell.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <Windows.h>
#include <direct.h>
#include <stdlib.h>
#include <processthreadsapi.h>

using namespace std;

#include <cprintf_m.h>
#include <processid_m.h>
//使用readline库 遵循GPL 3.0开源协议

int main(){

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

	while(1){
		colorful_printf(RED, "[Lshell]");
		printf("%S@%S:~%s",UserName,PCName,PathName);
		if (IsRunningAsAdmin(GetCurrentProcessId()) == true) {
			printf("#");
		}
		else
		{
			printf("$");
		}
		Sleep(1000000);

	}
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
