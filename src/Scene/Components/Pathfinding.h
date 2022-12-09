//
// Created by jaaps on 02/11/2022.
//

#ifndef GOLFENGINE_PATHFINDING_H
#define GOLFENGINE_PATHFINDING_H


#include <vector>
#include "../Vector2.h"
#include "Component.h"
#include "Scene/Graph.h"

class Pathfinding : public Component{
public:
    Pathfinding(GameObject *target, std::shared_ptr<Graph> graph );

    // Overrides
    void onStart() override;
    void onUpdate() override;
    void onRemove() override;
    bool getActive() override;
    void setActive(bool active) override;
    void setParentGameObject(GameObject& gameObject) override;
    void setPath(const std::vector<Node>& path);
    std::vector<Node> getPath();
    void setTarget(GameObject &gameObject);

    int countedFrames {0};

    Node& covertPosToNode(Vector2 position);
    Vector2 getTargetPosition();
    Vector2 getParentGameObjectPosition() const;

    std::shared_ptr<Graph> getGraph();

private:
    GameObject& _target;
    std::shared_ptr<Graph> _graph;
    std::vector<Node> _path;
};


#endif //GOLFENGINE_PATHFINDING_H
