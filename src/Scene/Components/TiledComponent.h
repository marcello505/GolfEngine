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
    /// A component that loads and renders a tile map created in Tiled
    /// \param mapPath Path to the map (.tmx) file
    /// \param pixelScale Base scale used to up/down-scale the tiles
    explicit TiledComponent(const std::string& mapPath, Vector2 pixelScale = Vector2{1,1});

    // Component overrides
    void onStart() override;
    void onUpdate() override;
    void onRemove() override;
    bool getActive() override;
    void setActive(bool active) override;
    void setParentGameObject(GameObject& gameObject) override;

    // Drawable overrides
    RenderShape& getRenderShape() override;

    /// Creates GameObjects with a BoxCollider for each tile with a collider property
    void initColliders();

    // Snapshot methods for IPersistable
    std::unique_ptr<ISnapshot> saveSnapshot() override;
    void loadSnapshot(const ISnapshot& rawSnapshot) override;

private:
    TileMapRenderShape _renderShape;
};


#endif //GOLFENGINE_TILEDCOMPONENT_H
