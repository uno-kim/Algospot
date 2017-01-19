#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int T, N, val[102][102], cache[102][102];
// (y, x) 지점에서의 최대 경로 개수
int func(int y, int x)
{
    int& ret = cache[y][x];
    if (ret != -1) return ret;
    ret = 0;
    if (val[y - 1][x] >= val[y - 1][x - 1])
        ret += func(y - 1, x);
    if (val[y - 1][x] <= val[y - 1][x - 1])
        ret += func(y - 1, x - 1);
    return ret;
}
int main()
{
    //freopen("TRIPATHCNT.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &N);
        int num;
        for (int y = 1; y <= N; ++y)
            for (int x = 1; x <= y; ++x)
            {
                scanf("%d", &num);
                val[y][x] = max(val[y - 1][x], val[y - 1][x - 1]) + num;
            }
        int maxLen = 0;
        for (int x = 1; x <= N; ++x)
            maxLen = max(maxLen, val[N][x]);
        memset(cache, -1, sizeof(cache));
        cache[1][1] = 1; // (1, 1) 에서는 무조건 1임
        int ret = 0;
        for (int x = 1; x <= N; ++x)
            if (val[N][x] == maxLen)
                ret += func(N, x);
        printf("%d\n", ret);
    }
    return 0;
}