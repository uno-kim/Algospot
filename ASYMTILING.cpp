#include <stdio.h>
#include <string.h>
#define MOD 1000000007
int T, N;
int tile[102]; // 2 * n 크기의 모든 타일링 개수
int ans[102]; // 2 * n 크기의 모든 타일링 개수 - 대칭 타일링 개수
int main()
{
    tile[1] = 1, tile[2] = 2;
    for (int i = 3; i <= 100; ++i)
        tile[i] = (tile[i - 1] + tile[i - 2]) % MOD;
    for (int i = 3; i <= 99; i += 2) // 짝수
        ans[i] = (tile[i] + MOD - tile[i / 2]) % MOD;
    for (int i = 4; i <= 100; i += 2) // 홀수
    {
        ans[i] = (tile[i] + MOD - tile[i / 2]) % MOD;
        ans[i] = (ans[i] + MOD - tile[(i - 2) / 2]) % MOD;
    }
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &N);
        printf("%d\n", ans[N]);
    }
    return 0;
}