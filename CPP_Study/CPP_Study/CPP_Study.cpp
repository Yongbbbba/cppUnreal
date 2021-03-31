#include <iostream>
#include <vector>

using namespace std;

// 오늘의 주제 : vector
template<typename T>
class Iterator
{
public:
	Iterator() : _ptr(nullptr)
	{

	}

	Iterator(T* ptr) : _ptr(ptr)
	{

	}

	// 전위형은 자기자신을 뱉어주는데 반해, 후위형은 복사값을 내뱉어준다. 그래서 (a++)++와 같이 쓸 수 없는 반면, ++(++a)는 가능한.
	Iterator& operator++()
	{
		_ptr++;
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator temp = *this;
		_ptr++; // 원본값을 증가시키기는 하지만 뱉어줄 때는 증가시키기 전을 뱉어줘야함. 후위형의 정의가 그런거니까.
		return temp;
	}

	Iterator& operator--()
	{
		_ptr--;
		return *this;
	}

	Iterator operator--(int)
	{
		Iterator temp = *this;
		_ptr--;
		return temp;
	}

	Iterator operator+(const int count)
	{
		Iterator temp = *this;
		temp._ptr += count;
		return temp;
	}

	Iterator operator-(const int count)
	{
		Iterator temp = *this;
		temp._ptr -= count;
		return temp;
	}

	bool operator==(const Iterator& right)
	{
		return  _ptr == right._ptr;
	}

	bool operator!=(const Iterator& right)
	{
		return !(*this == right);  // 위 == 연산자 오버로딩 재활용,   _ptr != right._ptr 과 같은 의미임
	}

	T& operator*()
	{
		return *_ptr;
	}

public:
	T* _ptr;
};

template<typename T>
class Vector
{

public:
	Vector() : _data(nullptr), _size(0), _capacity(0)
	{

	}

	~Vector()
	{
		if (_data)
			delete[] _data;
	}

	// [     ]
	void push_back(const T& val)
	{
		if (_size == _capacity)
		{
			// 증설 작업
			int newCapacity = static_cast<int>(_capacity * 1.5);
			if (newCapacity == _capacity)
				newCapacity++;

			reserve(newCapacity);
		}

		// 데이터 저장 및 개수 증가
		_data[_size++] = val;
	}

	void reserve(int capacity)
	{
		_capacity = capacity;

		T* newData = new T[_capacity];

		// 데이터 복사
		for (int i = 0; i < _size; i++)
			newData[i] = _data[i];

		// 기존에 있던 데이터 날리기
		if (_data)
			delete[] _data;

		// 데이터 교체
		_data = newData;
	}

	// 데이터를 조회하는 것 뿐만 아니라 값을 변경할 수도 있기 때문에 레퍼런스로 반환한다.
	T& operator[](const int pos) { return _data[pos];  }

	int size() { return _size; }
	int capacity() { return _capacity; }

public:
	typedef Iterator<T> iterator;

	iterator begin() { return iterator(&_data[0]); }
	iterator end() { return begin() + _size; }

private:
	T* _data;
	int _size;
	int _capacity;
};

int main()
{	
	Vector<int> v;
	v.reserve(100);

	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
		cout << v.size() << " " << v.capacity() << endl;
	}

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}
	
	for (Vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	{
		cout << (*it) << endl;
	}
	return 0;
}