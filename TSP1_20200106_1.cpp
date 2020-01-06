#include <cstdio>
#include <algorithm>
#include <cstring>
#include <ctime>

using namespace std;
int T;
int N; // 3 <= N <= 8 도시의 수
double dist[8][8]; // i ~ j 도시사이 거리 (0 ~ 1415 사이 소수점)
const double INF = 987654321.0;
double best;

double solve();

int main() {
//    freopen("../TSP1.txt", "rt", stdin);
//    clock_t start = clock();
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        for (int y = 0; y < N; ++y) {
            for (int x = 0; x < N; ++x) {
                scanf("%lf", &dist[y][x]);
            }
        }
        printf("%.10lf\n", solve());
    }
//    printf("time = %ld ms\n", clock() - start);
    return 0;
}

// current : 현재 방문중인 도시
// visited[] : 방문한 도시
// distance : 현재까지의 방문한 거리
double tsp(int current, bool visit[8], double distance) {
    // 현재까지 방문한 거리가 이미 후보답을 넘어서면 버린다.
    if (distance >= best) {
        return distance;
    }
    double ret = INF;
    // 다음 방문할 도시를 찾는다.
    int begin = -1;
    for (int i = 0; i < N; ++i) {
        if (!visit[i]) {
            begin = i;
            break;
        }
    }
    // 모두 방문했으면 종료
    if (begin == -1) {
        return distance;
    }
    for (int next = begin; next < N; ++next) {
        if (!visit[next]) {
            // 방문
            visit[next] = true;
            double candidate = tsp(next, visit, distance + dist[current][next]);
            ret = min(ret, candidate);
            // 원복
            visit[next] = false;
        }
    }
    return ret;
}

double solve() {
    best = INF;
    for (int i = 0; i < N; ++i) {
        bool visited[8] = {false,};
        visited[i] = true;
        best = min(best, tsp(i, visited, 0.0));
    }
    return best;
}