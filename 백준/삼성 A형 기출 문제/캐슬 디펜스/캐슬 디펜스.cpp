// 캐슬 디펜스.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <cstring>
#include <cmath>

typedef unsigned int UINT;
typedef unsigned int DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;

#define NUM_ARCHERS 3

using namespace std;

typedef struct tagEnemy
{
	UINT distance = 99999999;
	UINT x = 0, y = 0;
	bool isExist = false;
} Enemy;

UINT play(BYTE** place, BYTE* archerPos, UINT D)
{
	Enemy target[NUM_ARCHERS];
	UINT result = 0;

	UINT width = strlen((const char*)place[0]);
	UINT height;
	for (height = 0; place[height] != 0; height++);

	// place 훼손 방지를 위한 복사
	BYTE** placeC = new BYTE*[height + 1];
	for (UINT i = 0; i < height; i++)
	{
		placeC[i] = new BYTE[width];
		for (UINT j = 0; j < width; j++)
			placeC[i][j] = place[i][j];
	}
	placeC[height] = NULL;

	while (placeC[0] != NULL) // 턴 반복
	{
		for (UINT i = 0; placeC[i] != NULL && i < D; i++) // y축 탐색
		{
			for (UINT j = 0; j < width; j++) // x축 탐색
			{
				if (placeC[i][j] == '1') // 적 발견
				{
					for (UINT k = 0; k < NUM_ARCHERS; k++) // 각 궁수에 대해서
					{
						UINT distance = abs((int)(archerPos[k] - j)) + i + 1; // 적 까지의 거리계산

						// 공격 범위 안에 있고, 기존 타겟보다 거리가 가깝다면
						if (distance <= D && (target[k].distance > distance || !target[k].isExist))
						{
							// 타겟 변경
							target[k].distance = distance;
							target[k].x = j;
							target[k].y = i;
							target[k].isExist = true;
						}
						// 거리가 같은 타겟이 중복되면 왼쪽을 선택함
						else if (target[k].distance == distance && target[k].x > j && target[k].isExist)
						{
							// 타겟 변경
							target[k].distance = distance;
							target[k].x = j;
							target[k].y = i;
						}
					}
				}
			}
		}

		// 이 시점에서 궁수들이 처리할 target이 확정됨

		// target 죽이기
		for (UINT k = 0; k < NUM_ARCHERS; k++)
		{
			if (target[k].isExist && placeC[target[k].y][target[k].x] == '1')
			{
				result++; // 죽인 횟수 카운트
				placeC[target[k].y][target[k].x] = '0';
			}
			target[k].isExist = false;
		}
		placeC++; // 적들이 한 줄 앞으로 전진
	}

	return result;
}

UINT getMaxEnemies(BYTE** place, UINT D, UINT depth = 0, UINT next = 0)
{
	static BYTE archerPos[NUM_ARCHERS] = { 0, };

	if (depth == NUM_ARCHERS)
		return play(place, archerPos, D);

	UINT max = 0;
	UINT width;
	for (width = 0; place[0][width] != NULL; width++); // 주어진 맵의 가로 공간 구하기

	/* 조합(combination)을 만들며 완전탐색  */

	for (UINT i = next; i < width; i++)
	{
		archerPos[depth] = i;

		UINT result = getMaxEnemies(place, D, depth + 1, i + 1);
		if (max < result)
			max = result;
	}

	return max;
}

int main()
{
	UINT N, M, D;
	BYTE** place = (BYTE**)0x400;

	cin >> N >> M >> D;

	place = new BYTE*[N + 1];
	for (UINT i = 0; i < N; i++)
		place[i] = new BYTE[M + 1];

	// 격자판 입력은 상하 반전으로 받음
	for (UINT i = N; 0 < i; i--)
	{
		for (UINT j = 0; j < M; j++)
			cin >> place[i - 1][j];
		place[i - 1][M] = NULL;
	}
	place[N] = NULL;

	cout << getMaxEnemies(place, D);
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
