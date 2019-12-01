#include <random>
#include <vector>
#include <iostream>
#include <string>
#include <chrono>
#include "graph.h"
#include "algorithm.h"
#include "parser.h"


template <class TWeightedGraph, class TAlgorithm>
class ExperimentRandGraph : public Experiment<TWeightedGraph, TAlgorithm> {

public:

    static TWeightedGraph createRandomGraph(size_t n, size_t m) {
        TWeightedGraph graph(n);

        std::default_random_engine randGenWeight, randGenVertex;
        std::uniform_int_distribution<Weight> distWeight(MIN_WEIGHT + 1, MAX_WEIGHT - 1);
        std::uniform_int_distribution<Vertex> distVertex(0, n - 1);

        // generate path
        for (size_t i = 0; i + 1 < n; ++i) {
            graph.pushEdge(i, i + 1, distWeight(randGenWeight));
        }

        // generate map of edges
        size_t edgeSize = m - n + 1;
        std::vector<Edge> edgeVector;

        for (size_t i = 0; i < n; ++i)
            for (size_t j = i + 2; j < n; ++j) {
                edgeVector.push_back(Edge(i, j));
            }

        for (size_t i = 0; i < edgeSize; ++i) {
            size_t key = distVertex(randGenVertex) % edgeVector.size();
            graph.pushEdge(edgeVector[key].first, edgeVector[key].second, distWeight(randGenWeight));
            std::swap<Edge, Edge>(edgeVector[key], edgeVector[edgeVector.size() - 1]);
            edgeVector.pop_back();
        }

        return graph;

    }

    static void run(size_t n, size_t m) {

        TWeightedGraph graph = createRandomGraph(n, m);
        TAlgorithm algorithm;

        std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

        TWeightedGraph res = algorithm(graph);

        std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        std::chrono::milliseconds time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

        std::cout << "Time is " << time.count() << " milliseconds";
    }
};


int main(int argc, char** argv) {

    Parser parser;
    ParserStatus status = parser.parse(argc, argv);

    if (status == ParserStatus::HELP)
        return 0;

    if (status == ParserStatus::ERROR) {
        std::cout << "ERROR! Wrong arguments!" << std::endl;
        return 0;
    }

    Launcher launcher(parser);
    launcher.run<ExperimentRandGraph>();

    return 0;
}
