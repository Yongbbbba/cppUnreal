#include <iostream>
using namespace std;

// 오늘의 주제 : 타입 변환 (포인터)

// 참조 타입 변환은 프로그래머 인생에서 거의 사용한 적이 없었지만, 포인터 타입 변환은 실무에서도 많이 사용

class Knight
{
public:
	int _hp = 0;
};

class Item
{
public:
	Item()
	{
		cout << "Item()" << endl;
	}

	Item(int itemType) : _itemType(itemType)
	{
		cout << "Item(itemType)" << endl;
	}

	Item(const Item& item)
	{
		cout << "Item(cosnt Item&)" << endl;
	}
	virtual ~Item()
	{
		cout << "~Item()" << endl;
	}

public:
	int _itemType = 0;
	int _itemDbId = 0;

	char _dummy[4096] = {};  // 이런 저런 정보들로 인해 비대해진 클래스라는 걸를 보이기 위한 더미데이터
};

enum ItemType
{
	IT_WEAPON = 1,
	IT_ARMOR = 2,
};

class Weapon : public Item
{
public:
	Weapon() : Item(IT_WEAPON)
	{
		cout << "Weapon()" << endl;
		_damage = rand() % 100;
	}
	~Weapon()
	{
		cout << "~Weapon()" << endl;
	}

public:
	int _damage = 0;
};

class Armor : public Item
{
public:
	Armor() : Item(IT_ARMOR)
	{
		cout << "Armor()" << endl;
	}
	~Armor()
	{
		cout << "~Armor()" << endl;
	}

public:
	int _defence = 0;
};

int main()
{
	// 연관성이 없는 클래스 사이의 포인터 변환 테스트
	{
		//  Stack [  주소   ]   -> Heap [ _hp(4) ]
		Knight* knight = new Knight();

		// 암시적으로는 No
		// 명시적으로 Ok

		// Stack [  주소   ]   
		/*Item* item = (Item*)knight;
		item->_itemType = 2;
		item->_itemDbId = 1;*/

		delete knight;
	}

	// 부모 -> 자식 변환 테스트
	{
		Item* item = new Item();

		// 명시적으로 해줄 수는 있지만 매우 위험한 행위이다. 안전하지 않다
		//Weapon* weapon = (Weapon*)item;
		//weapon->_damage = 10;
	}

	// 자식 -> 부모 변환 테스트
	{
		Weapon* weapon = new Weapon();

		// 암시적으로도 된다!
		Item* item = weapon;

		delete weapon;
	}

	// 명시적으로 타입 변환할 때는 항상 항상 조심해야 한다! 
	// 암시적으로 될 때는 안전하다?
	// -> 그러면 평생 명시적으로 타입 변환(캐스팅)은 안하면 되는거 아닌가?  NO

	// 인벤토리 배열 안에 다양한 종류의 아이템이 들어간다면?
	Item* inventory[20] = {};

	srand((unsigned int)time(nullptr));

	for (int i = 0; i < 20; i++)
	{
		int randValue = rand() & 2;  // 0 ~ 1
		switch (randValue)
		{
		case 0:
			inventory[i] = new Weapon();  // 암시적 형변환이 일어났을 것임
			break;
		case 1:
			inventory[i] = new Armor();
			break;
		}
	}

	for (int i = 0; i < 20; i++)
	{
		Item* item = inventory[i];
		if (item == nullptr)
			continue;

		if (item->_itemType == IT_WEAPON)
		{
			Weapon* weapon = (Weapon*)item;   // weapon -> item -> weapon  으로 형변환이 일어난듯
			// 원래 부모 -> 자식 형변환은 위험한 것
			cout << "Weapon Damage : " << weapon->_damage << endl;
		}
	}

	// ********************매우 매우 매우 중요 ****************************
	for (int i = 0; i < 20; i++)
	{
		Item* item = inventory[i];
		if (item == nullptr)
			continue;

		delete item;  // 제대로된 방법이 아니다 !!  원본타입을 해제시켜줘야함
		// ex) Weapon* weapon = (Weapon*)item;  delete weapon;
		// 아니면 원본(부모) 클래스의 소멸자에 virtual 키워드를 붙여주면 자식들의 소멸자도 가상함수가 되기 때문에
		// item을 해제시켜도 알아서 weapon, armor에 따라 해제가 됨   ->  안전한 방법
	}

	//  부모 클래스의 소멸자는 반드시 가상함수로 만들어줘야함 !!! 그래야 실수를 하지 않는다
	// 가상함수 테이블이 만들어지면서, 원본 자체가 뭐로 만들어진건지 런타임에 확인해서 그에 맞는 소멸자를 호출해준다

	// [결론]
	// - 포인터 vs 일반 타입 : 차이를 이해하자
	// - 포인터 사이의 타입 변환(캐스팅)을 할 때는 매우 매우 조심해야 한다! 
	// - 부모-자식 관계에서 부모 클래스의 소멸자에는 까먹지 말고 virtual를 붙이자!!!!

	return 0;
}