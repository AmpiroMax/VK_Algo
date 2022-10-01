#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

const float EPS = 1e-6;
const int ITER_NUM = 30;

double derivative(double x, double a, int Vp, int Vf)
{
    return 1 - 1.0 / x + 1.0 * Vf / Vp * sqrt((a * a + (1 - x) * (1 - x)) / (x * x + (1 - a) * (1 - a)));
}

double bin_search(double a, int Vp, int Vf)
{
    double l = 0;
    double r = 1;

    for (int iter = 0; (iter < ITER_NUM) && ((r - l) > EPS); ++iter)
    {
        double m = (l + r) / 2;
        if (derivative(m, a, Vp, Vf) < 0)
            l = m;
        else
            r = m;
    }
    return l;
}

int main()
{
    double a;
    int Vp;
    int Vf;
    cin >> Vp >> Vf >> a;
    printf("%.5f\n", bin_search(a, Vp, Vf));

    return 0;
}