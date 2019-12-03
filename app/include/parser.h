#include <unordered_map>
#include <string>
#include <iostream>
#include <functional>
#include "graph.h"
#include "adjacency_list_graph.h"
#include "adjacency_matrix_graph.h"
#include "edge_list_graph.h"
#include "boruvkas_algorithm.h"
#include "prims_algorithm.h"
#include "kruskalls_algorithm.h"
#include "union_find.h"
#include "priority_queue.h"


enum ParserStatus {
    OK,
    HELP,
    ERROR
};

enum AlgorithmEnum {
    noAlgorithm,
    boruvka,
    kruskall,
    prim
};

enum GraphEnum {
    noGraph,
    adjMatrix,
    adjList,
    edgeList
};

enum UnionFindEnum {
    noUnionFind,
    unionFindByArray,
    unionFindByRanks,
    unionFindByRanksPathComp
};

enum PriorityQueueEnum {
    noQueue,
    queueByArray,
    queueByHeap
};


template <class TWeightedGraph, class TAlgorithm>
class Experiment {

public:

    static void run(size_t n, size_t m) {}

};


class Parser {

    template <class T>
    class CommandArgs {

        const std::vector<std::pair<std::string, T>> args;

    public:

        CommandArgs(const std::vector<std::pair<std::string, T>> & args) : args(args) {}

        std::string find(const T& t) const {
            for (size_t i = 0; i < args.size(); ++i) {
                if (args[i].second == t)
                    return args[i].first;
            }
            return "";
        }

        T find(const std::string& s) const {
            for (size_t i = 0; i < args.size(); ++i) {
                if (args[i].first == s)
                    return args[i].second;
            }
            return T(0);
        }

    };

    const CommandArgs<GraphEnum> argsGraph;
    const CommandArgs<AlgorithmEnum> argsAlgorithm;
    const CommandArgs<PriorityQueueEnum> argsPriorityQueue;
    const CommandArgs<UnionFindEnum> argsUnionFind;

public:

    size_t n, m;
    PriorityQueueEnum priorityQueue = PriorityQueueEnum::noQueue;
    GraphEnum graphType = GraphEnum::noGraph;
    AlgorithmEnum algorithm = AlgorithmEnum::noAlgorithm;
    UnionFindEnum unionFind = UnionFindEnum::noUnionFind;


    Parser() : argsGraph({ {"adjm", GraphEnum::adjMatrix},{"adjl", GraphEnum::adjList},{"edgl", GraphEnum::edgeList} }),
        argsAlgorithm({ {"boruvka", AlgorithmEnum::boruvka},{"kruskall", AlgorithmEnum::kruskall},{"prim", AlgorithmEnum::prim} }),
        argsPriorityQueue({ {"array", PriorityQueueEnum::queueByArray},{"heap", PriorityQueueEnum::queueByHeap} }),
        argsUnionFind({ {"array", UnionFindEnum::unionFindByArray},{"ranks", UnionFindEnum::unionFindByRanks},
            {"rpc", UnionFindEnum::unionFindByRanksPathComp} }) {}


    ParserStatus parse(int& argc, char** argv) {

        if (argc == 2 && std::string(argv[1]) == "-help") {
            printHelp();
            return ParserStatus::HELP;
        }

        if (argc != 6)
            return ParserStatus::ERROR;

        n = std::stoll(std::string(argv[1]));
        m = std::stoll(std::string(argv[2]));

        if (m < n - 1)
            return ParserStatus::ERROR;

        graphType = argsGraph.find(std::string(argv[3]));
        algorithm = argsAlgorithm.find(std::string(argv[4]));

        if (graphType == GraphEnum::noGraph ||
            algorithm == AlgorithmEnum::noAlgorithm)
            return ParserStatus::ERROR;

        if (algorithm == AlgorithmEnum::prim) {
            priorityQueue = argsPriorityQueue.find(std::string(argv[5]));

            if (priorityQueue == PriorityQueueEnum::noQueue)
                return ParserStatus::ERROR;
        }
        else {
            unionFind = argsUnionFind.find(std::string(argv[5]));

            if (unionFind == UnionFindEnum::noUnionFind)
                return ParserStatus::ERROR;
        }

        return ParserStatus::OK;
    }

