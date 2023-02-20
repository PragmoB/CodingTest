// 배열 돌리기4.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <cstring>

uint32_t N, M, K;
uint32_t *r, *c, *s;
uint32_t** arr;

using namespace std;

uint32_t calculate(const uint32_t* order)
{
	uint32_t** carr = new uint32_t*[N + 1];
	for (uint32_t i = 0; i < N; i++)
	{
		carr[i] = new uint32_t[M + 1];
		for (uint32_t j = 0; j < M; j++)
			carr[i][j] = arr[i][j];
	}

	/* 회전연산자에 대해 반복 */
	for (uint32_t i = 0; i < K; i++)
	{
		uint32_t turn_idx = order[i];

		/* 회전연산자 수행 */
		for (uint32_t j = 1; j <= s[turn_idx]; j++)
		{
			/* 단일 회전 연산 수행 */

			// 밑변 스왑
			uint32_t y = r[turn_idx] + j;
			uint32_t dup = carr[y][c[turn_idx] - j]; // 스왑시 손실 데이터 보존
			for (uint32_t k = c[turn_idx] - j; k < c[turn_idx] + j; k++)
				carr[y][k] = carr[y][k + 1];

			// 오른쪽변 스왑
			uint32_t x = c[turn_idx] + j;
			for (uint32_t k = r[turn_idx] + j; r[turn_idx] - j < k; k--)
				carr[k][x] = carr[k - 1][x];

			// 윗변 스왑
			y = r[turn_idx] - j;
			for (uint32_t k = c[turn_idx] + j; c[turn_idx] - j < k; k--)
				carr[y][k] = carr[y][k - 1];

			// 왼쪽변 스왑
			x = c[turn_idx] - j;
			for (uint32_t k = r[turn_idx] - j; k < r[turn_idx] + j - 1; k++)
				carr[k][x] = carr[k + 1][x];

			// 마지막 남은 데이터 끼우기
			carr[r[turn_idx] + j - 1][c[turn_idx] - j] = dup;
		}
	}

	// 결과값 계산
	uint32_t min = -1;
	for (uint32_t i = 0; i < N; i++)
	{
		uint32_t sum = 0;
		for (uint32_t j = 0; j < M; j++)
			sum += carr[i][j];

		if (sum < min)
			min = sum;
	}

	for (uint32_t i = 0; i < N; i++)
		delete[] carr[i];
	delete[] carr;
	return min;
}

uint32_t dfs(uint32_t depth = 0)
{
	static uint32_t order[6];
	static uint32_t min;

	if (depth == 0) // 첫 초기화
	{
		memset(order, 0, sizeof(uint32_t) * 6);
		min = -1;
	}
	else if (depth == K) // 순열이 다 만들어졌다면
	{
		// 순열대로 연산
		uint32_t result = calculate(order);
		if (result < min)
			min = result;

		return min;
	}

	// 0부터 K-1까지의 수를 order에 배열함(순열 생성)
	for (uint32_t i = 0; i < K; i++)
	{
		// 중복검사
		bool isDup = false;
		for (uint32_t j = 0; j < depth; j++)
		{
			if (order[j] == i) // 중복이면
			{
				isDup = true;
				break;
			}
		}
		if (isDup)
			continue;

		order[depth] = i;
		dfs(depth + 1);
	}
	return min;
}

int main()
{
	cin >> N >> M >> K;
	arr = new uint32_t*[N + 1];
	for (uint32_t i = 0; i < N; i++)
	{
		arr[i] = new uint32_t[M + 1];
		for (uint32_t j = 0; j < M; j++)
			cin >> arr[i][j];
	}

	r = new uint32_t[K + 1];
	c = new uint32_t[K + 1];
	s = new uint32_t[K + 1];

	for (uint32_t i = 0; i < K; i++)
	{
		cin >> r[i] >> c[i] >> s[i];
		r[i]--;
		c[i]--;
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
