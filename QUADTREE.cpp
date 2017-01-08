#include <stdio.h>
#include <string.h>
int T;
char in[1002], temp[1002];
int quadtree(char arr[], int idx)
{
    if (arr[idx] != 'x') return 1;
    int len1 = quadtree(arr, idx + 1);
    int len2 = quadtree(arr, idx + 1 + len1);
    int len3 = quadtree(arr, idx + 1 + len1 + len2);
    int len4 = quadtree(arr, idx + 1 + len1 + len2 + len3);
    for (int i = 0; i < len3; ++i)
        temp[idx + i + 1] = arr[idx + 1 + len1 + len2 + i];
    for (int i = 0; i < len4; ++i)
        temp[idx + i + 1 + len3] = arr[idx + 1 + len1 + len2 + len3 + i];
    for (int i = 0; i < len1; ++i)
        temp[idx + i + 1 + len3 + len4] = arr[idx + 1 + i];
    for (int i = 0; i < len2; ++i)
        temp[idx + i + 1 + len3 + len4 + len1] = arr[idx + 1 + len1 + i];
    int len = len1 + len2 + len3 + len4;
    for (int i = 0; i < len; ++i)
        arr[idx + i + 1] = temp[idx + i + 1];
    return len + 1;
}
int main()
{
    //freopen("QUADTREE.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", in);
        quadtree(in, 0);
        printf("%s\n", in);
    }
    return 0;
}