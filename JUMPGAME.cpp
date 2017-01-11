#include <stdio.h>
#include <string.h>
int T, N;
int in[102][102];
int cache[102][102];
// (y, x) 에서 마지막까지 도달 가능한지 여부
int jump(int y, int x)
{
    if (y == N - 1 && x == N - 1) return 1;
    if (x >= N || y >= N) return 0;
    int &ret = cache[y][x];
    if (ret != -1) return ret;
    ret = 0;
    ret = (jump(y + in[y][x], x) | jump(y, x + in[y][x]));
    return ret;
}

int main()
{
    //freopen("JUMPGAME.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &N);
        for (int y = 0; y < N; ++y)
            for (int x = 0; x < N; ++x)
                scanf("%d", &in[y][x]);
        memset(cache, -1, sizeof(cache));
        if (jump(0, 0)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}