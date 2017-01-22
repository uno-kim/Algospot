#include <stdio.h>
#include <algorithm>
using namespace std;
int T, N, K;
// k 원의 배추가 n 개 있을 때 수표로 바꿔서 최대 이익이 발생하는 배추의 개수를 반환
int func(int k, int n)
{
    // 전체 합
    int total = k * n / 10000;
    int ret = 0;
    double rate = 0.0;
    double tempRate = 0.0;
    for (int i = 1; i <= total; ++i)
    {
        int count = i * 10000 / k;
        if ((k * count) != (i * 10000)) count++; // 시작 count
                                                 // k 원 * count 개 값을로 수표 금액이 90% 이상이면서 % 가 높은 경우를 고름
        tempRate = ((k * count) - (k * count) % 10000) / (double)(k * count);
        if (tempRate >= 0.9 && tempRate > rate)
        {
            rate = tempRate;
            ret = max(ret, count);
        }
    }
    return ret;
}

int solve()
{
    int ret = 0;
    int count = 0;
    while ((count = func(K, N)) > 0)
    {
        // 수표로 정리
        ret += ((K * count) - (K * count) % 10000);
        N -= count;
    }
    ret += (K * N * 90) / 100;
    return ret;
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