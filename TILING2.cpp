#include <stdio.h>
#include <string.h>
#define MOD 1000000007
int T, N, cache[102];
int main()
{
    cache[1] = 1, cache[2] = 2;
    for (int i = 3; i <= 100; ++i)
        cache[i] = (cache[i - 1] + cache[i - 2]) % MOD;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &N);
        printf("%d\n", cache[N]);
    }
    return 0;
}