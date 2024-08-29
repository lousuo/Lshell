#pragma once
//得到进程PID
#include <Windows.h>
#include "tlhelp32.h"
#include <Psapi.h>
int getPidByName(const char* processName)
{
	HANDLE hSnapshot;
	PROCESSENTRY32 lppe;
	BOOL Found;
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	lppe.dwSize = sizeof(PROCESSENTRY32);
	Found = Process32First(hSnapshot, &lppe);
	char mProce[MAX_PATH] = "";
	int pid = -1;
	while (Found)
	{
		strcpy(mProce, processName);
		strcat(mProce, ".exe");
		if (strcmp(mProce, (const char*)lppe.szExeFile) == 0)//进程名比较  
		{
			Found = TRUE;
			pid = lppe.th32ProcessID;
			break;
		}
		Found = Process32Next(hSnapshot, &lppe);//得到下一个进程  
	}
	CloseHandle(hSnapshot);
	return pid;
}
//判断是否为管理员权限
BOOL IsRunningAsAdmin(DWORD pid) {
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
	if (!hProcess) {
		return FALSE;
	}
	HANDLE hToken;
	TOKEN_ELEVATION Elevation;
	DWORD cbSize = sizeof(TOKEN_ELEVATION);

	// 获取当前进程的访问令牌  
	if (!OpenProcessToken(hProcess, TOKEN_QUERY, &hToken))
		return false;

	// 获取令牌的提权信息  
	if (!GetTokenInformation(hToken, TokenElevation, &Elevation, cbSize, &cbSize)) {
		CloseHandle(hToken);
		return false;
	}

	// 检查是否提权  
	CloseHandle(hToken);
	return Elevation.TokenIsElevated != 0;
}

/*
TCHAR* GetProcessName() {
	TCHAR szProcessName[MAX_PATH] = TEXT("<Unknown>");

	// 获取当前进程句柄
	HANDLE hp = GetCurrentProcess();
	HMODULE hProcess = (HMODULE)hp;

	// 通过GetModuleFileName获取进程名
	GetModuleFileName(hProcess, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));

	CloseHandle(hProcess);
	return szProcessName;
}
*/