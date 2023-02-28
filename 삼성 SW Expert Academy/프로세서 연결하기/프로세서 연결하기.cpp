// 프로세서 연결하기.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

uint32_t T, N;
int** maxinos;

using namespace std;

uint32_t dfs(uint32_t processor_num, uint32_t processor = 1)
{
	static uint32_t connected_processors_max, electrics_min;
	static uint32_t connected_processors, electrics;

	if (processor_num < processor) // processor가 프로세스 개수보다 커질때(종료조건)
	{
		/* debug
		cout << endl;
		for (uint32_t i = 0; i < N; i++)
		{
			for (uint32_t j = 0; j < N; j++)
			{
				if (0 <= maxinos[i][j])
					cout << '+';
				cout << maxinos[i][j] << ' ';
			}
			cout << endl;
		}
		cout << endl; // */

		// 연결된 프로세서의 수를 신기록 갱신하면
		if (connected_processors_max < connected_processors)
		{
			connected_processors_max = connected_processors;
			electrics_min = electrics; // 전선 수도 갱신
		}
		// 프로세서는 같은데 전선을 덜 낭비하면
		else if (connected_processors == connected_processors_max &&
			electrics < electrics_min)
			electrics_min = electrics; // 전선 수 갱신

		return electrics_min;
	}
	else if (processor == 1)
	{
		connected_processors_max = connected_processors = electrics = 0;
		electrics_min = -1;
	}

	// 타겟 프로세서 위치 찾기
	uint32_t processor_x, processor_y;
	for (uint32_t i = 0; i < N; i++)
	{
		for (uint32_t j = 0; j < N; j++)
		{
			if (maxinos[i][j] == processor)
			{
				processor_x = j;
				processor_y = i;
			}
		}
	}

	// 이미 가장자리에서 연결된 경우라면
	if (processor_x == 0 || processor_x == N - 1 || processor_y == 0 || processor_y == N - 1)
	{
		connected_processors++;
		dfs(processor_num, processor + 1);
		connected_processors--;
	}
	else
	{
		uint32_t i;

		/* 위쪽 탐색 */

		for (i = 1; 0 <= (signed)(processor_y - i); i++)
		{
			if (maxinos[processor_y - i][processor_x] != 0) // 뭐가 막혀있으면
				break;
		}
		if ((signed)(processor_y - i) < 0) // 다 뚫려있다면
		{
			for (i = 1; 0 <= (signed)(processor_y - i); i++)
				maxinos[processor_y - i][processor_x] = -1; // 위쪽을 -1로 덮음

			electrics += processor_y; // 전선 개수를 반영
			connected_processors++; // 프로세서 연결 개수도 반영
			dfs(processor_num, processor + 1);
			electrics -= processor_y;
			connected_processors--;
			
			for (i = 1; 0 <= (signed)(processor_y - i); i++)
				maxinos[processor_y - i][processor_x] = 0; // 위쪽 전선을 제거
		}

		/* 아래쪽 탐색 */

		for (i = 1; processor_y + i < N; i++)
		{
			if (maxinos[processor_y + i][processor_x] != 0) // 뭐가 막혀있으면
				break;
		}
		if (N <= processor_y + i) // 다 뚫려있다면
		{
			for (i = 1; processor_y + i < N; i++)
				maxinos[processor_y + i][processor_x] = -1; // 아래쪽을 -1로 덮음

			electrics += N - processor_y - 1; // 전선 개수를 반영
			connected_processors++; // 프로세서 연결 개수도 반영
			dfs(processor_num, processor + 1);
			electrics -= N - processor_y - 1;
			connected_processors--;

			for (i = 1; processor_y + i < N; i++)
				maxinos[processor_y + i][processor_x] = 0; // 아래쪽 전선을 제거
		}

		/* 오른쪽 탐색 */

		for (i = 1; processor_x + i < N; i++)
		{
			if (maxinos[processor_y][processor_x + i] != 0)
				break;
		}
		if (N <= processor_x + i)
		{
			for (i = 1; processor_x + i < N; i++)
				maxinos[processor_y][processor_x + i] = -1; // 오른쪽을 -1로 덮음

			electrics += N - processor_x - 1; // 전선 개수를 반영
			connected_processors++; // 프로세서 연결 개수도 반영
			dfs(processor_num, processor + 1);
			electrics -= N - processor_x - 1;
			connected_processors--;

			for (i = 1; processor_x + i < N; i++)
				maxinos[processor_y][processor_x + i] = 0; // 오른쪽 전선을 제거
		}

		/* 왼쪽 탐색 */

		for (i = 1; 0 <= (signed)(processor_x - i); i++)
		{
			if (maxinos[processor_y][processor_x - i] != 0) // 뭐가 막혀있으면
				break;
		}
		if ((signed)(processor_x - i) < 0) // 다 뚫려있다면
		{
			for (i = 1; 0 <= (signed)(processor_x - i); i++)
				maxinos[processor_y][processor_x - i] = -1; // 왼쪽을 -1로 덮음

			electrics += processor_x; // 전선 개수를 반영
			connected_processors++; // 프로세서 연결 개수도 반영
			dfs(processor_num, processor + 1);
			electrics -= processor_x;
			connected_processors--;

			for (i = 1; 0 <= (signed)(processor_x - i); i++)
				maxinos[processor_y][processor_x - i] = 0; // 왼쪽 전선을 제거
		}

		/* 연결 하지 않는 경우 */
		dfs(processor_num, processor + 1);
	}
	return electrics_min;
}

int main()
{
	cin >> T;
	
	for (uint32_t i = 0; i < T; i++) // 테스트 케이스 반복
	{
		cin >> N;
		maxinos = new int*[N + 1];
		for (uint32_t j = 0; j < N; j++)
		{
			maxinos[j] = new int[N + 1];
			for (uint32_t k = 0; k < N; k++)
				cin >> maxinos[j][k];
		}

		// 프로세서에 번호 붙이기
		uint32_t processor_num = 1;
		for (uint32_t j = 0; j < N; j++)
			for (uint32_t k = 0; k < N; k++)
			{
				if (maxinos[j][k] == 1)
					maxinos[j][k] = processor_num++;
			}
		processor_num--;

		cout << '#' << i + 1 << ' ' << dfs(processor_num) << endl;

		for (uint32_t j = 0; j < N; j++)
			delete[] maxinos[j];
		delete[] maxinos;
	}
	return 0;
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
