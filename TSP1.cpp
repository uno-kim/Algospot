#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
int T, N;
double dist[8][8], best;
int visit; // bit [7, 6, 5, 4, 3, 2, 1, 0]
int visitAll;
const double INF = 987654321.0;

// 마지막 방문이 here, visited 만큼 방문했을 때 현재의 최소 거리가 current
void shortest(int here, int visit, double current)
{
	if (current >= best) return;
	if (visit == visitAll)
	{
		best = min(best, current);
		return;
	}
	for (int there = 0; there < N; ++there)
	{
		if (visit & (1 << there)) continue;
		visit += (1 << there);
		shortest(there, visit, current + dist[here][there]);
		visit -= (1 << there);
	}
}

void solve()
{
	visit = 0;
	visitAll = (1 << N) - 1;
	best = INF;
	for (int here = 0; here < N; ++here)
	{
		visit += (1 << here);
		shortest(here, visit, 0.0);
		visit -= (1 << here);
	}
}

int main()
{
//	freopen("TSP1.txt", "rt", stdin);
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &N);
		for (int y = 0; y < N; ++y)
			for (int x = 0; x < N; ++x)
				scanf("%lf", &dist[y][x]);
		solve();
		printf("%lf\n", best);
	}
	return 0;
}