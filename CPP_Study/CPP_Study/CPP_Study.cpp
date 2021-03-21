#include <iostream>
#include <iomanip>

using namespace std;

// 오늘의 주제 : 연습 문제 : 달팽이

const int MAX = 100;
int board[MAX][MAX] = {};
int N;

void PrintBoard()
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cout << setfill('0')  << setw(2) <<  board[y][x] << " ";
		}
		cout << endl;
	}
}

void MySetBoard(int board[MAX][MAX], int N)
{
	int r = 0;
	int c = -1;
	int num = 1;
	int endV = N * N;

	while (num <= endV)
	{

		for (int i = 0; i < N; i++)
		{
			c++;
			board[r][c] = num;
			num++;
		}
		N--;
		for (int i = 0; i < N; i++)
		{
			r++;
			board[r][c] = num;
			num++;
		}
		for (int i = 0; i < N; i++)
		{
			c--;
			board[r][c] = num;
			num++;
		}
		N--;
		for (int i = 0; i < N; i++)
		{
			r--;
			board[r][c] = num;
			num++;
		}
	}
}

enum DIR
{
	RIGHT,
	DOWN,
	LEFT,
	UP,
};

bool CanGo(int y, int x)
{
	if (y < 0 || y >= N)
		return false;
	if (x < 0 || x >= N)
		return false;
	if (board[y][x] != 0)
		return false;
	return true;
}

void SetBoard()
{
	int dir = RIGHT;

	int num = 1;
	int y = 0;
	int x = 0;

	int dy[] = { 0,1,0,-1 };
	int dx[] = { 1,0,-1,0 };

	while (true)
	{
		board[y][x] = num;

		if (num == N * N)
			break;

		int nextY = y + dy[dir];
		int nextX = x + dx[dir];

		//switch (dir)
		//{
		//case RIGHT:
		//	nextY = y;
		//	nextX = x+1;
		//	break;
		//case DOWN:
		//	nextY = y+1;
		//	nextX = x;
		//	break;
		//case LEFT:
		//	nextY = y;
		//	nextX = x - 1;
		//	break;
		//case UP:
		//	nextY = y-1;
		//	nextX = x;
		//	break;
		//}

		// 갈 수 있는 곳이면 
		if (CanGo(nextY, nextX))
		{
			y = nextY;
			x = nextX;
			num++;
		}

		// 갈 수 없으면 방향 바꾸기
		else
		{
			dir = (dir + 1) % 4;
			/*switch (dir)
			{
			case RIGHT:
				dir = DOWN;
				break;
			case DOWN:
				dir = LEFT;
				break;
			case LEFT:
				dir = UP;
				break;
			case UP:
				dir = RIGHT;
				break;
			}*/
		}
	}
}

int main()
{
	cin >> N;

	//MySetBoard(board, N);
	SetBoard();
	PrintBoard();

	return 0;
}