// 구슬 탈출 2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <cstring>

using namespace std;

char** board;
uint32_t N, M;

typedef struct Point {
	uint32_t x;
	uint32_t y;
} Point;

bool move(Point* Red, Point* Blue, uint32_t dir)
{
	Point Red_dir, Blue_dir;

	// dir( = 기울일 방향)에 따라 빨간색과 파란색 구슬이 움직일 위치 결정
	switch (dir)
	{
	case 0: // 위로
		// 좌표 움직임
		Red_dir.x = Red->x;
		for (Red_dir.y = Red->y - 1; board[Red_dir.y][Red->x] != '#' &&
									 board[Red_dir.y][Red->x] != 'O'; Red_dir.y--);
		if (board[Red_dir.y][Red->x] == '#')
			Red_dir.y++;


		Blue_dir.x = Blue->x;
		for (Blue_dir.y = Blue->y - 1; board[Blue_dir.y][Blue->x] != '#' &&
									   board[Blue_dir.y][Blue->x] != 'O'; Blue_dir.y--);
		if (board[Blue_dir.y][Blue->x] == '#')
			Blue_dir.y++;

		break;

	case 1: // 아래로
		// 좌표 움직임
		Red_dir.x = Red->x;
		for (Red_dir.y = Red->y + 1; board[Red_dir.y][Red->x] != '#' &&
									 board[Red_dir.y][Red->x] != 'O'; Red_dir.y++);
		if (board[Red_dir.y][Red->x] == '#')
			Red_dir.y--;


		Blue_dir.x = Blue->x;
		for (Blue_dir.y = Blue->y + 1; board[Blue_dir.y][Blue->x] != '#' &&
									   board[Blue_dir.y][Blue->x] != 'O'; Blue_dir.y++);
		if (board[Blue_dir.y][Blue->x] == '#')
			Blue_dir.y--;

		break;

	case 2: // 왼쪽으로
		// 좌표 움직임
		for (Red_dir.x = Red->x - 1; board[Red->y][Red_dir.x] != '#' &&
									 board[Red->y][Red_dir.x] != 'O'; Red_dir.x--);
		if (board[Red->y][Red_dir.x] == '#')
			Red_dir.x++;
		Red_dir.y = Red->y;

		for (Blue_dir.x = Blue->x - 1; board[Blue->y][Blue_dir.x] != '#' &&
									   board[Blue->y][Blue_dir.x] != 'O'; Blue_dir.x--);
		if (board[Blue->y][Blue_dir.x] == '#')
			Blue_dir.x++;
		Blue_dir.y = Blue->y;

		break;

	case 3: // 오른쪽으로
		// 좌표 움직임
		for (Red_dir.x = Red->x + 1; board[Red->y][Red_dir.x] != '#' &&
									 board[Red->y][Red_dir.x] != 'O'; Red_dir.x++);
		if (board[Red->y][Red_dir.x] == '#')
			Red_dir.x--;
		Red_dir.y = Red->y;

		for (Blue_dir.x = Blue->x + 1; board[Blue->y][Blue_dir.x] != '#' &&
									   board[Blue->y][Blue_dir.x] != 'O'; Blue_dir.x++);
		if (board[Blue->y][Blue_dir.x] == '#')
			Blue_dir.x--;
		Blue_dir.y = Blue->y;

		break;
	}

	/* 현 시점에서 빨간색과 파란색이 각각 움직인 좌표가 Red_dir과 Blue_dir에 저장되어 있으나, 겹쳐있을 수도 있음 */

	if (board[Blue_dir.y][Blue_dir.x] == 'O') // 파란색이 구멍에 들어간 경우
		return false;

	if (!memcmp(&Red_dir, &Blue_dir, sizeof(Point))) // 빨간색과 파란색이 겹친경우
	{
		switch (dir)
		{
		case 0: // 위로 움직였던 경우
			if (Red->y < Blue->y) // 원래 빨간색이 위에 있었다면
				Blue_dir.y++; // 파란색을 아래로 내림
			else
				Red_dir.y++;
			break;

		case 1: // 아래로 움직였던 경우
			if (Red->y < Blue->y) // 원래 빨간색이 위에 있었다면
				Red_dir.y--; // 빨간색을 위로 올림
			else
				Blue_dir.y--;
			break;

		case 2: // 왼쪽으로 움직였던 경우
			if (Red->x < Blue->x) // 원래 빨간색이 왼쪽에 있었다면
				Blue_dir.x++; // 파란색을 오른쪽으로 옮김
			else
				Red_dir.x++;
			break;

		case 3: // 오른쪽으로 움직였던 경우
			if (Red->x < Blue->x) // 원래 빨간색이 왼쪽에 있었다면
				Red_dir.x--; // 빨간색을 왼쪽으로 옮김
			else
				Blue_dir.x--;
			break;
		}
	}

	// 결과적으로 둘 다 이동하지 않았다면
	if (!memcmp(Red, &Red_dir, sizeof(Point)) && !memcmp(Blue, &Blue_dir, sizeof(Point)))
		return false;

	Red->x = Red_dir.x;
	Red->y = Red_dir.y;
	Blue->x = Blue_dir.x;
	Blue->y = Blue_dir.y;
	return true;
}

int dfs(Point Red = { 0, 0 }, Point Blue = { 0, 0 }, uint32_t distance = 0)
{
	static uint32_t min;
	
	if (Red.x == 0) // 초기화
	{
		min = -1;

		// 빨간색 구슬과 파란색 구슬 위치 결정
		for (uint32_t i = 0; i < N; i++)
			for (uint32_t j = 0; j < M; j++)
			{
				if (board[i][j] == 'R')
				{
					Red.x = j;
					Red.y = i;
				}
				else if (board[i][j] == 'B')
				{
					Blue.x = j;
					Blue.y = i;
				}
			}
	}
	if (distance == 10)
		return min;
	
	/* 상하좌우 이동 */
	
	for (uint32_t i = 0; i < 4; i++)
	{
		Point Red_dir = Red, Blue_dir = Blue;

		if (move(&Red_dir, &Blue_dir, i)) // 이동 성공이라면
		{
			if (board[Red_dir.y][Red_dir.x] == 'O') // 골인이라면
			{
				if (distance + 1 < min)
					min = distance + 1; // 기록 경신

				return min;
			}
			dfs(Red_dir, Blue_dir, distance + 1); // 가지 뻗기
		}
	}

	return min;
}

int main()
{
	cin >> N >> M;
	
	board = new char*[N + 1];
	for (uint32_t i = 0; i < N; i++)
	{
		board[i] = new char[M + 1];
		cin >> board[i];
	}
	
	cout << dfs();
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
