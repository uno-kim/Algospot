#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;
int T, N, cache[102][102];
char wild[102], file[102];
struct Ans
{ char file[102]; };

int match(int w, int f)
{
    if (wild[w] == 0 && file[f] == 0) return 1; // ��� �� �Ϸ�� true
    if (file[f] == 0 || wild[w] == 0) return 0; // ���ʸ� �Ϸ�Ǹ� false
    int &ret = cache[w][f];
    if (ret != -1) return ret;
    ret = 0;
    if (wild[w] != '*') // ������ ���ƾ� ��
    {
        if (wild[w] == file[f] || wild[w] == '?')
            ret = match(w + 1, f + 1); // ���� ���� ��
    }
    else 
    {
        if (wild[w + 1] == 0) return ret = 1; // ���࿡ * �� �������̸� ������ ����
        for (int i = 0; file[f + i] != 0; ++i)
            if (match(w + 1, f + i)) // * ���� ���ں��� file �� ���� ��� ���ڵ�� ��
                return ret = 1;
    }
    return ret;
}

bool comp(const Ans a, const Ans b)
{
    return strcmp(a.file, b.file) < 0;
}

int main()
{
    //freopen("WILDCARD.txt", "rt", stdin);
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", wild);
        scanf("%d", &N);
        vector<Ans> A;
        for (int i = 0; i < N; ++i)
        {
            scanf("%s", file);
            memset(cache, -1, sizeof(cache));
            if (match(0, 0))
            {
                Ans ans;
                strcpy(ans.file, file);
                A.push_back(ans);
            }
        }
        sort(A.begin(), A.end(), comp);
        for (int i = 0; i < A.size(); ++i)
            printf("%s\n", A[i].file);
    }
    return 0;
}