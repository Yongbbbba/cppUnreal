#include <iostream>
#include <vector>
#include <list>

using namespace std;

// 오늘의 주제 : delete (삭제된 함수)
// 자주 활용되는 문법은 아니지만 종종 등장

class Knight
{
public:


//private:
//	// 정의되지 않은 비공개(private)함수
//	// 이렇게 하면 = 연산자를 사용할 수 없음.   knight2 = knight1 같은 것들.
//	void operator=(const Knight& k)
//	{
//
//	}
//	friend class Admin;  // Admin class에는 내 private을 쓸 수 있게 열어준다. 사실 friend를 쓴다는 것은 설계가 잘못된 경우가 다수..

public:
	void operator=(const Knight& k) = delete;
private:
	int _hp = 100;
};

class Admin
{
public:
	void CopyKnight(const Knight& k)
	{
		Knight k1;
		// 복사 연산 
		k1 = k;
	}
};

int main()
{	
	Knight k1;
	Knight k2;

	// 복사 연산자
	//k1 = k2;

	
	return 0;
}