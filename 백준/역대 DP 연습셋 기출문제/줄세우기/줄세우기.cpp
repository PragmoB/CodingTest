﻿// 줄세우기.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

int main()
{
	uint32_t N;
	uint32_t input[200], dp[200]; // dp[A] = B A번째 값을 마지막으로 하는 가장 긴 부분수열의 길이는 B이다
	
	cin >> N;
	
	for (uint32_t i = 0; i < N; i++)
		cin >> input[i];

	dp[0] = 1;

	uint32_t max = 0;
	for (uint32_t i = 1; i < N; i++)
	{
		dp[i] = 1;
		for (uint32_t j = 0; j < i; j++)
		{
			if (input[j] < input[i] && dp[i] < dp[j] + 1)
				dp[i] = dp[j] + 1;
		}
		if (max < dp[i])
			max = dp[i];
	}

	cout << N - max << endl;
}