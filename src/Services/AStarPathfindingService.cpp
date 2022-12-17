//
// Created by Lucas on 4-12-2022.
//
#include <iostream>
#include <vector>
#include <valarray>
#include "AStarPathfindingService.h"
#include "Services/Singletons/PathfindingSingleton.h"
#include "Services/Singletons/RenderSingleton.h"
#include "Scene/Components/Collider.h"
#include "Scene/RenderShape/CircleRenderShape.h"
#include "Services/Singletons/PhysicsSingleton.h"

namespace GolfEngine::Services::Pathfinding {
    void AStarPathfindingService::findPathEveryTick(){
        int pathsCalculated = 0;
        // checks if any Pathfinding component needs update of his path
        for (auto& pathfindingComponent : _pathfindingComponents) {
            if(pathfindingComponent.get().needsNewPath() && !_graph->nodes.empty()){
                auto startNode = covertPosToNode(pathfindingComponent.get().getParentGameObjectPosition());
                auto targetNode = covertPosToNode(pathfindingComponent.get().getTargetPosition());
                pathfindingComponent.get().setPath(findPath(startNode,targetNode, *_graph));
                if(pathsCalculated++ >= _maxPathsToCalculatePerTic) break;
            }
        }

        if(_graph) _graph->updateGraphColors();
    }

    std::vector<Node> AStarPathfindingService::findPath(Node& start, Node& target, Graph& graph) {
        // Create map were all wights are saved
        std::map<int, heuristicValues> weights;
        for (auto &node : graph.nodes) {
            weights[node.id] = {};
            node.tag = NodeTags::None;
        }

        //Create priorityQueue where weight of node is considered
        node_priority_queue priority_list(
                [&weights](const Node &lhs, const Node &rhs) {
                    if (weights[lhs.id].f == weights[rhs.id].f) {
                        return weights[lhs.id].h > weights[rhs.id].h;
                    } else {
                        return weights[lhs.id].f > weights[rhs.id].f;
                    }
                });

        //Insert first startNode
        weights[start.id].f = 0;
        priority_list.push(start);

        while (!priority_list.empty()){
            // get estimated shortest route
           Node fNode = priority_list.top();
           priority_list.pop();

           //check if current node is equal to end node
           if(fNode.id == target.id){
               //Trace back Path
               std::vector<Node> path;

               Node* parent = &target;
               path.emplace_back(*parent);
               parent->tag = NodeTags::Path;

               //sets path by getting all parents untill parent is equal to -1
               while(weights[parent->id].parent != -1){
                   parent = &graph.nodes[weights.at(parent->id).parent];

                   //adds and tags all nodes in path
                   path.emplace_back(*parent);
                   parent->tag = NodeTags::Path;
               }
               path.pop_back();
               //Display Visited
               return path;
           }

            //if current node is not equal to end check all edges of current node
            for (auto edge : graph.nodes[fNode.id].edges) {
                auto& n = graph.nodes[edge];

                //tags node as visited
                if(n.tag == NodeTags::None){
                    n.tag = NodeTags::Visited;
                }

                // calculates AStar values(G,H,F)
                int g = weights[fNode.id].f + n.weight;
                int h = calculateHeuristic(n, target);
                int f = g + h;

                //checks if this is fastest known route or not
                if(f < weights[n.id].f){
                    //changes weights with new best route
                    weights[n.id].h = h;
                    weights[n.id].f = f;
                    weights[n.id].parent = fNode.id;

                    //adds it to priority queue
                    priority_list.push(n);
                }

            }
        }
        return {};
    }

    //Calculates the estimated distance between two nodes
    int AStarPathfindingService::calculateHeuristic(const Node& start, const Node& target) {
        int x = start.position.x - target.position.x;
        int y = start.position.y - target.position.y;
        int res = sqrt(pow(x, 2) + pow(y, 2)) / 10;

        //This tries to avoid going diagonally if not needed
        if(x ==0)
            res -= 1;
        if(y == 0)
            res -= 1;

        return res;
    }

    void AStarPathfindingService::removePathfinding(class Pathfinding &pathfinding) {
        _pathfindingComponents.erase(std::find_if(_pathfindingComponents.begin(), _pathfindingComponents.end(), [&](const std::reference_wrapper<class Pathfinding> &d) {
            return &d.get() == &pathfinding;
        }));
    }

    void AStarPathfindingService::addPathfinding(class Pathfinding &pathfinding) {
        _pathfindingComponents.emplace_back(std::ref(pathfinding));
    }


