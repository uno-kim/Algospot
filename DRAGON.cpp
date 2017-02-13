#include <stdio.h>
using namespace std;
int T, N, L;
long long P;
// n 세대의 총 글자길이
long long len[52];
void init()
{
    len[0] = 2;
    for (int i = 1; i <= 50; ++i)
        len[i] = len[i - 1] * 2 + 1;
}
const char strPlus[] = { "FX+YF" };
const char strMinus[] = { "FX-YF" };
void print(int p, int l, bool sign)
{
    if (sign)
    {
        for (int i = p; i < p + l; ++i)
            printf("%c", strPlus[i]);
    }
    else
    {
        for (int i = p; i < p + l; ++i)
            printf("%c", strMinus[i]);
    }
}

void printSign(bool plus) {
    plus ? printf("+") : printf("-");
}

void dragon(int n, long long p, int l, bool sign)
{
    if (n <= 1)
    {
        print(p, l, sign);
        return;
    }
    if (p + l - 1 < len[n - 1])
    {
        dragon(n - 1, p, l, true);
    }
    else if (p + l - 1 == len[n - 1])
    {
        dragon(n - 1, p, l - 1, true);
        printSign(sign);
    }
    else if (p > len[n - 1])
    {
        dragon(n - 1, p - len[n - 1] - 1, l, false);
    }
    else if (p == len[n - 1])
    {
        printSign(sign);
        dragon(n - 1, 0, l - 1, false);
    }
    else
    {
        dragon(n - 1, p, len[n - 1] - p, true);
        printSign(sign);
        dragon(n - 1, 0, p + l - len[n - 1] - 1, false);
    }
}

int main()
{
    //freopen("DRAGON.txt", "rt", stdin);
    init();
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%lld%d", &N, &P, &L);
        --P;
        dragon(N, P, L, true);
        printf("\n");
    }
    return 0;
}