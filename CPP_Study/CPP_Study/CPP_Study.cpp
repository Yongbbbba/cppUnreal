#include <iostream>

using namespace std;

// 오늘의 주제 : 배열

struct StatInfo
{
	int hp = 0xAAAAAAAA;
	int attack = 0xBBBBBBBB;
	int defence = 0xDDDDDDDD;
};

int main()
{
	// 배열의 크기는 상수여야 함 (VC 컴파일러 기준)
	const int monsterCount = 10;
	StatInfo monsters[monsterCount];

	// 여태껏 변수들의 [이름]은 바구니의 이름이었음

	// 그런데 배열은 [이름] 조금 다르게 동작한다
	//StatInfo players[10];
	//players = monsters;

	// 그럼 배열의 이름은 뭐지?
	// 배열의 이름은 곧 배열의 시작 주소
	// 정확히느 ㄴ시작 위치를 가리키는 TYPE* 포인터
	auto WhoAmI = monsters;
	
	// 주소[ (100, 10, 1) ]  StatInfo[ ] StatInfo[ ] StatInfo[ ] ... 
	// mosnter_0[ 주소 ]
	StatInfo* monster_0 = monsters;
	monster_0->hp = 100;
	monster_0->attack = 10;
	monster_0->defence = 1;

	// 포인터의 덧셈! 진짜 1을 더하라는게 아니라, StatInfo 타입 바구니 한 개씩 이동하라는 의미
	StatInfo* monster_1 = monsters + 1;

	monster_1->hp = 200;
	monster_1->attack = 20; 
	monster_1->defence = 2;

	return 0;
}
