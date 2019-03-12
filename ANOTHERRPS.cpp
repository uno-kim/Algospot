#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;
const char ANS[3] = { 'P', 'S', 'R' };
unsigned long long N;
unsigned long long arr[30][2];

int f(unsigned long n) {
    if (n < 3) return (int)n;
    int index = 0;
    for (;; index++) {
        if (n < arr[index][1]) break;
    }
    return (f(n - arr[index][0]) + 1) % 3;
}

int main() {
    arr[0][0] = 1;
    arr[0][1] = arr[0][0] * 3;
    for (unsigned long long i = 1; arr[i - 1][1] <= 1000000000000; ++i) {
        arr[i][0] = arr[i - 1][0] * 3;
        arr[i][1] = arr[i][0] * 3;
    }
    while (1) {
        scanf("%lu", &N);
        if (N == 0) return 0;
        printf("%c\n", ANS[f(N - 1)]);
    }
    return 0;
}
