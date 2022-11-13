#include <iostream>
#include <vector>

using namespace std;

class NotOrGraph
{
private:
    vector<vector<int>> adjlist;
    vector<int> components;

    void dfs(int v, int curr_comp)
    {
        components[v] = curr_comp;
        for (auto u : adjlist[v])
        {
            if (components[u] == -1)
            {
                dfs(u, curr_comp);
            }
        }
    }

public:
    NotOrGraph(int n)
    {
        adjlist.resize(n);
    }

    void add(int i, int j)
    {
        adjlist[i].push_back(j);
        adjlist[j].push_back(i);
    }

    vector<int> find_components(int &comp_count)
    {
        components = vector<int>(adjlist.size(), -1);
        int curr_comp = 1;
        for (int i = 0; i < adjlist.size(); ++i)
        {
            if (components[i] == -1)
            {
                dfs(i, curr_comp);
                curr_comp++;
            }
        }
        comp_count = curr_comp;
        return components;
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
        if (v == u)
            continue;
        my_graph.add(v, u);
    }
    int comp_count = -1;
    vector<int> answer = my_graph.find_components(comp_count);

    cout << comp_count - 1 << endl;
    for (auto el : answer)
    {
        cout << el << " ";
    }
    cout << endl;

    return 0;
}