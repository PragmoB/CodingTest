﻿// 트리와 쿼리.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>
#include <vector>

#define MAX_N 100000

using namespace std;

int dp[MAX_N + 1];
// visited[i - 1] = 그래프 탐색에서 i번 노드를 방문했는지 여부
bool visited[MAX_N + 1];
// num_node[i - 1] = i번 노드와 연결된 노드들의 번호
vector<int> num_nodes[MAX_N + 1];

int dfs(int num_node) {
	visited[num_node] = true;
	for (auto iter : num_nodes[num_node]) {
		if (!visited[iter])
			dp[num_node] += dfs(iter);
	}

	return dp[num_node];
}
int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for (int i = 0; i < MAX_N + 1; i++) {
		dp[i] = 1;
		visited[i] = false;
	}

	int N, R, Q;
	cin >> N >> R >> Q;

	for (int i = 0; i < N - 1; i++) {
		int U, V;
		cin >> U >> V;
		num_nodes[U].push_back(V);
		num_nodes[V].push_back(U);
	}
	dfs(R);

	for (int i = 0; i < Q; i++) {
		int U;
		cin >> U;
		// endl => '\n' 수정했더니 통과
		// 이게 맞냐? 나쁜놈들아
		cout << dp[U] << '\n';
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
