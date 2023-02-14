// 야구.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

typedef unsigned int UINT;
typedef unsigned int DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;

using namespace std;

UINT N;
UINT** innings;

/* order안의 값은 선수번호 */
UINT play(UINT** scores, UINT* order)
{
	UINT result = 0;
	UINT nextPlayer = 0;
	UINT ruta = 0, outs = 0;

	for (UINT k = 0; k < N; k++) // 이닝
	{
		for (UINT i = 0; i < 9; i++)
		{
			ruta  <<= scores[k][order[(nextPlayer + i) % 9]]; // 친 결과에 따라 진루
			if (scores[k][order[(nextPlayer + i) % 9]] == 0)
			{
				if (++outs == 3) // 삼진아웃
				{
					nextPlayer = (nextPlayer + i + 1) % 9; // 타순 유지를 위한
					break;
				}
			}
			else // 아웃이 아닐때만
				ruta += (1 << scores[k][order[(nextPlayer + i) % 9]] - 1); // 선수 추가

			// 홈으로 도착한 선수들을 result에 더함
			for (UINT j = (ruta & (~7)) >> 3; j != 0; j >>= 1)	// 7d = 111b
				result += j & 1;
			ruta &= 7;
		}
		if (outs != 3) // 이닝에서 삼진아웃을 안당하면
			k--; // 이닝을 다시 반복
		else
		{
			// 다음 이닝을 위한 초기화
			ruta = 0;
			outs = 0;
		}
	}
	return result;
}

// 선수 순서를 바꿔가며(순열을 생성하며) 완전탐색
UINT recur(UINT** scores, UINT i = 0)
{
	static UINT order[9];
	static UINT max;
	if (i == 0)
		max = 0;

	if (i == 9)
	{
		UINT result = play(scores, order);
		if (max < result)
			max = result;

		return max;
	}
	if (i != 3)
		for (UINT j = 1; j < 9; j++)
		{
			// 숫자 중복검사
			UINT k;
			for (k = 0; k < i; k++)
			{
				if (order[k] == j) // 중복이라면
					break;
			}
			if (k != i) // 위의 반복문이 break 됐다면
				continue; // 패스

			order[i] = j;
			recur(scores, i + 1);
		}
	else
	{
		order[i] = 0;
		recur(scores, i + 1);
	}

	return max;
}

int main()
{
	cin >> N;
	innings = new UINT*[N];

	for (UINT i = 0; i < N; i++)
	{
		innings[i] = new UINT[9];
		for (UINT j = 0; j < 9; j++)
			cin >> innings[i][j];
	}
	cout << recur(innings);
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
