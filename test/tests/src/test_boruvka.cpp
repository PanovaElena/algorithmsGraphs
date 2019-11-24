#include "test_utilities.h"
#include "test_graphs.h"
#include "union_find.h"
#include "boruvkas_algorithm.h"


TEST_ALL_GRAPH_TYPES_AND_UNFINDS(TestBoruvka, TestGraph1) {
    BoruvkasAlgorithm<TWeightedGraph, TUnionFind> boruvkasAlgorithm;

    TWeightedGraph res = boruvkasAlgorithm(graph);

    ASSERT_TRUE(spanningTree == res);
}

TEST_ALL_GRAPH_TYPES_AND_UNFINDS(TestBoruvka, TestGraph2) {
    BoruvkasAlgorithm<TWeightedGraph, TUnionFind> boruvkasAlgorithm;

    TWeightedGraph res = boruvkasAlgorithm(graph);

    ASSERT_TRUE(spanningTree == res);
}