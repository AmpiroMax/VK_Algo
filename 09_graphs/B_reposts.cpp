#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <unordered_map>

using namespace std;

class NotOrGraph
{
private:
    unordered_map<string, vector<string>> adjlist;
    unordered_map<string, int> visited;

public:
    NotOrGraph() {}

    void add(string v, string u)
    {
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
        visited[u] = -1;
        visited[v] = -1;
    }

    int dfs(string v, int my_depth)
    {
        visited[v] = 1;
        int new_depth = my_depth;

        if (adjlist.count(v))
            for (auto u : adjlist[v])
            {
                if (visited[u] == -1)
                {
                    int res = dfs(u, my_depth + 1);
                    new_depth = max(res, new_depth);
                }
            }
        return new_depth;
    }
};

std::string str_tolower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return s;
}

int main()
{
    int n;
    cin >> n;
    NotOrGraph my_graph;

    for (int i = 0; i < n; ++i)
    {
        string v;
        string u;
        string dump;
        cin >> v >> dump >> u;
        v = str_tolower(v);
        u = str_tolower(u);
        my_graph.add(v, u);
    }

    cout << my_graph.dfs("polycarp", 1) << endl;
    return 0;
}