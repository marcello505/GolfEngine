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

TEST_CASE("RigidBody.addForceToCenter() causes movement"){
    //Arrange
    auto* box2DPhysicsService = new GolfEngine::Services::Physics::Box2DPhysicsService{};
    GolfEngine::Services::Physics::setService(box2DPhysicsService);
    Scene* scene = new Scene{};
    GameObject gameObject {scene};
    scene->setRootGameObject(&gameObject);
    auto* rigidBody = gameObject.addComponent<RigidBody>();
    rigidBody->setParentGameObject(&gameObject); //TODO at some point this is automatic, this can be removed when that happens

    //Act
    rigidBody->onStart();


    //Assert
    CHECK_EQ(gameObject.getWorldTransform().position.x, 0);
    CHECK_EQ(gameObject.getWorldTransform().position.y, 0);
    rigidBody->applyForceToCenter({10000.f, 10000.f});
    box2DPhysicsService->update(1.0f);
    CHECK_GT(gameObject.getWorldTransform().position.x, 10);
    CHECK_GT(gameObject.getWorldTransform().position.y, 10);
}