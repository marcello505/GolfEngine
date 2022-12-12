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
    /// sets path for this component
    /// \param path vector with nodes
    void setPath(const std::vector<Node>& path);

    /// return the path this component has to target
    /// \return vector of nodes in path
    std::vector<Node> getPath();
    void setTarget(GameObject &gameObject);
    /// calculates vector displaying direction to target
    /// \return returns vector with direction to target
    Vector2 getNewDirection();

    /// Return the gameobject this component is navigating to
    /// \return Target gameobject
    Vector2 getTargetPosition();
    /// Return position of parent
    /// \return Vector with positin of parent
    Vector2 getParentGameObjectPosition() const;

    /// Checks if counted frames is bigger than duration
    /// \return true if new path needs to be calculated
    bool needsNewPath();


private:
    int _countedFrames {0};
    GameObject& _target;
    std::vector<Node> _path;
    int _fps;
    float _recalculatePathTime;

};


#endif //GOLFENGINE_PATHFINDING_H
