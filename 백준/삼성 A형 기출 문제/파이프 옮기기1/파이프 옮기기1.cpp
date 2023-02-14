// 파이프 옮기기1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

typedef unsigned int UINT;
typedef unsigned int DWORD;
typedef unsigned short WORD;

#define HIWORD(l) ((WORD)((((DWORD)(l)) >> 16) & 0xffff))
#define LOWORD(l) ((WORD)(((DWORD)(l)) & 0xffff))

using namespace std;

enum DIRT {
	Hor = 0,
	Ver = 1,
	Dia = 2
};

int recur(UINT** place, DWORD loc = 0x00000001, UINT dirt = Hor)
{
	WORD horizon = place[HIWORD(loc)][LOWORD(loc) + 1];
	WORD vertical = place[HIWORD(loc) + 1][LOWORD(loc)];
	WORD diagonal = place[HIWORD(loc) + 1][LOWORD(loc) + 1];

	UINT result = 0;

	// 가로 방향 이동
	if (horizon == 0 && (dirt == Hor || dirt == Dia))
		result += recur(place, loc + 1, 0);

	// 세로 방향 이동
	if (vertical == 0 && (dirt == Ver || dirt == Dia))
		result += recur(place, loc + (1 << 16), 1);

	// 대각선 방향 이동
	if (horizon == 0 && vertical == 0 && diagonal == 0)
		result += recur(place, loc + (1 << 16) + 1, 2);

	// 목적지 도착
	if (diagonal == 2)
		return 1;

	return result;
}

int main()
{
	UINT N;
	cin >> N;

	UINT** place = new UINT*[N + 1];
	for (UINT i = 0; i < N; i++)
	{
		place[i] = new UINT[N + 1];
		for (UINT j = 0; j < N; j++)
			cin >> place[i][j];
		place[i][N] = 1; // 가로줄 맨끝을 1로 막아놓음
	}
	// 마지막줄은 1로 막아놓고 맨 끝에 2를 넣음
		place[N] = new UINT[N + 1];
		for (UINT i = 0; i < N; i++)
			place[N][i] = 1;
		place[N][N] = 2;

	cout << recur(place);
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
