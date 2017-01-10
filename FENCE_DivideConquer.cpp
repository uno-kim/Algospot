#include <stdio.h>
#include <algorithm>
using namespace std;
int T, N, H[20002];
// H[left,right] 구간에서 찾아낼 수 있는 가장 큰 사각형의 넓이
int func(int left, int right)
{
    if (left == right) return H[left];
    int mid = (left + right) / 2;
    int ret = max(func(left, mid), func(mid + 1, right));
    // [mid, mid + 1] 중앙에 걸쳐있는 사각형부터 넓혀 나감
    int minHeight = min(H[mid], H[mid + 1]);
    ret = max(ret, minHeight * 2);
    int lo = mid, hi = mid + 1; // lo, hi 는 포인터
    while (left < lo || hi < right) // 하나라도 확장이 가능하면
    {
        while (lo - 1 >= left && H[lo - 1] >= minHeight) lo--;
        while (hi + 1 <= right && minHeight <= H[hi + 1]) hi++;
        ret = max(ret, minHeight * (hi - lo + 1));
        // 이제 좌,우측에서 minHeight 보다 작은 값 중에서 큰 값을 minHeight 로 갱신
        int tempHeight = -1;
        if (lo - 1 >= left) tempHeight = H[lo - 1];
        if (hi + 1 <= right) tempHeight = max(tempHeight, H[hi + 1]);
        if (tempHeight == -1) break;
        minHeight = tempHeight;
    }
    return ret;
}

int main()
{
    //freopen("FENCE1.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &N);
        for (int i = 0; i < N; ++i)
            scanf("%d", &H[i]);
        printf("%d\n", func(0, N - 1));
    }
    return 0;
}