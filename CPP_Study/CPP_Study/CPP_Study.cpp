#include <iostream>
using namespace std;

// 오늘의 주제 : 캐스팅 (타입 변환)
// 기본기니까 .. 면접에서 맨날 나오는 질문들
// C스타일 형변환은 잊어라!  괜히 C++에서 만들어 놓은게 아니다

class Player
{
public:
	virtual ~Player() {}
};

class Knight : public Player
{
public:

	virtual ~Knight() {}
};

class Archer : public Player
{
public:
	virtual ~Archer() {}
};

// 1) static_cast
// 2) dynamic_cast
// 3) const_cast
// 4) reinterpret_cast

void PrintName(char* str)
{
	cout << str << endl;
}

int main()
{
	// static_cast : 타입 원칙에 비춰볼 때 상식적인 캐스팅만 허용해준다
	// 1) int <-> float  (정밀도가 완전히 일치하지 않는 문제가 있기는 하지만..)
	// 2) Player* -> Knight* (다운캐스팅) 

	int hp = 100; 
	int maxHp = 200; 
	float ratio = static_cast<float>(hp) / maxHp;

	// 부모->자식   자식->부모
	Player* p = new Player();
	Knight* k1 = static_cast<Knight*>(p);  // 가능하다고 해서 더 안전해졌다는 것은 아니다.
	// 예를 들어 아래와 같은 경우에 이것이 안전하다고 볼 수는 없음
	// Archer가 원본이었으니까.. 
	// 엉뚱한 메모리를 고치게 되는 문제가 추후 생길 가능성이 매우 높아진다
	//Player* p2 = new Archer();
	//Knight* k2 = static_cast<Knight*>(p2);

	// dynamic_cast : 상속 관계에서의 안전한 형변환 지원( static_cast를 보완)
	// RTTI라는 것을 활용(RunTime Type Information)
	// 다형성을 활용하는 방식  -> virtual 함수를 하나라도 만들어줘야한다. 
	// - virtual 함수를 하나라도 만들면, 객체의 메모리에 가상 함수 테이블 (vftable) 주소가 기입된다
	// - 그냥 캐스팅 되는게 아니라 맞는 타입을 가상 함수 테이블에서 찾아서 캐스팅을 해준다
	// - 만약 잘못된 타입으로 캐스팅을 했으면, nullptr 반환 ********************
	// 이를 이용해서 맞는 타입으로 캐스팅을 했는지 확인을 하는데 유용하다 
	// 안전하니까 무조건 dynamic_cast 써야하는게 아니다. 이게 좀더 시간이 걸린다.
	Player* p2 = new Archer();
	Knight* k2 = dynamic_cast<Knight*>(p2);  // 만약 이렇게 하면 원본 타입을 확인해서 캐스팅 해주는데, 원본이 이상하니까 nulltpr 반환

	// const_cast : const를 붙이거나 떼거나 할 때 활용
	// 살면서 실무에서 써볼 일이 없을 것. 그냥 존재만 알고 있어라
	PrintName(const_cast<char*>("Rookiss"));  // Rookiss는 const char[] 이기 때문에 컴파일 에러 발생

	// reinterpret_cast
	// 가장 위험하고 강력한 형태의 캐스팅
	// 're-interpret' : 다시-간주하다/생각하다
	// - 포인터랑 전혀 관계없는 다른 타입 변환 등
	__int64 address = reinterpret_cast<__int64>(k2);

	// 결론
	// 실무에서 8~90%가 static_cast
	// 10% 남짓이 nynamic_cast
	// 1% const, reinterpret 정도..
	// 면접에 나올 수 있으니 특징은 알고 있어라.

	return 0; 
}