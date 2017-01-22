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
    for (int i = 0; i <= N; ++i) // �������� �Ǹ��� ���� i �� �پ�� ��
    {
        // ��ǥ�� �������� �ݾ�
        k = ((N - i) * K) % 10000;
        if (arr[k] != -1) break;
        arr[k] = i;
    }
    for (int i = 0; i < 10000; ++i)
    {
        if (arr[i] == -1) continue;
        // �������� �������� �ݾ�
        cache = arr[i] * K / 10.0;
        c = (int)cache;
        if (cache > (double)c) c++;
        ret = min(ret, i + c);
    }
    // ret �� �ּҷ� �������� �ݾ��̹Ƿ�
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