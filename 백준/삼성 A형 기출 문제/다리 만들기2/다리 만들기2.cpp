// 다리 만들기2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <cstring>

uint32_t N, M;
uint32_t** place;
uint32_t island_num = 2;
uint32_t bridge_connections[30][2];
uint32_t len_bridge_connections;

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
				for (uint32_t k = 1; 0 <= (signed)(j - k); k++)
				{
					if (place[i][j - k] == target2 && 2 < k) // 목적지에 도달했고 거리가 2이상이라면
					{
						if (k - 1 < min)
							min = k - 1;

						break;
					}
					if (place[i][j - k] != 0) // 바다가 아니라면(무언가 막고 있다면)
						break;
				}
				// 오른쪽으로 탐색
				for (uint32_t k = 1; j + k < M; k++)
				{
					if (place[i][j + k] == target2 && 2 < k) // 목적지에 도달했고 거리가 2이상이라면
					{
						if (k - 1 < min)
							min = k - 1;

						break;
					}
					if (place[i][j + k] != 0) // 바다가 아니라면(무언가 막고 있다면)
						break;
				}
				// 위쪽으로 탐색
				for (uint32_t k = 1; 0 <= (signed)(i - k); k++)
				{
					if (place[i - k][j] == target2 && 2 < k) // 목적지에 도달했고 거리가 2이상이라면
					{
						if (k - 1 < min)
							min = k - 1;

						break;
					}
					if (place[i - k][j] != 0) // 바다가 아니라면(무언가 막고 있다면)
						break;
				}
				// 아래쪽으로 탐색
				for (uint32_t k = 1; i + k < N; k++)
				{
					if (place[i + k][j] == target2 && 2 < k) // 목적지에 도달했고 거리가 2이상이라면
					{
						if (k - 1 < min)
							min = k - 1;

						break;
					}
					if (place[i + k][j] != 0) // 바다가 아니라면(무언가 막고 있다면) 
						break;
				}
			}

	return min;
}

uint32_t dfs(uint32_t num, uint32_t depth = 0, uint32_t next = 0)
{
	static uint32_t order[30];
	static uint32_t min;

	if (depth == 0)
		min = -1;

	// 연결 조합이 완성됐으면
	if (depth == num)
	{
		/* 연결성 검증 */
		uint32_t island_group[10];
		memset(island_group, -1, sizeof(uint32_t) * 10);
		island_group[0] = bridge_connections[order[0]][0];
		island_group[1] = bridge_connections[order[0]][1];
		uint32_t island_group_len = 2;
		for (uint32_t i = 0; i < island_group_len; i++)
		{
			for (uint32_t j = 0; j < num; j++)
			{
				uint32_t island = NULL;

				if (bridge_connections[order[j]][0] == island_group[i])
					island = bridge_connections[order[j]][1];
				else if (bridge_connections[order[j]][1] == island_group[i])
					island = bridge_connections[order[j]][0];

				// 연결성 그룹에 추가하기 전 중복검사
				uint32_t k;
				for (k = 0; k < island_group_len && island != NULL; k++)
					if (island == island_group[k])
						break;

				if (k == island_group_len)
					island_group[island_group_len++] = island;
			}
		}

		// 현 시점에서 하나로 연결된 섬들의 목록이 island_group에 저장됨

		// island_group에 모든 섬들이 포함됬는지 검사
		for (uint32_t i = 1; i <= island_num; i++)
		{
			uint32_t j;
			for (j = 0; j < island_group_len; j++)
				if (i == island_group[j])
					break;

			if (j == island_group_len) // 포함 안됐으면
				return min; // 종료
		}

		/* debug
		cout << endl;
		for (uint32_t i = 0; i < num; i++)
		{
			cout << bridge_connections[order[i]][0] << ' ' << bridge_connections[order[i]][1] << endl;
		}
		cout << endl;
		for (uint32_t i = 0; i < island_group_len; i++)
		{
			cout << island_group[i] << ' ';
		}
		cout << endl; // */

		// 계산 시작
		uint32_t result = 0;
		for (uint32_t i = 0; i < num; i++)
			result += bridge(bridge_connections[order[i]][0], bridge_connections[order[i]][1]);

		if (result < min)
			min = result;

		return min;
	}

	for (uint32_t i = next; i < len_bridge_connections; i++)
	{
		order[depth] = i;
		dfs(num, depth + 1, i + 1);
	}
	return min;
}

// 두가지의 섬을 연결하는 모든 경우를 bridge_connections에 때려넣음
void makeCombination(uint32_t depth = 0, uint32_t next = 1)
{
	static uint32_t order[2];

	if (depth == 0)
		len_bridge_connections = 0;

	if (depth == 2)
	{
		if (bridge(order[0], order[1]) == -1)
			return;

		bridge_connections[len_bridge_connections][0] = order[0];
		bridge_connections[len_bridge_connections++][1] = order[1];
	}
	for (uint32_t i = next; i <= island_num; i++)
	{
		order[depth] = i;
		makeCombination(depth + 1, i + 1);
	}
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
			cin >> place[i][j];
	}

	// 섬마다 번호를 다르게함
	for (uint32_t i = 0; i < N; i++)
		for (uint32_t j = 0; j < M; j++)
			if (place[i][j] == 1)
				numerate(j, i, island_num++);

	island_num -= 2;

	// 섬 번호가 2부터 시작했으므로 1부터 시작하게 바꿔줌
	for (uint32_t i = 0; i < N; i++)
		for (uint32_t j = 0; j < M; j++)
			if (place[i][j] != 0)
				place[i][j]--;

	makeCombination();
	
	/* debug
	cout << endl;
	for (uint32_t i = 0; i < N; i++)
	{
		for (uint32_t j = 0; j < M; j++)
		{
			cout << place[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;

	cout << endl;
	for (uint32_t i = 0; i < len_bridge_connections; i++)
		cout << bridge_connections[i][0] << ' ' << bridge_connections[i][1] << endl;
	cout << endl; // */
	
	uint32_t min = -1;
	for (uint32_t i = 1; i <= len_bridge_connections; i++)
	{
		uint32_t result = dfs(i);
		if (result < min)
			min = result;
	}

	cout << (signed)min;
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
