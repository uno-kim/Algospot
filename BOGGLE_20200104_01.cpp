#include <cstdio>
#include <cstring>
#include <ctime>

using namespace std;
int T, N;
char board[7][7], input[11];
int cache[7][7][11];

const int dy[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
const int dx[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

bool solve();
int hasWord(int y, int x, int idx);

int main() {
//    freopen("../BOGGLE.txt", "rt", stdin);
//    clock_t start = clock();
    scanf("%d", &T);
    while (T--) {
        for (int y = 1; y <= 5; ++y) {
            scanf("%s", &board[y][1]);
        }
        scanf("%d", &N);
        while (N--) {
            scanf("%s", input);
            printf("%s %s\n", input, solve() ? "YES" : "NO");
        }
    }
//    printf("time = %ld ms\n", clock() - start);
    return 0;
}

bool solve() {
    memset(cache, -1, sizeof(cache));
    for (int y = 1; y <= 5; ++y) {
        for (int x = 1; x <= 5; ++x) {
            if (hasWord(y, x, 0)) {
                return true;
            }
        }
    }
    return false;
}

// (y, x) 좌표에 input[idx] 에 해당하는 글자가 존재하는지 여부
int hasWord(int y, int x, int idx) {
    int& ret = cache[y][x][idx];
    if (ret != -1) return ret;
    ret = 0;
    // 글자가 다르면 false 리턴
    if (board[y][x] != input[idx]) return ret;
    // 마지막 글자이면 true 리턴
    if (input[idx + 1] == 0) return ret = 1;
    // 8방향으로 돌면서 다음글자 검색
    for (int d = 0; d < 8; ++d) {
        int ny = y + dy[d];
        int nx = x + dx[d];
        if (hasWord(y + dy[d], x + dx[d], idx + 1)) {
            return ret = 1;
        }
    }
    return ret;
}