#include <stdio.h>
int T, N, D, P, Q;
int adj[52][52]; // adj[here][i] - here 에서 연결되어 있는 there 의 index
int near[52]; // near[here] 에서 연결되어 있는 마을의 개수
double cache[102][52];
// d 일 후에 n 번째 마을에 있을 확률
double func(int d, int n)
{
    if (cache[d][n] != -1.0) return cache[d][n];
    double ret = 0.0;
    // n 번 마을에 인접한 것들을 찾아라.
    for (int i = 0; adj[n][i] != -1; ++i)
        ret += func(d - 1, adj[n][i]) / (double)near[adj[n][i]];
    return cache[d][n] = ret;
}
int main()
{
    //freopen("NUMB3RS.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d%d", &N, &D, &P);
        int t, idx;
        for (int y = 0; y < N; ++y)
        {
            near[y] = idx = 0;
            for (int x = 0; x < N; ++x)
            {
                scanf("%d", &t);
                if (t)
                {
                    adj[y][idx++] = x;
                    near[y]++;
                }
            }
            adj[y][idx] = -1;
        }
        // cache 초기화
        for (int d = 1; d <= D; ++d)
            for (int n = 0; n < N; ++n)
                cache[d][n] = -1.0;
        // default 셋팅
        for (int n = 0; n < N; ++n)
            cache[0][n] = 0.0;
        cache[0][P] = 1.0;
        scanf("%d", &t);
        for (int i = 0; i < t; ++i)
        {
            scanf("%d", &Q);
            printf("%0.8lf ", func(D, Q));
        }
        printf("\n");
    }
    return 0;
}