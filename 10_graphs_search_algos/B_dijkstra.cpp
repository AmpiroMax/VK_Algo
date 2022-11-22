#include <vector>
#include <iostream>
#include <queue>

using namespace std;

class NotOrGraph
{
private:
    vector<vector<pair<int, int>>> adjlist;
    vector<int> dists;

public:
    NotOrGraph(int n)
    {
        adjlist.resize(n);
        dists = vector<int>(n, -1);
        dists[0] = 0;
    }

    void add(int i, int j, int w)
    {
        adjlist[i].push_back({w, j});
        adjlist[j].push_back({w, i});
    }

    void dijkstra()
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        q.push({0, 0});

        while (!q.empty())
        {
            auto [dist, v] = q.top();
            q.pop();

            if (v != 0 && dists[v] != -1)
                continue;
            else
                dists[v] = dist;

            for (auto [w, u] : adjlist[v])
            {
                if (dists[u] == -1)
                    q.push({dist + w, u});
            }
        }
    }

    void print_dists()
    {
        for (int dist : dists)
            cout << dist << " ";
        cout << endl;
    }
};

int main()
{
    int n;
    int m;
    cin >> n >> m;
    NotOrGraph graph(n);

    for (int i = 0; i < m; ++i)
    {
        int u;
        int v;
        int w;
        cin >> v >> u >> w;
        v--;
        u--;
        graph.add(v, u, w);
    }

    graph.dijkstra();
    graph.print_dists();

    return 0;
}