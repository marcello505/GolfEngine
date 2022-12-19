//
// Created by marcello on 11/29/22.
//

#ifndef GOLFENGINE_SAVEGAMETESTSCENE_H
#define GOLFENGINE_SAVEGAMETESTSCENE_H

#include "Scene/ISceneFactory.h"

using namespace GolfEngine::Scene;

class SaveGameTestScene : public ISceneFactory {
public:
    void build(Scene& scene) const override;

};


#endif //GOLFENGINE_SAVEGAMETESTSCENE_H
