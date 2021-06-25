#pragma once
#include <mutex>

template<typename T>
class LockStack
{
public:
	LockStack() {}
	LockStack(const LockStack&) = delete;  // ��������� �õ��ϸ� ���ƹ�����
	LockStack& operator=(const LockStack&) = delete;

	void Push(T value)
	{
		lock_guard<mutex> lock(_mutex);
		_stack.push(std::move(value));  // �� ���� ������ ���ؼ�. move�� ���ٴ°Ŵ� value�� rvalue�� ����� ��.
		_condVar.notify_one();  // ������ ������ ������ �ϳ� �ƿ��.
	}

	bool TryPop(T& value)
	{
		// ������ ��������� stack�� ����ִ��� Ȯ���� �Ŀ� pop�� ���ִµ�, ��Ƽ������ ȯ�濡���� empty�� Ȯ�� �Ŀ� pop�� �ϴ� ���� �ǹ̰� ����. ��¥ empty���� ��Ȯ���� �ʱ� ������.
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
		_condVar.wait(lock, [this] {return _stack.empty() == false;});  // �����Ͱ� ���ͼ� notify_one�� ȣ���ϸ� ���� üũ�ؼ� ���ÿ� �����Ͱ� ���� ���� Ȯ���� �Ŀ� �Ͼ�� lock�� �ɰ� �۾��Ѵ�.
		value = std::move(_stack.top());
		_stack.pop();
	}


private:
	stack<T> _stack; 
	mutex _mutex;
	condition_variable _condVar;
};