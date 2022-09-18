#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int> &array, int l, int r)
{
    int i = 0;
    int j = 0;
    int med = (l + r) / 2;
    vector<int> tmp;
    tmp.resize(r - l);

    while ((i + j < r - l))
    {

        if ((j == (r - med)) || (i < (med - l) && array[l + i] < array[med + j]))
        {
            tmp[i + j] = array[l + i];
            i++;
        }
        else
        {
            tmp[i + j] = array[med + j];
            j++;
        }
    }

    for (int k = 0; k < (r - l); ++k)
        array[l + k] = tmp[k];
}

void merge_sort(vector<int> &array, int l, int r)
{
    if (r - l <= 1)
        return;

    merge_sort(array, l, (l + r) / 2);
    merge_sort(array, (l + r) / 2, r);
    merge(array, l, r);
}

/*
Tests:
5
1 2 3 4 5
1 2 3 4 5

7
3 4 1 2 10 5 1
1 1 2 3 4 5 10

*/

int main()
{
    vector<int> array;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int el;
        cin >> el;
        array.push_back(el);
    }

    merge_sort(array, 0, array.size());

    for (auto el : array)
        cout << el << " ";
    cout << endl;

    return 0;
}