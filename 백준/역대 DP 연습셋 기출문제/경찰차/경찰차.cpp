// 경찰차.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <algorithm>

using namespace std;

typedef struct tagPOINT {
	uint32_t x;
	uint32_t y;
} POINT, *LPPOINT;

uint32_t N, W;
POINT _event[1002];
uint32_t dp[1002][1002];

uint32_t getMinDistance(uint32_t police[2], uint32_t idx = 2)
{
	if (police[0] > police[1])
		swap(police[0], police[1]);

	if (idx == 2)
	{
		for (uint32_t i = 0; i < 1002; i++)
			for (uint32_t j = 0; j < 1002; j++)
				dp[i][j] = -1;
	}
	if (idx == W + 2)
	{
		dp[police[0]][police[1]] = 0;
		return 0;
	}


	for (uint32_t i = 0; i < 2; i++)
	{
		uint32_t police_after[2] = { police[0], police[1] };
		police_after[i] = idx;
		
		// 경찰차가 배치되는 경우를 나누어 탐색함, 이미 계산된 값이면 탐색을 스킵함
		uint32_t temp;
		if (dp[police[(1 + i) % 2]][idx] == -1)
			temp = getMinDistance(police_after, idx + 1);
		else
			temp = dp[police[(1 + i) % 2]][idx];

		// 현재 회차에서 경찰차의 이동거리 계산
		temp += abs((signed)(_event[police[i]].x - _event[idx].x)) + abs((signed)(_event[police[i]].y - _event[idx].y));
		
		if (temp < dp[police[0]][police[1]])
			dp[police[0]][police[1]] = temp;
	}

	return dp[police[0]][police[1]];
}
void printPath(uint32_t police[2])
{
	uint32_t police_temp[2] = { police[0], police[1] };

	for (uint32_t idx = 2; idx < W + 2; idx++)
	{
		// 이동거리 반영 후 police_after에 이동한 경찰차 좌표 업데이트
		uint32_t dis_police[2];
		dis_police[0] = 
			abs((signed)(_event[police_temp[0]].x - _event[idx].x)) + abs((signed)(_event[police_temp[0]].y - _event[idx].y));
		dis_police[1] =
			abs((signed)(_event[police_temp[1]].x - _event[idx].x)) + abs((signed)(_event[police_temp[1]].y - _event[idx].y));

		if (dis_police[0] + dp[police_temp[1]][idx] < dis_police[1] + dp[police_temp[0]][idx])
		{
			cout << 1 << endl;
			police_temp[0] = idx;
		}
		else
		{
			cout << 2 << endl;
			police_temp[1] = idx;
		}

	}
}
int main()
{
	cin >> N >> W;
	_event[0].x = _event[0].y = 1;
	_event[1].x = _event[1].y = N;
	for (uint32_t i = 2; i < W + 2; i++)
		cin >> _event[i].y >> _event[i].x;

	uint32_t police[2] = { 0, 1 };
	uint32_t result = getMinDistance(police);
	cout << result << endl;
	printPath(police);
}