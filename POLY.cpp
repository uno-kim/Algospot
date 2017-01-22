#include <stdio.h>
#include <string.h>
using namespace std;
const int MOD = 10000000;
int T, N, cache[102][102];
// 남은 n 개 블록 중 현재 층을 r 개로 구성
int poly(int n, int r)
{
    int& ret = cache[n][r];
    if (ret != -1) return ret;
    ret = 0;
    for (int i = 1; i <= n - r; ++i)
        ret = (ret + (r + i - 1) * poly(n - r, i) % MOD) % MOD;
    return ret;
}

int main()
{
    //freopen("POLY.txt", "rt", stdin);
    memset(cache, -1, sizeof(cache));
    for (int i = 0; i <= 100; ++i) cache[i][i] = 1;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &N);
        int ret = 0;
        for (int i = 1; i <= N; ++i)
            ret = (ret + poly(N, i)) % MOD;
        printf("%d\n", ret);
    }
    return 0;
}