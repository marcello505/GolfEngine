//
// Created by conner on 11/23/2022.
//

#include "SceneFactory.h"
#include "Scene/Components/SpriteComponent.h"

void SceneFactory::build(Scene& scene) const {
    auto& go = scene.createNewGameObject<GameObject>();
    go.addComponent<SpriteComponent>(R"(..\..\..\validation\US09_Animations\res\player.png)");
    go.setWorldTransform(Transform(Vector2(200,200), 0, Vector2(0.5f,0.5f)));
}