    void AStarPathfindingService::createGraph(){
        //Sets couple help variables
        std::vector<std::unique_ptr<RectRenderShape>> drawables {};
        std::vector<Node> nodeList;
        std::vector<std::pair<int,int>> edges;

        //calculate and set helpVariables
        int height = _graphHeight;
        int width = _graphWidth;
        int widthNodeDistance = _nodeDistance;
        int heightNodeDistance = _nodeDistance;
        int nodeCounter = 0;

        //loops until full width and height are covered in nodes
        while (heightNodeDistance < height){
            while(widthNodeDistance < width){
                //Checks if position is at valid place
                if(isValidSpot(Vector2(widthNodeDistance, heightNodeDistance))){
                    //creates drawable used to visualize graph
                    auto rect = std::make_unique<RectRenderShape>(Rect2(Vector2(widthNodeDistance, heightNodeDistance), Vector2(5, 5)), 0, Vector2{}, Color{});
                    drawables.push_back(std::move(rect));

                    // add node to nodeList
                    auto node = Node(nodeCounter,Vector2(widthNodeDistance, heightNodeDistance));
                    nodeList.emplace_back(node);
                    nodeCounter++;
                }
                widthNodeDistance += _nodeDistance;
            }
            widthNodeDistance = _nodeDistance;
            heightNodeDistance += _nodeDistance;
        }

        //Sets all edges of nodes by checking distances between the nodes
        for ( auto& outerNode : nodeList){
            for ( auto& innerNode : nodeList){
                if(outerNode.id != innerNode.id) {
                    if (std::abs(outerNode.position.x - innerNode.position.x) <= _nodeDistance &&
                        std::abs(outerNode.position.y - innerNode.position.y) <= _nodeDistance) {
                        outerNode.edges.emplace_back(innerNode.id);
                    }
                }
            }
        }

        //Create graph based on nodesList
        _graph = std::make_unique<Graph>(nodeList, std::move(drawables));
    }

    bool AStarPathfindingService::isValidSpot(Vector2 pos) const {
        auto* ps = GolfEngine::Services::Physics::getService();

        //gets all colliders where no nodes can be placed
        auto colliders = ps->getStaticColliders();

        for(auto& collider : colliders){
            //Calculates if node position is in rectangle then return false
            if(collider->getRenderShape().getType() == RenderShapeType::RectShape){

                auto* rect = (RectRenderShape *) &collider->getRenderShape();
                auto LX = rect->rect().position.x - (rect->rect().size.x /2) - rectMargin ;
                auto RX = rect->rect().position.x + (rect->rect().size.x/2 )+ rectMargin;
                auto LY = rect->rect().position.y - (rect->rect().size.y/2) - rectMargin;
                auto RY =  rect->rect().position.y + (rect->rect().size.y /2) + rectMargin;
                if( pos.x >=  LX &&
                    pos.x <=  RX &&
                    pos.y >= LY &&
                    pos.y <= RY)
                {
                    return false;
                }
            }else{
                //Calculates if node position is in circle then return false

                auto* circle = (CircleRenderShape *) &collider->getRenderShape();
                auto x = pow((pos.x - circle->position().x),2);
                auto y = pow((pos.y - circle->position().y),2);
                auto r = pow(circle->radius()+10,2);
                if(x+y <= r){
                    return false;
                }
            }
        }
        return true;
    }

    Node& AStarPathfindingService::covertPosToNode(Vector2 position){
        const auto dist = [position](const auto& p){
            return std::pow((p.position.x - position.x), 2) + std::pow((p.position.y - position.y), 2);
        };
        //Return node closest to given position
        const auto& closest = std::min_element(_graph->nodes.cbegin(), _graph->nodes.cend(),
                                               [&dist](const auto& p1, const auto& p2)
                                               { return dist(p1) < dist(p2); });

        auto& node = *(closest);

        return const_cast<Node &>(node);
    }

    Graph& AStarPathfindingService::getGraph() {
        return *_graph;
    }

    void AStarPathfindingService::setNodeDistance(int nodeDistance) {
        _nodeDistance = nodeDistance;
    }

    void AStarPathfindingService::setMarginAroundRectColliders(int margin) {
        rectMargin = margin;
    }

    void AStarPathfindingService::setGraphSize(int width, int height) {
        _graphWidth = width;
        _graphHeight = height;
    }

    void AStarPathfindingService::setMaxPathsToCalculatePerTic(int maxPathsPerTic) {
        _maxPathsToCalculatePerTic = std::max(1, maxPathsPerTic);
    }
}
