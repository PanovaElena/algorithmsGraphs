#include "test_utilities.h"
#include "test_graphs.h"
#include "prims_algorithm.h"
#include "priority_queue.h"


TEST_ALL_GRAPH_TYPES(TestPrimByArray, TestGraph1) {
    PrimsAlgorithm<TWeightedGraph, PriorityQueueByArray> primsAlgorithm;

    TWeightedGraph res = primsAlgorithm(graph);

    ASSERT_TRUE(spanningTree == res);
}

TEST_ALL_GRAPH_TYPES(TestPrimByArray, TestGraph2) {
    PrimsAlgorithm<TWeightedGraph, PriorityQueueByArray> primsAlgorithm;

    TWeightedGraph res = primsAlgorithm(graph);

    ASSERT_TRUE(spanningTree == res);
}


TEST_ALL_GRAPH_TYPES(TestPrimByHeap, TestGraph1) {
    PrimsAlgorithm<TWeightedGraph, PriorityQueueByHeap> primsAlgorithm;

    TWeightedGraph res = primsAlgorithm(graph);

    ASSERT_TRUE(spanningTree == res);
}

TEST_ALL_GRAPH_TYPES(TestPrimByHeap, TestGraph2) {
    PrimsAlgorithm<TWeightedGraph, PriorityQueueByHeap> primsAlgorithm;

    TWeightedGraph res = primsAlgorithm(graph);

    ASSERT_TRUE(spanningTree == res);
}