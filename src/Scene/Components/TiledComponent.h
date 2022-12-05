//
// Created by conner on 12/5/2022.
//

#ifndef GOLFENGINE_TILEDCOMPONENT_H
#define GOLFENGINE_TILEDCOMPONENT_H

#include "Component.h"

class TiledComponent : public Component{
public:
    // Component overrides
    void onStart() override;
    void onUpdate() override;
    void onRemove() override;
    bool getActive() override;
    void setActive(bool active) override;
    void setParentGameObject(GameObject &gameObject) override;
};


#endif //GOLFENGINE_TILEDCOMPONENT_H
