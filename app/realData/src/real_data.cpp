#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "graph.h"
#include "algorithm.h"
#include "parser.h"


template <class TWeightedGraph, class TAlgorithm>
class ExperimentRealData : public Experiment<TWeightedGraph, TAlgorithm> {

public:

    static TWeightedGraph readGraph(size_t& n, size_t& m) {
        const std::string nameFile(DATABASE);

        std::ifstream file(nameFile);

        file >> n >> m;

        TWeightedGraph graph(n);

        while (!file.eof()) {
            Vertex v1, v2;
            Weight w;

            file >> v1 >> v2 >> w;

            graph.pushEdge(v1 - 1, v2 - 1, w);
        }

        file.close();

        return graph;
    }

    static void run(size_t n, size_t m) {

        TWeightedGraph graph = readGraph(n, m);
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
    launcher.run<ExperimentRealData>();

    return 0;
}
