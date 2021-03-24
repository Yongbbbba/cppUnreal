#include <iostream>
using namespace std;

// 오늘의 주제 : 타입 변환 (포인터)

// 참조 타입 변환은 프로그래머 인생에서 거의 사용한 적이 없었지만, 포인터 타입 변환은 실무에서도 많이 사용

class Item
{
public:
	Item()
	{
		cout << "Item()" << endl;
	}

	Item(const Item& item)
	{
		cout << "Item(cosnt Item&)" << endl;
	}
	~Item()
	{
		cout << "~Item()" << endl;
	
	}
public:
	int _itemType = 0;
	int _itemDbId = 0;

	char _dummy[4096] = {};  // 이런 저런 정보들로 인해 비대해진 클래스라는 걸를 보이기 위한 더미데이터
};

void TestItem(Item item)
{
}

void TestItemPtr(Item* item)
{

}

int main()
{
	// 복습
	{
		// Stack [ type(4) dbid(4) dummy(4096) ]
		Item item;

		// Stack [  주소(4~8)  ]   -> Heap  [ type(4) dbid(4) dummy(4096)  ] 
		Item* item2 = new Item();

		// 내부적으로 temp 변수를 만들어서 여기에 값을 복사하게 되는데, 이 과정에서 Item 클래스 복사 생성자 호출과 소멸자 호출이 일어남
		// 그런데 이게 메모리 크기가 매우 크다면 매우 부담되는 연산이 될 것임
		TestItem(item);
		TestItem(*item2);

		// 반면에 포인터는 생성자 호출이 일어나지 않음. 객체를 생성할 필요가 없이 그냥 포인터가 넘어가기 떄문이다
		TestItemPtr(&item);
		TestItemPtr(item2);

		// 이 부분을 누락하게 되면 메모리 누수(Memory Leak) -> 점점 가용 메모리가 줄어들어서 Crash
		delete item2; 

		// 배열
		{
			cout << "----------------------------------------" << endl;
			// 진짜 아이템이 100개 있는 것  ( 스택 메모리에 올라와 있는)
			Item item3[100] = {};  // 배열 선언만으로 생성자가 100번 호출됨.
			
			cout << "----------------------------------------" << endl;

			// 아이템이 100개가 있을까요?
			// 아이템을 가리키는 바구니가 100개 있다는 뜻. 실제 아이템은 1개도 없을 수도 있음
			Item* item4[100] = {};   // 배열을 가리키는 포인터. 생성자가 호출되지 않음

			for (int i = 0; i < 100; i++)
				item4[i] = new Item();
			cout << "----------------------------------------" << endl;
			for (int i = 0; i < 100; i++)
				delete item4[i];
		}
	}

	return 0;
}