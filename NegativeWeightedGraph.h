#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <limits>
#include <unordered_map>
#include "WeightedGraph.h"
using namespace std;
#include <unordered_map>

template <typename T>
class NegativeWeightedGraph : public WeightedGraph<T>
{
public:
    NegativeWeightedGraph()
    {
        cout << "Created Negative Weighted Graph.\n";
    }

    void bellmanFord(const T &start) override
    {
        unordered_map<T, int> dist;
        for (auto &[v, _] : this->weightedAdj)
            dist[v] = numeric_limits<int>::max();
        dist[start] = 0;

        int n = this->weightedAdj.size();

        for (int i = 1; i < n; i++)
        {
            for (auto &[u, edges] : this->weightedAdj)
            {
                for (auto &[v, w] : edges)
                {
                    if (dist[u] != numeric_limits<int>::max() && dist[u] + w < dist[v])
                    {
                        dist[v] = dist[u] + w;
                    }
                }
            }
        }

        for (auto &[u, edges] : this->weightedAdj)
        {
            for (auto &[v, w] : edges)
            {
                if (dist[u] != numeric_limits<int>::max() && dist[u] + w < dist[v])
                {
                    cout << "Graph contains a negative weight cycle!\n";
                    return;
                }
            }
        }

        cout << "Shortest distances from " << start << ":\n";
        for (auto &[v, d] : dist)
        {
            if (d == numeric_limits<int>::max())
                cout << v << " : INF\n";
            else
                cout << v << " : " << d << "\n";
        }
    }
};
