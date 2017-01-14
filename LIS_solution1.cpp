#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int T, N, S[502], cache[502];
// S[start] 에서 시작하는 증가 부분 수열 중 최대 길이
int lis(int start)
{
    int& ret = cache[start];
    if (ret != -1) return ret;
    ret = 1;
    for (int next = start + 1; next <= N; ++next)
        if(S[start] < S[next])
            ret = max(ret, lis(next) + 1);
    return ret;
}

int main()
{
    //freopen("LIS.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &N);
        for (int i = 1; i <= N; ++i)
            scanf("%d", &S[i]);
        memset(cache, -1, sizeof(cache));
        printf("%d\n", lis(0) - 1);
    }
    return 0;
}