//
// Created by conner on 11/29/2022.
//

#ifndef GOLFENGINE_BOX2DCOLLISIONLISTENER_H
#define GOLFENGINE_BOX2DCOLLISIONLISTENER_H

#include <box2d/box2d.h>
#include "../Box2DPhysicsService.h"

namespace GolfEngine::Services::Physics {
    class Box2DCollisionListener : public b2ContactListener {
    public:
        explicit Box2DCollisionListener(Box2DPhysicsService& box2DPhysicsService);

        // b2ContactListener overrides
        void BeginContact(b2Contact *contact) override;
        void EndContact(b2Contact *contact) override;
    private:
        Box2DPhysicsService& _physicsService;
    };

}

#endif //GOLFENGINE_BOX2DCOLLISIONLISTENER_H
