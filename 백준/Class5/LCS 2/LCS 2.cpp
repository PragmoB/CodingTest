// LCS 2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <cstring>

#define MAX_LEN 1000

using namespace std;

char str1[MAX_LEN + 1], str2[MAX_LEN + 1];
int len_str1, len_str2;
// next_str2_idx_of[i][j] = str2에서 알파벳 (i + 0x41)를 j번 인덱스부터 찾았을 때 가장 가까운 인덱스
int next_str2_idx_of['Z' - 'A' + 1][MAX_LEN + 1];
// dp[i][j] = str1[i], str2[j] 부터 비교를 시작했을때 LCS len값
int dp[MAX_LEN + 1][MAX_LEN + 1];

int dfs(int depth = 0, int previous_str2_alphabet_idx = -1) {
	static char neg_cs[MAX_LEN + 1];

	if (depth == len_str1)
		return 0;
	if (dp[depth][previous_str2_alphabet_idx + 1] != -1)
		return dp[depth][previous_str2_alphabet_idx + 1];

	int ret = dfs(depth + 1, previous_str2_alphabet_idx);
	if (dp[depth][previous_str2_alphabet_idx + 1] < ret)
		dp[depth][previous_str2_alphabet_idx + 1] = ret;

	int next_idx = next_str2_idx_of[str1[depth] - 'A'][previous_str2_alphabet_idx + 1];
	if (next_idx != -1) { // str2에 str1[depth] 알파벳이 존재했다면
		ret = dfs(depth + 1, next_idx) + 1;
		if (dp[depth][previous_str2_alphabet_idx + 1] < ret)
			dp[depth][previous_str2_alphabet_idx + 1] = ret;
	}

	return dp[depth][previous_str2_alphabet_idx + 1];
}
int main() {
	cin >> str1 >> str2;
	len_str1 = strlen(str1);
	len_str2 = strlen(str2);

	for (int i = 0; i < 'Z' - 'A' + 1; i++)
		for (int j = 0; j < MAX_LEN + 1; j++)
			next_str2_idx_of[i][j] = -1;
	for (int i = 0; i < MAX_LEN + 1; i++)
		for (int j = 0; j < MAX_LEN + 1; j++)
			dp[i][j] = -1;

	// next_str2_idx_of 구성
	for (int i = 0; i < len_str2; i++) {
		int alphabet = str2[i] - 'A';
		for (int j = i; 0 <= j; j--) {
			if (next_str2_idx_of[alphabet][j] != -1)
				break;
			next_str2_idx_of[alphabet][j] = i;
		}
	}

	dfs();

	cout << dp[0][0] << endl;
	for (int i = 0, previous_str2_alphabet_idx = -1; i < len_str1; i++) {
		int alphabet = str1[i] - 'A';
		int matching_str2_idx = next_str2_idx_of[alphabet][previous_str2_alphabet_idx + 1];

		// str1[i]을 포함한 케이스가 존재하며 str1[i]를 포함한 케이스가 포함 안한 케이스보다 길이가 크다면
		if (matching_str2_idx != -1 && dp[i + 1][previous_str2_alphabet_idx + 1] <
			dp[i + 1][matching_str2_idx + 1] + 1) {
			// 이건 출력하는게 맞음
			cout << str1[i];
			previous_str2_alphabet_idx = matching_str2_idx;
		}
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
