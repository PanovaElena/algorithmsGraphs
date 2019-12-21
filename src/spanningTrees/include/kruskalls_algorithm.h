#pragma once
#include <type_traits>
#include "union_find.h"
#include "graph.h"
#include "algorithm.h"

// Kruskall's algorithm
template<class TGraph, template<class> class TUnionFind,
    class = typename std::enable_if<std::is_base_of<WeightedGraph, TGraph>::value>::type,
    class = typename std::enable_if<std::is_base_of<Graph, TGraph>::value>::type,
    class = typename std::enable_if<std::is_base_of<UnionFind<Vertex>, TUnionFind<Vertex>>::value>::type
>
class KruskallsAlgorithm : public AlgorithmSpanningTree<TGraph> {

    // algorithm complexity is 
    // 1) O(m*log(m)+n^2+m) for union-find by array
    // 2) O(m*log(m)+m*log(n)+m) ~ O(m*log(n)) for union-find by ranks
    // 3) O(m*log(m)+m*superlog(n)+n) ~ O(m*log(n)) for union-find by ranks with compressing paths

    // it may be possible to use linear sort for weights of edges
    // so the best complexity can be O(m+m*superlog(n)) ~ O(m)

public:

    TGraph operator()(const TGraph& graph) override {
        const size_t numVertices = graph.getVerticesNumber();

        TGraph res(numVertices);
        TUnionFind<Vertex> divSet(numVertices);

        for (Vertex i = 0; i < numVertices; ++i) {
            divSet.make(i);
        }

        std::vector<Edge> edgeList = graph.getEdgeList();
        std::sort(edgeList.begin(), edgeList.end(), [&graph](const Edge& edge1, const Edge& edge2) {  // O(m*log(m))
            return graph.getWeight(edge1.first, edge1.second) < graph.getWeight(edge2.first, edge2.second);
        });


        for (size_t i = 0; i < edgeList.size() && res.getEdgesNumber() < numVertices - 1; ++i) {  // O(m)
            Vertex x = divSet.find(edgeList[i].first);  // O(1), O(log(n)) or O(superlog(n)) for different union-finds
            Vertex y = divSet.find(edgeList[i].second);

            if (x != y) {
                res.pushEdge(edgeList[i].first, edgeList[i].second,
                    graph.getWeight(edgeList[i].first, edgeList[i].second));
                divSet.unite(x, y);  // O(n) or O(1) for different union-finds
            }
        }

        return res;
    }
};