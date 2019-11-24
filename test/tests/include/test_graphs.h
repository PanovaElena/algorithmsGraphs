#pragma once
#include "graph.h"


template<class TGraph>
class TestGraph1 {

public:

    size_t numVertices;
    TGraph graph;
    TGraph spanningTree;

    TestGraph1() : numVertices(8), graph(numVertices),
        spanningTree(numVertices) {

        graph.pushEdge(0, 1, 1);
        graph.pushEdge(0, 6, 8);
        graph.pushEdge(0, 2, 3);
        graph.pushEdge(2, 6, 4);
        graph.pushEdge(2, 3, 4);
        graph.pushEdge(2, 5, 9);
        graph.pushEdge(3, 4, 1);
        graph.pushEdge(4, 5, 2);
        graph.pushEdge(5, 7, 3);
        graph.pushEdge(5, 6, 5);

        spanningTree.pushEdge(0, 1, 1);
        spanningTree.pushEdge(0, 2, 3);
        spanningTree.pushEdge(2, 6, 4);
        spanningTree.pushEdge(2, 3, 4);
        spanningTree.pushEdge(3, 4, 1);
        spanningTree.pushEdge(4, 5, 2);
        spanningTree.pushEdge(5, 7, 3);
    }
};


// graph with edges (v, v)
template<class TGraph>
class TestGraph2 {

public:

    size_t numVertices;
    TGraph graph;
    TGraph spanningTree;

    TestGraph2() : numVertices(7), graph(numVertices),
        spanningTree(numVertices) {

        //graph.pushEdge(0, 0, 0);
        graph.pushEdge(0, 1, 7);
        graph.pushEdge(0, 3, 5);
        graph.pushEdge(1, 2, 8);
        graph.pushEdge(1, 3, 9);
        graph.pushEdge(1, 4, 7);
        graph.pushEdge(2, 4, 5);
        graph.pushEdge(3, 4, 15);
        graph.pushEdge(3, 5, 6);
        graph.pushEdge(4, 5, 8);
        //graph.pushEdge(4, 4, 1);
        graph.pushEdge(4, 6, 9);
        graph.pushEdge(5, 6, 11);

        spanningTree.pushEdge(0, 1, 7);
        spanningTree.pushEdge(0, 3, 5);
        spanningTree.pushEdge(1, 4, 7);
        spanningTree.pushEdge(2, 4, 5);
        spanningTree.pushEdge(3, 5, 6);
        spanningTree.pushEdge(4, 6, 9);
    }
};
