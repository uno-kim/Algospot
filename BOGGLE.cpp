#include <stdio.h>
#include <string.h>
using namespace std;
const int dy[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
const int dx[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
int T, N, L, cache[5][5][10];
char board[5][6], input[11];

// [y, x] 좌표에 input[idx] 에 해당하는 글자가 존재하는지
int hasChar(int y, int x, int idx)
{
    if (input[idx] != board[y][x]) return 0;
    if (idx == L - 1) return 1; // 마지막 글자까지 맞았으면 성공
    int &ret = cache[y][x][idx];
    if (ret != -1) return ret;
    ret = 0;
    for (int direction = 0; direction < 8; ++direction)
    {
        int ny = y + dy[direction];
        int nx = x + dx[direction];
        if (ny >= 0 && ny < 5 && nx >= 0 && nx < 5)
            if (hasChar(ny, nx, idx + 1) == 1)
                return ret = 1;
    }
    return ret;
}

bool solve()
{
    memset(cache, -1, sizeof(cache));
    for (int y = 0; y < 5; ++y)
        for (int x = 0; x < 5; ++x)
            if (hasChar(y, x, 0) == 1)
                return true;
    return false;
}

int main()
{
    //freopen("BOGGLE.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        for (int i = 0; i < 5; ++i)
            scanf("%s", &board[i][0]);
        scanf("%d", &N);
        for (int i = 0; i < N; ++i)
        {
            scanf("%s", input);
            L = strlen(input);
            bool ret = solve();
            printf("%s %s\n", input, ret ? "YES" : "NO");
        }
    }
    return 0;
}
