#include <cstdio>
#include <cmath>

double lg(double v)
{
    return log(v)/log(2);
}

const double GHZ = 1e+9;

int main()
{
    int N;
    double P, S, V;
    while(scanf("%d%lf%lf%lf", &N, &P, &S, &V) == 4) {
        double low = 0, mid, up = 80;
        double bestTime, c;

        for (int i = 0; i < 50; i++) {
            mid = (low+up)/2;

            double f_derivative = S / (mid*mid*V);
            double g_derivative = N * sqrt(2) * pow(lg(N), sqrt(2)*mid) * log(lg(N)) / (P*GHZ);

            if (g_derivative >= f_derivative) {
                up = mid;
            }
            else {
                low = mid;
            }
        }

        c = low;
        bestTime = S*(1+1/c)/V + (N * pow(lg(N), sqrt(2)*c)) / (P*GHZ);
        printf("%.12f %.12f\n", bestTime, c);
    }
	return 0;
}