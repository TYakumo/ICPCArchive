#include <cstdio>
#include <vector>
#include <functional>
#include <algorithm>

class timelinePoint
{
public:
	int timing;
	int leavePoint;

	timelinePoint() : timing(0), leavePoint(0)
	{}

	timelinePoint(int t, int lp) : timing(t), leavePoint(lp)
	{}
};

bool custom_cmp_for_sort(const timelinePoint &a, const timelinePoint& b)
{
	if (a.timing != b.timing) {
		return a.timing < b.timing;
	}
	return a.leavePoint > b.leavePoint;
}

int main()
{
	int N, M;

	while (scanf("%d%d", &N, &M) == 2) {
		int a, s;
		int answer = 0;
		std::vector <timelinePoint> tpVector;
		std::vector <int> leavingPoint;

		for (int i = 0; i < N; ++i) {
			scanf("%d%d", &a, &s);	
			tpVector.push_back(timelinePoint(a, 0));
			tpVector.push_back(timelinePoint(a+s, 1));
		}
		
		std::sort(tpVector.begin(), tpVector.end(), custom_cmp_for_sort);

		for (int i = 0;  i < tpVector.size(); ++i) {
			if (tpVector[i].leavePoint == 0) {
				int current = tpVector[i].timing;

				while(!leavingPoint.empty()) {					
					int topValue = leavingPoint.front();
					std::pop_heap(leavingPoint.begin(), leavingPoint.end(), std::greater<int>());
					leavingPoint.pop_back();

					if (current - topValue <= M) {
						++answer;
						break;
					}
				}				
			}
			else {
				leavingPoint.push_back(tpVector[i].timing);
				std::push_heap(leavingPoint.begin(), leavingPoint.end(), std::greater<int>());
			}
		}

		printf("%d\n", answer);
	}

	return 0;
}