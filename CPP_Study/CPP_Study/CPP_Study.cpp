#include <iostream>

using namespace std;

// 오늘의 주제 : 다중 포인터

void SetNumber(int* a)
{
	*a = 1;
}

void SetMessage(const char* a)
{
	a = "Bye";  // Bye의 주소를 a에 넣어주라는 뜻, 스택프레임이 종료가 되면 유효하지 않게 됨
}

int main()
{
	int a = 0;
	SetNumber(&a);
	//cout << a << endl;

	// .rdata  Hello주소[H][e][l][l][o][\0]
	// msg[ Hello주소 ] << 8바이트
	const char* msg = "Hello";

	// [매개변수][RET][지역변수][매개변수][RET][지역변수]
	SetMessage(msg);
	cout << msg << endl;  // bye가 아니라 여전히 hello로 출력됨

	// 주소2[  ] << 1바이트 짜리 바구니(const char)
	// 주소1[ 주소2 ]  << 8바이트
	// pp[ 주소1 ] << 8바이트

	// .rdata   Hello주소[H][e][l][l][o][\0]
	// msg[  Hello 주소 ]  << 8바이트
	// pp[ &msg ] << 8바이트
	const char** pp = &msg;
	*pp = "Bye";
	cout << msg << endl; // Bye 출력



	return 0;
}
