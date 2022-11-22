#include <doctest.h>
#define GOLFENGINE_SINGLETON_PRIVATE
#include <Services/Singletons/PhysicsSingleton.h>
#include <Services/Box2DPhysicsService.h>
#include "Scene/Components/BoxCollider.h"
#include "Scene/Components/CircleCollider.h"
#include "Core/SceneManager.h"

namespace Box2DPysicstest{
    class SceneFactory : public ISceneFactory{
        void build(Scene &scene) const override{
            auto& go = scene.createNewGameObject<GameObject>();
            go.addComponent<BoxCollider>(Vector2{50,50});
            go.addComponent<CircleCollider>(50);
            go.addComponent<RigidBody>();
        }
    };
}

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

TEST_CASE("RigidBody adds all colliders to the physics simulation"){
    //Arrange
    auto* box2DPhysicsService = new GolfEngine::Services::Physics::Box2DPhysicsService{};
    GolfEngine::Services::Physics::setService(box2DPhysicsService);
    GolfEngine::SceneManager::GetSceneManager().clearScenes();
    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<Box2DPysicstest::SceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");
    //Act
    //Arrange
    CHECK_EQ(box2DPhysicsService->getFixtureCount(), 2); //Added 2 Colliders and 1 RigidBody, thus the fixture count should be 2
}

TEST_CASE("RigidBody.addForceToCenter() causes movement"){
    //Arrange
    auto* box2DPhysicsService = new GolfEngine::Services::Physics::Box2DPhysicsService{};
    GolfEngine::Services::Physics::setService(box2DPhysicsService);
    GolfEngine::SceneManager::GetSceneManager().clearScenes();
    GolfEngine::SceneManager::GetSceneManager().addSceneFactory<Box2DPysicstest::SceneFactory>("main");
    GolfEngine::SceneManager::GetSceneManager().loadScene("main");

    //Act
    auto& gameObject = GolfEngine::SceneManager::GetSceneManager().getCurrentScene().getRootGameObject().childAt(0);
    auto& rigidBody = gameObject.getComponent<RigidBody>();

    //Assert
    CHECK_EQ(gameObject.getWorldTransform().position.x, 0);
    CHECK_EQ(gameObject.getWorldTransform().position.y, 0);
    rigidBody.applyForceToCenter({10000.f, 10000.f});
    box2DPhysicsService->update(1.0f);
    CHECK_GT(gameObject.getWorldTransform().position.x, 10);
    CHECK_GT(gameObject.getWorldTransform().position.y, 10);
}