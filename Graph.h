#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <limits>
#include "DirectedGraph.h"
#include "UndirectedGraph.h"
#include "WeightedGraph.h"
#include <unordered_map>
using namespace std;

template <class T>
class Graph
{
protected:
    unordered_map<T, vector<T>> adj;
    unordered_map<T, bool> visited;
    vector<pair<T, T>> spanningTree;

    void dfs(T v)
    {
        visited[v] = true;
        for (T u : adj[v])
        {
            if (!visited[u])
            {
                spanningTree.push_back({v, u});
                dfs(u);
            }
        }
    }

public:
    Graph() {}

    virtual void addEdge(T u, T v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void buildSpanningTree(T start)
    {
        spanningTree.clear();
        for (auto &p : visited)
            p.second = false;

        for (auto &p : adj)
            visited[p.first] = false;

        dfs(start);

        cout << "Spanning tree consists of edges:\n";
        for (auto &e : spanningTree)
        {
            cout << e.first << " - " << e.second << endl;
        }
    }

    void bfs(T start)
    {
        for (auto &p : adj)
            visited[p.first] = false;

        queue<T> q;
        visited[start] = true;
        q.push(start);

        cout << "BFS traversal starting from " << start << ": ";

        while (!q.empty())
        {
            T v = q.front();
            q.pop();

            cout << v << " ";

            for (T u : adj[v])
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
