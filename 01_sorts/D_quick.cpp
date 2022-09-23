#include <iostream>
#include <vector>

using namespace std;

void printArray(const vector<int> &array, int l = 0, int r = -1)
{
    if (r == -1)
        r = array.size();

    for (int i = l; i < r; ++i)
        cout << array[i] << " ";
    cout << endl;
}

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

void quick_sort(vector<int> &array, int l, int r)
{
    if (r - l <= 1)
        return;

    int med1 = l;
    int med2 = l;

    split(array, l, r, med1, med2);

    quick_sort(array, l, med1);
    quick_sort(array, med2, r);
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

    quick_sort(array, 0, array.size());

    for (auto el : array)
        cout << el << " ";
    cout << endl;

    return 0;
}