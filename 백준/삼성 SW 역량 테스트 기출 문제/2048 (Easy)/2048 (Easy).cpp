// 2048 (Easy).cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

uint32_t N;

void move(uint32_t board[20][20], uint32_t dir)
{
	switch (dir)
	{
	case 0: // 위로 밀기
		for (uint32_t x = 0; x < N; x++)
			for (uint32_t block_complete = 0;; block_complete++)
			{
				uint32_t currentBlock = NULL; // 선택된 블록
				uint32_t foundBlock = NULL; // currentBlock과 짝지어진 블록

				for (uint32_t y = block_complete; y < N; y++)
					if (board[y][x] != 0) // 블록을 만나면
					{
						if (!currentBlock) // 블록이 선택되지 않았다면
						{
							currentBlock = board[y][x]; // 선택하기
							board[y][x] = 0;
						}
						else if (board[y][x] == currentBlock) // 만난 블록이 선택된 블록이라면
						{
							foundBlock = board[y][x]; // 짝짓기 후
							board[y][x] = 0;
							break; // 탈출
						}
						else // 블록이 선택되있는데 다른 블록을 만난거면
							break; // 탈출
					}

				if (!currentBlock) // 더이상 블록이 남아있지 않다면
					break;

				board[block_complete][x] = currentBlock + foundBlock; // 찾은 블록과 합쳐서 위에 쌓기
			}
		break;

	case 1: // 아래로 밀기
		for (uint32_t x = 0; x < N; x++)
			for (uint32_t block_complete = N - 1;; block_complete--)
			{
				uint32_t currentBlock = NULL; // 선택된 블록
				uint32_t foundBlock = NULL; // currentBlock과 짝지어진 블록

				for (uint32_t y = block_complete; 0 <= (signed)y; y--)
					if (board[y][x] != 0) // 블록을 만나면
					{
						if (!currentBlock) // 블록이 선택되지 않았다면
						{
							currentBlock = board[y][x]; // 선택하기
							board[y][x] = 0;
						}
						else if (board[y][x] == currentBlock) // 만난 블록이 선택된 블록이라면
						{
							foundBlock = board[y][x]; // 짝짓기 후
							board[y][x] = 0;
							break; // 탈출
						}
						else // 블록이 선택되있는데 다른 블록을 만난거면
							break; // 탈출
					}

				if (!currentBlock) // 더이상 블록이 남아있지 않다면
					break;

				board[block_complete][x] = currentBlock + foundBlock; // 찾은 블록과 합쳐서 아래에 쌓기
			}
		
		break;
	
	case 2: // 좌로 밀기
		for (uint32_t y = 0; y < N; y++)
			for (uint32_t block_complete = 0;; block_complete++)
			{
				uint32_t currentBlock = NULL; // 선택된 블록
				uint32_t foundBlock = NULL; // currentBlock과 짝지어진 블록

				for (uint32_t x = block_complete; x < N; x++)
					if (board[y][x] != 0) // 블록을 만나면
					{
						if (!currentBlock) // 블록이 선택되지 않았다면
						{
							currentBlock = board[y][x]; // 선택하기
							board[y][x] = 0;
						}
						else if (board[y][x] == currentBlock) // 만난 블록이 선택된 블록이라면
						{
							foundBlock = board[y][x]; // 짝짓기 후
							board[y][x] = 0;
							break; // 탈출
						}
						else // 블록이 선택되있는데 다른 블록을 만난거면
							break; // 탈출
					}

				if (!currentBlock) // 더이상 블록이 남아있지 않다면
					break;

				board[y][block_complete] = currentBlock + foundBlock; // 찾은 블록과 합쳐서 왼쪽에 쌓기
			}
		
		break;

	case 3: // 우로 밀기
		for (uint32_t y = 0; y < N; y++)
			for (uint32_t block_complete = N - 1;; block_complete--)
			{
				uint32_t currentBlock = NULL; // 선택된 블록
				uint32_t foundBlock = NULL; // currentBlock과 짝지어진 블록

				for (uint32_t x = block_complete; 0 <= (signed)x; x--)
					if (board[y][x] != 0) // 블록을 만나면
					{
						if (!currentBlock) // 블록이 선택되지 않았다면
						{
							currentBlock = board[y][x]; // 선택하기
							board[y][x] = 0;
						}
						else if (board[y][x] == currentBlock) // 만난 블록이 선택된 블록이라면
						{
							foundBlock = board[y][x]; // 짝짓기 후
							board[y][x] = 0;
							break; // 탈출
						}
						else // 블록이 선택되있는데 다른 블록을 만난거면
							break; // 탈출
					}

				if (!currentBlock) // 더이상 블록이 남아있지 않다면
					break;

				board[y][block_complete] = currentBlock + foundBlock; // 찾은 블록과 합쳐서 오른쪽에 쌓기
			}

		break;
	}
}

uint32_t dfs(uint32_t chance, uint32_t board[20][20], bool first = true)
{
	static uint32_t max;
	if (first)
		max = 0;
	if (!chance) // 이동기회를 다 썼다면
	{
		// board를 탐색하며
		for (uint32_t i = 0; i < N; i++)
			for (uint32_t j = 0; j < N; j++)
				if (max < board[i][j])
					max = board[i][j]; // 가장 큰 블록을 뽑아냄

		return max;
	}

	uint32_t tboard[20][20];

	/* 상하좌우로 이동하고 가지를 뻗어감 */
	for (uint32_t i = 0; i < 4; i++)
	{
		for (uint32_t i = 0; i < N; i++)
			for (uint32_t j = 0; j < N; j++)
				tboard[i][j] = board[i][j];

		move(tboard, i);

		dfs(chance - 1, tboard, false);
	}

	return max;
}

int main()
{
	uint32_t board[20][20];
	cin >> N;
	
	for (uint32_t i = 0; i < N; i++)
		for (uint32_t j = 0; j < N; j++)
			cin >> board[i][j];
	
	cout << dfs(5, board);
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
