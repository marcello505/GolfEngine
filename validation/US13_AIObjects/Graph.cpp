//
// Created by olafv on 12/6/2022.
//

#include "Graph.h"

Graph::Graph(std::vector<int> nodes, std::map<int, int> edges) {

    for (auto node : nodes){
        AddNode(node);
    }
    for (auto edge : edges){
        AddEdge(edge);
    }
}

void Graph::AddNode(int node){
    nodeList[node] = std::vector<int>();
}

void Graph::AddEdge(std::pair<int, int> edge){
    if (nodeList.count(edge.first) > 0 && nodeList.count(edge.second) > 0)
    {
        nodeList[edge.first].push_back(edge.second);
        nodeList[edge.second].push_back(edge.first);
    }
}

