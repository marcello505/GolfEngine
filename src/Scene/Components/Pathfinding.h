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
    Pathfinding(GameObject *target, float recalculatePathTime = 1.0 );

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


    Vector2 getTargetPosition();
    Vector2 getParentGameObjectPosition() const;


    bool needsNewPath();


private:
    int _countedFrames {0};

    GameObject& _target;
    std::vector<Node> _path;
    int _fps;
    float _recalculatePathTime;

};


#endif //GOLFENGINE_PATHFINDING_H
