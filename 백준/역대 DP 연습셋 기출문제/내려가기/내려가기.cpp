// 내려가기.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string.h>

using namespace std;

uint32_t max_t(uint32_t* arr, size_t len)
{
	uint32_t result = 0;
	for (uint32_t i = 0; i < len; i++)
	{
		if (result < arr[i])
			result = arr[i];
	}
	return result;
}
uint32_t min_t(uint32_t* arr, size_t len)
{
	uint32_t result = -1;
	for (uint32_t i = 0; i < len; i++)
	{
		if (arr[i] < result)
			result = arr[i];
	}
	return result;
}

int main()
{
	uint32_t input[100000][3];
	uint32_t N;
	
	cin >> N;

	for (uint32_t i = 0; i < N; i++)
		for (uint32_t j = 0; j < 3; j++)
			cin >> input[i][j];

	uint32_t dp[3], dp_prev[3];
	
	// solving task : max
	for (uint32_t i = 0; i < 3; i++)
		dp_prev[i] = 0;
	for (uint32_t i = N - 1; 0 <= (signed)i; i--)
	{
		dp[0] = input[i][0] + max_t(dp_prev, 2);
		dp[1] = input[i][1] + max_t(dp_prev, 3);
		dp[2] = input[i][2] + max_t(dp_prev + 1, 2);

		memcpy(dp_prev, dp, 3 * sizeof(uint32_t));
	}
	cout << max_t(dp, 3);

	cout << ' ';

	// solving task : min
	for (uint32_t i = 0; i < 3; i++)
		dp_prev[i] = 0;
	for (uint32_t i = N - 1; 0 <= (signed)i; i--)
	{
		dp[0] = input[i][0] + min_t(dp_prev, 2);
		dp[1] = input[i][1] + min_t(dp_prev, 3);
		dp[2] = input[i][2] + min_t(dp_prev + 1, 2);

		memcpy(dp_prev, dp, 3 * sizeof(uint32_t));
	}
	cout << min_t(dp, 3);
}