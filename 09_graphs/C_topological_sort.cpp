#include <iostream>
#include <vector>

using namespace std;

class OrGraph
{
private:
    vector<vector<int>> adjlist;
    vector<int> colors;
    vector<int> topol_sort;
    int cycle_found = 0;

    void dfs(int v)
    {
        if (cycle_found)
            return;

        colors[v] = 1;
        for (auto u : adjlist[v])
        {
            if (colors[u] == -1)
            {
                dfs(u);
            }
            if (colors[u] == 1)
            {
                cycle_found = 1;
            }
        }
        colors[v] = 2;
        topol_sort.push_back(v + 1);
    }

public:
    OrGraph(int n)
    {
        adjlist.resize(n);
        colors = vector<int>(n, -1);
    }

    void add(int v, int u)
    {
        adjlist[v].push_back(u);
    }

    void topologocal_sort()
    {
        for (int i = 0; i < adjlist.size(); ++i)
            if (colors[i] == -1)
                dfs(i);
    }

    int is_cycle() { return cycle_found; }
    vector<int> get_sorted() { return topol_sort; }
};

int main()
{
    int n;
    int m;
    cin >> n >> m;
    OrGraph my_graph(n);

    for (int i = 0; i < m; ++i)
    {
        int v;
        int u;
        cin >> v >> u;
        v--;
        u--;
        my_graph.add(v, u);
    }

    my_graph.topologocal_sort();
    if (my_graph.is_cycle())
    {
        cout << -1 << endl;
        return 0;
    }

    vector<int> ans = my_graph.get_sorted();
    for (int i = ans.size() - 1; i >= 0; --i)
    {
        cout << ans[i] << " ";
    }

    cout << endl;
    return 0;
}