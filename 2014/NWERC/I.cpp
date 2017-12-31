#include <cstdio>
#include <utility>
#include <vector>
#include <cstring>
#include <algorithm>

const int MAXP = 1;
const int MAXPRIME = 2753;
const int PRIME[MAXP] = {MAXPRIME}; //loading factor around 0.3 => MAXCOMB/PRIME
const int FILTERSIZE = (MAXPRIME+63)/64;
const int MAXCOMB = 720;
const int MAXN = 14, MAXL = 8;
using VecType = std::vector<int>;

long long dist[MAXN][MAXN];

long long valueTable[MAXN][MAXCOMB];
long long bloomfilter[MAXN][FILTERSIZE];
int tableCounter[MAXN];

int N;
int chosen[MAXN];
int notChosen[MAXN];
long long L;
std::vector< VecType > combinations[MAXL];
VecType temp;

void initializeValueTable()
{
    memset(tableCounter, 0, sizeof(tableCounter));
    memset(bloomfilter, 0, sizeof(bloomfilter));
}

void organizeValueTable()
{
    for (int i = 0; i < MAXN; ++i)
        if (tableCounter[i]) {
            std::sort(valueTable[i], valueTable[i] + tableCounter[i]);
        }
}

void setValueTable(int tableSet, long long value)
{   
    valueTable[tableSet][tableCounter[tableSet]++] = value;

    for (int i = 0; i < MAXP; ++i) {
        long long modValue = value%PRIME[i];
        long long bQValue = modValue/64;
        long long bRValue = modValue%64;
        bloomfilter[tableSet][bQValue] |= (1<<bRValue);
    }
}

int getValueTable(int tableSet, long long value)
{
    for (int i = 0; i < MAXP; ++i) {
        long long modValue = value%PRIME[i];
        long long bQValue = modValue/64;
        long long bRValue = modValue%64;
        if ( (bloomfilter[tableSet][bQValue] & (1<<bRValue)) == 0 ) {
            return 0;
        }
    }

    int low = 0, upper = tableCounter[tableSet]-1, mid = 0;

    while (low <= upper) {
        mid = (low+upper) / 2;

        if (valueTable[tableSet][mid] < value) {
            low = mid+1;
        } else if (valueTable[tableSet][mid] > value) {
            upper = mid-1;
        } else {
            return 1;
        }
    }

    return 0;
}

void generateCombinations(int depth, int len, int bitmask)
{
    if (depth == len) {
        combinations[len].push_back(temp);
        return ;
    }

    for (int i = 0; i < len; ++i) {
        if ((bitmask & (1<<i)) == 0) {
            temp.push_back(i);
            generateCombinations(depth+1, len, bitmask|(1<<i));
            temp.pop_back();
        }
    }
}

void searchPossibility(int now, int depth, int ndepth, int start, int targetDepth, bool *possible)
{   
    // if (now == start) {
    //     searchPossibility(now+1, depth, ndepth, start, targetDepth, possible);
    //     return ;
    // }   

    if (*possible) {
        return ;
    }

    if (now == N) {
        initializeValueTable();

        for (int i = 0; i < combinations[targetDepth].size(); ++i) {
            int previousNode = start;
            long long totalDistance = 0;
            for (int a = 0; a < targetDepth; ++a) {
                int now = chosen[ combinations[targetDepth][i][a] ];
                totalDistance += dist[previousNode][now];
                previousNode = now;
                // if (totalDistance > L) {
                //     break;
                // }
            }

            setValueTable(previousNode, totalDistance);
        }

        organizeValueTable();

        for (int middle = 0; middle < targetDepth; ++middle) {
            int middlePoint = chosen[middle];
            int remainingLength = N-1 - targetDepth;

            for (int i = 0; i < combinations[remainingLength].size(); i++) {
                long long totalDistance = 0;
                int previousNode = middlePoint;

                for (int a = 0; a < remainingLength; ++a) {
                    int now = notChosen[ combinations[remainingLength][i][a] ];
                    totalDistance += dist[previousNode][now];
                    previousNode = now;
                }

                totalDistance += dist[previousNode][start];
                if (getValueTable(middlePoint, L-totalDistance) != 0) {
                    *possible = true;
                    return ;
                }
            }
        }

        return ;
    }

    if (depth < targetDepth) {
        chosen[depth] = now;
        searchPossibility(now+1, depth+1, ndepth, start, targetDepth, possible);
    }
    
    if (ndepth < N-1-targetDepth) {  
        notChosen[ndepth] = now;
        searchPossibility(now+1, depth, ndepth+1, start, targetDepth, possible);
    }
}

int main()
{
    for (int len = 0; len < MAXL; ++len) {
        generateCombinations(0, len, 0);
    }

    while (scanf("%d%lld", &N, &L) == 2) {

        for (int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j) {
                scanf("%lld", &dist[i][j]);
            }

        bool possible = false;

        int len = (N-1+1)/2;
        searchPossibility(1, 0, 0, 0, len, &possible);

        printf("%s\n", possible ? "possible" : "impossible");
    }

    return 0;
}