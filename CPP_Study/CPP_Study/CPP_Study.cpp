#include <iostream>
#include <vector>
#include <list>

using namespace std;

// 오늘의 주제 : enum class

// unscoped enum (범위없는)
enum PlayerType
{
	PT_Knight,  // 0
	PT_Archer,  // 1
	PT_mage,  // 2
};

enum class ObjectType
{
	Player,
	Monster,
	Projectile
};

enum class ObjectType2
{
	Player,
	Monster,
	Projectile
};

int main()
{	
	// enum class (scoped enum)
	// 1) 이름공간 관리에 이점 (scoped)
	// 2) 암묵적인 변환 금지 - 장점이 될 수도 있고, 단점이 될 수도 있음
	double value = static_cast<double>(ObjectType::Player);

	int choice;
	cin >> choice;

	if (choice == static_cast<int>(ObjectType::Monster));
	{

	}

	return 0;
}