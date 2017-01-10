#include <stdio.h>
int T;
char mem[200002], fan[200002]; // 멤버,  팬
int memLen, fanLen, fanMaleLen; // 멤버숫자, 팬숫자, 팬중남자숫자
int memMaleArr[200002]; // 멤버 중 남자 index 배열
int memMaleIdx; // 멤버 중 남자 index 배열의 숫자

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
    for (int f = 0; f <= loop; ++f) // 팬의 시작 index
        for (int m = 0; m < memMaleIdx; ++m) // 멤버중 남자만 비교
            if (fan[f + memMaleArr[m]] == 'M') // M + M 조합이면 답에서 뺀다.
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