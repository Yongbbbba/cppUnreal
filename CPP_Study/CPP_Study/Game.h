#pragma once
#include "Player.h"

// is - a
// has - a  (v)
class Game
{
public:

private:
	Player* _player;  // 포인터가 아닌 클래스 타입 변수로 해두면 다른 타입의 플레이어를 담을 수 없음. 데이터 유실 발생
	// 객체 생성할 때마다 복사가 일어나서 비효율적
};

