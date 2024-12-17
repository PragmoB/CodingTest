#include <iostream>

#define MAX_N 500
#define MAX_R 500
#define MAX_C 500

using namespace std;

int main() {
	unsigned int N;
	cin >> N;

	unsigned int r[MAX_N], c[MAX_N];
	for (int i = 0; i < N; i++)
		cin >> r[i] >> c[i];

	unsigned int dp[MAX_N][MAX_N];
	for (int i = 0; i < MAX_N; i++)
		for (int j = 0; j < MAX_N; j++)
			dp[i][j] = 0;

	for (int i = 1; i < N; i++)
	{
		for (int j = i - 1; 0 <= j; j--)
		{
			unsigned int min = -1;
			for (int k = j; k < i; k++)
			{
				unsigned int res;
				res = dp[j][k] + dp[k + 1][i] + r[j] * c[k] * c[i];
				if (res < min)
					min = res;
			}
			dp[j][i] = min;
		}
	}

	cout << dp[0][N - 1] << endl;

	return 0;
}