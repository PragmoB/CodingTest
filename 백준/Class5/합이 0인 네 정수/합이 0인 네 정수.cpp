// 합이 0인 네 정수.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#define MAX_n 4000
using namespace std;

int compare(const void* a, const void* b)
{
	return *((long long*)a) - *((long long*)b);
}
int main() {
	int n;
	cin >> n;

	long long A[MAX_n], B[MAX_n], C[MAX_n], D[MAX_n];
	for (int i = 0; i < n; i++)
		cin >> A[i] >> B[i] >> C[i] >> D[i];

	long long AB[MAX_n * MAX_n], CD[MAX_n * MAX_n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			AB[i * n + j] = A[i] + B[j];
			CD[i * n + j] = C[i] + D[j];
		}

	qsort(AB, n * n, sizeof(*AB), compare);
	qsort(CD, n * n, sizeof(*CD), compare);

	long long res = 0;
	long long ab = 0, cd = n * n - 1;
	while (ab < n * n && 0 <= cd)
	{
		long long sum = AB[ab] + CD[cd];
		if (sum == 0)
		{
			long long num_ab = 1, num_cd = 1;
			while (AB[ab] == AB[ab + num_ab] && ab + num_ab < n * n)
				num_ab++;
			while (CD[cd] == CD[cd - num_cd] && 0 <= cd - num_cd)
				num_cd++;

			res += num_ab * num_cd;
			ab += num_ab;
			cd -= num_cd;
		}
		else if (sum < 0)
			ab++;
		else
			cd--;
	}

	cout << res << endl;
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
