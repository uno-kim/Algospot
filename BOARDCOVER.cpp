#include <stdio.h>
using namespace std;
int T, H, W;
char board[50][51];
// (y, x) 가 주어졌을 때 다음 빈칸을 (ny, nx) 로 반환
void nextPos(int y, int x, int& ny, int &nx)
{
    for (int xx = x + 1; xx < W; ++xx)
        if (board[y][xx] == '.')
        {
            ny = y, nx = xx;
            return;
        }
    for (int yy = y + 1; yy < H; ++yy)
        for (int xx = 0; xx < W; ++xx)
            if (board[yy][xx] == '.')
            {
                ny = yy, nx = xx;
                return;
            }
    ny = H, nx = 0;
}
// 블록의 상대적인 위치 (y + dy, x + dx)
const int dy[4][2] = { { 1, 1 }, { 1, 1 },{ 0, 1 },{ 0, 1 } };
const int dx[4][2] = { { 0, -1 }, { 0, 1 },{ 1, 0 },{ 1, 1 } };

// rotation = 0, 1, 2, 3
bool canCover(int y, int x, int r)
{
    for (int i = 0; i < 2; ++i)
    {
        int ny = y + dy[r][i];
        int nx = x + dx[r][i];
        if (ny < 0 || ny >= H || nx < 0 || nx >= W || board[ny][nx] == '#') return false;
    }
    return true;
}

void set(int y, int x, int r, char ch)
{
    board[y][x] = ch;
    for (int i = 0; i < 2; ++i)
    {
        int ny = y + dy[r][i];
        int nx = x + dx[r][i];
        board[ny][nx] = ch;
    }
}

// (y, x) 위치에서 놓을 수 있는 가지수
int func(int y, int x)
{
    // 끝까지 완료하였으면 종료
    if (y == H) return 1;
    int ret = 0;
    // 4개 블록을 돌려가면서 cover 한다
    for (int i = 0; i < 4; ++i)
    {
        // 만약에 cover 가능하면 cover
        if (canCover(y, x, i))
        {
            // cover
            set(y, x, i, '#');
            int ny, nx;
            nextPos(y, x, ny, nx);
            ret += func(ny, nx);
            // restore
            set(y, x, i, '.');
        }
    }
    return ret;
}

int solve()
{
    int white = 0;
    for (int y = 0; y < H; ++y)
        for (int x = 0; x < W; ++x)
            if (board[y][x] == '.')
                white++;
    if ((white % 3) != 0) return 0;
    int y, x;
    nextPos(0, -1, y, x);
    return func(y, x);
}

int main()
{
    //freopen("BOARDCOVER.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &H, &W);
        for (int y = 0; y < H; ++y)
            scanf("%s", &board[y][0]);
        printf("%d\n", solve());
    }
    return 0;
}