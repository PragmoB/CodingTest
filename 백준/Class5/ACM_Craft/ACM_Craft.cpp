#include <iostream>

#define MAX_N 1000
#define MAX_K 100000
#define MAX_D 100000

using namespace std;

int N, K, D[MAX_N], X[MAX_K], Y[MAX_K], dp[MAX_N];

int dfs(int W) {
	if (dp[W - 1] == -1) {
		int max = 0;
		for (int i = 0; i < K; i++) {
			if (Y[i] == W) {
				int res = dfs(X[i]);
				if (max < res)
					max = res;
			}
		}
		dp[W - 1] = max + D[W - 1];
	}
	return dp[W - 1];
}

void solve() {
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		dp[i] = -1;
		cin >> D[i];
	}
	for (int i = 0; i < K; i++)
		cin >> X[i] >> Y[i];

	int W;
	cin >> W;

	cout << dfs(W) << '\n';
}

int main() {
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
		solve();

	return 0;
}