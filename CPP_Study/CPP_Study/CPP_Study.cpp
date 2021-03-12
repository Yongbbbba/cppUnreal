#include <iostream>
#include <string>

using namespace std;

const int S = 1; // 가위
const int R = 2; // 바위
const int P = 3; // 보



// 가위(1) 바위(2) 보 게임 만들기
int main()
{

	// rand(); // 0 ~ 32767 출력
	// int value = 1 + rand() % 3; // 0, 1, 2 세 가지 랜덤으로 출력하는 꼼수
	int my_value;
	int your_value;
	string my;
	string your;
	
	cout << "가위(1) 바위(2) 보(3) 게임" << endl;
	cout << endl;

	while (true)
	{
		srand(time(0)); // 시드값 설정해주는 것

		cout << "가위! 바위! 보! : ";
		cin >> my_value;
		cout << endl;

		if (my_value == R) my = "바위";
		else if (my_value == S) my = "가위";
		else my = "보";

		your_value = 1 + rand() % 3;

		if (your_value == R) your = "바위";
		else if (your_value == S) your = "가위";
		else your = "보";
		

		if (my_value == R || my_value == S || my_value == P)
		{
			cout << my << "(나) vs " << your << "(상대방) " << "=> ";
			// 내가 가위 냈을 때
			if (my_value == S)
			{
				if (your_value == S) cout << "비겼습니다" << endl;

				else if (your_value == R) cout << "졌습니다" << endl;
				else cout << "이겼습니다" << endl;
			}

			// 내가 바위 냈을 때
			else if (my_value == R)
			{
				if (your_value == S) cout << "이겼습니다" << endl;

				else if (your_value == R) cout << "비겼습니다" << endl;
				else cout << "졌습니다" << endl;
			}

			// 내가 보냈을 때
			else
			{
				if (your_value == S) cout << "졌습니다" << endl;

				else if (your_value == R) cout << "이겼습니다" << endl;
				else cout << "비겼습니다" << endl;
			}

		}

		else
		{
			cout << "게임이 종료되었습니다." << endl;
			return 0;
		}
	}
}

