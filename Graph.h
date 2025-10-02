#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <limits>
using namespace std;

class Graph
{
protected:
    int n;
    vector<vector<int>> adj;
    vector<bool> visited;
    vector<pair<int, int>> spanningTree;

    void dfs(int v)
    {
        visited[v] = true;
        for (int u : adj[v])
        {
            if (!visited[u])
            {
                spanningTree.push_back({v, u});
                dfs(u);
            }
        }
    }

public:
    Graph(int vertices)
    {
        n = vertices;
        adj.assign(n, {});
        visited.assign(n, false);
    }

    virtual void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void buildSpanningTree(int start = 0)
    {
        spanningTree.clear();
        fill(visited.begin(), visited.end(), false);

        dfs(start);

        cout << "Spanning tree consists of edges:\n";
        for (pair<int, int> e : spanningTree)
        {
            cout << e.first << " - " << e.second << endl;
        }
    }
    void bfs(int start)
    {
        fill(visited.begin(), visited.end(), false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS traversal starting from " << start << ": ";

        while (!q.empty())
        {
            int v = q.front();
            q.pop();

            cout << v << " ";

            for (int u : adj[v])
            {
                if (!visited[u])
                {
                    visited[u] = true;
                    q.push(u);
                }
            }
        }
        cout << endl;
    }
};

class DirectedGraph : public Graph
{
private:
    bool dfsCycleDirected(int v, vector<int> &state)
    {
        state[v] = 1;
        for (int u : adj[v])
        {
            if (state[u] == 0)
            {
                if (dfsCycleDirected(u, state))
                    return true;
            }
            else if (state[u] == 1)
            {
                return true;
            }
        }
        state[v] = 2;
        return false;
    }

public:
    DirectedGraph(int vertices) : Graph(vertices)
    {
        cout << "Created Directed Graph with " << vertices << " vertices.\n";
    }

    void addEdge(int u, int v) override
    {
        adj[u].push_back(v);
    }

    int getOutDegree(int v) const
    {
        if (v >= 0 && v < n)
        {
            return adj[v].size();
        }
        return -1;
    }

    int getInDegree(int v) const
    {
        if (v < 0 || v >= n)
            return -1;
        int in_degree = 0;
        for (int u = 0; u < n; u++)
        {
            for (int neighbor : adj[u])
            {
                if (neighbor == v)
                {
                    in_degree++;
                }
            }
        }
        return in_degree;
    }

    bool isCyclic()
    {
        vector<int> state(n, 0);
        for (int i = 0; i < n; i++)
        {
            if (state[i] == 0)
            {
                if (dfsCycleDirected(i, state))
                    return true;
            }
        }
        return false;
    }
};

class UndirectedGraph : public Graph
{
private:
    bool dfsCycleUndirected(int v, int parent)
    {
        visited[v] = true;
        for (int u : adj[v])
        {
            if (!visited[u])
            {
                if (dfsCycleUndirected(u, v))
                    return true;
            }
            else if (u != parent)
            {
                return true;
            }
        }
        return false;
    }

public:
    UndirectedGraph(int vertices) : Graph(vertices)
    {
        cout << "Created Undirected Graph with " << vertices << " vertices.\n";
    }

    bool isCyclic()
    {
        fill(visited.begin(), visited.end(), false);
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                if (dfsCycleUndirected(i, -1))
                    return true;
            }
        }
        return false;
    }
};

class WeightedGraph : public Graph
{
private:
    vector<vector<pair<int, int>>> weightedAdj;

public:
    WeightedGraph(int vertices) : Graph(vertices)
    {
        weightedAdj.assign(vertices, {});
        cout << "Created Weighted Graph with " << vertices << " vertices.\n";
    }

    void addEdge(int u, int v, int w)
    {
        if (u < 0 || v < 0 || u >= n || v >= n)
            return;
        weightedAdj[u].push_back({v, w});
        weightedAdj[v].push_back({u, w});
    }

    void dijkstra(int start)
    {
        vector<int> dist(n, numeric_limits<int>::max());
        dist[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start});

        while (!pq.empty())
        {
            int d = pq.top().first;
            int v = pq.top().second;
            pq.pop();

            if (d > dist[v])
                continue;

            for (auto [u, w] : weightedAdj[v])
            {
                if (dist[v] + w < dist[u])
                {
                    dist[u] = dist[v] + w;
                    pq.push({dist[u], u});
                }
            }
        }

        cout << "Shortest distances from vertex " << start << ":\n";
        for (int i = 0; i < n; i++)
        {
            if (dist[i] == numeric_limits<int>::max())
                cout << i << " : INF\n";
            else
                cout << i << " : " << dist[i] << "\n";
        }
    }
};

class NegativeWeightedGraph : public WeightedGraph
{
public:
    NegativeWeightedGraph(int vertices) : WeightedGraph(vertices)
    {
        cout << "Created Negative Weighted Graph with " << vertices << " vertices.\n";
    }

    void bellmanFord(int start)
    {
        vector<int> dist(n, numeric_limits<int>::max());
        dist[start] = 0;

        for (int i = 1; i < n; i++)
        {
            for (int u = 0; u < n; u++)
            {
                for (auto [v, w] : weightedAdj[u])
                {
                    if (dist[u] != numeric_limits<int>::max() && dist[u] + w < dist[v])
                    {
                        dist[v] = dist[u] + w;
                    }
                }
            }
        }

        for (int u = 0; u < n; u++)
        {
            for (auto [v, w] : weightedAdj[u])
            {
                if (dist[u] != numeric_limits<int>::max() && dist[u] + w < dist[v])
                {
                    cout << "Graph contains a negative weight cycle!\n";
                    return;
                }
            }
        }

        cout << "Shortest distances from " << start << ":\n";
        for (int i = 0; i < n; i++)
        {
            if (dist[i] == numeric_limits<int>::max())
                cout << i << " : INF\n";
            else
                cout << i << " : " << dist[i] << "\n";
        }
    }
};
