#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    vector<pair<int, int>> moves = {
        {1, 2},
        {2, 1},
        {-1, 2},
        {2, -1},
        {1, -2},
        {-2, 1},
        {-1, -2},
        {-2, -1},
    };
    int N;
    pair<int, int> start;
    pair<int, int> end;

    cin >> N;
    cin >> start.first >> start.second;
    cin >> end.first >> end.second;

    vector<vector<pair<int, int>>> parent(N, vector<pair<int, int>>(N, {-1, -1}));

    start.first--;
    start.second--;
    end.first--;
    end.second--;

    queue<pair<int, int>> q;
    q.push(start);

    while (!q.empty())
    {
        pair<int, int> curr = q.front();
        q.pop();

        for (auto [dx, dy] : moves)
        {
            int x = curr.first + dx;
            int y = curr.second + dy;
            if (x >= 0 && y >= 0 && x < N && y < N && parent[x][y].first == -1)
            {
                q.push({x, y});
                parent[x][y] = curr;
            }
        }
    }

    vector<pair<int, int>> path;
    pair<int, int> curr = end;

    while (curr != start)
    {
        path.push_back(curr);
        curr = parent[curr.first][curr.second];
    }
    path.push_back(curr);

    cout << path.size() << endl;

    for (int i = path.size() - 1; i >= 0; --i)
    {
        cout << path[i].first + 1 << " " << path[i].second + 1 << endl;
    }

    return 0;
}