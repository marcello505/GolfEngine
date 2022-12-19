//
// Created by marcello on 11/8/22.
//

#ifndef GOLFENGINE_PHYSICSSINGLETON_H
#define GOLFENGINE_PHYSICSSINGLETON_H

#include "../Abstracts/PhysicsService.h"

// Odd way to do Singleton, reason for this is that c++ can't initialize Static fields.
// The actual instance is hidden in the cpp file and can't be accessed by other classes
// Feel free to find a better method.
namespace GolfEngine::Services::Physics{
    /// Retrieves the global instance of the Physics Service
    /// \return pointer reference to service
    PhysicsService* getService();

    /// Checks whether there is an active global service
    /// \return true if there is an active global service
    bool hasService();

#ifdef GOLFENGINE_SINGLETON_PRIVATE
    void setService(PhysicsService* service);
#endif
}



#endif //GOLFENGINE_PHYSICSSINGLETON_H
