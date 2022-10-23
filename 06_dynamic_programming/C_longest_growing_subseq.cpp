#include <iostream>
#include <vector>

using namespace std;

void game(const vector<int> &seq, int n)
{
    vector<int> subseqs(n, 1);
    vector<int> path(n, 0);
    vector<int> ans_path;
    for (int i = 0; i < n; ++i)
    {
        int max_j = -1;
        int max_cnt = 0;
        for (int j = 0; j < i; ++j)
        {
            if (seq[j] < seq[i] && (max_cnt < subseqs[j]))
            {
                max_j = j;
                max_cnt = subseqs[j];
            }
        }

        if (max_j == -1)
        {
            path[i] = i;
            continue;
        }

        subseqs[i] = subseqs[max_j] + 1;
        path[i] = max_j;
    }

    int max_ind = -1;
    int max_length = 0;
    for (int i = 0; i < n; ++i)
    {
        if (subseqs[i] > max_length)
        {
            max_length = subseqs[i];
            max_ind = i;
        }
    }
    cout << max_length << endl;

    int i = max_ind;
    for (; path[i] != i;)
    {
        ans_path.push_back(seq[i]);
        i = path[i];
    }
    ans_path.push_back(seq[i]);

    for (int i = ans_path.size() - 1; i >= 0; --i)
        cout << ans_path[i] << " ";
    cout << endl;
}

int main()
{
    int n = 0;
    cin >> n;

    vector<int> sequence(n, 0);
    for (int i = 0; i < n; ++i)
        cin >> sequence[i];

    game(sequence, n);

    return 0;
}