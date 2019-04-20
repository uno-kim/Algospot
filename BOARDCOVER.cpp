#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int T, H, W;
char board[22][22];
// (y, x) 가 주어졌을 때 다음 빈칸 (ny, nx) 를 반환
void next(int y, int x, int& ny, int& nx)
{
	for (int xx = x + 1; xx <= W; ++xx)
		if (board[y][xx] == '.')
		{
			ny = y, nx = xx;
			return;
		}
	for (int yy = y + 1; yy <= H; ++yy)
		for (int xx = 1; xx <= W; ++xx)
			if (board[yy][xx] == '.')
			{
				ny = yy, nx = xx;
				return;
			}
	ny = H + 1, nx = 0;
}
/*
  블록의 상대적인 위치
  dy[direction][block number]
  d0   d1   d2   d3  
  #     #   ##   ##
  ##   ##    #   #
*/
const int dy[4][2] = { 
	{1, 1}, // d0
	{1, 1}, // d1
    {0, 1}, // d2
    {1, 0} }; // d3
const int dx[4][2] = {
	{0, 1}, // d0
	{0, -1}, // d1
	{1, 1}, // d2
	{0, 1} }; // d3

// (y, x) 좌표에 d 방향으로 블록을 놓을 수 있는지
bool canCover(int y, int x, int d)
{
	for (int i = 0; i < 2; ++i)
	{
		int ny = y + dy[d][i];
		int nx = x + dx[d][i];
		if (board[ny][nx] != '.')
			return false;
	}
	return true;
}

void set(int y, int x, int d, bool restore)
{
	char ch = restore ? '.' : '#';
	board[y][x] = ch;
	for (int i = 0; i < 2; ++i)
	{
		int ny = y + dy[d][i];
		int nx = x + dx[d][i];
		board[ny][nx] = ch;
	}
}


// (y, x) 점에 블록을 놓을 수 있는 경우의 수
int cover(int y, int x)
{
	// 마지막 까지 이동한 경우는 종료
	if (y == H + 1) return 1;
	int ret = 0;
	if (board[y][x] == '.')
	{
		for (int d = 0; d < 4; ++d) // 4가지 형태
		{
			// d = 0 일 떼 채울 수 있는 경우
			if (canCover(y, x, d))
			{
				set(y, x, d, false); // set
				int ny, nx;
				next(y, x, ny, nx);
				ret += cover(ny, nx);
				set(y, x, d, true); // restore
			}
		}
	}
	return ret;
}

int solve()
{
	int ret = 0;
	for (int y = 1; y <= H; ++y)
		for (int x = 1; x <= W; ++x)
			if (board[y][x] == '.')
			{
				ret = cover(y, x);
				return ret;
			}
	return ret;
}

int main()
{
//	freopen("BOARDCOVER.txt", "rt", stdin);
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &H, &W);
		memset(board, 0, sizeof(board));
		for (int y = 1; y <= H; ++y)
			scanf("%s", &board[y][1]);
		printf("%d\n", solve());
	}
	return 0;
}