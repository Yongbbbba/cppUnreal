#include <iostream>

using namespace std;

// 오늘의 주제 : 로또 번호 생성기

void Swap(int& a, int& b);
void Sort(int numbers[], int size);
void ChooseLotto();

int main()
{
	// 1) Swap 함수 만들기 
	int a = 1;
	int b = 2;
	Swap(a, b);
	// a = 2, b = 1
	//cout << a << " " << b << endl;

	// 2) 정렬 함수 만들기 (작은 숫자가 먼저 오도록 정렬)
	int numbers[6] = { 1,42,3,15,5,6 };
	Sort(numbers, 6);   // sizeof(numbers) / sizeof(int) => 배열 사이즈 구하는 법
	// {1,3,5,6,15,42}
	//for (auto num : numbers) cout << num << " ";

	// 3) 로또 번호 생성기
	ChooseLotto();
	
	return 0;
}

void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void Sort(int numbers[], int size)
{
	// 선택정렬 사용
	for (int i = 0; i < size; i++)
	{
		int min = numbers[i];
		int min_idx=i;
		for (int j = i+1; j < size; j++)
		{
			if (numbers[j] < min)
			{
				min = numbers[j];
				min_idx = j;
			}
		}

		int temp = numbers[i];
		numbers[i] = numbers[min_idx];
		numbers[min_idx] = temp;
	}
}

void ChooseLotto()
{
	// TODO : 랜덤으로 1~45 사이의 숫자 6개를 골라주세요! (단, 중복이 없어야함)
	// 순서대로 출력

	srand(time(0)); // 랜덤 시드 설정
	int numbers[6];
	int temp;
	int i = 0;
	while (i != 6)
	{
		temp = (rand() % 46) + 1;
		bool check = true;
		// 중복 체크하기
		for (int j = 0; j < i; j++)
		{
			if (numbers[j] == temp)
			{
				check = false;
				break;
			}
		}

		if (check)
		{
			numbers[i] = temp;
			i++;	
		}
	}
	
	Sort(numbers, 6);
	for (auto num : numbers) cout << num << " ";
	cout << endl;
}