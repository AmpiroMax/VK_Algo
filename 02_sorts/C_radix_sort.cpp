#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int ALPHABET_SIZE = 27;

void radix_sort_iteration(vector<string> &array, int digit)
{
    vector<int> cnt(ALPHABET_SIZE, 0);
    vector<int> pos_digit(ALPHABET_SIZE, 0);

    for (int i = 0; i < array.size(); ++i)
        cnt[array[i][digit] - 'a']++;

    for (int i = 1; i < ALPHABET_SIZE; ++i)
        pos_digit[i] = pos_digit[i - 1] + cnt[i - 1];

    vector<string> array_new(array.size(), "");
    for (int i = 0; i < array.size(); ++i)
        array_new[pos_digit[array[i][digit] - 'a']++] = array[i];

    array = array_new;
}

int main()
{
    int n;
    int m;
    int k;
    cin >> n >> m >> k;

    vector<string> array;

    for (int i = 0; i < n; ++i)
    {
        string str;
        cin >> str;
        array.push_back(str);
    }

    for (int i = 0; i < k; ++i)
        radix_sort_iteration(array, m - 1 - i);

    for (auto str : array)
        cout << str << endl;

    return 0;
}