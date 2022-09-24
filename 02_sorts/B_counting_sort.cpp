#include <iostream>
#include <vector>

using namespace std;

const int M = 101;

int main()
{
    vector<int> cnt;
    cnt.resize(M);

    int ind;
    for (; cin >> ind;)
    {
        cnt[ind]++;
    }

    vector<int> array;

    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < cnt[i]; ++j)
            array.push_back(i);
    }

    for (auto el : array)
        cout << el << " ";
    cout << endl;

    return 0;
}