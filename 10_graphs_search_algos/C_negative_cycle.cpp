#include <vector>
#include <iostream>
#include <queue>

using namespace std;

const int INF = 100000;

class OrGraph
{
private:
    vector<vector<pair<int, int>>> adjlist;
    vector<vector<int>> next;
    vector<vector<int>> dist;
    vector<int> path;

public:
    OrGraph(int n)
    {
        adjlist.resize(n);
        dist.resize(n);

        next = vector<vector<int>>(n, vector<int>(n, -1));

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                next[i][j] = j;
            }
        }
    }

    void add(int i, int j, int w)
    {
        adjlist[i].push_back({w, j});
        dist[i].push_back(w);
    }

    void floid()
    {
        int n = adjlist.size();
        for (int k = 0; k < n; ++k)
        {
            for (int u = 0; u < n; ++u)
            {
                for (int v = 0; v < n; ++v)
                {
                    if (dist[u][k] == INF || dist[k][v] == INF)
                        continue;

                    if (dist[u][v] > dist[u][k] + dist[k][v])
                    {
                        dist[u][v] = dist[u][k] + dist[k][v];
                        next[u][v] = next[u][k];
                    }
                }
            }
        }
    }

    void find_path()
    {
        int neg_idx = 0;
        int n = adjlist.size();

        for (; neg_idx < n; ++neg_idx)
            if (dist[neg_idx][neg_idx] < 0)
                break;
        if (neg_idx == n)
            return;

        int curr = next[neg_idx][neg_idx];

        for (int i = 0; i < n; ++i)
        {
            curr = next[curr][neg_idx];
        }
        neg_idx = curr;
        curr = next[neg_idx][neg_idx];
        while (curr != neg_idx)
        {
            path.push_back(curr);
            curr = next[curr][neg_idx];
        }
        path.push_back(curr);
    }

    void print_path()
    {
        if (path.size() == 0)
        {
            cout << "NO" << endl;
            return;
        }

        cout << "YES" << endl;
        cout << path.size() << endl;

        for (auto el : path)
            cout << el + 1 << " ";
        cout << endl;
    }

    void print_dists()
    {
        for (auto row : dist)
        {
            for (auto el : row)
            {
                cout << el << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    int n;
    cin >> n;
    OrGraph graph(n);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int w;
            cin >> w;
            graph.add(i, j, w);
        }
    }

    graph.floid();
    graph.find_path();
    graph.print_path();

    return 0;
}