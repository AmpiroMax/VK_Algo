#include <vector>
#include <iostream>
#include <queue>

using namespace std;

const int64_t INF = 1e15 * 2000;

class NotOrGraph
{
private:
    enum Status
    {
        OK,
        NEG,
        UNREACHED
    };

    vector<vector<pair<int64_t, int64_t>>> adjlist;
    vector<int64_t> parent;
    vector<int64_t> dists;
    vector<Status> status;

public:
    NotOrGraph(int64_t n)
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

        parent = vector<int64_t>(n, -1);

        status = vector<Status>(n, UNREACHED);
        dists = vector<int64_t>(n, INF);
        status[start] = Status::OK;
        dists[start] = 0;

        for (int64_t k = 1; k < n - 1; ++k)
        {
            for (int64_t v = 0; v < n; ++v)
            {
                if (dists[v] != INF)
                    for (auto [w, u] : adjlist[v])
                    {
                        if (dists[u] > dists[v] + w)
                        {
                            // cout << v << " " << u << " " << w << endl;
                            dists[u] = dists[v] + w;
                            status[u] = Status::OK;
                            parent[u] = v;
                        }
                    }
            }
        }

        vector<int64_t> neg_cycle_verts;

        for (int64_t v = 0; v < n; ++v)
        {
            if (dists[v] != INF)
                for (auto [w, u] : adjlist[v])
                {
                    if (dists[u] > dists[v] + w)
                    {
                        neg_cycle_verts.push_back(u);

                        dists[u] = dists[v] + w;
                        parent[u] = v;
                    }
                }
        }

        // cout << "I| dist[i], parent[i]" << endl;
        // for (int i = 0; i < n; ++i)
        //     cout << i << "| " << dists[i] << ", " << parent[i] << endl;

        // for (int64_t v = 0; v < n; ++v)
        // {
        //     for (auto [w, u] : adjlist[v])
        //     {
        //         if ((status[u] == Status::OK) && (dists[u] > dists[v] + w))
        //         {
        //             for (int64_t i = 0; i < n; ++i)
        //                 v = parent[v];

        //             int64_t curr = parent[v];
        //             while (curr != v)
        //             {
        //                 status[curr] = Status::ONE_OF_NEG;
        //                 neg_cycle_verts.push_back(curr);
        //                 curr = parent[curr];
        //             }
        //             status[curr] = Status::ONE_OF_NEG;
        //             neg_cycle_verts.push_back(curr);
        //             break;
        //         }
        //     }
        // }

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

        print_dists(start);
    }

    void
    print_dists(int64_t start)
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

/*
13 14 5
1 2 10
2 3 5
1 3 100
3 5 7
5 4 10
4 3 -18
6 1 -1
4 8 1
5 7 1
7 9 1
7 10 1
8 11 1
8 12 1
13 2 1

3 3 1
1 1 -1
2 2 2
3 3 3


2 1 2
1 1 -1


3 4 1
1 1 -1
1 2 1
2 3 1
3 1 1

8 9 1
1 2 1
1 3 1
2 4 1
3 5 1
5 3 -2
4 6 1
6 4 -2
6 8 1
5 7 1

asn:
0
1
-
-
-
-
-
-


3 1 1
2 2 -1
------
0
*
*

3 1 1
1 1 -1
------
-
*
*

5 5 1
1 2 1
2 3 1
3 4 1
3 5 1
5 2 -1
------
0
1
2
3
3


4 5 4
1 2 1
2 3 1
3 1 1
1 1 -1
4 3 1
------
-
-
-
0

*/

int main()
{
    int64_t n;
    int64_t m;
    int64_t start;
    cin >> n >> m >> start;
    start--;

    NotOrGraph graph(n);

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
    // cout << "----------------------" << endl;
    graph.ford_bellman(start);
    // graph.print64_t_dists();

    return 0;
}