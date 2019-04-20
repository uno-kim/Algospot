#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <string.h>
using namespace std;
const int dy[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
const int dx[8] = { 1, 0, -1, -1, -1, 0, 1, 1 };
const char* ans[2] = { "NO\n", "YES\n" };

int T, N;
char board[7][7];
char input[11];
int cache[7][7][11];

// (y, x) 좌표에 input[idx] 에 해당하는 글자가 존재하는지 여부
int hasWord(int y, int x, int idx)
{
	int& ret = cache[y][x][idx];
	if (ret != -1) return ret;
	ret = 0;

	if (board[y][x] != input[idx]) return ret;
	if (input[idx + 1] == 0) return ret = 1;
	for (int d = 0; d < 8; ++d)
	{
		int ny = y + dy[d];
		int nx = x + dx[d];
		if (hasWord(ny, nx, idx + 1))
			return ret = 1;
	}
	return ret;
}

bool solve()
{
	memset(cache, -1, sizeof(cache));
	for (int y = 1; y <= 5; ++y)
		for (int x = 1; x <= 5; ++x)
			if (hasWord(y, x, 0))
				return true;
	return false;
}

int main() 
{
//	freopen("BOGGLE.txt", "rt", stdin);
	scanf("%d", &T);
	while (T--)
	{
		for (int y = 1; y <= 5; ++y)
			scanf("%s", &board[y][1]);
		scanf("%d", &N);
		for (int i = 0; i < N; ++i)
		{
			scanf("%s", input);
			printf("%s ", input);
			bool success = solve();
			printf(ans[success ? 1 : 0]);
		}
	}
	return 0;
}