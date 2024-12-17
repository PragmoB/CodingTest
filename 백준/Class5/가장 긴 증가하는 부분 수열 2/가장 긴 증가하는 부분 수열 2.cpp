#include <iostream>

#define MAX_N 1000000

using namespace std;


int main() {
	int N;
	int A[MAX_N], LIS[MAX_N], len_LIS = 0;

	cin >> N;
	cin >> A[0];
	LIS[len_LIS++] = A[0];

	for (int i = 1; i < N; i++)
	{
		cin >> A[i];

		// 추가
		if (LIS[len_LIS - 1] < A[i])
		{
			LIS[len_LIS++] = A[i];
			continue;
		}

		// 대체
		int idx = (len_LIS - 1) / 2, lp = 0, rp = len_LIS - 1;
		while (abs(rp - lp) > 1)
		{
			if (LIS[idx] == A[i])
			{
				lp = rp = idx;
				break;
			}
			else if (LIS[idx] < A[i])
			{
				lp = idx;
				idx = (rp + lp) / 2;
			}
			else
			{
				rp = idx;
				idx = (rp + lp) / 2;
			}
		}
		while (LIS[lp] > A[i] && lp > 0)
			lp--;
		while (A[i] > LIS[rp] && rp < len_LIS)
			rp++;
		for (; A[i] <= LIS[rp - 1]; rp--);
		for (; LIS[lp + 1] <= A[i]; lp++);

		LIS[rp] = A[i];
	}

	cout << len_LIS << endl;
	return 0;
}