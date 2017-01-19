#include <stdio.h>
#include <string.h>
int T, N, M;
double cache[1002][2004];
int main()
{
    //freopen("SNAIL.txt", "rt", stdin);
    scanf("%d", &T);
    cache[1][1] = 0.25;
    cache[1][2] = 0.75;
    for (int d = 2; d <= 1000; ++d)
        for (int h = 2; h <= d * 2; ++h)
            cache[d][h] = cache[d - 1][h - 2] * 0.75 + cache[d - 1][h - 1] * 0.25;
    while (T--)
    {
        scanf("%d%d", &N, &M);
        double ret = 0.0;
        for (int n = N; n <= 2 * M; ++n)
            ret += cache[M][n];
        printf("%0.10lf\n", ret);
    }
    return 0;
}