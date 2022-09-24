#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int ALPHABET_SIZE = 26;

vector<int> count_letters(const string &str, int l = 0, int r = -1)
{
    if (r == -1)
        r = str.size();

    vector<int> count(ALPHABET_SIZE, 0);

    for (int i = l; i < r; ++i)
        count[str[i] - 'a']++;
    return count;
}

size_t count_substrings(string cards, string str)
{
    vector<int> cards_stats = count_letters(cards);

    size_t count = 0;

    int l = 0;
    int r = 0;

    while (r < str.size())
    {
        if (cards_stats[str[r] - 'a'] > 0)
        {
            cards_stats[str[r] - 'a']--;
            r++;
            count += r - l;
        }
        else if (r != l)
        {
            cards_stats[str[l] - 'a']++;
            l++;
        }
        else
        {
            l++;
            r++;
        }
    }

    return count;
}

int main()
{
    int dumb;
    cin >> dumb >> dumb;

    string str;
    string cards;
    cin >> str;
    cin >> cards;

    cout << count_substrings(cards, str) << endl;

    return 0;
}