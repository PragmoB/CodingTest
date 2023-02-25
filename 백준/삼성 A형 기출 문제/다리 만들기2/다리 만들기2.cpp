// 다리 만들기2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

uint32_t N, M;
uint32_t** place;

using namespace std;

// target1과 target2를 연결하는 다리의 최소길이를 구함, target은 섬 번호
uint32_t bridge(uint32_t target1, uint32_t target2)
{
	uint32_t min = -1;
	for (uint32_t i = 0; i < N; i++)
		for (uint32_t j = 0; j < M; j++)
			// 출발지를 발견했으면
			if (place[i][j] == target1)
			{
				// 왼쪽으로 탐색
				for (uint32_t k = 1; 0 <= (signed)j - k; k++)
				{
					if (place[i][j - k] == target1) // 출발지가 막고 있으면 
						break;
					else if (place[i][j - k] == target2 && 2 < k) // 목적지에 도달했고 거리가 2이상이라면
					{
						if (k - 1 < min)
							min = k - 1;

						break;
					}
				}
				// 오른쪽으로 탐색
				for (uint32_t k = 1; j + k < M; k++)
				{
					if (place[i][j + k] == target1) // 출발지가 막고 있으면 
						break;
					else if (place[i][j + k] == target2 && 2 < k) // 목적지에 도달했고 거리가 2이상이라면
					{
						if (k - 1 < min)
							min = k - 1;

						break;
					}
				}
				// 아래쪽으로 탐색
				for (uint32_t k = 1; 0 <= (signed)i - k; k++)
				{
					if (place[i - k][j] == target1) // 출발지가 막고 있으면 
						break;
					else if (place[i - k][j] == target2 && 2 < k) // 목적지에 도달했고 거리가 2이상이라면
					{
						if (k - 1 < min)
							min = k - 1;

						break;
					}
				}
				// 아래쪽으로 탐색
				for (uint32_t k = 1; i + k < N; k++)
				{
					if (place[i + k][j] == target1) // 출발지가 막고 있으면 
						break;
					else if (place[i + k][j] == target2 && 2 < k) // 목적지에 도달했고 거리가 2이상이라면
					{
						if (k - 1 < min)
							min = k - 1;

						break;
					}
				}
			}

	return min;
}

// (x, y)위치의 섬 전체를 상하좌우로 탐색하며 num으로 덮음
void numerate(uint32_t x, uint32_t y, uint32_t num)
{
	place[y][x] = num;
	
	if (0 < x)
		if (place[y][x - 1] == 1)
			numerate(x - 1, y, num);

	if (0 < y)
		if (place[y - 1][x] == 1)
			numerate(x, y - 1, num);
	
	if (x + 1 < M)
		if (place[y][x + 1] == 1)
			numerate(x + 1, y, num);
	
	if (y + 1 < N)
		if (place[y + 1][x] == 1)
			numerate(x, y + 1, num);
}

int main()
{
	cin >> N >> M;
	place = new uint32_t*[N + 1];

	for (uint32_t i = 0; i < N; i++)
	{
		place[i] = new uint32_t[M + 1];
		for (uint32_t j = 0; j < M; j++)
		{
			cin >> place[i][j];
		}
	}

	// 섬마다 번호를 다르게함
	uint32_t island_num = 2;
	for (uint32_t i = 0; i < N; i++)
	{
		for (uint32_t j = 0; j < M; j++)
		{
			if (place[i][j] == 1)
			{
				numerate(j, i, island_num++);
			}
		}
	}

	// 섬 번호가 2부터 시작했으므로 1부터 시작하게 바꿔줌
	for (uint32_t i = 0; i < N; i++)
	{
		for (uint32_t j = 0; j < M; j++)
		{
			if (place[i][j] != 0)
			{
				place[i][j]--;
			}
		}
	}

	for (uint32_t i = 0; i < N; i++)
	{
		for (uint32_t j = 0; j < M; j++)
		{
			cout << place[i][j] << ' ';
		}
		cout << endl;
	}
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
