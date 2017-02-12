#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
const long long MAX_N = 2147483647;
int T, N, K, in[502];
int L; // lis 길이
int A[502], idx; // 정답
struct sorted
{
    int idx;
    int val;
};
sorted S[502];
bool comp(const sorted & A, const sorted & B) { return A.val < B.val;}

// in[start] 부터 시작하는 lis 값
int cacheLis[502];
int lis(int start)
{
    if (cacheLis[start] != -1) return cacheLis[start];
    cacheLis[start] = 1;
    for (int next = start + 1; next < N; ++next)
        if (in[start] < in[next])
            cacheLis[start] = max(cacheLis[start], lis(next) + 1);
    return cacheLis[start];
}
// in[start] 에서 시작하는 lis 의 총 개수를 반환한다.
int cache[502];
int lisCount(int start)
{
    if (lis(start) == 1) return cache[start] = 1;
    if (cache[start] != -1) return cache[start];
    cache[start] = 0;
    for (int next = start + 1; next < N; ++next)
        if (in[start] < in[next] && lis(start) == lis(next) + 1)
            cache[start] = (int)min(MAX_N, ((long long)cache[start] + lisCount(next)));
    return cache[start];
}

void klis(int start, int len, int k)
{
    A[idx++] = in[start];
    int val = 0, next;
    for (int i = 0; i < N; ++i)
    {
        next = S[i].idx;
        if (start < next && in[start] < in[next] && N - next >= len - 1 && lis(start) == lis(next) + 1)
        {
            val += lisCount(next);
            if (val >= k)
            {
                klis(next, len - 1, k - (val - lisCount(next)));
                return;
            }
        }
    }
}

int main()
{
    //freopen("KLIS.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &N, &K);
        N++;
        S[0].idx = 0, S[0].val = 0;
        for (int i = 1; i < N; ++i)
        {
            scanf("%d", &in[i]);
            S[i].idx = i;
            S[i].val = in[i];
        }
        sort(&S[0], &S[N], comp);
        memset(cacheLis, -1, sizeof(cacheLis));
        memset(cache, -1, sizeof(cache));
        L = lis(0);
        printf("%d\n", L - 1);
        idx = 0;
        klis(0, L, K);
        for (int i = 1; i < L; ++i)
            printf("%d ", A[i]);
        printf("\n");
    }
    return 0;
}