#pragma once
#include <mutex>

template<typename T>
class LockStack
{
public:
	LockStack() {}
	LockStack(const LockStack&) = delete;  // 복사생성자 시도하면 막아버리기
	LockStack& operator=(const LockStack&) = delete;

	void Push(T value)
	{
		lock_guard<mutex> lock(_mutex);
		_stack.push(std::move(value));  // 더 빠른 연산을 위해서. move를 쓴다는거는 value를 rvalue로 만드는 것.
		_condVar.notify_one();  // 데이터 들어오면 스레드 하나 꺠운다.
	}

	bool TryPop(T& value)
	{
		// 기존의 방법에서는 stack이 비어있는지 확인한 후에 pop을 해주는데, 멀티스레드 환경에서는 empty를 확인 후에 pop을 하는 것이 의미가 없다. 진짜 empty인지 정확하지 않기 때문에.
		lock_guard<mutex> lock(_mutex);
		if (_stack.empty())
			return false;
		// empty -> top -> pop
		value = std::move(_stack.top());
		_stack.pop();
		return true;
	}

	void WaitPop(T& value)
	{
		unique_lock<mutex> lock(_mutex);
		_condVar.wait(lock, [this] {return _stack.empty() == false;});  // 데이터가 들어와서 notify_one을 호출하면 조건 체크해서 스택에 데이터가 들어온 것을 확인한 후에 일어나서 lock을 걸고 작업한다.
		value = std::move(_stack.top());
		_stack.pop();
	}


private:
	stack<T> _stack; 
	mutex _mutex;
	condition_variable _condVar;
};