//
// Created by conner on 12/5/2022.
//

#ifndef GOLFENGINE_TILEDCOMPONENT_H
#define GOLFENGINE_TILEDCOMPONENT_H

#include "Component.h"
#include "Scene/Components/Drawable.h"
#include "Scene/RenderShape/TileMapRenderShape.h"

class TiledComponent : public Component, public Drawable {
public:
    TiledComponent(const std::string& mapPath, const std::string& tileSetPath, Vector2 pixelScale = Vector2{1,1});

    // Component overrides
    void onStart() override;
    void onUpdate() override;
    void onRemove() override;
    bool getActive() override;
    void setActive(bool active) override;
    void setParentGameObject(GameObject& gameObject) override;

    // Drawable overrides
    RenderShape& getRenderShape() override;
private:
    TileMapRenderShape _renderShape;
};


#endif //GOLFENGINE_TILEDCOMPONENT_H
