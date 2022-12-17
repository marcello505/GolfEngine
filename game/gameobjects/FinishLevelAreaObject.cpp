//
// Created by marcello on 12/17/22.
//

#include "FinishLevelAreaObject.h"
#include "Scene/Components/BoxCollider.h"
#include "Scene/Components/RigidBody.h"
#include "Scene/Components/SpriteComponent.h"

FinishLevelAreaObject::FinishLevelAreaObject(const Vector2& position, const Vector2& extents) {
    tag = TAG_FINISH;

    //Handle Sprite
    {
        float spriteY, spriteX;
        spriteX = spriteY = 256.0f; //The sprite is 256x256
        Vector2 pixelScale {
                1.0f / (extents.x * 2.0f / spriteX),
                1.0f / (extents.y * 2.0f / spriteY),
        };

        auto& spriteComponent = addComponent<SpriteComponent>("res/sprites/LevelFinishSprite.png", pixelScale);
        spriteComponent.setColor(Color{20, 255, 20, 180});
    }


    addComponent<BoxCollider>(extents);
    addComponent<RigidBody>(RigidBodyDef{RigidBodyTypes::AreaBody});
    setLocalPosition(position);
}
