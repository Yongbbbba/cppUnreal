#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

// 오늘의 주제 : 전달 참조(forwarding reference)
class Knight
{
public:
	Knight() { cout << "기본 생성자" << endl; }
	Knight(const Knight& ) { cout << "복사 생성자" << endl; }
	Knight(Knight&&) noexcept { cout << "이동 생성자" << endl; }

};

void Test_RValueRef(Knight&& k) // 오른값 참조
{

}

template<typename T>
void Test_ForwardingRef(T&& param) // 전달 참조
{
	// 인자로 왼값을 넣어줬으면 왼값 참조, 오른값을 넣어줬으면 오른값 참조
}

int main()
{
	// 보편 참조(universal reference) - 명칭 변경 
	// 전달 참조(forwarding reference) C++ 17

	// &&	&를 두 번 쓰면 -> 오른값 참조

	Knight k1;

	Test_RValueRef(std::move(k1));  // rvalue_cast.. 기능밖에 없는 move.

	Test_ForwardingRef(k1);  // 왼값 참조 변환
	Test_ForwardingRef(std::move(k1));  // 오른값 참조 변환
	
	auto&& k2 = k1;  // 왼값 참조 변환
	auto&& k3 = std::move(k1); // 오른값 참조 변환

	// 공통점 : 형식 연역 (type deduction)이 일어날 때  (template, auto 등)

	// 전달 참조를 구별하는 방법
	// --------------------------------------------------------------------

	Knight& k4 = k1; // 왼값 참조 
	Knight&& k5 = std::move(k1);  // 오른값 참조

	// 오른값 : 왼값이 아니다 = 단일식에서 벗어나면 사용 x
	// 오른값 참조 : 오른값만 참조할 수 있는 참조 타입
	// 
	Test_RValueRef(k4);
	Test_RValueRef(k5); // k5는 오른값이 맞나? 그저 오른값 참조를 받았을 뿐. 그렇기 때문에 엄밀히 오른값은 아니다.
	Test_RValueRef(std::move(k5));

	


	
	return 0;
}