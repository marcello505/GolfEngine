//
// Created by marcello on 11/29/22.
//

#ifndef GOLFENGINE_PLAYERTESTSCENE_H
#define GOLFENGINE_PLAYERTESTSCENE_H

#include "Scene/ISceneFactory.h"


class PlayerTestScene : public ISceneFactory {
public:
    void build(Scene& scene) const override;

};


#endif //GOLFENGINE_PLAYERTESTSCENE_H
