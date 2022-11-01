#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> z_function(string str)
{
    vector<int> z(str.size(), -1);
    int left = 0;
    int right = 0;

    for (int i = 1; i < str.size(); ++i)
    {
        z[i] = max(0, min(right - i, z[i - left]));
        while ((i + z[i] < str.size()) && (str[z[i]] == str[i + z[i]]))
            z[i]++;

        if (i + z[i] > right)
        {
            left = i;
            right = z[i] + i;
        }
    }

    return z;
}

int main()
{
    string str;
    cin >> str;

    vector<int> ans = z_function(str);

    for (auto el : ans)
        if (el != -1)
            cout << el << " ";
    cout << endl;

    return 0;
}