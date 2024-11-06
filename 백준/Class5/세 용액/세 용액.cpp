// 세 용액.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#define MAX_N 5000

using namespace std;

int compare(const void* a, const void* b) {
	return (*(long long*)b) - (*(long long*)a);
}

int main()
{
	int N;
	cin >> N;

	long long solutions[MAX_N];
	for (int i = 0; i < N; i++)
		cin >> solutions[i];

	qsort(solutions, N, sizeof(*solutions), compare);

	unsigned long long min = -1;
	long long answers[3];

	// 용액 두개로 만들 수 있는 조합을 모두 선택
	for (int i = 0; i < N - 1; i++)
		for (int j = i + 1; j < N; j++)
		{
			long long sum = solutions[i] + solutions[j];

			// 선택된 용액 2개 조합에서 0에 가장 가까운 조합을 선택
			int idx = N / 2;
			int lp = 0, rp = N - 1;
			while (1 < rp - lp)
			{
				if (sum + solutions[idx] == 0)
				{
					lp = rp = idx;
					break;
				}

				if (sum + solutions[idx] > 0)
				{
					lp = idx;
					idx = (idx + rp) / 2 + (idx + rp) % 2;
				}
				else
				{
					rp = idx;
					idx = (idx + lp) / 2;
				}
			}
			if (abs(sum + solutions[lp]) < abs(sum + solutions[rp]))
				idx = lp;
			else
				idx = rp;
			while (idx == i || idx == j)
			{
				if (N <= idx + 1 && ((idx - 1) == i || (idx - 1) == j))
					idx -= 2;
				else if (idx - 1 < 0 && ((idx + 1) == i || (idx + 1) == j))
					idx += 2;

				else if (idx - 1 < 0 || (idx - 1) == i || (idx - 1) == j)
					idx++;
				else if (N <= idx + 1 || (idx + 1) == i || (idx + 1) == j)
					idx--;
				else if (abs(sum + solutions[idx - 1]) < abs(sum + solutions[idx + 1]))
					idx--;
				else
					idx++;
			}
			sum += solutions[idx];
			if (abs(sum) < min)
			{
				min = abs(sum);
				answers[0] = solutions[i];
				answers[1] = solutions[j];
				answers[2] = solutions[idx];
			}
			if (min == 0)
				break;
		}

	for (int i = 0; i < 2; i++)
		for (int j = i + 1; j < 3; j++)
			if (answers[i] > answers[j]) {
				long long tmp = answers[i];
				answers[i] = answers[j];
				answers[j] = tmp;
			}
	cout << answers[0] << ' ' << answers[1] << ' ' << answers[2];
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
