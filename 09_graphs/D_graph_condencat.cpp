#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class OrGraph
{
private:
    vector<vector<int>> adjlist;
    vector<vector<int>> revadjlist;
    vector<vector<int>> condence;

    vector<int> colors;
    vector<int> components;
    int comp_count;

    void comp_dfs(int v, int curr_comp)
    {
        components[v] = curr_comp;
        for (auto u : revadjlist[v])
        {
            if (components[u] == -1)
            {
                comp_dfs(u, curr_comp);
            }
        }
    }
    vector<int> topol_sort;
    int cycle_found = 0;

    void topol_dfs(int v)
    {
        colors[v] = 1;
        for (auto u : adjlist[v])
        {
            if (colors[u] == -1)
            {
                topol_dfs(u);
            }
        }
        colors[v] = 2;
        topol_sort.push_back(v);
    }

public:
    OrGraph(int n)
    {
        adjlist.resize(n);
        revadjlist.resize(n);

        colors = vector<int>(n, -1);
        components = vector<int>(adjlist.size(), -1);
    }

    void add(int v, int u)
    {
        adjlist[v].push_back(u);
        revadjlist[u].push_back(v);
    }

    void topologocal_sort()
    {
        for (int i = 0; i < adjlist.size(); ++i)
            if (colors[i] == -1)
                topol_dfs(i);
        reverse(topol_sort.begin(), topol_sort.end());
    }

    void find_components()
    {
        components = vector<int>(adjlist.size(), -1);
        comp_count = 1;
        for (auto i : topol_sort)
        {
            if (components[i] == -1)
            {
                comp_dfs(i, comp_count);
                comp_count++;
            }
        }
        comp_count--;
    }

    int condence_graph_edges_count()
    {
        condence.resize(comp_count);
        int edges_count = 0;

        for (int v = 0; v < adjlist.size(); ++v)
        {
            for (auto u : adjlist[v])
            {
                if (components[u] != components[v])
                {
                    int are_connected = 0;
                    for (auto comp_num : condence[components[v]])
                    {
                        if (comp_num == components[u])
                        {
                            are_connected = 1;
                            break;
                        }
                    }
                    if (!are_connected)
                    {
                        edges_count += 1;
                        condence[components[v]].push_back(components[u]);
                    }
                }
            }
        }

        return edges_count;
    }

    int is_cycle() { return cycle_found; }
    vector<int> get_sorted() { return topol_sort; }
    vector<int> get_components() { return components; }
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
    my_graph.find_components();

    cout << my_graph.condence_graph_edges_count() << endl;

    return 0;
}