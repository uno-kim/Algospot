#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int T, lenA, lenB, cache[102][102];
const long long NEGINF = numeric_limits<long long>::min();
long long A[102], B[102];
// A[a] 와 B[b] 는 무조건 서로 다른 값만 수행이 됨
// 따라서 default 로 return 은 2가 됨
int jlis(int a, int b)
{
    if (cache[a][b] != 0) return cache[a][b];
    int ret = 2;
    long long maxElement = max(A[a], B[b]);
    for (int nextA = a + 1; nextA < lenA; ++nextA)
        if (maxElement < A[nextA])
            ret = max(ret, jlis(nextA, b) + 1);
    for (int nextB = b + 1; nextB < lenB; ++nextB)
        if (maxElement < B[nextB])
            ret = max(ret, jlis(a, nextB) + 1);
    return cache[a][b] = ret;
}
int main()
{
    //freopen("JLIS.txt", "rt", stdin);
    scanf("%d", &T);
    A[0] = B[0] = NEGINF; // 64bit 값
    B[0]++;
    while (T--)
    {
        scanf("%d%d", &lenA, &lenB);
        for (int i = 1; i <= lenA; ++i)
            scanf("%lld", &A[i]);
        for (int i = 1; i <= lenB; ++i)
            scanf("%lld", &B[i]);
        lenA++, lenB++;
        memset(cache, 0, sizeof(cache));
        printf("%d\n", jlis(0, 0) - 2);
    }
    return 0;
}