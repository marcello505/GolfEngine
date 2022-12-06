//
// Created by olafv on 12/6/2022.
//

#ifndef GOLFENGINE_GRAPH_H
#define GOLFENGINE_GRAPH_H
#include <vector>
#include <map>


class Graph {
public:
    Graph(const std::vector<int>& nodes, std::vector<std::pair<int,int>> edges);
    std::map<int, std::vector<int>> nodeList;
private:
    void AddNode(int node);
    void AddEdge(std::pair<int, int> edge);
};


#endif //GOLFENGINE_GRAPH_H
