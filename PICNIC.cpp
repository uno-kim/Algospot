#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int T, N, M, u, v, ans;
bool areFriends[10][10];
// taken[i] : i 번째 학생이 짝을 찾았으면 true
int countParings(bool taken[10])
{
    int from = -1;
    for (int i = 0; i < N; ++i)
        if (!taken[i])
        {
            from = i;
            break;
        }
    if (from == -1) return 1; // 짝을 모두 찾은 경우
    int ret = 0;
    for (int to = from + 1; to < N; ++to)
        if (!taken[to] && areFriends[from][to])
        {
            taken[from] = taken[to] = true;
            ret += countParings(taken);
            taken[from] = taken[to] = false;
        }
    return ret;
}

int main()
{
    //freopen("PICNIC.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &N, &M);
        memset(areFriends, false, sizeof(areFriends));
        for (int i = 0; i < M; ++i)
        {
            scanf("%d%d", &u, &v);
            areFriends[u][v] = areFriends[v][u] = true;
        }
        bool taken[10] = { false, };
        printf("%d\n", countParings(taken));
    }
    return 0;
}
