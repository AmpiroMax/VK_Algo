#include <iostream>

using namespace std;

void bin_search(int n)
{
    int l = 0;
    int r = n + 1;
    int status = 1;
    int iter = 0;

    while (status != 0)
    {
        int m = (l + r) / 2;
        cout << m << endl;
        cin >> status;
        if (status == -1)
            r = m;
        if (status == 1)
            l = m + 1;
    }
}

int main()
{
    int n;
    cin >> n;
    bin_search(n);
    return 0;
}