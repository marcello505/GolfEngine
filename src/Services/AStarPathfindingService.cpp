//
// Created by Lucas on 4-12-2022.
//
#include <iostream>
#include <vector>
#include <valarray>
#include "AStarPathfindingService.h"
namespace GolfEngine::Services::Pathfinding {
    AStarPathfindingService::AStarPathfindingService() {

    }

    std::vector<Node> AStarPathfindingService::findPath(const Node& start, const Node& target,const Graph& graph) {

        std::map<int, heuristicValues> weights;
        for (auto &node : graph.nodes) {
            weights[node.id] = {};
        }

        node_priority_queue priority_list(
                [&weights](const Node &lhs, const Node &rhs) {
                    if (weights[lhs.id].f == weights[rhs.id].f) {
                        return weights[lhs.id].h > weights[rhs.id].h;
                    } else {
                        return weights[lhs.id].f > weights[rhs.id].f;
                    }
                });


        weights[start.id].f = 0;
        priority_list.push(start);
        while (!priority_list.empty()){
            // get estimated shortest route
           Node fNode = priority_list.top();
            priority_list.pop();

           if(fNode.id == target.id){
               //Trace back Path
               std::vector<Node> path;

               auto parent = target;
               path.emplace_back(parent);

               while(weights[parent.id].parent != -1){
                   parent = graph.nodes[weights.at(parent.id).parent];
                   path.emplace_back(parent);

               }
               path.pop_back();

                return path;
           }

            //if not at end check edges
            for (auto edge : graph.nodes[fNode.id].edges) {
                auto n = graph.nodes[edge];

                int g = weights[fNode.id].f + 1;
                int h = calculateHeuristic(n, target);
                int f = g + h;

                if(f < weights[n.id].f){
                    weights[n.id].h = h;
                    weights[n.id].f = f;
                    weights[n.id].parent = fNode.id;

                    priority_list.push(n);
                }

            }
        }
        return {};

    }

    int AStarPathfindingService::calculateHeuristic(Node start, Node target) {
        int x = start.position.x - target.position.x;
        int y = start.position.y - target.position.y;
        int res = sqrt(pow(x, 2) + pow(y, 2)) / 32;

        return res;

    }


}