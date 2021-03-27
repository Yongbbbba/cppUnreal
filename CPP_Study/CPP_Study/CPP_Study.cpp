#include <iostream>
#include <vector>

using namespace std;

// 오늘의 주제 : nullptr	

class Knight
{

};

Knight* FindKnight()
{
	// TODO,

	return nullptr;
}

void Test(int a)
{
	cout << "Test(int)" << endl;
}

void Test(void* ptr)
{
	cout << "Test(*)" << endl;
}

// Nullptr 구현

class NullPtr
{
public:
	template<typename T>
	operator T* () const
	{
		return 0;
	}
	
};

int main()
{	
	// NULL은 그냥 0임
	// define NULL 0
	
	int* ptr = NULL; // 0 NULL

	// 1) 오동작 방지 가능
	Test(0);
	Test(NULL);
	Test(nullptr);

	// 2) 가독성
	auto knight = FindKnight();

	auto whoami = nullptr;  // nullptr_t 타입
	

	return 0; 
}