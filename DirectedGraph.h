#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <limits>
#include "Graph.h"
using namespace std;
#include <unordered_map>

template <class T>
class DirectedGraph : public Graph<T>
{
private:
    bool dfsCycleDirected(T v, unordered_map<T, int> &state)
    {
        state[v] = 1;

        for (T u : this->adj[v])
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
    DirectedGraph()
    {
        cout << "Created Directed Graph.\n";
    }

    void addEdge(T u, T v) override
    {
        this->adj[u].push_back(v);
    }

    int getOutDegree(T v) const
    {
        auto it = this->adj.find(v);
        if (it != this->adj.end())
            return it->second.size();
        return 0;
    }

    int getInDegree(T v) const
    {
        int in_degree = 0;
        for (auto &p : this->adj)
        {
            for (T neighbor : p.second)
            {
                if (neighbor == v)
                    in_degree++;
            }
        }
        return in_degree;
    }

    bool isCyclic()
    {
        unordered_map<T, int> state;
        for (auto &p : this->adj)
            state[p.first] = 0;

        for (auto &p : this->adj)
        {
            if (state[p.first] == 0)
            {
                if (dfsCycleDirected(p.first, state))
                    return true;
            }
        }
        return false;
    }
};