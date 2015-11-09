#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

const int MAXS = 20;
char str[MAXS];

int main()
{
    int N, D;

    while (scanf("%d", &N)==1) {      

        map <string, int> mapCount[2];

        for (int c = 0; c < 2; ++c)
            for (int i = 0; i < N; ++i) {
                scanf("%s", str);
                ++mapCount[c][ str ];
            }

        int ans = 0;

        map <string, int> :: iterator iter = mapCount[0].begin();

        while (iter != mapCount[0].end()) {
            ans += min(iter->second, mapCount[1][iter->first]);
            ++iter;
        }

        printf("%d\n", ans);
    }

    return 0;
}