    void printHelp() const {
        std::cout <<

            "The first and the second args is number of vertices and edges (n, m)\n\n" <<

            "The third arg is type of weighted graph:\n" <<
            argsGraph.find(GraphEnum::adjMatrix) << " -- adjecency matrix\n" <<
            argsGraph.find(GraphEnum::adjList) << " -- adjecency list\n" <<
            argsGraph.find(GraphEnum::edgeList) << " -- list of edges\n\n" <<

            "The fourth arg is alorithm:\n" <<
            argsAlgorithm.find(AlgorithmEnum::boruvka) << " -- boruvka's algorithm\n" <<
            argsAlgorithm.find(AlgorithmEnum::kruskall) << " -- kruskall's algorithm\n" <<
            argsAlgorithm.find(AlgorithmEnum::prim) << " -- prim's algorithm\n\n" <<

            "The fifst arg is union-find (for boruvka's and kruskall's alorithms):\n" <<
            argsUnionFind.find(UnionFindEnum::unionFindByArray) << " -- union-find by array\n" <<
            argsUnionFind.find(UnionFindEnum::unionFindByRanks) << " -- union-find by ranks\n" <<
            argsUnionFind.find(UnionFindEnum::unionFindByRanksPathComp) << " -- union-find by ranks with path compressing\n\n" <<

            "Or the fifst arg is priority queue type (for prim's alorithms):\n" <<
            argsPriorityQueue.find(PriorityQueueEnum::queueByArray) << " -- priority queue by array\n" <<
            argsPriorityQueue.find(PriorityQueueEnum::queueByHeap) << " -- priority queue by 2-heap\n\n" <<

            std::endl;
    }

};


class Launcher {

private:

    std::reference_wrapper<Parser> parser;

public:

    Launcher(Parser& parser) : parser(parser) {}

    template <template <class, class> class TExperiment>
    void run() {
        runExperiment<TExperiment>(parser.get().n, parser.get().m,
            parser.get().graphType, parser.get().algorithm,
            parser.get().unionFind, parser.get().priorityQueue);
    }

private:

    template <template <class, class> class TExperiment>
    void runExperiment(size_t n, size_t m, GraphEnum graphType, AlgorithmEnum algorithm,
        UnionFindEnum unionFind, PriorityQueueEnum priorityQueue) {
        switch (graphType)
        {

        case GraphEnum::adjMatrix:
            runExperiment<WeightedAdjacencyMatrixGraph, TExperiment>(n, m, algorithm, unionFind, priorityQueue);
            break;

        case GraphEnum::adjList:
            runExperiment<WeightedAdjacencyListGraph, TExperiment>(n, m, algorithm, unionFind, priorityQueue);
            break;

        case GraphEnum::edgeList:
            runExperiment<WeightedEdgeListGraph, TExperiment>(n, m, algorithm, unionFind, priorityQueue);
            break;

        default:
            break;
        }
    }

    template <class TWeightedGraph, template <class, class> class TExperiment>
    void runExperiment(size_t n, size_t m, AlgorithmEnum algorithm,
        UnionFindEnum unionFind, PriorityQueueEnum priorityQueue) {
        switch (algorithm) {

        case AlgorithmEnum::boruvka:
            switch (unionFind)
            {
            case UnionFindEnum::unionFindByArray:
                TExperiment<TWeightedGraph,
                    BoruvkasAlgorithm<TWeightedGraph, UnionFindByArray>>::run(n, m);
                break;

            case UnionFindEnum::unionFindByRanks:
                TExperiment<TWeightedGraph,
                    BoruvkasAlgorithm<TWeightedGraph, UnionFindByRanks>>::run(n, m);
                break;

            case UnionFindEnum::unionFindByRanksPathComp:
                TExperiment<TWeightedGraph,
                    BoruvkasAlgorithm<TWeightedGraph, UnionFindByRanksWithPathCompressing>>::run(n, m);
                break;

            default:
                break;
            }
            break;

        case AlgorithmEnum::kruskall:
            switch (unionFind)
            {
            case UnionFindEnum::unionFindByArray:
                TExperiment<TWeightedGraph,
                    KruskallsAlgorithm<TWeightedGraph, UnionFindByArray>>::run(n, m);
                break;

            case UnionFindEnum::unionFindByRanks:
                TExperiment<TWeightedGraph,
                    KruskallsAlgorithm<TWeightedGraph, UnionFindByRanks>>::run(n, m);
                break;

            case UnionFindEnum::unionFindByRanksPathComp:
                TExperiment<TWeightedGraph,
                    KruskallsAlgorithm<TWeightedGraph, UnionFindByRanksWithPathCompressing>>::run(n, m);
                break;

            default:
                break;
            }
            break;

        case AlgorithmEnum::prim:
            switch (priorityQueue)
            {
            case PriorityQueueEnum::queueByArray:
                TExperiment<TWeightedGraph,
                    PrimsAlgorithm<TWeightedGraph, PriorityQueueByArray>>::run(n, m);
                break;

            case PriorityQueueEnum::queueByHeap:
                TExperiment<TWeightedGraph,
                    PrimsAlgorithm<TWeightedGraph, PriorityQueueByHeap>>::run(n, m);
                break;

            default:
                break;
            }
            break;

        default:
            break;
        }
    }

};