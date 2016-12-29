#include <stdio.h>
#include <algorithm>
using namespace std;
int T, N, L, cost[1002], psum[1002];
double solve()
{
    double ret = 100.0;
    for (int size = L; size <= N; ++size)
    {
        int sum = 100000;
        for (int i = 1; i <= N - size + 1; ++i)
            sum = min(sum, psum[i + size - 1] - psum[i - 1]);
        ret = min(ret, sum / (double)size);
    }
    return ret;
}
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &N, &L);
        for (int i = 1; i <= N; ++i)
        {
            scanf("%d", &cost[i]);
            psum[i] = psum[i - 1] + cost[i];
        }
        printf("%0.10lf\n", solve());
    }
    return 0;
}