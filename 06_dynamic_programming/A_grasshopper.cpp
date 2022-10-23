#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e5 + 1;

void game(const vector<int> &costs, int n, int k)
{
    vector<int> max_costs(n, 0);
    vector<int> path(n, -1);
    vector<int> ans_path;
    for (int i = 1; i < n; ++i)
    {
        int max_elem = -INF;
        for (int j = 1; j <= k && (i - j >= 0); ++j)
        {
            if (max_costs[i - j] > max_elem)
            {
                max_elem = max_costs[i - j];
                path[i] = i - j;
            }
        }
        max_costs[i] = max_elem + costs[i];
    }

    for (int i = n - 1; i >= 0;)
    {
        ans_path.push_back(i);
        i = path[i];
    }

    cout << max_costs[n - 1] << endl;
    cout << ans_path.size() - 1 << endl;
    for (int i = ans_path.size() - 1; i >= 0; --i)
        cout << ans_path[i] + 1 << " ";
    cout << endl;
}

int main()
{
    int n;
    int k;
    cin >> n >> k;
    vector<int> costs(n, 0);
    for (int i = 1; i < n - 1; ++i)
        cin >> costs[i];

    game(costs, n, k);

    return 0;
}