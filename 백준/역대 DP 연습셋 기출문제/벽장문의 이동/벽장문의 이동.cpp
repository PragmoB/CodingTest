// 벽장문의 이동.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <math.h>

using namespace std;

uint32_t dfs(const uint32_t N, const uint32_t open1, const uint32_t open2, const uint32_t len_target, const uint32_t* target)
{
	if (!len_target)
		return 0;

	int open_int1 = target[0] - open1, open_int2 = target[0] - open2;
	uint32_t min;

	if (open_int1 * open_int2 < 0) // 타겟이 open들 사이에 있음(가지가 2개로 뻗음)
	{
		min = abs(open_int1) + dfs(N, target[0], open2, len_target - 1, target + 1);
		uint32_t temp = abs(open_int2) + dfs(N, open1, target[0], len_target - 1, target + 1);
		if (temp < min)
			min = temp;
	}
	else // 아니라면 가장 가까운 open만 움직임, 가지가 1개로 뻗음
	{
		if (abs(open_int1) < abs(open_int2))
			min = abs(open_int1) + dfs(N, target[0], open2, len_target - 1, target + 1);
		else
			min = abs(open_int2) + dfs(N, open1, target[0], len_target - 1, target + 1);
	}

	return min;
}

int main()
{
	/*
	FILE* old;
	freopen_s(&old, "input.txt", "r", stdin);
	*/
	uint32_t N, open1, open2, len_target, target[20];

	cin >> N >> open1 >> open2 >> len_target;
	for (uint32_t i = 0; i < len_target; i++)
		cin >> target[i];

	cout << dfs(N, open1, open2, len_target, target);
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
