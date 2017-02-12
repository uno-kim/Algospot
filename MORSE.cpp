#include <stdio.h>
#include <algorithm>
using namespace std;
const int MAX_K = 1000000000;
int T, N, M, K;
// n, m 개로 만들 수 있는 총 부호의 가지수
int cache[102][102];

void init()
{
    for (int i = 0; i <= 100; ++i)
        cache[i][0] = cache[0][i] = 1;
    for (int n = 1; n <= 100; ++n)
        for (int m = 1; m <= 100; ++m)
            cache[n][m] = min(MAX_K, cache[n - 1][m] + cache[n][m - 1]);
}

void morse(int n, int m, int k)
{
    if (n == 0) // m 개수만큼
    {
        for(int i = 0; i < m; ++i) printf("o");
        return;
    }
    if (m == 0) // n 개수만큼
    {
        for(int i = 0; i < n; ++i) printf("-");
        return;
    }
    if (k <= cache[n - 1][m])
    {
        printf("-");
        morse(n - 1, m, k);
    }
    else
    {
        printf("o");
        morse(n, m - 1, k - cache[n - 1][m]);
    }
}

int main()
{
    //freopen("MORSE.txt", "rt", stdin);
    init();
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &N, &M, &K);
        morse(N, M, K);
        printf("\n");
    }
    return 0;
}