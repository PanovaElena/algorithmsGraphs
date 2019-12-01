#pragma once
#include <type_traits>
#include "graph.h"

template<class TGraph,
    class = typename std::enable_if<std::is_base_of<WeightedGraph, TGraph>::value>::type
>
class AlgorithmSpanningTree {

public:

    virtual TGraph operator()(const TGraph& graph) = 0;

};