#include <cstdio>
#include <algorithm>
#include <cstring>
#include <ctime>

using namespace std;
int T;
unsigned int clocks; // 시계의 상태를 32bit 로 표시함 (16개 * 4개의 status 인 2비트)
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
    unsigned int input;
    scanf("%d", &T);
    while (T--) {
        clocks = 0;
        for (unsigned int i = 0; i < 16; ++i) {
            scanf("%ud", &input);
            input = (input / 3) % 4;
            clocks |= (input << (i * 2));
        }
        printf("%d\n", solve());
    }
//    printf("time = %ld ms\n", clock() - start);
    return 0;
}

// switchIndex 번째 스위치를 1회 눌러 시계를 회전시킴
void clockSync(int switchIndex) {
    for (int i = 0; switches[switchIndex][i] != -1; ++i) {
        int clockIndex = switches[switchIndex][i];
        unsigned int shift = clockIndex * 2;
        unsigned int value = ((clocks & 3u << shift) >> shift);
        value = (value + 1) % 4;
        clocks = (clocks & ~(3u << shift)) + (value << shift);
    }
}

// 현재 pushCount 만큼 누른 상태에서, switchIndex 번째 스위치를 컨트롤 할 때 최소 가지수
int push(int switchIndex, int pushCount) {
    // 시계가 모두 정렬되었으면 종료
    if (clocks == 0) {
        return pushCount;
    }
    // 시계가 정렬 안되었는데, 스위치가 10번 눌러졌으면 INF 리턴
    if (switchIndex == 10) {
        return INF;
    }
    int ret = INF;
    for (int i = 0; i < 4; ++i) {
        // 다음번 idx 값을 계산
        ret = min(ret, push(switchIndex + 1, pushCount + i));
        // 스위치를 1회 누른다, for loop 4회를 거치면 4회가 눌러지게 되며 원상복구되기 때문에
        // restore 를 안해도 됨
        clockSync(switchIndex);
    }
    return ret;
}

int solve() {
    int ret = push(0, 0);
    if (ret == INF) ret = -1;
    return ret;
}