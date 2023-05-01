// 외판원 순회.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

uint32_t N, W[16][16];
uint32_t dp[16][1 << 16]; // j(비트마스크) 도시들을 방문한 상태에서 i번 도시에서 출발해 첫번째 도시로 가는데 비용의 최솟값 dp[i][j]


uint32_t dfs(uint32_t current = 0, uint32_t bitmask = 1)
{
	// 종료조건
	if ((1 << N) - 1 == bitmask)
	{
		dp[current][bitmask] = W[current][0];
		return dp[current][bitmask];
	}

	if (dp[current][bitmask] != -1)
		return dp[current][bitmask];

	// 도시들을 순회함
	for (uint32_t i = 0; i < N; i++)
	{
		if (!((1 << i) & bitmask) && W[current][i] != 0) // 도시가 bitmask(순회한 도시 목록)에 없고 current에서 도시로 갈 수 있는 경우
		{
			dfs(i, (1 << i) | bitmask);
			
			if (dp[i][(1 << i) | bitmask] != -1 && dp[i][(1 << i) | bitmask] != 0)
				dp[current][bitmask] = min(dp[current][bitmask], dp[i][(1 << i) | bitmask] + W[current][i]);
		}
	}
	if (dp[current][bitmask] == -1)
		dp[current][bitmask] = 0;

	return dp[current][bitmask];
}

int main()
{
	cin >> N;

	for (uint32_t i = 0; i < N; i++)
		for (uint32_t j = 0; j < N; j++)
			cin >> W[i][j];

	for (uint32_t i = 0; i < N; i++)
		memset(dp[i], -1, (1 << 16) * sizeof(uint32_t));

	cout << dfs(0, 1);

}