#include <iostream>
#include <vector>

using namespace std;

void split(vector<int> &array, int l, int r, int &med1, int &med2)
{
    int rand_ind = l + rand() % (r - l);
    int pivot = array[rand_ind];

    for (int i = l; i < r; ++i)
    {
        if (pivot == array[i])
        {
            swap(array[med2], array[i]);
            med2 += 1;
        }
        else if (pivot > array[i])
        {
            swap(array[med1], array[i]);
            if (med1 != med2)
            {
                swap(array[med2], array[i]);
            }
            med1 += 1;
            med2 += 1;
        }
    }
}

int statistic(vector<int> &array, int l, int r, int k)
{
    if (r - l == 1)
        return array[k];

    int med1 = l;
    int med2 = l;
    split(array, l, r, med1, med2);

    if (k < med1)
        return statistic(array, l, med1, k);

    if (med1 <= k && k < med2)
        return array[med1];

    if (med2 <= k)
        return statistic(array, med2, r, k);

    return -1;
}

int main()
{
    int n;
    cin >> n;

    vector<int> array;
    array.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> array[i];
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        int l;
        int r;
        int k;
        cin >> l >> r >> k;
        k--;
        l--;
        vector<int> array_for_split(array.begin() + l, array.begin() + r);
        cout << statistic(array_for_split, 0, array_for_split.size(), k) << endl;
    }

    return 0;
}