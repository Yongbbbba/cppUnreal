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

	// 포인터와 참조는 자유자재로 변환 가능하다
	StatInfo& monster_2 = *(monsters + 2);
	monster_2.hp = 200;
	monster_2.attack = 30;
	monster_2.defence = 3;

	// [주의] 이거는 완전 다른 의미다
	// 배열에 직접 접근한 것이 아니고 배열의 값만 복사해서 새로운 변수를 만든 것. 아래의 작업을 해도 배열의 값은 변동이 없다
	StatInfo temp = *(monsters + 2);
	temp.hp = 300;
	temp.attack = 30;
	temp.defence = 3;

	// 이를 조금 더 자동화한다! 
	for (int i = 0; i < 10; i++)
	{
		StatInfo& monster = *(monsters + i);
		monster.hp = 100 * (i+1);
		monster.attack = 10 * (i+1);
		monster.defence = (i+1);
	}

	// 근데 *(monsters + i) 너무 불편하고 가독성이 떨어진다.. .더 편한 방법? 
	// 인덱스!
	// 배열은 0번부터 시작. N번째 인덱스에 해당하는 데이터에 접근하려면 배열이름[N]
	// *(monsters + i) = monsters[i]

	// 배열 초기화 문법 몇 가지 
	int numbers[5] = {}; // 0으로 초기화, 반복문이랑 이렇게 초기화하는 것이 성능상으로는 차이가 없다. 어차피 어셈블리 코드 까보면 하나하나 0넣어주고 있다
	int numbers1[10] = { 1,2,3,4,5 }; // 설정값은 설정한 애들로 초기화 되고, 나머지 값들은 0으로 초기화
	int numbers2[] = { 1,2,31,2,3,21,45,1, };
	
	char helloStr[] = { 'H', 'e', 'l', 'l', 'o', '\0' };
	cout << helloStr << endl; 


	return 0;
}
