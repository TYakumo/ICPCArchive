#include <cstdio>
#include <cmath>
#include <climits>
#include <cstring>
#include <iostream>

const int MAXN = 1000010;
int N, R, P;
long long answerTable[MAXN];

long long calculateAnswer(int num)
{
	if (answerTable[num] != LLONG_MAX || num == 0) {
		return answerTable[num];
	}

	for (long long k = 1; k < num; ++k) {
		long long cost = (k*P+R) + calculateAnswer(ceil((double)num/(k+1)));
		answerTable[num] = std::min(answerTable[num], cost);
	}

	return answerTable[num];
}

int main()
{

	while( scanf("%d%d%d", &N, &R, &P) == 3 ) {

		for (int i = 0; i <= N; ++i)
			answerTable[i] = LLONG_MAX;

		answerTable[0] = answerTable[1] = 0;

		printf("%lld\n", calculateAnswer(N));
	}

	return 0;
 }