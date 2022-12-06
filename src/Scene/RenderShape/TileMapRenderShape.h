//
// Created by conner on 12/6/2022.
//

#ifndef GOLFENGINE_TILEMAPRENDERSHAPE_H
#define GOLFENGINE_TILEMAPRENDERSHAPE_H

#include "RenderShape.h"
#include <string>

// Struct that contains info about the TileSet used by a TileMap
typedef struct TileSet{
    int tileWidth;
    int tileHeight;
    int columns;
    int imageWidth;
    int imageHeight;
    TileSet(int tileW, int tileH, int cols, int imageW, int imageH) :tileWidth{tileW},
    tileHeight{tileH}, columns{cols}, imageWidth{imageW}, imageHeight{imageH} {}
} TileSet_t;

class TileMapRenderShape : public RenderShape {
public:
    TileMapRenderShape(const std::string& imagePath, TileSet_t tileSet);

    // Rendershape overrides
    void applyTransform(const Transform &transform) override;
    RenderShapeType getType() override;

    // Getters/Setters
    [[nodiscard]] std::string imagePath() const;
    [[nodiscard]] const TileSet_t& tileSet() const;
private:
    std::string _imagePath;
    TileSet_t _tileSet;
    Vector2 _position;
};


#endif //GOLFENGINE_TILEMAPRENDERSHAPE_H
