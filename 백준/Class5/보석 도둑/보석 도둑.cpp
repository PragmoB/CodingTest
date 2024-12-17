#include <iostream>
#include <queue>

#define MAX_N 300000
#define MAX_K 300000

using namespace std;

typedef struct Jewelry
{
	int M, V;
} Jewelry;

int compare_jewelry(const void* a, const void* b)
{
	return ((Jewelry*)a)->M - ((Jewelry*)b)->M;
}
int compare_suitcase(const void* a, const void* b)
{
	return *((int*)a) - *((int*)b);
}
int main()
{
	int N, K;
	cin >> N >> K;

	Jewelry jewelrys[MAX_N];
	for (int i = 0; i < N; i++)
		cin >> jewelrys[i].M >> jewelrys[i].V;

	int C[MAX_N];
	for (int i = 0; i < K; i++)
		cin >> C[i];

	// 보석들을 가벼운 순으로 정렬
	qsort(jewelrys, N, sizeof(*jewelrys), compare_jewelry);
	// 가방은 작은 순으로 정렬
	qsort(C, K, sizeof(*C), compare_suitcase);

	// j : 보석을 넣은 횟수
	long long res = 0, j = 0;
	// pq = 가방에 들어가는 보석들의 가치
	priority_queue<int> pq;
	// i : 가방을 작은 것 부터 하나씩 선택
	for (int i = 0; i < K; i++)
	{
		int V_jewelry = jewelrys[j].V;
		int M_jewelry = jewelrys[j].M;
		while (M_jewelry <= C[i] && j < N)
		{
			pq.push(V_jewelry);
			V_jewelry = jewelrys[++j].V;
			M_jewelry = jewelrys[j].M;
		}
		if (!pq.empty())
		{
			res += pq.top();
			pq.pop();
		}
	}

	cout << res << endl;

	return 0;
}