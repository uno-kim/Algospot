#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int MAX_N = 987654321;
int T, N, S, in[102], cache[102][11];
int psum[102], psqrsum[102];
int cache_sqrsum[102][102];
// in[idx] 부터 n 개의 오차 제곱의 합
int sqrsum(int idx, int n)
{
    int &ret = cache_sqrsum[idx][n];
    if (ret != -1) return ret;
    int x = (int)((double)(psum[idx + n - 1] - psum[idx - 1]) / (double)n + 0.5);
    return ret = n * x * x  + psqrsum[idx + n - 1] - psqrsum[idx - 1] - 2 * (psum[idx + n - 1] - psum[idx - 1]) * x;
}
// in[idx] 부터해서 사용할 숫자가 s개 남았을 때 최소값
int func(int idx, int s)
{
    if (idx == N) return 0;
    if (s == 0) return MAX_N;
    int& ret = cache[idx][s];
    if (ret != -1) return ret;
    ret = MAX_N;
    for (int i = 1; idx + i <= N; ++i)
        ret = min(ret, sqrsum(idx, i) + func(idx + i, s - 1));
    return ret;
}
int main()
{
    //freopen("QUANTIZE.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &N, &S);
        for (int i = 1; i <= N; ++i)
            scanf("%d", &in[i]);
        N++;
        sort(&in[0], &in[N]);
        for (int i = 1; i <= N; ++i)
        {
            psum[i] = psum[i - 1] + in[i];
            psqrsum[i] = psqrsum[i - 1] + in[i] * in[i];
        }
        memset(cache, -1, sizeof(cache));
        memset(cache_sqrsum, -1, sizeof(cache_sqrsum));
        printf("%d\n", func(1, S));
    }
    return 0;
}