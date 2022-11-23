#include <vector>
#include <iostream>
#include <queue>

using namespace std;

const int64_t INF = 1e15 * 2000;

class OrGraph
{
private:
    enum Status
    {
        OK,
        NEG,
        UNREACHED
    };

    vector<vector<pair<int64_t, int64_t>>> adjlist;
    vector<int64_t> dists;
    vector<Status> status;

public:
    OrGraph(int64_t n)
    {
        adjlist.resize(n);
    }

    void add(int64_t v, int64_t u, int64_t w)
    {
        adjlist[v].push_back({w, u});
    }

    void ford_bellman(int64_t start)
    {

        int64_t n = adjlist.size();

        status = vector<Status>(n, UNREACHED);
        dists = vector<int64_t>(n, INF);
        status[start] = Status::OK;
        dists[start] = 0;

        for (int64_t k = 0; k < n - 1; ++k)
        {
            for (int64_t v = 0; v < n; ++v)
            {
                if (dists[v] != INF)
                {
                    for (auto [w, u] : adjlist[v])
                    {
                        if (dists[u] > dists[v] + w)
                        {
                            dists[u] = dists[v] + w;
                            status[u] = Status::OK;
                        }
                    }
                }
            }
        }

        vector<int64_t> neg_cycle_verts;

        for (int64_t v = 0; v < n; ++v)
        {
            if (dists[v] != INF)
            {
                for (auto [w, u] : adjlist[v])
                {
                    if (dists[u] > dists[v] + w)
                    {
                        neg_cycle_verts.push_back(v);
                        dists[u] = dists[v] + w;
                    }
                }
            }
        }

        while (!neg_cycle_verts.empty())
        {
            int64_t v = neg_cycle_verts.back();
            neg_cycle_verts.pop_back();
            status[v] = Status::NEG;

            for (auto [w, u] : adjlist[v])
            {
                if (status[u] != Status::NEG)
                {
                    neg_cycle_verts.push_back(u);
                }
            }
        }
    }

    void print_dists()
    {
        for (int i = 0; i < adjlist.size(); ++i)
        {
            if (status[i] == Status::OK)
                cout << dists[i] << endl;

            if (status[i] == Status::NEG)
                cout << "-" << endl;

            if (status[i] == Status::UNREACHED)
                cout << "*" << endl;
        }
    }
};

int main()
{
    int64_t n;
    int64_t m;
    int64_t start;
    cin >> n >> m >> start;
    start--;

    OrGraph graph(n);

    for (int64_t i = 0; i < m; ++i)
    {
        int v;
        int64_t u;
        int64_t w;
        cin >> v >> u >> w;
        v--;
        u--;
        graph.add(v, u, w);
    }

    graph.ford_bellman(start);
    graph.print_dists();

    return 0;
}