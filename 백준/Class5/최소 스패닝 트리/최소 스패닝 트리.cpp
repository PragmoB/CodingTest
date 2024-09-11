// 최소 스패닝 트리.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>
#include <vector>
#include <cstdlib>

#define MAX_V 10000
#define MAX_E 100000

using namespace std;

typedef struct tagLink {
	long long A, B;
	long long weight;
} Link;

// 가중치 적은 순으로 정렬
int compare(const void* a, const void* b) {
	long long res = (*(Link*)a).weight - (*(Link*)b).weight;
	if (res > 0)
		return 1;
	else if (res == 0)
		return 0;
	else
		return -1;
}

int main(int argc, char* argv[]) {
	int V, E;
	cin >> V >> E;

	// parent_of[i] = i번 노드의 루트 노드 번호
	int parent_of[MAX_V + 1];
	for (int i = 0; i < MAX_V + 1; i++)
		parent_of[i] = i;

	Link links[MAX_E];
	for (int i = 0; i < E; i++)
		cin >> links[i].A >> links[i].B >> links[i].weight;

	qsort(links, E, sizeof(*links), compare);

	long long answer = 0;
	// 연결 정보들을 탐색함
	for (int i = 0; i < E; i++) {
		int parent_of_A = parent_of[links[i].A];
		int parent_of_B = parent_of[links[i].B];

		// 부모노드가 같다면
		if (parent_of_A == parent_of_B)
			continue; // 순환 구조가 생기므로 패스

		// 두 노드를 연결함
		answer += links[i].weight;
		for (int j = 1; j < V + 1; j++)
			if (parent_of[j] == parent_of_B)
				parent_of[j] = parent_of_A;
	}

	cout << answer << endl;

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
