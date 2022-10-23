#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e5 + 1;
const int R = 1;
const int D = 0;

void game(const vector<vector<int>> &maze, int n, int m)
{
    vector<vector<int>> max_coins(n + 1, vector<int>(m + 1, -INF));
    vector<vector<pair<int, int>>> path(n + 1, vector<pair<int, int>>(m + 1, {0, 0}));
    vector<int> ans_path;

    max_coins[1][1] = maze[1][1];

    for (int i = 1; i < n + 1; ++i)
    {
        for (int j = 1; j < m + 1; ++j)
        {
            if (i == 1 && j == 1)
                continue;

            if (max_coins[i - 1][j] < max_coins[i][j - 1])
            {
                max_coins[i][j] = max_coins[i][j - 1];
                path[i][j] = {i, j - 1};
            }
            else
            {
                max_coins[i][j] = max_coins[i - 1][j];
                path[i][j] = {i - 1, j};
            }
            max_coins[i][j] += maze[i][j];
        }
    }

    int i = n;
    int j = m;
    for (; i != 1 || j != 1;)
    {
        if (path[i][j].first < i)
            ans_path.push_back(D);
        else
            ans_path.push_back(R);
        int new_i = path[i][j].first;
        j = path[i][j].second;
        i = new_i;
    }

    cout << max_coins[n][m] << endl;
    for (int i = ans_path.size() - 1; i >= 0; --i)
        cout << (ans_path[i] == R ? "R" : "D");
    cout << endl;
}

int main()
{
    int n;
    int m;
    cin >> n >> m;

    // Лабиринт с каёмочкой
    vector<vector<int>> maze(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i < n + 1; ++i)
        for (int j = 1; j < m + 1; ++j)
            cin >> maze[i][j];

    game(maze, n, m);

    return 0;
}