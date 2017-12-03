#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <iostream>

const int MAXN = 101, MAX_DEPTH = MAXN;

std::vector <int> adja[MAXN];
bool run[MAX_DEPTH][MAXN];
int avail[3][MAXN][MAXN];
int used[MAXN][MAXN];
int N, M;
int step[3];

void availCalculate(int start, int now, int step, int curAdja[][MAXN], int targetStep)
{
	if (step == targetStep) {
		curAdja[start][now] = 1;
		return ;
	}

	if (run[step][now]) {
		return ;
	}

	run[step][now] = true;

	for (int i = 0; i < adja[now].size(); ++i) {
		int nextv = adja[now][i];
		availCalculate(start, nextv, step+1, curAdja, targetStep);
	}
}

int maxChoice(int, int);
int minChoice(int, int, int);

int maxChoice(int nowNode, int depth)
{
	if (nowNode == N-1) {
		return used[depth][nowNode] = depth;
	}

	if (depth == N+1) {
		return INT_MAX;
	}

	if (used[depth][nowNode] != -1) {
		return used[depth][nowNode];
	}

	int ret = INT_MIN;
	for (int i = 0; i < 3; ++i)
	{
		ret = std::max(ret, minChoice(nowNode, i, depth));
		if (ret == INT_MAX) {
			break;
		}
	}

	return used[depth][nowNode] = ret;
}

int minChoice(int nowNode, int distIdx, int depth)
{
	if (nowNode == N-1) {
		return depth;
	}

	int ret = INT_MAX;

	for (int i = 0; i < N; ++i)
		if (avail[distIdx][nowNode][i]) {
			ret = std::min(ret, maxChoice(i, depth + 1));
		}

	return ret;
}


int main()
{

	while (scanf("%d%d%d%d%d", &N, &M, &step[0], &step[1], &step[2]) == 5) {

		for (int i = 0; i < N; ++i) {
			adja[i].clear();
		}

		for (int i = 0; i < M; ++i) {
			int f, t;
			scanf("%d%d", &f, &t);
			adja[f-1].push_back(t-1);
		}

		memset(avail, 0, sizeof(avail));
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < N; ++j) {
				memset(run, false, sizeof(run));
				availCalculate(j, j, 0, avail[i], step[i]);
			}

		memset(used, -1, sizeof(used));
		int result = maxChoice(0, 0);
		
		if (result != INT_MAX) {
			printf("%d\n", result);
		}
		else {
			printf("IMPOSSIBLE\n");
		}
	}

	return 0;
}
