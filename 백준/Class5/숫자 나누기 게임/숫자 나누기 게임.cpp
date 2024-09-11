// 숫자 나누기 게임.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>

#define MAX_X 1000000
#define MAX_N 100000

using namespace std;

int main() {
	int N;
	cin >> N;

	int x[MAX_N];
	// player_idx[i] = i번 카드를 가진 플레이어의 번호
	// 플레이어가 존재하지 않음 = -1
	int player_idx[MAX_X + 1];
	for (int i = 0; i < MAX_X + 1; i++)
		player_idx[i] = -1;

	for (int i = 0; i < N; i++) {
		cin >> x[i];
		player_idx[x[i]] = i;
	}

	int answer[MAX_N];
	for (int i = 0; i < MAX_N; i++)
		answer[i] = 0;

	// i = 플레이어 순번
	for (int i = 0; i < N; i++) {
		// j = i번 플레이어가 가진 카드 숫자의 배수
		for (int j = x[i] * 2; j <= MAX_X; j += x[i]) {
			// x[i]로 나눴을 때 j가 나누어 떨어지므로
			// j가 존재한다는건 j를 가진 플레이어가 패배했다는 것
			if (player_idx[j] != -1) {
				answer[i] += 1;
				answer[player_idx[j]] -= 1;
			}
		}
	}

	for (int i = 0; i < N; i++)
		cout << answer[i] << ' ';
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
