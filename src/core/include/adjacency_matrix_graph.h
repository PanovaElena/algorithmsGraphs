#pragma once
#include "graph.h"
#include "matrix.h"


// adjacencyMatrix(i, j) is 1 or defaultValue = INF
// if there is not edge (i, j) then adjacencyMatrix(i, j) = defaultValue
class AdjacencyMatrixGraph : public Graph {

protected:

    Matrix<Weight> adjacencyMatrix;
    size_t numEdges = 0;

public:

    AdjacencyMatrixGraph(size_t verticesNumber = 0, Weight defaultValue = MAX_WEIGHT) :
        adjacencyMatrix(defaultValue) {
        initialize(verticesNumber);
    }

    AdjacencyMatrixGraph(size_t verticesNumber, const std::vector<Edge>& edges,
        Weight defaultValue = MAX_WEIGHT) : adjacencyMatrix(defaultValue) {
        initialize(verticesNumber, edges);
    }

    friend bool operator==(const AdjacencyMatrixGraph& graph1, const AdjacencyMatrixGraph& graph2) {
        return graph1.adjacencyMatrix == graph2.adjacencyMatrix;
    }

    friend bool operator!=(const AdjacencyMatrixGraph& graph1, const AdjacencyMatrixGraph& graph2) {
        return !(graph1 == graph2);
    }

    void setVerticesNumber(size_t number) override {
        adjacencyMatrix.resize(number);
    }

    size_t getVerticesNumber() const override {
        return adjacencyMatrix.size();
    }

    size_t getEdgesNumber() const override {
        return numEdges;
    }

    // O(1)
    virtual void pushEdge(const Vertex& v1, const Vertex& v2) override {
        adjacencyMatrix(v1, v2) = 1;
        adjacencyMatrix(v2, v1) = 1;

        ++numEdges;
    }

    // O(n)
    std::vector<Vertex> getNeighbours(const Vertex& v) const override {
        std::vector<Vertex> neighbours;
        for (size_t i = 0; i < adjacencyMatrix.size(); i++) {
            if (adjacencyMatrix(v, i) != adjacencyMatrix.getDefaultValue()) {
                neighbours.push_back(i);
            }
        }
        return neighbours;
    }

    // O(n^2)
    std::vector<Edge> getEdgeList() const override {
        std::vector<Edge> res;
        for (size_t i = 0; i < adjacencyMatrix.size(); ++i)
            for (size_t j = i; j < adjacencyMatrix.size(); ++j)
                if (adjacencyMatrix(i, j) != adjacencyMatrix.getDefaultValue()) {
                    res.push_back(Edge(i, j));
                }
        return res;
    }

};


// adjacencyMatrix(i, j) is a weight of edge (i, j)
// if there is not edge (i, j) then adjacencyMatrix(i, j) = Inf
class WeightedAdjacencyMatrixGraph : public WeightedGraph, public AdjacencyMatrixGraph {

public:

    WeightedAdjacencyMatrixGraph(size_t verticesNumber = 0) :
        AdjacencyMatrixGraph(verticesNumber) {}

    WeightedAdjacencyMatrixGraph(size_t verticesNumber, const std::vector<Edge>& edges,
        const std::vector<Weight>& weights) : AdjacencyMatrixGraph(verticesNumber, edges) {
        for (size_t i = 0; i < edges.size(); ++i) {
            adjacencyMatrix(edges[i].first, edges[i].second) = weights[i];
            adjacencyMatrix(edges[i].second, edges[i].first) = weights[i];
        }
    }

    Weight getWeight(const Vertex& v1, const Vertex& v2) const override {
        return adjacencyMatrix(v1, v2);
    }

    void pushEdge(const Vertex& v1, const Vertex& v2, const Weight& w) override {
        AdjacencyMatrixGraph::pushEdge(v1, v2);
        adjacencyMatrix(v1, v2) = w;
        adjacencyMatrix(v2, v1) = w;
    }

};