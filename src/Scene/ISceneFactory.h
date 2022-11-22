//
// Created by conner on 11/21/2022.
//

#ifndef GOLFENGINE_ISCENEFACTORY_H
#define GOLFENGINE_ISCENEFACTORY_H


class ISceneFactory {
public:
    virtual ~ISceneFactory() = default;
    virtual void build(Scene& scene) const = 0;
};


#endif //GOLFENGINE_ISCENEFACTORY_H
