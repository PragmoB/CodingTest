// 도시 분할 계획.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>
#include <vector>
#include <cstdlib>

#define MAX_N 100000
#define MAX_M 1000000

using namespace std;

typedef struct tagLink {
	int A, B, C;
} Link;

int compare(const void* a, const void* b) {
	return ((Link*)a)->C - ((Link*)b)->C;
}
int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, M;
	cin >> N >> M;

	// parent_of[i] = i번 노드의 루트노드
	int parent_of[MAX_N + 1];
	// children_of[i] = i번 노드의 자식들의 번호(i번 노드 포함)
	vector<int> children_of[MAX_N + 1];
	for (int i = 0; i <= N; i++) {
		parent_of[i] = i;
		children_of[i].push_back(i);
	}

	Link links[MAX_M];
	for (int i = 0; i < M; i++)
		cin >> links[i].A >> links[i].B >> links[i].C;

	qsort(links, M, sizeof(*links), compare);

	int max_C = 0;
	int sum = 0;
	for (int i = 0; i < M; i++) {
		int parent_of_A = parent_of[links[i].A];
		int parent_of_B = parent_of[links[i].B];

		// 순환구조로 연결된다면
		if (parent_of_A == parent_of_B)
			continue; // 낭비라서 패스

		max_C = links[i].C;
		sum += links[i].C;

		// 노드 간 부모-자식 관계도 반영함
		// bigger_group, smaller_group은 시간을 줄이기 위한 최적화
		int bigger_group, smaller_group;
		bigger_group = smaller_group = parent_of_B;
		if (children_of[parent_of_A].size() <= children_of[parent_of_B].size())
			smaller_group = parent_of_A;
		else
			bigger_group = parent_of_A;
		for (auto iter : children_of[smaller_group]) {
			parent_of[iter] = bigger_group;
			children_of[bigger_group].push_back(iter);
		}
		children_of[smaller_group].clear();
		children_of[smaller_group].shrink_to_fit();
	}

	sum -= max_C;
	cout << sum << endl;
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
