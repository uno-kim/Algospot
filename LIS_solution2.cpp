#include <stdio.h>
using namespace std;
int T, N, in, C[502], lenC; // C[i] = 지금까지 만든 부분 배열이 갖는 길이 i인 증가 부분 수열 중 최소의 마지막 값
int main()
{
    //freopen("LIS.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &N);
        scanf("%d", &C[0]); // C[0] 에 처음 입력값을 바로 넣는다.
        lenC = 1;
        for (int i = 1; i < N; ++i)
        {
            scanf("%d", &in);
            for (int j = 0; j < lenC; ++j)
                if (C[j] >= in)
                {
                    C[j] = in;
                    break;
                }
            if (C[lenC - 1] < in)
                C[lenC++] = in;
        }
        printf("%d\n", lenC);
    }
    return 0;
}