#include <iostream>

using namespace std;

// 오늘의 주제 : 연습 문제

// 문제1) 문자열 길이를 출력하는 함수
int StrLen(const char* str)
{
	// str이라는 문자열의 길이를 반환
	int length = 1;
	for (auto i = 0; i < sizeof(str); i++)
	{
		if (str[i] == '\0') break;
		length++;
	}

	return length;
}

// 문제2) 문자열 복사 함수
void StrCpy(char* dest, char* src)
{
	//int i = 0;
	//while (src[i] != '\0')
	//{
	//	dest[i] = src[i];
	//	i++;
	//}
	//dest[i] = '\0';

	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}

// 문제3) 문자열 덧붙이는 함수
char* StrCat(char* dest, char* src)
{
	char* ret = dest;

	while (*dest) 
		dest++;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return ret;
}

#pragma warning(disable:4996)

int main()
{
	const int BUF_SIZE = 100;

	char a[BUF_SIZE] = "Hello";
	char b[BUF_SIZE] = "World";

	//cout << StrLen(a) << endl;
	//cout << strlen(a) << endl;

	//strcpy(b, a);
	//StrCpy(b, a);

	StrCat(a, b);
	cout << a << endl;
	cout << b << endl;

	return 0;
}