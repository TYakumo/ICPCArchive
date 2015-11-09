#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 2010, MAXD = 22, INF = 200000000, MOD = 10;
int num[MAXN];
int DP[2][MOD][MAXD] = {};

int main()
{
    int N, D;

    while (scanf("%d%d", &N, &D)==2) {
        int total = 0;
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &num[i]);
            total += num[i];
            num[i] %= 10;
        }
        num[++N] = 0;
        ++D;

        for (int a = 0; a < MOD; ++a)
            for(int b = 0; b <= D; ++b)
                DP[0][a][b] = DP[1][a][b] = -INF;

        DP[0][0][0] = 0;

        int nowdp = 1;
        for (int i = 1; i <= N; ++i) {            

            for (int a = 0; a < MOD; ++a)
                for(int b = 0; b <= D; ++b)
                    DP[nowdp][a][b] = -INF;

            for (int j = 0; j < MOD; ++j)
                for(int d = 0; d <= D && d < i; ++d){
                        //new group
                    if (d+1 <= D) {
                        int newSave = j-((j+5)/MOD*MOD) + DP[nowdp^1][j][d];
                        DP[nowdp][num[i]][d+1] = max(newSave, DP[nowdp][num[i]][d+1]);
                    }

                    //stay the same
                    DP[nowdp][(j+num[i])%MOD][d] = max(DP[nowdp^1][j][d], DP[nowdp][(j+num[i])%MOD][d]);
                }

            nowdp ^= 1;
        }

        nowdp ^= 1;
        int bestSave = -INF;
        for (int d = D; d >= 1; --d)
            bestSave = max(bestSave, DP[nowdp][0][d]);

        printf("%d\n", total - bestSave);
    }

    return 0;
}
