#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

const float EPS = 1e-7;
const int ITER_NUM = 40;

double bin_search(double C)
{
    double l = 0;
    double r = sqrt(C);

    double m = (l + r) / 2;
    for (int iter = 0; (iter < ITER_NUM) && ((r - l) > EPS); ++iter)
    {
        m = (l + r) / 2;
        if (m < (C - m * m) * (C - m * m))
            l = m;
        else
            r = m;
    }
    return m;
}

int main()
{
    double C;
    cin >> C;
    printf("%.7f\n", bin_search(C));

    return 0;
}