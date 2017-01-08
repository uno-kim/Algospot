#include <stdio.h>
int T, in[16];
const int switchs[10][6] = 
{
    { 0, 1, 2, -1, -1, -1 }, // 0
    { 3, 7, 9, 11, -1, -1 }, // 1
    { 4, 10, 14, 15, -1, -1 }, // 2
    { 0, 4, 5, 6, 7, -1 }, // 3
    { 6, 7, 8, 10, 12, -1 }, // 4
    { 0, 2, 14, 15, -1, -1 }, // 5
    { 3, 14, 15, -1, -1, -1 }, // 6
    { 4, 5, 7, 14, 15, -1 }, // 7
    { 1, 2, 3, 4, 5, -1 }, // 8
    { 3, 4, 5, 9, 13, -1 } // 9
};
// idx 번째 스위치를 rotate 만큼 돌린다.
int push(int idx, int rotate)
{
    if (rotate == 0) return 0;
    for (int i = 0; switchs[idx][i] != -1; ++i)
        in[switchs[idx][i]] = (in[switchs[idx][i]] + rotate) % 4;
    return rotate;
}

int solve()
{
    int ret = 0;
    // 4번 clock
    if (in[8] != in[12]) return -1;
    ret += push(4, (4 - in[8]) % 4);
    // 1번 clock
    ret += push(1, (4 - in[11]) % 4);
    // 9번 clock
    if (in[9] != in[13]) return -1;
    ret += push(9, (4 - in[13]) % 4);
    // 3번 clock
    ret += push(3, (4 - in[6]) % 4);
    // 7번 clock
    ret += push(7, (4 - in[7]) % 4);
    // 8번 clock
    ret += push(8, (4 - in[5]) % 4);
    // 2번 clock
    if (in[4] != in[10]) return -1;
    ret += push(2, (4 - in[4]) % 4);
    // 0번 clock
    ret += push(0, (4 - in[1]) % 4);
    // 5번 clock
    if (in[0] != in[2]) return -1;
    ret += push(5, (4 - in[0]) % 4);
    // 6번 clock
    if (in[3] != in[14] || in[14] != in[15]) return -1;
    ret += push(6, (4 - in[3]) % 4);
    return ret;
}

int main()
{
    //freopen("CLOCKSYNC.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        for (int i = 0; i < 16; ++i)
        {
            scanf("%d", &in[i]);
            in[i] = (in[i] / 3) % 4;
        }
        printf("%d\n", solve());
    }
    return 0;
}