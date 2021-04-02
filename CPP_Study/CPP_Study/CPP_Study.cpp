#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <map>

using namespace std;

// 오늘의 주제 : map
class Player
{
public:
	Player() : _playerId(0) {}
	Player(int playerId) : _playerId(playerId) {}

public:
	int _playerId;
};


int main()
{
	// 연관 컨테이너
	
	vector<Player*> v;

	// 10만 명 입장
	for (int i = 0; i < 100000; i++)
	{
		Player* p = new Player(i);
		v.push_back(p);
	}

	// 5만 명이 퇴장
	// 랜덤으로 나간다고 생각
	for (int i = 0; i < 50000; i++)
	{
		int randIndex = rand() % v.size();

		Player* p = v[randIndex];
		delete p;

		v.erase(v.begin() + randIndex);
	}

	// (ID = 2만 플레이어)가 (ID = 1만 player)를 공격하고 싶어요
	// Q) ID = 1만인 player를 찾아주세요
	// A) 찾아본다. vector는 처음부터 끝까지 원하는 값이 나올 때까지 찾아봐야함! 

	// vector, list의 치명적인 단점
	// -> 원하는 조건에 해당하는 데이터를 빠르게 찾을 수 [없다]

	// map :  균형 이진 트리 (AVL)
	// - 노드 기반
	
	class Node
	{
	public:
		Node* _left;
		Node* _right;
		// DATA
		pair<int, Player*> _data;
		/*int _key;
		Player* _value;*/
	};
	srand(static_cast<unsigned int>(time(nullptr)));
	// (Key, value)
	map<int, int> m;

	pair<map<int, int>::iterator, bool> ok;
	
	ok = m.insert(make_pair(1, 100));
	ok = m.insert(make_pair(1, 200));


	// 이미 존재하는 키라면 insert 되지 않음. 해당 키에 다른 값을 넣고 싶으면 insert말고 다른 걸 써야함

	m.insert(make_pair(1, 100));
	m.insert(make_pair(1, 200));

	// 10만명
	for (int i = 0; i < 100000; i++)
	{
		m.insert(pair<int, int>(i, i * 100));
	}

	// 5만명 퇴장
	for (int i = 0; i < 50000; i++)
	{
		int randomValue = rand() % 50000;

		// Erase By Key
		m.erase(randomValue);
	}

	// Q) ID = 1만인 Player 찾고 싶다!
	// A) 매우 빠르게 찾을 수 있음
	unsigned int count = 0;
	count = m.erase(10000);
	count = m.erase(10000);
	
	map<int,int>::iterator findIt = m.find(10000);


	if (findIt != m.end())
	{
		cout << "찾음" << endl;
	}

	// 끝까지 10000을 못찾았다는 이야기
	else
	{
		cout << "못찾음" << endl;
	}

	// map 순회
	// v[0] ~ v[i] 
	for (map<int, int>::iterator it = m.begin(); it != m.end(); ++it)
	{
		pair<const int, int>& p = (*it);
		int key = p.first;   // it->first;
		int value = p.second; // it->second;
		
		cout << key << " " << value << endl;
	}

	// 없으면 추가, 있으면 수정

	map<int, int>::iterator findIt = m.find(10000);
	if (findIt != m.end())
	{
		findIt->second = 200;
	}
	else
	{
		m.insert(make_pair(10000, 200));
	}

	// 없으면 추가, 있으면 수정 v2
	m[5] = 500;

	m.clear();
	// [] 연산자 사용할 때 주의할 점
	// 대입을 하지 않더라도 (Key/vlaue)형태의 데이터가 추가된다.
	for (int i = 0; i < 10; i++)
	{
		cout << m[i] << endl;
	}

	// 넣고 (insert, [])
	// 뺴고 (erase)
	// 찾고 (find, [])
	// 반복자 (map::iterator) (*it) pair<key, value>&
	

	return 0;
}