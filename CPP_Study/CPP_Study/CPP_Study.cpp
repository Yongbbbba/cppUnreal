#include <iostream>
#include <string>

using namespace std;

// 오늘의 주제 : 포인터
\
int main()
{
	// 지금까지 사용한 방식
	// number라는 이름의 4바이트 정수타입의 바구니를 만든다
	// number라는 변수 스택 메모리에 할당
	// number = 1라 함은, number 바구니에 1이라는 숫자를 넣으라는 의미
	// number는 비유하자면 메모리에 이름을 붙인 것(찰떡같이 알아들어서)
	// 나쁘지 않고 편리한데, textRPG 원본 수정

	int number = 1;

	// TYPE* 변수이름;
	// 일단 2가지 요소
	// - TYPE
	// - *
	int* ptr = &number;
	// 바구니는 바구니인데...
	// [주소를 저장하는 바구니다!]
	// 변수를 선언할 때 * 등장했다 -> 포인터 = 주소
	// 참고) 포인터라는 바구니는 8바이트(64비트) 고정 크기, type에 따라 달라지는게 아님.
	// - 앞에 나온 타입은 바구니에 담을 변수의 타입이다

	// 근데 남의 주소를 갖고 뭘 하라는거지?
	// 추가 문법 : [주소를 저장하는 바구니]가ㅏ 가리키는 주소로 가서 무엇인가를 해라!
	// *변수이름 = 값;

	int value1 = *ptr;
	*ptr = 2;
	cout << *ptr << endl;
	cout << value1 << endl;


	return 0;
}


