#pragma once
#include <algorithm>
#include <unordered_map>
#include "graph.h"


class AdjacencyListGraph : public Graph {

protected:

    std::vector<std::vector<Vertex>> adjacencyList;
    size_t numEdges = 0;

public:

    AdjacencyListGraph(size_t verticesNumber = 0) {
        initialize(verticesNumber);
    }

    AdjacencyListGraph(size_t verticesNumber, const std::vector<std::pair<Vertex, Vertex>>& edges) {
        initialize(verticesNumber, edges);
    }

    friend bool operator==(const AdjacencyListGraph& graph1, const AdjacencyListGraph& graph2) {
        if (graph1.adjacencyList.size() != graph2.adjacencyList.size())
            return false;

        for (size_t i = 0; i < graph1.adjacencyList.size(); ++i)
            for (size_t j = 0; j < graph1.adjacencyList[i].size(); ++j)
                if (std::find(graph2.adjacencyList[i].begin(), graph2.adjacencyList[i].end(),
                    graph1.adjacencyList[i][j]) == graph2.adjacencyList[i].end())
                    return false;

        return true;
    }

    friend bool operator!=(const AdjacencyListGraph& graph1, const AdjacencyListGraph& graph2) {
        return !(graph1 == graph2);
    }

    void setVerticesNumber(size_t number) override {
        adjacencyList.resize(number);
    }

    size_t getVerticesNumber() const override {
        return adjacencyList.size();
    }

    size_t getEdgesNumber() const override {
        return numEdges;
    }

    // O(1)
    void pushEdge(const Vertex& v1, const Vertex& v2) override {
        adjacencyList[v1].push_back(v2);
        adjacencyList[v2].push_back(v1);

        ++numEdges;
    }

    // O(1)
    std::vector<Vertex> getNeighbours(const Vertex& v) const override {
        return adjacencyList[v];
    }

    // O(m)
    std::vector<Edge> getEdgeList() const override {
        std::vector<Edge> res;
        std::vector<bool> ifCycleAdded(getVerticesNumber(), false);
        for (size_t i = 0; i < adjacencyList.size(); ++i)
            for (size_t j = 0; j < adjacencyList[i].size(); ++j) {
                if (adjacencyList[i][j] > i) {
                    res.push_back(Edge(i, adjacencyList[i][j]));
                }
                else if (adjacencyList[i][j] == i && !ifCycleAdded[i]) {
                    ifCycleAdded[i] = true;
                    res.push_back(Edge(i, i));
                }
            }
        return res;
    }

};


class WeightedAdjacencyListGraph : public WeightedGraph, public AdjacencyListGraph {

    std::vector<std::unordered_map<Vertex, Weight>> weightList;

public:

    WeightedAdjacencyListGraph(size_t verticesNumber = 0) : AdjacencyListGraph(verticesNumber),
        weightList(verticesNumber) {}

    WeightedAdjacencyListGraph(size_t verticesNumber, const std::vector<Edge>& edges,
        const std::vector<Weight>& weights) : AdjacencyListGraph(verticesNumber),
        weightList(verticesNumber) {
        for (size_t i = 0; i < edges.size(); ++i) {
            pushEdge(edges[i].first, edges[i].second, weights[i]);
        }
    }

    Weight getWeight(const Vertex& v1, const Vertex& v2) const override {
        return weightList[v1].find(v2)->second;
    }

    void pushEdge(const Vertex& v1, const Vertex& v2, const Weight& w) override {
        AdjacencyListGraph::pushEdge(v1, v2);
        weightList[v1].emplace(v2, w);
        weightList[v2].emplace(v1, w);
    }
};