#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int T, N, K, arr[10000];
int solve()
{
    int ret = 2147483647;
    memset(arr, -1, sizeof(arr));
    int k, c;
    double cache;
    for (int i = 0; i <= N; ++i) // 현금으로 판매한 개수 i 를 줄어야 함
    {
        // 수표로 버려지는 금액
        k = ((N - i) * K) % 10000;
        if (arr[k] != -1) break;
        arr[k] = i;
    }
    for (int i = 0; i < 10000; ++i)
    {
        if (arr[i] == -1) continue;
        // 현금으로 버려지는 금액
        cache = arr[i] * K / 10.0;
        c = (int)cache;
        if (cache > (double)c) c++;
        ret = min(ret, i + c);
    }
    // ret 는 최소로 버려지는 금액이므로
    return (N * K) - ret;
}

int main()
{
    freopen("BILLS.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &N, &K);
        printf("%d\n", solve());
    }
    return 0;
}