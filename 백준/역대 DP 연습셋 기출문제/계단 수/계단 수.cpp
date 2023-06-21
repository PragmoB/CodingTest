// 계단 수.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//


/*
 * 풀이방법 : dfs 탐색 구현 후 dp로 중복연산 줄임
 */
#include <iostream>

#define MOD 1000000000

using namespace std;

// bitmask : 방문한 숫자 체크
uint32_t dfs(uint32_t times, uint32_t bitmask = 0, int last_num = -1)
{
	static int dp[101][1 << 10][10];

	if (last_num == -1) // 초기 실행
	{
		for (uint32_t i = 0; i < (1 << 10); i++)
			for (uint32_t j = 0; j < 101; j++)
				for (uint32_t k = 0; k < 10; k++)
					dp[j][i][k] = -1;

		dp[times][0][0] = 0;
		for (uint32_t i = 9; 0 < i; i--)
		{
			dfs(times - 1, (1 << i), i);
			dp[times][0][0] += dp[times - 1][1 << i][i] % MOD;
			dp[times][0][0] %= MOD;
		}

		return dp[times][0][0];
	}
	if (times == 0) // 재귀 종료 조건
	{
		if ((1 << 10) - 1 <= bitmask)
			dp[0][bitmask][last_num] = 1;
		else
			dp[0][bitmask][last_num] = 0;

		return dp[0][bitmask][last_num];
	}

	dp[times][bitmask][last_num] = 0;

	// 가지 치기
	if (last_num < 9)
	{
		if (dp[times - 1][bitmask | (1 << (last_num + 1))][last_num + 1] == -1)
			dfs(times - 1, bitmask | (1 << (last_num + 1)), last_num + 1);

		dp[times][bitmask][last_num] += dp[times - 1][bitmask | (1 << (last_num + 1))][last_num + 1];
		dp[times][bitmask][last_num] %= MOD;
	}
	if (0 < last_num)
	{
		if (dp[times - 1][bitmask | (1 << (last_num - 1))][last_num - 1] == -1)
			dfs(times - 1, bitmask | (1 << (last_num - 1)), last_num - 1);

		dp[times][bitmask][last_num] += dp[times - 1][bitmask | (1 << (last_num - 1))][last_num - 1];
		dp[times][bitmask][last_num] %= MOD;
	}

	return dp[times][bitmask][last_num];
}

int main()
{
	uint32_t N;
	cin >> N;
	cout << dfs(N);
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
