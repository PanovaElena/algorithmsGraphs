#pragma once
#include <type_traits>
#include <vector>
#include "graph.h"
#include "priority_queue.h"


// Prim's algorithm
template<class TGraph, template <class, class> class TPriorityQueue,
    class = typename std::enable_if<std::is_base_of<WeightedGraph, TGraph>::value>::type,
    class = typename std::enable_if<std::is_base_of<Graph, TGraph>::value>::type,
    class = typename std::enable_if<std::is_base_of<PriorityQueue<Vertex, Weight>, TPriorityQueue<Vertex, Weight>>::value>::type
>
class PrimsAlgorithm {

    // algorithm complexity is
    // O(n^2+m) = O(n^2) for array of weights of projections
    // O((n+m)*log(n)) = O(m*log(n)) for d-heap of weights of projections

public:

    TGraph operator()(const TGraph& graph) {
        const size_t n = graph.getVerticesNumber();

        TGraph res(n);
        TPriorityQueue<Vertex, Weight> projWeightQueue(n, MAX_WEIGHT);  // queue for vertices
        std::vector<Vertex> projBase(n, n);

        Vertex root = 0;
        projWeightQueue.decreasePriority(root, MIN_WEIGHT);
        projWeightQueue.exactMin();

        std::vector<Vertex> neighboursRoot = graph.getNeighbours(root);
        for (size_t i = 0; i < neighboursRoot.size(); i++) {
            Weight neighbourWeight = graph.getWeight(root, neighboursRoot[i]);

            projWeightQueue.decreasePriority(neighboursRoot[i], neighbourWeight); // O(log(n))
            projBase[neighboursRoot[i]] = root;
        }

        while (res.getEdgesNumber() < n - 1) {  // O(n)
            std::pair<Vertex, Weight> minPair = projWeightQueue.exactMin();  // O(n) or O(log(n))
            Vertex current = minPair.first;
            Weight currentWeight = minPair.second;

            res.pushEdge(current, projBase[current], currentWeight);

            std::vector<Vertex> neighbours = graph.getNeighbours(current);

            for (size_t j = 0; j < neighbours.size(); j++) {  // O(m) at all
                Weight neighbourWeight = graph.getWeight(current, neighbours[j]);

                if (projWeightQueue.isInQueue(neighbours[j]) &&
                    projWeightQueue.getPriority(neighbours[j]) > neighbourWeight) {

                    projWeightQueue.decreasePriority(neighbours[j], neighbourWeight);  // O(1) or O(log(n))
                    projBase[neighbours[j]] = current;
                }
            }
        }

        return res;
    }

};