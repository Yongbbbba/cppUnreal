#include <iostream>

using namespace std;

// 오늘의 주제 : 콜백 (Callback)

class Item
{
public:

public:
	int _itemId = 0 ;
	int _rarity = 0;
	int _ownerID = 0;
};

class FindByOwnerId
{
public:
	bool operator() (const Item* item)
	{
		return (item->_itemId == _ownerId);
	}

public:
	int _ownerId;
};

class FindByRarity
{
public:
	bool operator() (const Item* item)
	{
		return (item->_itemId >= _rarity);
	}

public:
	int _rarity;
};

template<typename T>
Item* FindItem(Item items[], int itemCount, T selector)
{
	for (int i = 0; i < itemCount; i++)
	{
		Item* item = &items[i];
		// TODO : 조건 체크
		if (selector(item))
			return item;
	}

	return nullptr;
}

int main()
{	
	// 함수 포인터 + 함수 객체 + 템플릿
	// 콜백 (Callback) : 다시 호출하다? 역으로 호출하다?

	// 게임을 만들 때 이런 콜백의 개념이 자주 등장한다.
	// ex MoveTask 실습 등

	// 어떤 상황이 일어나면 -> 이 기능을 호출해줘
	// ex) UI 스킬 버튼을 누르면 -> 스킬을 쓰는 함수를 호출

	Item items[10];
	items[3]._ownerID = 100;
	items[8]._rarity = 2;

	FindByOwnerId functor1;
	functor1._ownerId = 100;

	FindByRarity functor2;
	functor2._rarity = 1;

	Item* item1 = FindItem(items, 10, functor1);
	Item* item2 = FindItem(items, 10, functor2);

	return 0;

}