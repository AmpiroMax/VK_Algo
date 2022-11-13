#include <iostream>
#include <vector>

using namespace std;

class NotOrGraph
{
private:
    vector<vector<int>> adjlist;
    vector<int> up;
    vector<int> tin;
    vector<int> articulation_points;
    int points_count;
    vector<int> visited;
    int time;

    void dfs(int v, int p)
    {
        tin[v] = time;
        up[v] = time;
        time += 1;

        visited[v] = 1;

        int child_count = 0;
        for (auto u : adjlist[v])
        {
            if (u == p)
                continue;

            if (visited[u] == -1)
            {
                dfs(u, v);
                up[v] = min(up[v], up[u]);

                if (up[u] >= tin[v] && p != -1 && articulation_points[v] != 1)
                {

                    articulation_points[v] = 1;
                    points_count++;
                }
                ++child_count;
            }
            else
            {
                up[v] = min(up[v], tin[u]);
            }
        }
        if (p == -1 && child_count > 1 && articulation_points[v] != 1)
        {
            articulation_points[v] = 1;
            points_count++;
        }
    }

public:
    NotOrGraph(int n)
    {
        adjlist.resize(n);
        articulation_points.resize(n);
    }

    void add(int i, int j)
    {
        adjlist[i].push_back(j);
        adjlist[j].push_back(i);
    }

    void find_articulation_points()
    {
        points_count = 0;
        int n = adjlist.size();
        visited = vector<int>(n, -1);
        up = vector<int>(n, -1);
        tin = vector<int>(n, -1);

        time = 0;
        for (int i = 0; i < n; ++i)
        {
            if (visited[i] == -1)
                dfs(i, -1);
        }
    }

    void get_articulation_points()
    {
        cout << points_count << endl;
        for (int i = 0; i < adjlist.size(); ++i)
        {
            if (articulation_points[i] == 1)
            {
                cout << i + 1 << " ";
            }
        }
        cout << endl;
    }
};

int main()
{
    int n;
    int m;
    cin >> n >> m;
    NotOrGraph my_graph(n);

    for (int i = 0; i < m; ++i)
    {
        int v;
        int u;
        cin >> v >> u;
        v--;
        u--;

        my_graph.add(v, u);
    }
    my_graph.find_articulation_points();
    my_graph.get_articulation_points();

    return 0;
}