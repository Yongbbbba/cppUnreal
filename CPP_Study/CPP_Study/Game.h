#pragma once

// 전방선언
// 헤더파일에서 전방선언을 활용하는 이유는 헤더파일간의 순환을 방지하기 위해서다.
// 예를 들어서 Game 헤더파일을 작성하기 위해서 Player 헤더파일을 include 하고,
// 동시에 Player 헤더파일에서 Game 헤더파일을 include 하는 상황이 발생할 때 이를 헤더파일의 순환구조가 만들어졌다고 한다.
// 이럴 경우 문제가 생길 수 있기 때문에 전방선언을 활용한다.
// 다만 cpp 파일에서는 전방선언을 활용하지 않는다.
class Player;
class Field;

// is - a
// has - a  (v)
class Game
{
public:
	Game();
	~Game();

	void Init();
	void Update();
	void CreatePlayer();

private:
	Player* _player;  // 포인터가 아닌 클래스 타입 변수로 해두면 다른 타입의 플레이어를 담을 수 없음. 데이터 유실 발생
	// 객체 생성할 때마다 복사가 일어나서 비효율적, 포인터 변수의 크기는 [4 - 8]
	// 포인터라는 것은 Player를 담는 주소 바구니에 불과하니까, Player 헤더파일이 완성될 필요는 없다. 그내용을 알 필요는 없다.
	// 하지만 Player 클래스가 나중에 구현될 것이라는 것을 알려줘야하니까 전방선언을 해둔다.
	// 그러면 문제없이 컴파일 된다.
	Field* _field;
};

