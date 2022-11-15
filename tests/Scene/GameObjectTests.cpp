//
// Created by conner on 11/14/2022.
//

#include <../doctest/doctest.h>
#include "Scene/Scene.h"
#include "Scene/Components/BehaviourScript.h"

namespace GameObjectTests{
    class Counter : public BehaviourScript{
    private:
        int _count = 0;
    public:
        explicit Counter(GameObject* gameObject) : BehaviourScript(gameObject){}
        void onStart() override {
            _count = 0;
        }
        void onUpdate() override {
            _count++;
        }
        [[nodiscard]] int getCount() const {return _count;}
    };
}

TEST_CASE("Component creation on GameObject"){
    // Arrange
    Scene* scene {new Scene{}};
    GameObject* go {new GameObject{scene}};

    // Act
    go->addComponent<BehaviourScript>(go);

    // Assert
    auto script {go->getComponent<BehaviourScript>()};
    CHECK_NE(script, nullptr);

    // Cleanup
    delete scene;
}

TEST_CASE("Component removal on GameObject"){
    // Arrange
    Scene* scene{new Scene{}};
    GameObject* go{new GameObject{scene}};

    // Act
    go->addComponent<BehaviourScript>(go);
    go->removeComponent(*go->getComponent<BehaviourScript>());

    // Assert
    CHECK_EQ(go->getComponent<BehaviourScript>(), nullptr);

    // Cleanup
    delete scene;
}

TEST_CASE("Custom behavior script on GameObject"){
    // Arrange
    Scene* scene{new Scene{}};
    GameObject* go{new GameObject{scene}};
    go->addComponent<GameObjectTests::Counter>(go);

    // Act
    scene->startScene();
    scene->updateScene();

    // Assert
    CHECK_EQ(go->getComponent<GameObjectTests::Counter>()->getCount(), 1);

    // Cleanup
    delete scene;
}