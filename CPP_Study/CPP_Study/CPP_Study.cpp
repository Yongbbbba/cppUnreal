#include <iostream>
using namespace std;

// 오늘의 주제 : 얕은 복사  vs 깊은 복사
// 면접 단골 질문
class Pet
{
public:
	Pet()
	{
		cout << "Pet()" << endl;
	}
	~Pet()
	{
		cout << "~Pet()" << endl;
	}
	Pet(const Pet& pet)
	{
		cout << "Pet(const Pet&)" << endl;
	}
};

class RabbitPet : public Pet
{

};

class Knight
{
public:
	Knight()
	{
		_pet = new Pet();
	}

	Knight(const Knight& knight)
	{
		_hp = knight._hp;
		_pet = new Pet(*knight._pet);  // 깊은 복사
	}

	Knight& operator=(const Knight& knight)
	{
		_hp = knight._hp;
		_pet = new Pet(*knight._pet);  // 깊은 복사
		return *this;
	}

	~Knight()
	{
		delete _pet;
	}

public:
	int _hp = 100;
	// Pet _pet;  // 만약 Pet이 4000바이트가 넘는 크기를 가지고 있다면 Knight 객체를 만들 떄마다 이만한 크기가 덩달아 생김
	// 보통 클래스의 멤버 변수로 다른 클래스 타입의 변수를 가져야하는 경우에 포인터 형태로 갖고 있는 경우가 일반적
	Pet* _pet;
};


int main()
{

	// Pet* pet = new Pet();

	Knight knight;  // 기본 생성자
	knight._hp = 200;
	// knight._pet = pet;

	// 아래 두 방법이 같아 보이지만 미묘하게 다름
	Knight knight2 = knight;  // 복사 생성자
	// Knight knight3(knight);

	Knight knight3; // 기본 생성자
	knight3 = knight;  // 복사 대입 연산자

	// [복사 생성자] + [복사 대입 연산자]
	// 둘 다 안만들어주면 컴파일러가 '암시적으로' 만들어준다

	// 중간 결론) 컴파일러가 알아서 잘 만들어준다?
	// 수고하세요~ 다음 주제 넘어갈까요?  << NO 

	// [ 얕은 복사 Shallow Copy ] 
	// 멤버 데이터를 비트열 단위로 '똑같이' 복사 (메모리 영역 값을 그대로 복사)
	// 복사 생성자나 복사 대입 연산자를 통해서 knight1이 가지고 있던 것을 그대로 복사해버림 - 심지어 pet 포인터가 가리키고 있던 주소까지도..
	// 마치 같은 주소 공간을 공유하는 느낌처럼 되어버림.
	// 포인터는 주소값 바구니 -> 주소값을 똑같이 복사 -> 동일한 객체를 가리키는 상태가 됨
	// 	   이런 경우 발생되는 문제는 knight1이 소멸하게 되면 같은 주소 공간을 쓰고 있던 knight2, knight3이 소멸하면서 double free 문제가 발생하면서 crash가 발생할 수 있다는 것이다
	// 
	// Stack : Knight1 [ hp  0x1000  ]  -> Heap  0x1000 Pet [   ]
	// Stack : Knight2 [ hp  0x1000  ]  
	// Stack : Knight3 [ hp  0x1000  ]  

	// [ 깊은 복사 Deep Copy ]
	// 멤버 데이터가 참조(주소) 값이라면, 데이터를 새로 만들어준다 (원본 객체가 참조하는 대상까지 새로 만들어서 복사)
	// 포인터는 주소값 바구니 -> 새로운 객체를 생성 -> 상이한 객체를 가리키는 상태가 됨
	// Stack : Knight1 [ hp  0x1000  ]  -> Heap  0x1000 Pet [   ]
	// Stack : Knight2 [ hp  0x2000  ]  -> Heap 0x2000 Pet [   ]
	// Stack : Knight3 [ hp  0x3000  ]  -> Heap 0x3000 Pet [   ]

	return 0;
}