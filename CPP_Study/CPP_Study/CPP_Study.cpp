#include <iostream>

using namespace std;

// 오늘의 주제 : 다차원 배열
// 2차원 배열을 만들어도 메모리는 선형으로 쭉 할당되어있음. 다루기 편하게하는 기능이라고 보면 됨

int main()
{
	int apartment2D[2][5] = {
		{4,2,3,4,1},
		{1,1,5,2,2},
	};

	for (int floor = 0; floor < 2; floor++)
	{
		for (int room = 0; room < 5; room++)
			// apartment2D + (floor * 20) + 4 * room과 아래는 동일
			cout << apartment2D[floor][room] << " ";
		cout << endl;
	}

	int apartment1D[10] = { 4,2,3,4,1,1,1,5,2,2 };
	for (int floor = 0; floor < 2; floor++)
	{
		for (int room = 0; room < 5; room++)
		{
			int index = (floor * 5) + room;
			int num = apartment1D[index];
			cout << num << " ";
		}
		cout << endl;
	}

	// 2차 배열은 언제 사용할까? 대표적으로 2D 로그라이크 맵
	// 갈 수 있는 길과 그럴 수 없는 길을 2차원 배열로 표시
	int map[5][5] =
	{
		{1,1,1,1,1},
		{1,0,1,1,1},
		{0,0,0,0,1},
		{1,1,1,0,0},
		{1,1,1,1,1},
	};

	return 0;
}

