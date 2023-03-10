// 뱀.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <cstring>

class Point
{
public :
	uint32_t x;
	uint32_t y;
};
class Turn
{
public :
	uint32_t sec;
	char dir;
};

uint32_t N, K, L;

Point loc_apple[100];
Turn snakeMove[100];

using namespace std;

char inverseDir(char dir)
{
	switch (dir)
	{
	case 'U': return 'D';
	case 'D': return 'U';
	case 'L': return 'R';
	case 'R': return 'L';
	}

	return 0;
}

// changeDir : 뱀의 입장에서 본 전환방향
// playerDir : 플레이어 입장에서 본 현재 뱀의 진행방향
// return (changeDir방향으로 틀어진 playerDir)
char turn(char changeDir, char playerDir)
{
	switch (changeDir)
	{
	case 'U':
		switch (playerDir)
		{
		case 'U': return 'L';
		case 'D': return 'R';
		case 'L': return 'D';
		case 'R': return 'U';
		}

	case 'D':
		return inverseDir(turn('U', playerDir));
		
	case 'L':
		switch (playerDir)
		{
		case 'U': return 'L';
		case 'D': return 'R';
		case 'L': return 'D';
		case 'R': return 'U';
		}

	case 'R':
		return inverseDir(turn('L', playerDir));
	}

	return 0;
}

// 방향에 따라 뱀의 머리 위치 업데이트
void move(Point* target, char dir)
{
	switch (dir)
	{
	case 'U': target->y--; return;
	case 'D': target->y++; return;
	case 'L': target->x--; return;
	case 'R': target->x++; return;
	}
}
uint32_t play()
{
	Point loc_snake;
	loc_snake.x = 2;
	loc_snake.y = 1;
	char dir_snake = 'R'; // 뱀의 이동방향 : 상하좌우, UDLR 
	uint32_t len_snake = 2; // 뱀의 길이
	uint32_t cnt_snakeMove = 0; // 뱀이 방향을 튼 횟수
	
	for (uint32_t time = 1;; time++) // 시간흐름 카운트 
	{
		// 벽에 부딪혔나?
		if (loc_snake.x == 0 || loc_snake.y == 0 || N < loc_snake.x || N < loc_snake.y)
			return time;
		
		// 왔던 길을 자기 몸 길이만큼 되짚어가며 꼬리와 부딪혔는지 탐색
		{
			uint32_t idx_snakeMove = cnt_snakeMove - 1;
			char inversedDir = inverseDir(dir_snake);
			Point loc_tail = loc_snake;
			move(&loc_tail, inversedDir);

			for (uint32_t i = 1; i < len_snake; i++)
			{
				if (!memcmp(&loc_snake, &loc_tail, sizeof(Point))) // 부딪혔다면!
					return time;

				if (0 <= (signed)idx_snakeMove)
					if (snakeMove[idx_snakeMove].sec == time - i)
					{
						inversedDir = turn(inverseDir(snakeMove[idx_snakeMove].dir), inversedDir);
						idx_snakeMove--;
					}

				move(&loc_tail, inversedDir);
			}
		}

		for (uint32_t i = 0; i < K; i++) // 사과 목록을 돌며 탐색
		{
			// 사과를 먹었다면
			if (!memcmp(&loc_apple[i], &loc_snake, sizeof(Point)))
			{
				// 사과 하나 없어짐
				K--;
				memcpy(&loc_apple[i], &loc_apple[K], sizeof(Point));
				len_snake++;
				break;
			}
		}

		// 뱀이 방향을 튼다면
		if (snakeMove[cnt_snakeMove].sec == time)
		{
			/* 
			 * class Move의 dir은 뱀의 입장에서 본 방향이므로,
			 * 이를 플레이어의 입장에서 본 방향(dir_snake)으로 바꿔줄 필요가 있음
			 */
			dir_snake = turn(snakeMove[cnt_snakeMove].dir, dir_snake);
			cnt_snakeMove++;
		}
		
		// 뱀 머리 위치 업데이트
		move(&loc_snake, dir_snake);
	}
}

int main()
{
	cin >> N >> K;

	for (uint32_t i = 0; i < K; i++)
		cin >> loc_apple[i].y >> loc_apple[i].x;

	cin >> L;
	
	for (uint32_t i = 0; i < L; i++)
		cin >> snakeMove[i].sec >> snakeMove[i].dir;

	cout << play();
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
