#include <stdio.h>
#include <algorithm>
using namespace std;
int T, N, in[102][102], cache[102][102];
// (y, x) 점에서의 최대 경로
int path(int y, int x)
{
    int& ret = cache[y][x];
    if (ret != -1) return ret;
    ret = in[y][x];
    ret += max(path(y - 1, x), path(y - 1, x - 1));
    return ret;
}

int solve()
{
    int ret = 0;
    for (int i = 1; i <= N; ++i)
        ret = max(ret, path(N, i));
    return ret;
}

int main()
{
    //freopen("TRIANGLEPATH.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &N);
        for (int y = 1; y <= N; ++y)
            for (int x = 1; x <= y; ++x)
            {
                scanf("%d", &in[y][x]);
                cache[y][x] = -1;
            }
        printf("%d\n", solve());
    }
    return 0;
}