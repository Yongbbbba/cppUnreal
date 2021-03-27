#include <iostream>

using namespace std;

// 오늘의 주제 : 함수 포인터	

int Add(int a, int b)
{
	return a + b;
}

int Sub(int a, int b)
{
	return a - b;
}

class Item
{
public:
	Item() : _itemID(0), _rarity(0), _owerId(0)
	{

	}

public:
	int _itemID;  // 아이템을 구분하기 위한 ID
	int _rarity;  // 희귀도
	int _owerId;  // 소지자 ID
};

typedef bool(ITEM_SELECTOR)(Item* item);

// bool(*selector)(Item* item), 세 번째 인자에 이것을 넣는 것과 저것은 같은 의미
Item* FindItem(Item items[], int itemCount, ITEM_SELECTOR* selector )
{
	// 안전 체크

	for (int i = 0; i < itemCount; i++)
	{
		Item* item = &items[i];
		// TODO 조건
		if (selector(item))
			return item;
	}

	return nullptr;
}

bool IsRareItem(Item* item)
{
	return item->_rarity >= 2;
}

int main()
{	
	int a = 10;
	
	// 바구니 주소 
	// pointer[ 주소 ]    => 주소 [ ]

	typedef int DATA;

	// 포인터 구성 요소
	// 1) 포인터		*
	// 2) 변수 이름     pointer
	// 3) 데이터 타입	int
	DATA* pointer = &a;

	// 함수
	typedef int(FUNC_TYPE)(int, int);
	// using FUNC_TYPE = (int)(int a, int b);

	// 함수 포인터 구성 요소
	// 1) 포인터		*
	// 2) 변수 이름     fn
	// 3) 데이터 타입	함수(인자는 int, int 반환은 int)
	FUNC_TYPE* fn;

	// 함수 포인터
	fn = Add;  // 시그니처가 동일하다면 이런 식으로 구현 가능
	// fn = Sub; 로 바꾸는게 가능해진다! 재사용성이 높아짐

	// 함수의 이름은 함수의 시작 주소를 들고 있는 것 같음 (배열과 유사)
	int result = fn(1, 2); // 기본 문법
	cout << result << endl;

	int result2 = (*fn)(1, 2); // 함수 포인터는 *(접근 연산자) 붙여도 함수 주소임
	cout << result2 << endl;

	Item items[10] = {};
	items[3]._rarity = 2;  // RARE
	Item* rareItem = FindItem(items, 10, IsRareItem);  // 함수 파라미터로 함수를 넣을 수 있게 됨! 

	return 0; 
}