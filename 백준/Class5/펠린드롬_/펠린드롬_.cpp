// 펠린드롬_.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>

#define FASTIO() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

#define MAX_N 2000
#define MAX_M 1000000

using namespace std;

int main() {

	FASTIO();

	// dp[i][j] = i번째 수부터 j번째 수까지는 펠린드롬인가? 계산이 안돼있을 경우 -1
	char dp[MAX_N + 1][MAX_N + 1];
	for (int i = 0; i < MAX_N + 1; i++)
		for (int j = 0; j < MAX_N + 1; j++)
			dp[i][j] = -1;
	int N;
	cin >> N;

	for (int i = 0; i < N; i++)
		dp[i][i] = 1;

	int a[MAX_N];
	for (int i = 0; i < N; i++)
		cin >> a[i];

	int M;
	cin >> M;

	for (int i = 0; i < M; i++) {
		int S0, E0; // 0부터 시작한다는 의미에서 0을 붙인 네이밍
		cin >> S0 >> E0;
		S0--, E0--;

		if (dp[S0][E0] == -1) {
			// 수열 가운데서부터 점점 확장하며 탐색.
			// j : 왼쪽 포인터, k : 오른쪽 포인터
			for (int j = (S0 + E0) / 2,
				k = (S0 + E0) / 2 + (S0 + E0) % 2;
				S0 <= j && k <= E0; j--, k++) {
				// 이미 계산되어 있는 구간이라면
				if (dp[j][k] != -1)
					continue; // 건너뜀

				if (a[j] == a[k])
					dp[j][k] = 1;
				else { // 펠린드롬이 안되는 구간부터는
					// 전부 다 0으로 계산
					for (; 0 <= j && k < N; j--, k++)
						dp[j][k] = 0;
					break;
				}
			}
		}
		cout << (int)dp[S0][E0] << '\n';
	}

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
