#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> p_function(string str)
{
    vector<int> p(str.size(), 0);
    for (int i = 1; i < str.size(); ++i)
    {
        int k = p[i - 1];
        while (k > 0 && str[i] != str[k])
            k = p[k - 1];
        if (str[i] == str[k])
            k++;
        p[i] = k;
    }
    return p;
}

int main()
{
    string str;
    string text;
    cin >> str;
    cin >> text;

    vector<int> p_rez = p_function(str + "#" + text);
    vector<int> ans;
    for (int i = str.size() + 1; i < p_rez.size(); ++i)
    {
        if (p_rez[i] == str.size())
            ans.push_back(i - str.size() - str.size() + 1);
    }
    cout << ans.size() << endl;

    for (auto el : ans)
        cout << el << " ";
    cout << endl;

    return 0;
}