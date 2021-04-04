#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

// 오늘의 주제 : 스마트 포인터 (smart pointer)
// 서버 시간에 주로 활용할 것인데, 기본적인 것만 훑고 갈 것

class Knight
{
public:
	Knight() { cout << "Knight 생성" << endl; }
	~Knight() { cout << "Knight 소멸" << endl; }

	void Attack()
	{
		if (_target)
		{
			_target->_hp -= _damage;
			cout << "HP: " << _target->_hp << endl;
		}
	}

public:
	int _hp = 100;
	int _damage = 10;
	shared_ptr<Knight> _target = nullptr;
};

class RefCountBlock
{
public:
	int _refCount = 1;
};

template<typename T>
class SharedPtr
{
public:
	SharedPtr() {}
	SharedPtr(T* ptr) : _ptr(ptr)
	{
		if (_ptr != nullptr)
		{
			_block = new RefCountBlock();
			cout << "RefCount : " << _block->_refCount << endl;
		}
	}

	SharedPtr(const SharedPtr& sptr) : _ptr(sptr._ptr), _block(sptr._block)
	{
		if (_ptr != nullptr)
		{
			_block->_refCount++;
			cout << "RefCount : " << _block->_refCount << endl;
		}
	}

	void operator=(const SharedPtr& sptr)
	{
		_ptr(sptr._ptr);
		_block(sptr._block);
		if (_ptr != nullptr)
		{
			_block->_refCount++;
			cout << "RefCount : " << _block->_refCount << endl;
		}
	}

	~SharedPtr()
	{
		if (_ptr != nullptr)
		{
			_block->_refCount--;
			cout << "RefCount : " << _block->_refCount << endl;

			if (_block->_refCount == 0)
			{
				delete _ptr;
				delete _block;
				cout << "Delete Data" << endl;
			}
		}
	}

public:
	T* _ptr = nullptr;
	RefCountBlock* _block = nullptr;
};

int main()
{
	//Knight* k1 = new Knight();
	//Knight* k2 = new Knight();

	//k1->_target = k2;

	//delete k2;

	//// k2가 이미 삭제되었지만 k1의 target이 nullptr로 자동으로 바뀌는 것이 아니기 때문에 엉뚱한 값을 출력하게 된다.
	//k1->Attack();

	// 스마트 포인터 : 포인터를 알맞는 정책에 따라 관리하는 객체 (포인터를 래핑해서 사용)
	// shared_ptr, weak_ptr, unique_ptr 
	// shared_ptr이 스마트 포인터의 대표
	//SharedPtr<Knight> k1(new Knight());
	//SharedPtr<Knight> k2 = k1;
	{
		shared_ptr<Knight> k1 = make_shared<Knight>();
		{
			shared_ptr<Knight> k2 = make_shared<Knight>();
			k1->_target = k2;
		}

		k1->Attack();  // k2는 중괄호 안에서만 유효한데, shared_ptr로 k2가 소멸되지 않는다. 누가 k2를 참조하고 있다는 것을 기억하고 있기 때문.
	}

	// shared_ptr 외에 다른 것들은 왜 있는건가? 
	{
		shared_ptr<Knight> k1 = make_shared<Knight>();
		
		shared_ptr<Knight> k2 = make_shared<Knight>();
		k1->_target = k2;
		k2->_target = k1;
		// 순환이 발생해서 절대 소멸하지 않는 문제가 발생
		
		k1->Attack();
		
		// 이렇게 순환을 끊어줘야 소멸한다.
		k1->_target = nullptr;
		k2->_target = nullptr;
	}

	unique_ptr<Knight> uptr = make_unique<Knight>();
	// unique_ptr<Knight> uptr2 = uptr;  // 사용불가
	unique_ptr<Knight> uptr2 = move(uptr);




	return 0;
}