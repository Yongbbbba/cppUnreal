#include <iostream>

using namespace std;

// 오늘의 주제 : 포인터 실습

struct StatInfo // 12bytes
{
	int hp;   // +0
	int attack;  // +4
	int defence; // +8
};

void EnterLobby();
StatInfo CreatePlayer();
void CreateMonster(StatInfo* info);
// 플레이어 승리 시 true, 아니면 false
bool StartBattle(StatInfo* player, StatInfo* monster);


int main()
{
	EnterLobby();
	
	return 0;
}

void EnterLobby()
{
	cout << "로비에 입장하였습니다." << endl;
	
	// 어셈블리 코드 까보면 temp 변수를 만들고 거기에 값을 복사해서 createPlayer에 매개변수로 넘겨준다.(정확히는 temp의 주소를)
	// 반면에 monster에서는 monster의 주소랄 매개변수로 넘겨주기 때문에 복사작업이 일어나지 않아서 메모리 효율적이다.
	StatInfo player;
	player.hp = 0xbbbbbbbb;
	player.attack = 0xbbbbbbbb;
	player.defence = 0xbbbbbbbb;

	player = CreatePlayer();

	StatInfo monster;
	monster.hp = 0xbbbbbbbb;
	monster.defence = 0xbbbbbbbb;
	monster.attack = 0xbbbbbbbb;
	
	CreateMonster(&monster);

	bool victory = StartBattle(&player, &monster);

	if (victory)
		cout << "승리!" << endl;
	else
		cout << "패배!" << endl;
	// 번외편1)
	// 구조체끼리 복사할 때는 무슨 일이 일어날까?
	//player = monster;
	// 위와 동일
	/*player.hp = monster.hp;
	player.attack = monster.attack;
	player.defence = monster.defence;*/

}

StatInfo CreatePlayer()
{
	StatInfo ret;

	cout << "플레이어 생성" << endl;

	ret.hp = 100; 
	ret.attack = 10;
	ret.defence = 2;

	return ret;
}

void CreateMonster(StatInfo* info)
{
	cout << "몬스터 생성" << endl;

	info->hp = 40;
	info->attack = 8;
	info->defence = 1;
}

bool StartBattle(StatInfo* player, StatInfo* monster)
{
	while (true)
	{
		int damage = player->attack - monster->defence;
		if (damage < 0)
			damage = 0;

		monster->hp -= damage;
		if (monster->hp < 0)
			monster->hp = 0;

		cout << "몬스터 HP: " << monster->hp << endl;

		if (monster->hp == 0)
			return true;

		damage = monster->attack - player->defence;
		if (damage < 0)
			damage = 0;

		cout << "플레이어 HP : " << player->hp << endl;

		player->hp -= damage;
		if (player->hp < 0)
			player->hp = 0;

		if (player->hp == 0)
			return false;
	}
}


