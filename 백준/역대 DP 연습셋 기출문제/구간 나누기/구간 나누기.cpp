// 구간 나누기.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

uint32_t N, M, nums[100];

/*
// 그래프로 시도했다가 망함
int dfs(uint32_t section_count, uint32_t idx = -1, int section_sum = 0)
{
	static int max;

	if (idx == -1) // 첫 호출시 초기화
		max = 0x80000000;
	else
		section_sum += nums[idx];

	if (N - idx <= section_count) // 종료조건
		return max;

	if (section_count == 0)
	{
		if (max < section_sum)
			max = section_sum;
	}

	// 안묶음
	if (idx == -1)
		dfs(section_count - 1, idx + 1, section_sum);
	else
		dfs(section_count, idx + 1, section_sum);
		
	for (uint32_t i = 2; idx + i < N; i++)
		dfs(section_count - 1, idx + i, section_sum); // 묶음

	return max;
}
*/

int main()
{
	cin >> N >> M;

	for (uint32_t i = 0; i < N; i++)
		cin >> nums[i];

	int dp[100][100];
	for (uint32_t i = 0; i < 100; i++)
		for (uint32_t j = 0; j < 100; j++)
			dp[i][j] = 0x80000000;

	// M = 1일때는 점화식을 쓰기 애매해서 따로 빼서 처리함
	
	dp[0][0] = nums[0];
	for (uint32_t i = 1; i < N; i++)
	{
		dp[i][0] = dp[i - 1][0];
		
		int sum = 0;
		for (uint32_t l = 0; l <= i; l++)
			sum += nums[l];

		for (uint32_t k = 0; k <= i; k++)
		{
			if (dp[i][0] < sum)
				dp[i][0] = sum;

			sum -= nums[k];
		}
	}

	// M = 2부터 dp계산
	for (uint32_t i = 1; i < M; i++)
		for (uint32_t j = i * 2; j < N; j++)
		{
			dp[j][i] = dp[j - 1][i];

			int sum = 0;
			for (uint32_t l = i * 2; l <= j; l++)
				sum += nums[l];

			for (uint32_t k = i * 2; k <= j; k++)
			{
				if (dp[j][i] < dp[k - 2][i - 1] + sum)
					dp[j][i] = dp[k - 2][i - 1] + sum;

				sum -= nums[k];
			}
		}

	cout << dp[N - 1][M - 1];
}