// 게리멘더링.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

uint32_t N;
uint32_t populations[10];
uint32_t relates[10][10];

using namespace std;

/* wards안에 있는 ward1과 ward2가 이어져 있는지 여부 탐색 */
bool isRelatable(uint32_t* wards, uint32_t wards_len, uint32_t ward1, uint32_t ward2)
{
	// 1차적으로 인접하는지 비교
	for (uint32_t i = 0; relates[ward1 - 1][i] != -1; i++)
	{
		if (relates[ward1 - 1][i] == ward2)
			return true;
	}

	// 길을 따라가기 앞서, ward1은 이미 방문했던 곳이므로 wards에서 제외한다
	for (uint32_t i = 0; i < wards_len; i++)
	{
		if (wards[i] == ward1)
		{
			wards[i] = 0; // 제외
			break;
		}
	}

	// 주변의 길을 따라가보며 비교
	for (uint32_t i = 0; i < wards_len; i++)
	{
		// ward1에서 wards[i]로 길이 나있는지 탐색
		for (uint32_t j = 0; relates[ward1 - 1][j] != -1; j++)
		{
			// 그렇다면
			if (relates[ward1 - 1][j] == wards[i])
			{
				// 길을 따라가봄
				if (isRelatable(wards, wards_len, wards[i], ward2))
					return true;

				break;
			}
		}
	}
	// 막다른 길이면 이어져 있지 않음!
	return false;
}

bool areRelatable(uint32_t* ward, uint32_t len)
{
	uint32_t cward[10];
	for (uint32_t i = 0; i < len; i++)
		cward[i] = ward[i];


	// 버블정렬 식 비교
	for (uint32_t i = 0; i < len - 1; i++)
	{
		for (uint32_t j = i + 1; j < len; j++)
		{
			// 두 지역구 cward[i], cward[j]에 대하여

			// 두 지역구가 이어져있는지 검사
			if (!isRelatable(cward, len, cward[i], cward[j]))
				return false;

			for (uint32_t k = 0; k < len; k++)
				cward[k] = ward[k];
		}
	}
	return true;
}

/* num크기 선거구의 조합을 생성하며 bruteforce */
uint32_t dfs(uint32_t num, uint32_t depth = 0, uint32_t next = 1)
{
	static uint32_t min;
	static uint32_t ward1[10];
	if (depth == 0)
		min = -1;

	// 조합이 완성됐다면
	if (depth == num)
	{
		if (!areRelatable(ward1, num))
			return min;

		// ward1에 없는 구역번호 ward2에 집어넣는다
		uint32_t ward2[10];
		uint32_t ward2_len = 0;
		for (uint32_t i = 1; i <= N; i++)
		{
			bool found = false;
			for (uint32_t j = 0; j < num; j++)
			{
				if (ward1[j] == i)
				{
					found = true;
					break;
				}
			}
			if (!found)
				ward2[ward2_len++] = i;
		}

		if (!areRelatable(ward2, ward2_len))
			return min;

		// 인구 수 차이 계산
		int result = 0;
		for (uint32_t i = 0; i < num; i++)
			result += populations[ward1[i] - 1];
		for (uint32_t i = 0; i < ward2_len; i++)
			result -= populations[ward2[i] - 1];

		// 절댓값
		if (result < 0)
			result *= -1;

		if (result < min)
			min = result;

		return min;
	}
	for (uint32_t i = next; i <= N; i++)
	{
		ward1[depth] = i;
		dfs(num, depth + 1, i + 1);
	}
	return min;
}

int main()
{
	cin >> N;

	for (uint32_t i = 0; i < N; i++)
		cin >> populations[i];

	for (uint32_t i = 0; i < N; i++)
	{
		uint32_t num;
		cin >> num;
		for (uint32_t j = 0; j < num; j++)
		{
			cin >> relates[i][j];
		}

		relates[i][num] = -1;
	}

	// 선거구의 크기를 바꿔가며 탐색
	uint32_t min = -1;
	for (uint32_t i = 1; i <= N / 2; i++)
	{
		uint32_t result = dfs(i);
		if (result < min)
			min = result;
	}
	cout << (int)min;
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
