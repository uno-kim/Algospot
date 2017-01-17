#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int MAX_N = 987654321;
int T, cache[10002], len;
char in[10002];

int difficulty(int idx, int len) 
{
    bool ret = true;
    int diff = in[idx + 1] - in[idx];
    for (int i = 1; i <= len - 2; ++i)
        if (in[idx + i + 1] - in[idx + i] != diff)
        {
            ret = false;
            break;
        }
    if (ret)
    {
        if (diff == 0) return 1;
        if (diff == 1 || diff == -1) return 2;
        return 5;
    }
    ret = true;
    int loop = (len - 1) / 2;
    for (int i = 0; i < loop; ++i)
        if (in[idx + i * 2] != in[idx + i * 2 + 2])
        {
            ret = false;
            break;
        }
    if (ret && len > 3)
        if (in[idx + 1] != in[idx + 3])
            ret = false;
    if (ret) return 4;
    return 10;
}

// in[idx] 에서부터 시작하는 최소 난이도의 합
int func(int idx)
{
    //if (idx == len) return 0;
    int &ret = cache[idx];
    if (ret != -1) return ret;
    ret = MAX_N;
    for (int i = 3; i <= 5; ++i)
        if (len - idx >= i)
            ret = min(ret, difficulty(idx, i) + func(idx + i));
    return ret;
}

int main()
{
    //freopen("PI.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", in);
        len = (int)strlen(in);
        memset(cache, -1, sizeof(cache));
        cache[len] = 0;
        printf("%d\n", func(0));
    }
    return 0;
}