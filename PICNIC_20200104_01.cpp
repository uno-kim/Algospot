#include <cstdio>
#include <cstring>
#include <ctime>

using namespace std;
int T, N, M, a, b;
bool areFriends[10][10]; // a, b 가 친구인지 여부
bool taken[10]; // 짝을 찾았는지 여부
int pick(bool picked[10]);

int main() {
//    freopen("../PICNIC.txt", "rt", stdin);
//    clock_t start = clock();
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &N, &M);
        memset(areFriends, false, sizeof(areFriends));
        for (int m = 0; m < M; ++m) {
            scanf("%d%d", &a, &b);
            areFriends[a][b] = areFriends[b][a] = true;
        }
        memset(taken, false, sizeof(taken));
        printf("%d\n", pick(taken));
    }
//    printf("time = %ld ms\n", clock() - start);
    return 0;
}

// 이미 짝지어진 사람들이 주어졌을 때, 남은 사람들끼리 짝을 지을 수 있는 가지수
int pick(bool picked[10]) {
    int begin = -1;
    for (int i = 0; i < N; ++i) {
        if (!picked[i]) {
            begin = i;
            break;
        }
    }
    // 모두 선택되었으면 리턴
    if (begin == -1) return 1;

    int ret = 0;
    for (int next = begin + 1; next < N; ++next) {
        // next 가 짝지어지지 않았고 begin 과 친구이면 짝지어주고 재귀로 넘김
        if (!picked[next] && areFriends[begin][next]) {
            picked[begin] = picked[next] = true;
            ret += pick(picked);
            picked[begin] = picked[next] = false;
        }
    }
    return ret;
}