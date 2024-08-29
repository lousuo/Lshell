#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
#include <Windows.h>
#include <stdarg.h>
#define BLUE (FOREGROUND_INTENSITY | FOREGROUND_BLUE)
#define GREEN (FOREGROUND_INTENSITY | FOREGROUND_GREEN)
#define RED (FOREGROUND_INTENSITY | FOREGROUND_RED)
#define CYAN (FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN)
#define PURPLE (FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED)
#define YELLOW (FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED)
#define WHITEBGBLACKFONT ((BACKGROUND_INTENSITY | (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED)) | (FOREGROUND_INTENSITY | !(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)))
#define DEFAULT (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)

#define cprintf colorful_printf

int colorful_printf(WORD color, const char* format, ...)
{
	char str[256];// 要输出的字符�?
	va_list ap;// 指向参数的指�?
	va_start(ap, format);// 初始化指向参数的指针
	HANDLE consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);// 输出窗口的句�?
	SetConsoleTextAttribute(consolehwnd, color);// 改为使用预期的颜色输�?
	// 按预期的颜色输出
	int ret = vsprintf(str, format, ap);
	printf("%s", str);
	SetConsoleTextAttribute(consolehwnd, DEFAULT);// 恢复默认效果
	va_end(ap);// 结束可变参数的获�?

	return ret;
}