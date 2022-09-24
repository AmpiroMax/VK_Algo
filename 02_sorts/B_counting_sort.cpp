#include <iostream>
#include <vector>

using namespace std;

const int m = 101;

int main()
{
    vector<int> cnt;
    cnt.resize(m);

    int ind;
    for (; cin >> ind;)
    {
        cnt[ind]++;
    }

    vector<int> array;

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < cnt[i]; ++j)
            array.push_back(i);
    }

    for (auto el : array)
        cout << el << " ";
    cout << endl;

    return 0;
}