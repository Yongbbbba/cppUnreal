#include <iostream>
using namespace std;

// 오늘의 주제 : 객체지향 마무리

// 1) Struct vs class

// C++에서는 struct나 class나 종이 한 장 차이다.
// struct는 기본 접근 지정자가 public이고, class는 private이다.
// 왜 이렇게 했을까? C++은 C언어에서 파생되어 발전했기 때문에, 호환성을 어느정도 지키기 위해서.
// -> struct는 그냥 구조체 (데이터 묶음)을 표현하는 정도
// -> class는 객체 지향 프로그래밍의 특징 나타내는 용도


// 2) static 변수, static 함수 (static = 정적 = 고정된)

class Marine
{
public:
	// 일반 멤버 변수는 특정 마린 객체에 종속적
	int _hp;

	void TakeDamage(int damage)
	{
		_hp -= damage;
	}

	// 일종의 전역함수처럼 기능함
	// 해당 클래스의 객체를 생성하지 않고도, 클래스 이름만으로 호출할 수 있음
	// 객체를 생성하지 않으므로, this 포인터를 가지지 않는다
	// 특정 객체와 결합하지 않으므로, 정적 멤버 변수밖에 사용할 수 없음
	static void SetAttack()
	{
		s_attack = 100;
	}
	
	// 특정 마린 객체와 무관
	// 마린이라는 '클래스' 자체와 연관
	// 마치 전역변수를 만든 것과 같은 느낌..
	// 클래스 영역에서 선언되지만, 정의는 파일 영역에서 수행
	static int s_attack;  // 설계도상으로만 존재
};
// static 변수는 어떤 메모리?
// 초기화 하면 .data
// 초기화 하지 않으면 .bss
int Marine::s_attack = 0; // 파일 영역에서 정의

class Player
{
public:
	int _id;
};

int GeneratedId()
{
	// 생명주기 : 프로그램 시작/종료 (메모리에 항상 올라가 있음)
	// 가시범위 : 함수 내부
	// 
	// 정적 지역 객체
	static int s_id = 1;

	return s_id++;
}

int main()
{
	Marine m1;
	m1._hp = 40;
	//m1.s_attack = 6;
	Marine::s_attack = 6;

	Marine m2;
	m2._hp = 40;
	//m2.s_attack = 6;

	// 마린 공격력 업그레이드 완료! (Academy에서 업그레이드 끝) 
	// 한 마리의 마린만 공격력 업그레이드 되는 것이 아니라 모든 마린이 공격력이 올라야함
	// 이걸 가능하게 해주는 것이 static 키워드
	//m1.s_attack = 7;
	//m2.s_attack = 7;
	Marine::s_attack = 7;
	Marine::SetAttack();

	// 스택 아님.  .data 영역
	static int id = 10;
	int a = id;

	return 0;
}