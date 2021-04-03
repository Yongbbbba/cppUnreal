#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

// 오늘의 주제 : 오른값(rvalue) 참조와 std::move
// modern c++의 꽃!
class Pet
{
	
};

class Knight
{
public:
	Knight()
	{
		cout << "Knight()" << endl;
	}

	// 복사 생성자
	Knight(const Knight& knight)
	{
		cout << "const Knight()" << endl;
	}

	// 이동 생성자
	Knight(Knight&& knight)
	{

	}

	~Knight()
	{
		cout << "~Knight()" << endl;
		if (_pet)
			delete _pet;
	}

	void operator=(const Knight& knight)
	{
		cout << "oeprator=(const Knight&)" << endl;
		_hp = knight._hp;

		// 얕은 복사
		// _pet = knight._pet;  // 이렇게 만들면 동일한 pet을 보유하는 모양새. _pet이 포인터 변수니까. 

		if (knight._pet)
			_pet = new Pet(*knight._pet);
	}

	// 이동 대입 연산자
	void operator=(Knight&& knight) noexcept
	{
		cout << "oeprator=(Knight&&)" << endl;

		// 얕은 복사
		_hp = knight._hp;
		_pet = knight._pet;

		knight._pet = nullptr;

	}




public:
	int _hp = 100;
	Pet* _pet = nullptr;
};

void TestKnight_Copy(Knight knight) 
{ 
	knight._hp = 200; // 원본에 영향을 미치지 않음
}

void TestKnight_LValueRef(Knight& knight) { }
void TestKnight_constLValueRef(const Knight& knight) { }

void TestKnight_RValueRef(Knight&& knight) { }  // 이동 대상!!. 원본은 더이상 사용하지 않겠다라는 힌트를 강력하게 남길 수 있는 이점.

int main()
{
	// 왼값(lvalue) vs 오른값(rvalue)
	// - lvalue : 단일식을 넘어서 게속 지속되는 개체
	// - rvalue : lvalue가 아닌 나머지 (임시 값, 열거형, 람다, i++ 등)

	// int a = 3;
	// 3 = a; 이런 식으로 쓸 수 없음

	//Knight k1;

	//TestKnight_Copy(k1);
	//TestKnight_Copy(Knight());

	//TestKnight_LValueRef(k1);
	////TestKnight_LValueRef(Knight());  불가능 ~  

	//TestKnight_constLValueRef(Knight());

	//TestKnight_RValueRef(Knight());

	Knight k2;
	k2._pet = new Pet();
	k2._hp = 1000;

	// 원본은 날려도 된다 << 는 Hint를 주는 쪽에 가깝다!
	Knight k3;
	//k3 = static_cast<Knight&&>(k2);  // 이동대입 연산자 호출
	k3 = std::move(k2); // 오른값 참조로 캐스팅. 윗 문장과 같은 의미임
	// std::move의 본래 이름 후보 중 하나가 rvalue_cast 였... 
	
	std::unique_ptr<Knight> uptr = std::make_unique<Knight>();
	//std::unique_ptr<Knight> uptr2 = uptr; // 불가
	std::unique_ptr<Knight> uptr2 = std::move(uptr);

	return 0;
}