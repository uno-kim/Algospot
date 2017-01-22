#include <stdio.h>
#include <algorithm>
using namespace std;
int T, N, K;
// k ���� ���߰� n �� ���� �� ��ǥ�� �ٲ㼭 �ִ� ������ �߻��ϴ� ������ ������ ��ȯ
int func(int k, int n)
{
    // ��ü ��
    int total = k * n / 10000;
    int ret = 0;
    double rate = 0.0;
    double tempRate = 0.0;
    for (int i = 1; i <= total; ++i)
    {
        int count = i * 10000 / k;
        if ((k * count) != (i * 10000)) count++; // ���� count
                                                 // k �� * count �� ������ ��ǥ �ݾ��� 90% �̻��̸鼭 % �� ���� ��츦 ��
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
        // ��ǥ�� ����
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