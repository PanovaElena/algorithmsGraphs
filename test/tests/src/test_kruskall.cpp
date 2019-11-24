#include "test_utilities.h"
#include "test_graphs.h"
#include "union_find.h"
#include "kruskalls_algorithm.h"


TEST_ALL_GRAPH_TYPES_AND_UNFINDS(TestKruskall, TestGraph1) {
    KruskallsAlgorithm<TWeightedGraph, TUnionFind> kruskallsAlgorithm;

    TWeightedGraph res = kruskallsAlgorithm(graph);

    ASSERT_TRUE(spanningTree == res);
}


TEST_ALL_GRAPH_TYPES_AND_UNFINDS(TestKruskall, TestGraph2) {
    KruskallsAlgorithm<TWeightedGraph, TUnionFind> kruskallsAlgorithm;

    TWeightedGraph res = kruskallsAlgorithm(graph);

    ASSERT_TRUE(spanningTree == res);
}