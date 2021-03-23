#include <iostream>
using namespace std;

// 오늘의 주제 : 은닉성

// 객체지향 (OOP Object Oriented Programming)
// - 상속성
// - 은닉성
// - 다형성
// 
// 은닉성(Data Hiding) = 캡슐화(Encapsulation)
//몰라도 되는 것은 깔끔하게 숨기겠다!
// 숨기는 이유?
// 1) 정말 위험하고 건드리면 안되는 경우
// 2) 다른 경로로 접근하길 원하는 경우

// 자동차
// - 핸들
// - 페달
// - 엔진
// - 문
// - 각종 전기선

// 일반 구매자 입장에서 사용하는 것?
// 어떤 인터페이스로 자동차를 활용할까?
// -핸들/페달/문
// 몰라도 됨 (오히려 건드리면 큰일남)
// - 엔진, 각종 전기선

// public(공개적?)  protected (보호받는?)  private (개인의?)
// - public : 누가한테나 공개. 실컷 사용하세요
// - protected : 나의 자손들한테만 허락
// - private : 나만 사용할꺼! << class Car 내부에서만 사용할 수 있다. 상속자들도 사용할 수 없음

// 상속 접근 지정자 : 다음 세대한테 부모님의 유산을 어떻게 물려줄지?
// 부모님한테 물려받은 유산을 꼭 나의 자손들한테도 똑같이 물려줘야 하진 않음
// - public : 공개적 상속? 부모님의 유산 설계 그대로 ~ (public -> public, protected -> protected)
// - protected : 보호받은 상속? 내 자손들한테만 물려줄거야 (public-> protected, protected->protected) -> 실무에서 거의 안쓰임
// - private : 개인적인 상속? 나까지만 잘 쓰고 자손들한테는 아예 안 물려줄꺼야~ (public->private, protected->private) -> 실무에서 거의 안쓰임

class Car
{
public:  // (멤버) 접근 지정자
	void MoveHandle() {}
	void PushPedal() {}
	void OpenDoor() {}

	void TurnKey()
	{
		// ... 
		RunEngine();
	}

protected:
	// 사용자가 직접 조작할 필요도 없고 일반적으로 그래서는 안되는 부분.
	// 다른 인터페이스를 통해서 접근할 수 있는 부분
	
	void DisassembleCar() {} // 차를 분해한다
	void RunEngine() {} // 엔진을 구동시킨다 
	void Connectcircuit() {} // 전기선 연결

public:
	// 핸들
	// 페달
	// 엔진
	// 각종 전기선
	// 문
};

class SuperCar : public Car // 상속 접근 지정자
{
public:
	void PushRemotecontroller()
	{
		RunEngine();
	}
};

// '캡술화'
// 연관된 데이터와 함수를 논리적으로 묶어놓은 것

class Berserker
{
public:
	int GetHp() { return _hp; }
	
	// 사양 : 체력이 50 이하로 떨어지면 버서커 모드 발동 (강해짐)
	void SetHp(int hp)
	{
		_hp = hp;
		if (_hp <= 50)
			SetBerserkerMode();
	}

private:
	void SetBerserkerMode()
	{
		cout << "매우 강해짐!" << endl;
	}

private:
	int _hp = 100;
	
};

int main()
{
	Berserker b;
	b.SetHp(20);
	
	
	return 0;
}