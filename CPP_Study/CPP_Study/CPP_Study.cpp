#include <iostream>
#include <vector>
#include <list>

using namespace std;

// 오늘의 주제 : override, final

class Player
{
public:
	virtual void Attack()
	{
		cout << "Player!" << endl;
	}
};

class Knight : public Player
{
public:
	// 재정의(override)
	// 이것만 보아서는 최초로 virtual을 선언한 곳이 어딘지 알 수 없음 -> override
	
	virtual void Attack() override  // final -> 내 자식들은 더이상 이 함수를 오버라이딩 할 수 없다.
	{
		cout << "Knight!" << endl;
	}

	// 오버로딩(overloading) : 함수 이름의 재사용
	void Attack(int a)
	{

	}
};

int main()
{

	Player* player = new Knight();

	player->Attack();
	
	return 0;
}