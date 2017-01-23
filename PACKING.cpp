#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int T, N, W, cache[102][1002], cnt;
bool choices[102]; // 선택 여부
struct goods
{
    char name[21];
    int vol;
    int needs;
};
goods G[102];

// n 번물건부터 시작해서 남은 공간이 w 일 때 최대 절박도 계산
int func(int n, int w)
{
    if (cache[n][w] != -1) return cache[n][w];
    int ret = func(n + 1, w); // n 번을 선택 안함
    if (w - G[n].vol >= 0) // n 번을 선택함
        ret = max(ret, func(n + 1, w - G[n].vol) + G[n].needs);
    return cache[n][w] = ret;
}

void reconstruct(int n, int w)
{
    if (n == N) return;
    if (cache[n][w] == cache[n + 1][w])
    {
        choices[n] = false;
        reconstruct(n + 1, w);
    }
    else
    {
        choices[n] = true;
        cnt++;
        reconstruct(n + 1, w - G[n].vol);
    }
}

int main()
{
    //freopen("PACKING.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &N, &W);
        memset(cache, -1, sizeof(cache));
        for (int i = 0; i < N; ++i) cache[i][0] = 0;
        for (int i = 0; i <= W; ++i) cache[N][i] = 0;
        for (int i = 0; i < N; ++i)
            scanf("%s%d%d", G[i].name, &G[i].vol, &G[i].needs);
        printf("%d ", func(0, W));
        cnt = 0;
        reconstruct(0, W);
        printf("%d\n", cnt);
        for (int i = 0; i < N; ++i)
            if (choices[i])
                printf("%s\n", G[i].name);
    }
    return 0;
}