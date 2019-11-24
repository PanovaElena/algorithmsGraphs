#pragma once
#include <type_traits>
#include <unordered_set>
#include "union_find.h"
#include "graph.h"

// Boruvka's algorithm
template<class TGraph, template<class> class TUnionFind,
    class = typename std::enable_if<std::is_base_of<WeightedGraph, TGraph>::value>::type,
    class = typename std::enable_if<std::is_base_of<Graph, TGraph>::value>::type,
    class = typename std::enable_if<std::is_base_of<UnionFind<Vertex>, TUnionFind<Vertex>>::value>::type
>
class BoruvkasAlgorithm {

    // algorithm complexity is
    // O(n^2+m*log(n)) for union-find by array
    // O(m*(log(n))^2+n*log(n)) = O(m*(log(n))^2) for union-find by ranks
    // O((m*log(n)+n)*superlog(n)) ~ O(m*log(n)) for union-find by ranks with compressing paths

public:

    TGraph operator()(const TGraph& graph) {
        const size_t n = graph.getVerticesNumber();

        TGraph res(n);

        std::vector<Edge> edgeList = graph.getEdgeList();

        TUnionFind<Vertex> divSet(n);

        for (Vertex i = 0; i < n; ++i) {
            divSet.make(i);
        }

        while (res.getEdgesNumber() < n - 1) {  // O(log(n))

            std::vector<Weight> minWeightComp(n, MAX_WEIGHT);
            std::vector<Edge> minWeightEdgeComp(n);

            for (size_t i = 0; i < edgeList.size(); ++i) {  // O(m)
                Vertex x = divSet.find(edgeList[i].first);  // O(1), O(log(n)) or O(superlog(n)) for different union-finds
                Vertex y = divSet.find(edgeList[i].second);

                Weight weight = graph.getWeight(edgeList[i].first, edgeList[i].second);

                if (x != y) {
                    if (minWeightComp[x] > weight) {
                        minWeightComp[x] = weight;
                        minWeightEdgeComp[x] = edgeList[i];
                    }
                    if (minWeightComp[y] > weight) {
                        minWeightComp[y] = weight;
                        minWeightEdgeComp[y] = edgeList[i];
                    }
                }
            }

            for (size_t i = 0; i < minWeightComp.size(); ++i) {  // O(n) at all
                if (minWeightComp[i] != MAX_WEIGHT) {
                    Edge edge = minWeightEdgeComp[i];

                    Vertex x = divSet.find(edge.first);  // O(1), O(log(n)) or O(superlog(n)) for different union-finds
                    Vertex y = divSet.find(edge.second);

                    if (x != y) {
                        res.pushEdge(edge.first, edge.second, minWeightComp[i]);
                        divSet.unite(x, y);  // O(n) or O(1) for different union-finds
                    }
                }
            }

        }

        return res;
    }
};
