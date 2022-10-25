#include <iostream>
#include <vector>
#include <string>

using namespace std;

void levenshtein_distance(const string &str1, const string &str2)
{
    vector<vector<int>> minimal_error(str1.size() + 1, vector<int>(str2.size() + 1, 0));

    for (int i = 0; i <= str1.size(); ++i)
    {
        for (int j = 0; j <= str2.size(); ++j)
        {
            if (i == 0)
            {
                minimal_error[i][j] = j;
                continue;
            }
            if (j == 0)
            {
                minimal_error[i][j] = i;
                continue;
            }

            int error = 0;
            if (str1[i - 1] != str2[j - 1])
                error = 1;

            minimal_error[i][j] = min(min(minimal_error[i - 1][j] + 1, minimal_error[i][j - 1] + 1), minimal_error[i - 1][j - 1] + error);
        }
    }

    cout << minimal_error[str1.size()][str2.size()] << endl;
}

int main()
{
    string str1 = "";
    string str2 = "";

    cin >> str1 >> str2;

    levenshtein_distance(str1, str2);

    return 0;
}