#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 10010;
vector <int> adja[MAXN];
int parent[MAXN], freq[MAXN][2], freqUsed[MAXN][2];
int usedFreq;

void solve(int now)
{
    freq[now][1] = ++usedFreq;

    for (int i = 0; i < adja[now].size(); ++i) {
        int nextv = adja[now][i];
        if (parent[nextv] == -1) {
            parent[nextv] = now;
            int cho = 0;

            if (!freqUsed[now][0]) {
                cho = 0;
            }
            else {
                cho = 1;
            }

            freq[nextv][0] = freq[now][cho];
            freqUsed[now][cho] = freqUsed[nextv][0] = 1;

            if (adja[nextv].size() >= 2) {
                solve(nextv);   
            }
            else { //leaf node
                cho ^= 1;
                freq[nextv][1] = freq[now][cho];
                freqUsed[now][cho] = freqUsed[nextv][1] = 1;
            }
        }
    }
}

int main()
{
    int N;

    while (scanf("%d", &N) == 1) {

        usedFreq = 1;

        for (int i = 1; i <= N; ++i) {
            adja[i].clear();
            parent[i] = -1;
            freq[i][0] = freq[i][1] = -1;
            freqUsed[i][0] = freqUsed[i][1] = 0;
        }

        for (int i = 1; i < N; ++i) {
            int f, t;
            scanf("%d%d", &f, &t);
            adja[f].push_back(t);
            adja[t].push_back(f);
        }

        int startNode = 1;

        for (int i = 1; i <= N; ++i) {
            if (adja[i].size() >= 2) {
                startNode = i;
                break;
            }
        }

        parent[startNode] = 0;
        freq[startNode][0] = 1;
        solve(startNode);

        for (int i = 1; i <= N; ++i) {
            printf("%d %d\n", freq[i][0], freq[i][1]);
        }
    }
	return 0;
}