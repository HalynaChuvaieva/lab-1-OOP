#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <limits>
#include "Graph.h"
using namespace std;

template <typename T>
class UndirectedGraph : public Graph<T>
{
private:
    bool dfsCycleUndirected(const T &v, const T &parent)
    {
        this->visited[v] = true;
        for (const T &u : this->adj[v])
        {
            if (!this->visited[u])
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
    UndirectedGraph() { cout << "Created Undirected Graph.\n"; }
    void addEdge(const T &u, const T &v) override
    {
        this->adj[u].push_back(v);
        this->adj[v].push_back(u);
        this->visited[u] = false;
        this->visited[v] = false;
    }
    bool isCyclic()
    {
        for (auto &v : this->visited)
            v.second = false;
        for (auto &[vertex, _] : this->adj)
        {
            if (!this->visited[vertex])
            {
                if (dfsCycleUndirected(vertex, vertex))
                    return true;
            }
        }
        return false;
    }
};