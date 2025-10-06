#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <limits>
#include "Graph.h"
#include "NegativeWeightedGraph.h"
using namespace std;

template <class T = int>
class WeightedGraph : public Graph<T>
{
private:
    vector<vector<pair<T, int>>> weightedAdj;

public:
    WeightedGraph(int vertices) : Graph<T>(vertices)
    {
        weightedAdj.assign(vertices, {});
        cout << "Created Weighted Graph with " << vertices << " vertices.\n";
    }

    void addEdge(T u, T v, int w)
    {
        if (u < 0 || v < 0 || u >= this->n || v >= this->n)
            return;

        weightedAdj[u].push_back({v, w});
        weightedAdj[v].push_back({u, w});
    }

    void dijkstra(T start)
    {
        vector<int> dist(this->n, numeric_limits<int>::max());
        dist[start] = 0;

        priority_queue<pair<int, T>, vector<pair<int, T>>, greater<pair<int, T>>> pq;
        pq.push({0, start});

        while (!pq.empty())
        {
            int d = pq.top().first;
            T v = pq.top().second;
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
        for (int i = 0; i < this->n; i++)
        {
            if (dist[i] == numeric_limits<int>::max())
                cout << i << " : INF\n";
            else
                cout << i << " : " << dist[i] << "\n";
        }
    }
};
