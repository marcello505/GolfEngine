#include <doctest.h>
#define GOLFENGINE_SINGLETON_PRIVATE
#include <Services/Singletons/PhysicsSingleton.h>
#include <Services/Box2DPhysicsService.h>


TEST_CASE("RigidBody adds/removes itself to the physics simulation"){
    //Arrange
    auto* box2DPhysicsService = new GolfEngine::Services::Physics::Box2DPhysicsService{};
    GolfEngine::Services::Physics::setService(box2DPhysicsService);
    auto* rigidBody = new RigidBody{};

    //Act
    rigidBody->onStart();

    //Assert
    SUBCASE("Added"){
        CHECK_GT(box2DPhysicsService->getBodyCount(), 0);
    }
    SUBCASE("Removed"){
        rigidBody->onRemove();
        CHECK_EQ(box2DPhysicsService->getBodyCount(), 0);
    }
}