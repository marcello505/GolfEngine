//
// Created by marcello on 11/8/22.
//

#ifndef GOLFENGINE_PHYSICSSINGLETON_H
#define GOLFENGINE_PHYSICSSINGLETON_H

#include <memory>
#include "../Abstracts/PhysicsService.h"

// Odd way to do Singleton, reason for this is that c++ can't initialize Static fields.
// The actual instance is hidden in the cpp file and can't be accessed by other classes
// Feel free to find a better method.
namespace GolfEngine::Services::Physics{
    PhysicsService* getService();
    bool hasService();
    void setService(PhysicsService* service);
}



#endif //GOLFENGINE_PHYSICSSINGLETON_H
