#include <stdio.h>
#include <algorithm>
using namespace std;
int m, q, n;
char in[502][12]; // 원문에 출현할 수 있는 m 개의 단어
long long hashValue[502]; // 원문에 출현할 수 있는 단어의 hash value
double B[502]; // 각 단어가 문장의 처음에 출현할 확률 B[i] 가 m 개의 실수로 주어짐
double T[502][502]; // T[i][j] 는 i 번 단어의 다음 단어가 j 번 단어일 확률임
double M[502][502]; // M[i][j] 는 i 번 단어가 적힌 조각을 j 번 단어로 분류할 확률
char question[102][12]; // q 줄에서 분류기로 인식한 문장: I am a buy
int query[102]; // question 문장 I am a buy 를 0, 1, 2, 4 와 같이 in[] 에 대한 index 로 표시함
int Map[128];
void init() // hash value 를 만들기 위한 초기작업
{
    for (char c = 'A'; c <= 'Z'; ++c)
        Map[c] = c - 'A' + 1;
    for (char c = 'a'; c <= 'z'; ++c)
        Map[c] = c - 'a' + 27;
}
// 입력 string 을 hash value 로 변경, 단어의 길이는 10 이하임
long long makeHash(char in[12])
{
    long long ret = 0;
    for (int i = 0; in[i]; ++i)
        ret = ret * 53 + Map[in[i]];
    return ret;
}
// cache[][] : func(idx, n) 에 대한 cache 값
double cache[102][502];
void initCache()
{
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            cache[i][j] = -1.0;
}
// 0 1 2 3 4 가 주어졌을 때
// 0 1 2 4 로 인식되었을 경우
// f(0, 1) 은 0번째 글자에서 1이 0으로 인식될 확률
// f(0, 2) 는 0번째 글자에서 2가 0으로 인식될 확률
// f(1, 1) 은 1번째 글자에서 1이 1로 인식될 확률
// f(1, 3) 은 1번째 글자에서 3이 1로 인식될 확률
double func(int idx, int val)
{
    if (cache[idx][val] != -1) return cache[idx][val];
    double ret = 0.0;
/* main() 함수 내에서 미리 계산완료함
    if (idx == 0)
        return ret = B[val] * M[val][query[idx]];
*/
    for (int i = 0; i < m; ++i)
        ret = max(ret, func(idx - 1, i) * T[i][val] * M[val][query[idx]]);
    return cache[idx][val] = ret;
}
int choice[102]; // 최종 답안
// 최대 확률이 계산되었을 때, 이것을 가지고 실제로 선택한 값을 만들어낸다.
void reconstruct()
{
    double d = 0;
    for (int i = 0; i < m; ++i)
        if (d < cache[n - 1][i])
        {
            choice[n - 1] = i;
            d = cache[n - 1][i];
        }
    for (int idx = n - 1; idx > 0; --idx)
        for (int i = 0; i < m; ++i)
            if (cache[idx][choice[idx]] == (cache[idx - 1][i] * T[i][choice[idx]] * M[choice[idx]][query[idx]]))
            {
                choice[idx - 1] = i;
                break;
            }
}

int main()
{
    init();
    //freopen("OCR.txt", "rt", stdin);
    scanf("%d%d", &m, &q);
    for (int i = 0; i < m; ++i)
    {
        // I am a boy buy 로 들어오는 입력을 hash value 로 바꾼다
        scanf("%s", in[i]);
        hashValue[i] = makeHash(in[i]);
    }
    // 각 단어가 문장의 처음에 출현할 확률 B[i]
    for (int i = 0; i < m; ++i)
        scanf("%lf", &B[i]);
    // T[i][j] 는 i 번 단어의 다음 단어가 j 번 단어일 확률임
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%lf", &T[i][j]);
    // M[i][j] 는 i 번 단어가 적힌 조각을 j 번 단어로 분류할 확률
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%lf", &M[i][j]);
    // q 줄에 단어의 수 n 과, n 개의 단어로 분류기 인식 결과가 주어짐
    while(q--)
    {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            // I am a buy 를 입력받아, 0, 1, 2, 4 와 같이 hash value 로 변경하고
            // query[] 에 index 를 넣어준다
            scanf("%s", question[i]);
            long long val = makeHash(question[i]);
            for (int idx = 0; idx < m; ++idx)
                if (val == hashValue[idx])
                {
                    query[i] = idx;
                    break;
                }
        }
        initCache(); // cache 초기화
        for (int val = 0; val < m; ++val) //func(0, val) 에 대한 선 처리
            cache[0][val] = B[val] * M[val][query[0]];
        func(n, 0);
        reconstruct();
        // 최대 확률에 대한 실제 답안을 출력함
        for (int i = 0; i < n; ++i)
            printf("%s ", in[choice[i]]);
        printf("\n");
    }
    return 0;
}