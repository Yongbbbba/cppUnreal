#include <iostream>

using namespace std;

// 오늘의 주제 : 데이터 연산

unsigned char flag; // 부호를 없애야 >>를 하더라도 부호비트가 딸려오지 않음

// 한 번 정해지면 절대 바뀌지 않을 값들 -> 상수
// constant의 약자인 const를 붙임 (변수를 상수화 한다고 함)
// const를 붙였으면 초기값을 반드시 지정해야 함

int AIR = 0;
int STUN = 1;
int POLYMORPH = 2;
int INVINCIBLE = 3;

int main()
{

#pragma region 비트 연산
	// 언제 필요한가? (사실 많이는 없음)
	// 비트 단위의 조작이 필요할 때가 가끔 생김
	// - 대표적으로 BitFlag

	// ~ : bitwise not
	// 단일 숫자의 모든 비트를 대상으로 0은 1, 1은 0으로 비트를 뒤집는 작업

	// & : bitwise and
	// 두 숫자의 모든 비트 쌍을 대상으로 and를 한다

	// | : bitwise or
	// 두 숫자의 모든 비트 쌍을 대상으로 or를 한다
	
	// ^ bitwise xor
	// 두 숫자의 모든 비트 쌍을 대상으로, xor를 한다
	//int a = 1;
	//int b = 123;
	//a = a ^ b;
	//cout << a << endl;
	//a = a ^ b;
	//cout << a << endl;

	// << 비트 좌측 이동
	// 비트열을 N만큼 좌측 이동
	// 왼쪽의 넘치는 N개의 비트는 사라짐. N개의 새로 생성된 비트는 모두 0임
	// *2를 할 때 자주 보이는 패턴 

	// >> 비트 우측 이동 
	// 비트열을 N만큼 우측으로 이동
	// 오른쪽의 넘치는 N개의 비트는 버림
	// 왼쪽의 생성되는 N개의 비트는 
	// - 부호 비트가 존재할 경우 부호 비트를 따라감 (부호있는 정수라면 이 부분을 유의)
	// - 아니면 0 (unsigned일 때)
	// 비트 쉬프트 할 일이 있으면 데이터 타입을 unsigned로 하는게 정신건강에 이로움

	// 실습
	// 0b0000 [무적][변이][스턴][공중부양]

	// 무적 상태로 만든다
	flag = (1 << INVINCIBLE);

	// 변이 상태를 추가한다 (무적 + 변이)
	flag |= (1 << STUN);

	// 무적인지 확인하고 싶다? (다른 상태는 관심 없음)
	// bitmask
	bool invincible = (flag & (1 << INVINCIBLE)) != 0;
	cout << invincible << endl;
	// 무적이거나 스턴 상태인지 확인하고 싶다면?
	unsigned char mask = (1 << INVINCIBLE) | (1 << STUN);
	bool stunOrInvincible = ((flag & mask) != 0); // ((flag & 0b1010) != 0); bool mask = (1 << 3) | (1 << 1);
	cout << stunOrInvincible << endl;

#pragma endregion


}

