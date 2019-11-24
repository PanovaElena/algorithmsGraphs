#pragma once
#include <unordered_map>
#include "graph.h"

class EdgeListGraph : public Graph {

    size_t numVertices;
    std::vector<Edge> edgeList;

public:

    EdgeListGraph(size_t verticesNumber = 0) {
        initialize(verticesNumber);
    }

    EdgeListGraph(size_t verticesNumber, const std::vector<std::pair<Vertex, Vertex>>& edges) {
        initialize(verticesNumber, edges);
    }

    friend bool operator==(const EdgeListGraph& graph1, const EdgeListGraph& graph2) {
        if (graph1.numVertices != graph2.numVertices ||
            graph1.edgeList.size() != graph2.edgeList.size())
            return false;

        for (size_t i = 0; i < graph1.edgeList.size(); ++i)
            if (std::find(graph2.edgeList.begin(), graph2.edgeList.end(), graph1.edgeList[i]) == graph2.edgeList.end() &&
                std::find(graph2.edgeList.begin(), graph2.edgeList.end(),
                    Edge(graph1.edgeList[i].second, graph1.edgeList[i].first)) == graph2.edgeList.end())
                return false;

        return true;
    }

    friend bool operator!=(const EdgeListGraph& graph1, const EdgeListGraph& graph2) {
        return !(graph1 == graph2);
    }

    void setVerticesNumber(size_t number) override {
        numVertices = number;
    }

    size_t getVerticesNumber() const override {
        return numVertices;
    }

    size_t getEdgesNumber() const override {
        return edgeList.size();
    }

    void pushEdge(const Vertex& v1, const Vertex& v2) override {
        edgeList.push_back(Edge(v1, v2));
    }

    std::vector<Vertex> getNeighbours(const Vertex& v) const override {
        std::vector<Vertex> res;
        for (size_t i = 0; i < edgeList.size(); ++i) {
            if (edgeList[i].first == v) {
                res.push_back(edgeList[i].second);
            }
            else if (edgeList[i].second == v) {
                res.push_back(edgeList[i].first);
            }
        }
        return res;
    }

    std::vector<Edge> getEdgeList() const override {
        return edgeList;
    }
};


class WeightedEdgeListGraph : public WeightedGraph, public EdgeListGraph {

    std::vector<std::unordered_map<Vertex, Weight>> weightList;

public:

    WeightedEdgeListGraph(size_t verticesNumber = 0) : EdgeListGraph(verticesNumber),
        weightList(verticesNumber) {}

    WeightedEdgeListGraph(size_t verticesNumber, const std::vector<Edge>& edges,
        const std::vector<Weight>& weights) : EdgeListGraph(verticesNumber),
        weightList(verticesNumber) {
        for (size_t i = 0; i < edges.size(); ++i) {
            pushEdge(edges[i].first, edges[i].second, weights[i]);
        }
    }

    Weight getWeight(const Vertex& v1, const Vertex& v2) const override {
        if (weightList[v1].find(v2) != weightList[v1].end())
            return weightList[v1].find(v2)->second;

        if (weightList[v2].find(v1) != weightList[v2].end())
            return weightList[v2].find(v1)->second;

        return MAX_WEIGHT;
    }

    void pushEdge(const Vertex& v1, const Vertex& v2, const Weight& w) override {
        EdgeListGraph::pushEdge(v1, v2);
        weightList[v1].emplace(v2, w);
    }
};
