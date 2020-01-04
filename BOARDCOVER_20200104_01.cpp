#include <cstdio>
#include <cstring>
#include <ctime>

using namespace std;
int T, H, W;
int board[22][22]; // BLACK 과 WHITE 로 채워짐
char input[22];
const int BLACK = 0;
const int WHITE = 1;

int solve();

int main() {
//    freopen("../BOARDCOVER.txt", "rt", stdin);
//    clock_t start = clock();
    scanf("%d", &T);
    while (T--) {
        memset(board, BLACK, sizeof(board));
        scanf("%d%d", &H, &W);
        for (int y = 1; y <= H; ++y) {
            scanf("%s", &input[1]);
            for (int x = 1; x <= W; ++x) {
                board[y][x] = (input[x] == '#') ? BLACK : WHITE;
            }
        }
        printf("%d\n", solve());
    }
//    printf("time = %ld ms\n", clock() - start);
    return 0;
}

// (y, x) 가 주어졌을 때 다음 좌표 (ny, nx) 를 반환한다.
void nextPos(int y, int x, int &ny, int &nx) {
    for (int xx = x + 1; xx <= W; ++xx) {
        if (board[y][xx] == WHITE) {
            nx = xx, ny = y;
            return;
        }
    }
    for (int yy = y + 1; yy <= H; ++yy) {
        for (int xx = 1; xx <= W; ++xx) {
            if (board[yy][xx] == WHITE) {
                nx = xx, ny = yy;
                return;
            }
        }
    }
    ny = -1, nx = -1;
}

/* 다음과 같이 4가지가 존재함
1) ##   2)  #   3)  #    4) ##
   #       ##      ##       #
*/
const int dy[4][2] = {{0, 1},
                      {1, 1},
                      {1, 1},
                      {0, 1}};
const int dx[4][2] = {{1, 1},
                      {0, -1},
                      {0, 1},
                      {1, 0}};

// (y, x) 좌표에서 덮을 수 있는지
int canCover(int y, int x) {
    // 만약 좌표가 맨 마지막이면 종료
    if (y == -1 && x == -1) return 1;

    int ret = 0;
    // 4가지 방향으로 체크를 한다
    for (int i = 0; i < 4; ++i) {
        // 블록 3개 모두 커버 가능하면
        if (board[y + dy[i][0]][x + dx[i][0]] == WHITE &&
            board[y + dy[i][1]][x + dx[i][1]] == WHITE) {
            // 커버
            board[y + dy[i][0]][x + dx[i][0]] = BLACK;
            board[y + dy[i][1]][x + dx[i][1]] = BLACK;

            // 다음좌표 구해서 넘긴다
            int ny, nx;
            nextPos(y, x, ny, nx);
            ret += canCover(ny, nx);

            // 복원
            board[y + dy[i][0]][x + dx[i][0]] = WHITE;
            board[y + dy[i][1]][x + dx[i][1]] = WHITE;
        }
    }
    return ret;
}

int solve() {
    // board 판에서 WHITE 개수를 세서 3으로 나눠지지 않으면 종료
    int numWhite = 0;
    for (int y = 1; y <= H; ++y) {
        for (int x = 1; x <= W; ++x) {
            if (board[y][x] == WHITE) {
                numWhite++;
            }
        }
    }
    if (numWhite % 3 != 0) return 0;

    // 최초로 WHITE 인 곳부터 시작함
    int ny, nx;
    nextPos(0, 0, ny, nx);
    if (ny == -1 && nx == -1) return 0;
    return canCover(ny, nx);
}