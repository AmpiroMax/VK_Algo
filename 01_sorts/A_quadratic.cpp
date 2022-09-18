#include <iostream>
#include <vector>

using namespace std;

void quadratic_sort(vector<int> &array)
{
    for (int i = 0; i < array.size(); ++i)
    {
        for (int j = i; j > 0 && array[j - 1] > array[j]; --j)
        {
            int tmp = array[j];
            array[j] = array[j - 1];
            array[j - 1] = tmp;
        }
    }
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

    quadratic_sort(array);

    for (auto el : array)
        cout << el << " ";
    cout << endl;

    return 0;
}