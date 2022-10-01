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

int lower_bound(const vector<int> &mass, int x)
{
    int l = -1;
    int r = mass.size();

    while (l < r - 1)
    {
        int m = (l + r) / 2;
        if (x <= mass[m])
            r = m;
        else
            l = m;
    }
    return r;
}

int main()
{
    int n;
    int k;
    cin >> n;

    vector<int> mass;
    for (int i = 0; i < n; ++i)
    {
        int el;
        cin >> el;
        mass.push_back(el);
    }
    quick_sort(mass, 0, mass.size());

    cin >> k;
    for (int i = 0; i < k; ++i)
    {
        int l;
        int r;
        cin >> l >> r;
        int lb_l = lower_bound(mass, l);
        int ub_r = lower_bound(mass, r + 1);
        cout << ub_r - lb_l << endl;
    }

    return 0;
}