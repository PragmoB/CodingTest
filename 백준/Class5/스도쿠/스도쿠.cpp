// 스도쿠.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>

using namespace std;
// horizontal[i][j] = (i+1)번째 가로줄에서 숫자 (j+1)가 존재하는가?
// vertical[i][j] = (i+1)번째 세로줄에서 숫자 (j+1)가 존재하는가?
// box[i][j][k] = 가로 (i+1)번째, 세로 (j+1)번째 상자에서 숫자 (k+1)가 존재하는가?
bool horizontal[9][9], vertical[9][9];
bool box[3][3][9];

// board[i][j] = (i+1)번째 가로줄의 (j+1)번째 숫자
char board[11][11];

bool dfs() {
	int idx_horizontal, idx_vertical;
	for (idx_horizontal = 0; idx_horizontal < 9; idx_horizontal++) {
		for (idx_vertical = 0; idx_vertical < 9; idx_vertical++)
			if (board[idx_horizontal][idx_vertical] == '0')
				break;
		if (board[idx_horizontal][idx_vertical] == '0')
			break;
	}

	// 스도쿠 판을 다 채웠다면
	if (idx_horizontal >= 9 && idx_vertical >= 9)
		return true; // 끝

	for (int num = 0; num < 9; num++) {
		// 숫자 (num+1)이 현재위치(idx_horizontal, idx_vertical)에서 들어가도 된다면
		if (!horizontal[idx_horizontal][num] &&
			!vertical[idx_vertical][num] &&
			!box[idx_horizontal / 3][idx_vertical / 3][num]) {

			// board에다 넣고 horizontal, vertical, box에도 반영
			board[idx_horizontal][idx_vertical] = (num + 1) + '0';
			horizontal[idx_horizontal][num] =
				vertical[idx_vertical][num] =
				box[idx_horizontal / 3][idx_vertical / 3][num] = true;

			// 다음 자리 채우기
			if (dfs()) // 판을 다 채웠다면
				return true; // 끝

			// 채워넣었던 숫자 초기화
			board[idx_horizontal][idx_vertical] = '0';
			horizontal[idx_horizontal][num] =
				vertical[idx_vertical][num] =
				box[idx_horizontal / 3][idx_vertical / 3][num] = false;
		}
	}

	// 채울 숫자가 없어서 실패
	return false;
}

int main() {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			horizontal[i][j] = false;
			vertical[i][j] = false;
			box[i / 3][i % 3][j] = false;
		}

	for (int i = 0; i < 9; i++)
		cin >> board[i];

	// board에 따라 horizontal, vertical, box값 셋팅
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int num = board[i][j] - '0';
			if (num > 0) {
				horizontal[i][num - 1] = true;
				vertical[j][num - 1] = true;
				box[i / 3][j / 3][num - 1] = true;
			}
		}
	}

	dfs();
	for (int i = 0; i < 9; i++)
		cout << board[i] << endl;
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
