//
// Created by conner on 11/29/2022.
//

#ifndef GOLFENGINE_COLLISIONLISTENER_H
#define GOLFENGINE_COLLISIONLISTENER_H

#include <box2d/box2d.h>
#include "../Box2DPhysicsService.h"

namespace GolfEngine::Services::Physics {
    class CollisionListener : public b2ContactListener {
    public:
        explicit CollisionListener(Box2DPhysicsService& box2DPhysicsService);

        // b2ContactListener overrides
        void BeginContact(b2Contact *contact) override;
        void EndContact(b2Contact *contact) override;
    private:
        Box2DPhysicsService& _physicsService;
    };

}

#endif //GOLFENGINE_COLLISIONLISTENER_H
