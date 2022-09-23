#include <iostream>
#include <vector>

using namespace std;

size_t merge(vector<int> &array, int l, int r)
{
    int i = 0;
    int j = 0;
    size_t inv_num = 0;
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
            inv_num += (med - l - i);
            j++;
        }
    }

    for (int k = 0; k < (r - l); ++k)
        array[l + k] = tmp[k];

    return inv_num;
}

size_t merge_sort(vector<int> &array, int l, int r)
{
    if (r - l <= 1)
        return 0;

    size_t inv_num = 0;
    inv_num += merge_sort(array, l, (l + r) / 2);
    inv_num += merge_sort(array, (l + r) / 2, r);
    inv_num += merge(array, l, r);

    return inv_num;
}

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

    cout << merge_sort(array, 0, array.size()) << endl;

    return 0;
}