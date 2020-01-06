#include <cstdio>
#include <algorithm>
#include <cstring>
#include <ctime>

using namespace std;
int T;
// 여기서 실수했음 CLOCK 이 16개인데..
int clocks[16]; // 0, 1, 2, 3 으로 세팅
int best; // 최소로 누를는 회수
const int INF = 987654321;
const int switches[10][6] = {{0, 1,  2,  -1, -1, -1},
                             {3, 7,  9,  11, -1, -1},
                             {4, 10, 14, 15, -1, -1},
                             {0, 4,  5,  6,  7,  -1},
                             {6, 7,  8,  10, 12, -1},
                             {0, 2,  14, 15, -1, -1},
                             {3, 14, 15, -1, -1, -1},
                             {4, 5,  7,  14, 15, -1},
                             {1, 2,  3,  4,  5,  -1},
                             {3, 4,  5,  9,  13, -1}};

int solve();

int main() {
//    freopen("../CLOCKSYNC.txt", "rt", stdin);
//    clock_t start = clock();
    scanf("%d", &T);
    while (T--) {
        for (int i = 0; i < 16; ++i) {
            scanf("%d", &clocks[i]);
            clocks[i] = (clocks[i] / 3) % 4; // 0, 1, 2, 3 으로 값을 변경
        }
        printf("%d\n", solve());
    }
//    printf("time = %ld ms\n", clock() - start);
    return 0;
}

bool isSynchronized() {
    int sum = 0;
    for (int i = 0; i < 16; ++i)
        sum += clocks[i];
    return sum == 0;
}

// switchIndex 번째 스위치를 count 만큼 돌려 시계를 회전시킴. restore 는 역으로 회전시킴
void clockSync(int switchIndex, int count, bool restore) {
    if (count == 0) return;
    if (restore) {
        count = -count;
    }
    for (int i = 0; switches[switchIndex][i] != -1; ++i) {
        int clockIndex = switches[switchIndex][i];
        clocks[clockIndex] = (clocks[clockIndex] + 4 + count) % 4;
    }
}

// 현재 pushCount 만큼 누른 상태에서, switchIndex 번째 스위치를 컨트롤 할 때 최소 가지수
int push(int switchIndex, int pushCount) {
    // 시계가 모두 정렬되었으면 종료
    if (isSynchronized()) {
        return pushCount;
    }
    // 시계가 정렬 안되었는데, 스위치가 10번 눌러졌으면 INF 리턴
    if (switchIndex == 10) {
        return INF;
    }
    int ret = INF;
    // switchIndex 번째 스위치를 0 ~ 3 번 누름
    for (int i = 0; i <= 3; ++i) {
        // clocks 을 변경함
        clockSync(switchIndex, i, false);
        // 다음번 idx 값을 계산
        ret = min(ret, push(switchIndex + 1, pushCount + i));
        // clocks 을 원위치
        clockSync(switchIndex, i, true);
    }
    return ret;
}

int solve() {
    int ret = push(0, 0);
    if (ret == INF) ret = -1;
    return ret;
}