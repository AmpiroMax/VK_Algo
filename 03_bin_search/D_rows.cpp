#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int function(const vector<int> &ropes, int len, int k)
{
    int count = 0;
    for (int rope_len : ropes)
        count += rope_len / len;
    return count >= k;
}

int bin_search(const vector<int> &ropes, int max_len, int k)
{
    int l = 0;
    int r = max_len + 1;

    while ((r - l) > 1)
    {
        int med_len = (l + r) / 2;
        if (function(ropes, med_len, k))
            l = med_len;
        else
            r = med_len;
    }
    return l;
}

int main()
{
    int n;
    int k;
    int max_len = 0;
    vector<int> ropes;
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
    {
        int rope;
        cin >> rope;
        if (rope > max_len)
            max_len = rope;
        ropes.push_back(rope);
    }

    cout << bin_search(ropes, max_len, k) << endl;
    return 0;
}