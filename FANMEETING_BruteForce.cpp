#include <stdio.h>
int T;
char mem[200002], fan[200002]; // ���,  ��
int memLen, fanLen, fanMaleLen; // �������, �Ҽ���, ���߳��ڼ���
int memMaleArr[200002]; // ��� �� ���� index �迭
int memMaleIdx; // ��� �� ���� index �迭�� ����

int solve()
{
    memLen = fanLen = fanMaleLen = 0;
    memMaleIdx = 0;
    for (int i = 0; mem[i]; ++i)
    {
        if (mem[i] == 'M') memMaleArr[memMaleIdx++] = i;
        memLen++;
    }
    for (int i = 0; fan[i]; ++i)
    {
        if (fan[i] == 'M') fanMaleLen++;
        fanLen++;
    }
    int ret = fanLen - memLen + 1;
    if (memMaleIdx == 0 || fanMaleLen == 0) return ret;
    int loop = fanLen - memLen;
    for (int f = 0; f <= loop; ++f) // ���� ���� index
        for (int m = 0; m < memMaleIdx; ++m) // ����� ���ڸ� ��
            if (fan[f + memMaleArr[m]] == 'M') // M + M �����̸� �信�� ����.
            {
                ret--;
                break;
            }
    return ret;
}

int main()
{
    //freopen("FANMEETING.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", mem);
        scanf("%s", fan);
        printf("%d\n", solve());
    }
    return 0;
}