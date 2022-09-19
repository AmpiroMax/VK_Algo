#include <iostream>
#include <vector>

using namespace std;

void swapper(vector<int> &array, int i, int j)
{
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

/*
Location of idicies
------------------------------------
   |l      |m1       |m2    [i]   |r
------------------------------------
*/

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
            swapper(array, med2, i);
            med2 += 1;
        }
        else if (pivot > array[i])
        {
            swapper(array, i, med1);
            if (med1 != med2)
            {
                swapper(array, i, med2);
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

/*
Tests:

5
1 5 2 7 3
1 2 3 5 7

5
1 2 3 4 5
1 2 3 4 5

7
3 4 1 2 10 5 1
1 1 2 3 4 5 10

10
1 8 2 1 4 7 3 2 3 6
1 1 2 2 3 3 4 6 7 8

5
1 1 1 1 1
1 1 1 1 1

6
1 2 1 2 1 2
1 1 1 2 2 2

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

    quick_sort(array, 0, array.size());

    for (auto el : array)
        cout << el << " ";
    cout << endl;

    return 0;
}