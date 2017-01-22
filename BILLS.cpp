#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int NAX_N = std::numeric_limits<int>::max();
int T, N, K, k, c, arr[10000];
double loss;
int solve()
{
    int ret = NAX_N;
    memset(arr, -1, sizeof(arr));
    // 현금으로 i 개를 구입시 수표로는 (N - i) 개 구입하게 됨
    for (int i = 0; i <= N; ++i)
    {
        // 수표로 구입시 손실금액이 k 원일 때, 현금 구매시 최소 손실이 발생하는 i 를 저장: arr[k] = i
        k = ((N - i) * K) % 10000;
        if (arr[k] != -1) break;
        arr[k] = i; 
    }
    for (int k = 0; k < 10000; ++k)
    {
        if (arr[k] == -1) continue;
        // 수표 손실금액 k + 현금 손실금액 (arr[k] * K) * 0.1 의 최소값을 구한다
        loss = arr[k] * K * 0.1;
        c = (int)loss;
        if (loss > (double)c) c++;
        ret = min(ret, k + c);
    }
    return (N * K) - ret;
}

int main()
{
    //freopen("BILLS.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &N, &K);
        printf("%d\n", solve());
    }
    return 0;
}