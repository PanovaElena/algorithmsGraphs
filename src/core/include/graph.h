#pragma once
#include <vector>
#include <functional>

typedef int Weight;

const Weight MAX_WEIGHT = std::numeric_limits<Weight>::max();
const Weight MIN_WEIGHT = std::numeric_limits<Weight>::min();

typedef size_t Vertex;
typedef std::pair<Vertex, Vertex> Edge;

// undirected graph without multiple edges
// vertices are integers from zero to number of vertices
class Graph {

public:

    void initialize(size_t verticesNumber = 0) {
        setVerticesNumber(verticesNumber);
    }

    void initialize(size_t verticesNumber, const std::vector<Edge>& edges) {
        setVerticesNumber(verticesNumber);
        for (size_t i = 0; i < edges.size(); ++i) {
            pushEdge(edges[i].first, edges[i].second);
        }
    }

    virtual void setVerticesNumber(size_t number) = 0;

    // get number of vertices or edges, O(1)
    virtual size_t getVerticesNumber() const = 0;
    virtual size_t getEdgesNumber() const = 0;

    // push edge O(1)
    virtual void pushEdge(const Vertex& v1, const Vertex& v2) = 0;

    // get neighbours for vertex, O(1), O(n) or O(m) for different graph types
    virtual std::vector<Vertex> getNeighbours(const Vertex& v) const = 0;

    // get list of edges, O(1) or O(m) for different graph types
    virtual std::vector<Edge> getEdgeList() const = 0;  // O(m), O(n^2) or O(1) for different graph types

};


class WeightedGraph {

public:

    // find weight of edge, O(1)
    virtual Weight getWeight(const Vertex& v1, const Vertex& v2) const = 0;

    // push edge with its weight, O(1)
    virtual void pushEdge(const Vertex& v1, const Vertex& v2, const Weight& w) = 0;

};
