// RGB거리2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>

#define MAX_N 1000

using namespace std;

int N;
int cost[MAX_N][3];

typedef enum Color {
	RED = 0, GREEN, BLUE
} Color;

const Color colors[] = { RED, GREEN, BLUE };

// dp[i][color1][color2] = i번째 집을 color1로 도색 시작하여 마지막 집을 color2로 도색했을때 i번째 집부터 비용의 최소값
unsigned int dp[MAX_N][3][3];

// 또래프 탐색 지겹노..
int dfs(int depth, Color prev_color, Color last_color) {

	if (depth == N - 1) {
		// 마지막 집과 그 전 집이 똑같은 색으로 도색되어 있다면
		if (prev_color == last_color)
			return -1; // 오류 발생

		// 마지막 집은 last_color로 도색하는 것으로 정해져 있음
		return dp[N - 1][last_color][last_color];
	}

	unsigned int min_val = -1;
	for (auto color : colors) // 색칠할 색깔을 바꿔가며
		if (color != prev_color) {
			if (dp[depth][color][last_color] == -1) { // dp가 계산이 안되어있다면
				// 계산 진행
				int ret = dfs(depth + 1, color, last_color);
				if (ret != -1)
					dp[depth][color][last_color] = ret + cost[depth][color];
			}
			// 최소 비용 도출
			if (dp[depth][color][last_color] < min_val)
				min_val = dp[depth][color][last_color];
		}

	// 최소 비용 값 상신
	return min_val;
}

unsigned int start() {
	for (auto color : colors)
		dp[N - 1][color][color] = cost[N - 1][color];

	unsigned int min_val = -1;
	for (auto color : colors)
		for (auto last_color : colors)
			if (color != last_color) {
				int ret = dfs(1, color, last_color);
				dp[0][color][last_color] = ret + cost[0][color];

				if (dp[0][color][last_color] < min_val)
					min_val = dp[0][color][last_color];
			}
	return min_val;
}

int main() {

	for (int i = 0; i < MAX_N; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				dp[i][j][k] = -1;
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> cost[i][RED] >> cost[i][GREEN] >> cost[i][BLUE];

	cout << start() << endl;

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
