#include <iostream>
#include <map>
#include <vector>

#define MAX_N 1000000

using namespace std;

bool dfs(const int len_LIS, const int* A, vector<int>* LIS_idx_A, int* LIS, int depth = 0)
{
    static int idxes[MAX_N];
    static map<int, bool> dp[MAX_N]; // dp[i][j] = LIS[i]가 A[j]로 결정되었을 때 나머지 LIS를 끝까지 결정할 수 있는지 여부

    if (depth == 0)
        for (int i = 0; i < len_LIS; i++)
            dp[i].clear();

    if (depth == len_LIS)
        return true;

    for (auto idx : LIS_idx_A[depth])
    {
        idxes[depth] = idx;
        LIS[depth] = A[idx];

        if ((idxes[depth - 1] < idxes[depth] &&  // 수열의 순서가 올바르고
            LIS[depth - 1] < LIS[depth] && // 수열이 증가하는 꼴인지 검사
            dp[depth].find(idx) == dp[depth].end()) // 또한 검사에서 탈락한 전과도 없어야함
            || depth == 0) // root node라면 예외
        {
            if (dfs(len_LIS, A, LIS_idx_A, LIS, depth + 1))
                return true;
            else
                dp[depth][idx] = false;
        }
    }

    return false;
}

/*
 * input  |  N  | length of A
 * input  |  A  | subsequence
 * output | LIS | the longest increasing subsequence
 */
int get_LIS(const int N, const int* A, int* LIS)
{
    // A[LIS_idx_A[i][j]] = LIS[i]의 제 (j + 1)대 값 (i >= 0, j >= 0)
    int len_LIS = 0;
    vector<int> LIS_idx_A[MAX_N];

    LIS[0] = A[0];
    LIS_idx_A[0].push_back(0);
    len_LIS++;
    for (int i = 1; i < N; i++)
    {
        // LIS 추가
        if (LIS[len_LIS - 1] < A[i])
        {
            LIS_idx_A[len_LIS].push_back(i);
            LIS[len_LIS++] = A[i];
            continue;
        }

        // LIS 교체
        int lp = 0, rp = len_LIS - 1;
        int idx = (lp + rp) / 2;
        while (rp - lp > 1)
        {
            if (LIS[idx] == A[i])
                lp = rp = idx;
            else if (LIS[idx] < A[i])
            {
                lp = idx;
                idx = (lp + rp) / 2;
            }
            else
            {
                rp = idx;
                idx = (lp + rp) / 2;
            }
        }

        for (; LIS[rp] < A[i] && rp < len_LIS - 1; rp++);
        for (; A[i] < LIS[lp] && lp > 0; lp--);
        for (; A[i] <= LIS[rp - 1] && rp > 0; rp--);
        for (; LIS[lp + 1] <= A[i] && lp < len_LIS - 1; lp++);

        LIS[rp] = A[i];
        LIS_idx_A[rp].push_back(i);
    }

    dfs(len_LIS, A, LIS_idx_A, LIS);

    return len_LIS;
}

int main()
{
    int N, A[MAX_N + 1];

    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> A[i];

    // 풀다가 뭔가 API화 해보고 싶어서 바꿔봤음ㅋㅋ get_LIS라니 PS때 말고 쓸일이 있을까 싶지만
    int LIS[MAX_N];
    int len = get_LIS(N, A, LIS);

    cout << len << endl;
    for (int i = 0; i < len; i++)
        cout << LIS[i] << ' ';
    cout << endl;

    return 0;
}