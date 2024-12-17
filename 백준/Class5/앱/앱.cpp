#include <iostream>

#define MAX_N 100
#define MAX_M 10000000
#define MAX_C 100

using namespace std;

unsigned int N, M;
unsigned int m[MAX_N], c[MAX_N];
// dp[i][j] = 앱 종료 여부 결정이 i번, 쓸 수 있는 비용이 j일때 모을 수 있는 메모리 크기의 최대값
unsigned int dp[MAX_N + 1][MAX_N * MAX_C + 1];

int main()
{
	for (int i = 0; i <= MAX_N; i++)
		for (int j = 0; j < MAX_N * MAX_C + 1; j++)
			dp[i][j] = 0;

	cin >> N >> M;

	for (int i = 0; i < N; i++)
		cin >> m[i];
	int sum_c = 0;
	for (int i = 0; i < N; i++)
	{
		cin >> c[i];
		sum_c += c[i];
	}

	unsigned int res = -1;
	for (int i = 1; i <= N; i++)
		for (int j = 0; j <= sum_c; j++)
		{
			m[i - 1];
			c[i - 1];
			if (j < c[i - 1]) // 선택한 앱이 너무 비싸다면
				dp[i][j] = dp[i - 1][j]; // 선택 x
			else // 구매 가능하다면
				dp[i][j] = max(dp[i - 1][j - c[i - 1]] + m[i - 1], dp[i - 1][j]); // 선택 하는 것과 안하는 경우 중에서 메모리 값이 큰 경우를 선택

			if (dp[i][j] >= M && j < res)
				res = j;
		}

	cout << res;
}