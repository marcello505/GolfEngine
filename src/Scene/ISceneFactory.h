//
// Created by conner on 11/21/2022.
//

#ifndef GOLFENGINE_ISCENEFACTORY_H
#define GOLFENGINE_ISCENEFACTORY_H

#include "Scene.h"

class ISceneFactory {
public:
    virtual ~ISceneFactory() = default;

    /// Function used when scene is loaded (used to fill scene with gameObject)
    /// \param scene reference to scnene to create new gameObjects
    virtual void build(Scene& scene) const = 0;
};


#endif //GOLFENGINE_ISCENEFACTORY_H
