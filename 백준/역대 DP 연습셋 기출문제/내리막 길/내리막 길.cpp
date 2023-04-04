// 내리막 길.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

uint32_t N, M, map[500][500], dp[500][500];

void  dfs(uint32_t x, uint32_t y)
{
	uint32_t result = 0;

	if (x == N - 1 && y == M - 1)
		return;

	// 위로 이동
	if (0 <= (signed)y - 1)
		// 높이는 위에서 아래로 가야함
		if (map[y - 1][x] < map[y][x])
		{
			if (dp[y - 1][x] == -1)
				dfs(x, y - 1);

			result += dp[y - 1][x];
		}

	// 아래로 이동
	if (y + 1 < M)
		if (map[y + 1][x] < map[y][x])
		{
			if (dp[y + 1][x] == -1)
				dfs(x, y + 1);

			result += dp[y + 1][x];
		}

	// 왼쪽으로 이동
	if (0 <= (signed)x - 1)
		if (map[y][x - 1] < map[y][x])
		{
			if (dp[y][x - 1] == -1)
				dfs(x - 1, y);

			result += dp[y][x - 1];
		}

	// 오른쪽으로 이동
	if (x + 1 < N)
		if (map[y][x + 1] < map[y][x])
		{
			if (dp[y][x + 1] == -1)
				dfs(x + 1, y);
			
			result += dp[y][x + 1];
		}

	dp[y][x] = result;
}

int main()
{
	cin >> M >> N;
	for (uint32_t i = 0; i < M; i++)
		for (uint32_t j = 0; j < N; j++)
		{
			cin >> map[i][j];
			dp[i][j] = -1;
		}

	// solving task
	dp[M - 1][N - 1] = 1;
	dfs(0, 0);
	
	cout << (signed)dp[0][0];
}