// 색종이 붙이기.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#define RECT_WIDTH 10
#define RECT_HEIGHT 10

typedef unsigned int UINT;
typedef unsigned int DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;

using namespace std;

BYTE place[RECT_HEIGHT][RECT_WIDTH];
UINT num_confettis[] = { 5, 5, 5, 5, 5 };
UINT len_confetti = 5;
UINT cnt = 0;
UINT minn = -1;

void getMin(UINT x = 0, UINT y = 0)
{
	
	for (UINT i = y; i < RECT_HEIGHT; i++) // y축 탐색
	for (UINT j = 0; j < RECT_WIDTH; j++) // x축 탐색
		if (place[i][j] == '1') // 왼쪽 위 꼭짓점 발견
		{
			// 정사각형의 크기를 줄여가며 탐색
			for (UINT l = len_confetti; 0 < l; l--)
			{
				if (num_confettis[l - 1] == 0
					|| RECT_HEIGHT <= i + l - 1 || RECT_WIDTH <= j + l - 1) //  붙일 색종이가 없으면
					continue; // 패스

				bool isSquare = true;
				for (UINT k = 0; k < l; k++) // 사각형 탐색 세로방향
				for (UINT m = 0; m < l; m++) // 사각형 탐색 가로방향
				{
					if (place[i + k][j + m] != '1') // 선이 끊기면
					{
						isSquare = false;
						k = l;
						m = l;
					}
				}
				if (!isSquare)
					continue;

				// 색종이 붙이기
				for (UINT k = 0; k < l; k++)
				for (UINT m = 0; m < l; m++)
					place[i + k][j + m] = '0';
				--num_confettis[l - 1];
				cnt++;

				getMin(j, i); // 가지뻗기

				// 색종이 떼기
				++num_confettis[l - 1];
				for (UINT k = 0; k < l; k++)
				for (UINT m = 0; m < l; m++)
					place[i + k][j + m] = '1';
				cnt--;
			}

			goto no_square;
		}
	
	for (UINT i = 0; i < RECT_HEIGHT; i++)
	for (UINT j = 0; j < RECT_WIDTH; j++)
		if (place[i][j] == '1')
			cnt = -1;
	
	if (cnt < minn)
		minn = cnt;

	return;

no_square:

	return;
}

int main()
{
	for (UINT i = 0; i < RECT_HEIGHT; i++)
		for (UINT j = 0; j < RECT_WIDTH; j++)
			cin >> place[i][j];

	getMin();
	cout << (int)minn;
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
