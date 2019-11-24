#pragma once
#include "gtest.h"
#include "graph.h"
#include "adjacency_matrix_graph.h"
#include "adjacency_list_graph.h"
#include "edge_list_graph.h"
#include "union_find.h"


#define TEST_ANY_GRAPH_TYPE_AND_UNFIND(test_case, test_graph, wgraph_t, unfind_t) \
typedef test_case##_##test_graph##_template_all_graphs_types_and_unfinds<wgraph_t, unfind_t> \
    test_case##_##test_graph##_##wgraph_t##_##unfind_t; \
TEST_F(test_case##_##test_graph##_##wgraph_t##_##unfind_t, test) { \
    testBody(); \
}

#define TEST_ALL_GRAPH_TYPES_AND_UNFINDS(test_case, test_graph) \
template <class TWeightedGraph, template<class> class TUnionFind> \
class test_case##_##test_graph##_template_all_graphs_types_and_unfinds : \
    public test_graph<TWeightedGraph>, public testing::Test { \
public: \
    void testBody(); \
}; \
\
TEST_ANY_GRAPH_TYPE_AND_UNFIND(test_case, test_graph, WeightedEdgeListGraph, UnionFindByArray) \
TEST_ANY_GRAPH_TYPE_AND_UNFIND(test_case, test_graph, WeightedEdgeListGraph, UnionFindByRanks) \
TEST_ANY_GRAPH_TYPE_AND_UNFIND(test_case, test_graph, WeightedEdgeListGraph, UnionFindByRanksWithPathCompressing) \
TEST_ANY_GRAPH_TYPE_AND_UNFIND(test_case, test_graph, WeightedAdjacencyListGraph, UnionFindByArray) \
TEST_ANY_GRAPH_TYPE_AND_UNFIND(test_case, test_graph, WeightedAdjacencyListGraph, UnionFindByRanks) \
TEST_ANY_GRAPH_TYPE_AND_UNFIND(test_case, test_graph, WeightedAdjacencyListGraph, UnionFindByRanksWithPathCompressing) \
TEST_ANY_GRAPH_TYPE_AND_UNFIND(test_case, test_graph, WeightedAdjacencyMatrixGraph, UnionFindByArray) \
TEST_ANY_GRAPH_TYPE_AND_UNFIND(test_case, test_graph, WeightedAdjacencyMatrixGraph, UnionFindByRanks) \
TEST_ANY_GRAPH_TYPE_AND_UNFIND(test_case, test_graph, WeightedAdjacencyMatrixGraph, UnionFindByRanksWithPathCompressing) \
\
template <class TWeightedGraph, template<class> class TUnionFind> \
void test_case##_##test_graph##_template_all_graphs_types_and_unfinds<TWeightedGraph, TUnionFind>::testBody()


#define TEST_ANY_GRAPH_TYPE(test_case, test_graph, wgraph_t) \
typedef test_case##_##test_graph##_template_all_graph_types<wgraph_t> test_case##_##test_graph##_##wgraph_t; \
TEST_F(test_case##_##test_graph##_##wgraph_t, test) { \
    testBody(); \
}

#define TEST_ALL_GRAPH_TYPES(test_case, test_graph) \
template <class TWeightedGraph> \
class test_case##_##test_graph##_template_all_graph_types : \
    public test_graph<TWeightedGraph>, public testing::Test { \
public: \
    void testBody(); \
}; \
\
TEST_ANY_GRAPH_TYPE(test_case, test_graph, WeightedAdjacencyListGraph) \
TEST_ANY_GRAPH_TYPE(test_case, test_graph, WeightedAdjacencyMatrixGraph) \
TEST_ANY_GRAPH_TYPE(test_case, test_graph, WeightedEdgeListGraph) \
\
template <class TWeightedGraph> \
void test_case##_##test_graph##_template_all_graph_types<TWeightedGraph>::testBody()