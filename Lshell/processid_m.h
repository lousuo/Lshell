#pragma once
//�õ�����PID
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
		if (strcmp(mProce, (const char*)lppe.szExeFile) == 0)//�������Ƚ�  
		{
			Found = TRUE;
			pid = lppe.th32ProcessID;
			break;
		}
		Found = Process32Next(hSnapshot, &lppe);//�õ���һ������  
	}
	CloseHandle(hSnapshot);
	return pid;
}
//�ж��Ƿ�Ϊ����ԱȨ��
BOOL IsRunningAsAdmin(DWORD pid) {
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
	if (!hProcess) {
		return FALSE;
	}
	HANDLE hToken;
	TOKEN_ELEVATION Elevation;
	DWORD cbSize = sizeof(TOKEN_ELEVATION);

	// ��ȡ��ǰ���̵ķ�������  
	if (!OpenProcessToken(hProcess, TOKEN_QUERY, &hToken))
		return false;

	// ��ȡ���Ƶ���Ȩ��Ϣ  
	if (!GetTokenInformation(hToken, TokenElevation, &Elevation, cbSize, &cbSize)) {
		CloseHandle(hToken);
		return false;
	}

	// ����Ƿ���Ȩ  
	CloseHandle(hToken);
	return Elevation.TokenIsElevated != 0;
}

/*
TCHAR* GetProcessName() {
	TCHAR szProcessName[MAX_PATH] = TEXT("<Unknown>");

	// ��ȡ��ǰ���̾��
	HANDLE hp = GetCurrentProcess();
	HMODULE hProcess = (HMODULE)hp;

	// ͨ��GetModuleFileName��ȡ������
	GetModuleFileName(hProcess, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));

	CloseHandle(hProcess);
	return szProcessName;
}
*/