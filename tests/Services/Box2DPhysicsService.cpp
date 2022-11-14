#include <doctest.h>
#define GOLFENGINE_SINGLETON_PRIVATE
#include <Services/Singletons/PhysicsSingleton.h>
#include <Services/Box2DPhysicsService.h>


TEST_CASE("RigidBody.onStart() adds itself to the physics simulation"){
    //Arrange
    GolfEngine::Services::Physics::Box2DPhysicsService box2DPhysicsService {};
    GolfEngine::Services::Physics::setService(&box2DPhysicsService);
    RigidBody rigidBody {};

    //Act
    rigidBody.onStart();

    //Assert
    CHECK_GT(box2DPhysicsService.getBodyCount(), 0);
}