// 고층 빌딩.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string.h>

using namespace std;

uint64_t dp[101][101][101];
uint32_t N, L, R;

int main()
{
	cin >> N >> L >> R;

	for (uint32_t i = 0; i < 100; i++)
	{
		for (uint32_t j = 0; j < 100; j++)
			memset(dp[i][j], 0, 100);
	}

	dp[0][0][0] = 1;
	for (uint32_t i = 0; i < N; i++)
	{
		for (uint32_t j = 0; j <= i; j++)
		{
			for (uint32_t k = 0; k <= i; k++)
			{
				dp[i + 1][j + 1][k] = (dp[i + 1][j + 1][k] + dp[i][j][k]) % 1000000007;
				dp[i + 1][j][k] = (dp[i + 1][j][k] + (dp[i][j][k] * i)) % 1000000007;
				dp[i + 1][j][k + 1] = (dp[i + 1][j][k + 1] + dp[i][j][k]) % 1000000007;
			}
		}
	}
	
	cout << dp[N - 1][L - 1][R - 1];
}