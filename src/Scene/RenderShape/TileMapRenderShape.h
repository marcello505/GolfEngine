//
// Created by conner on 12/6/2022.
//

#ifndef GOLFENGINE_TILEMAPRENDERSHAPE_H
#define GOLFENGINE_TILEMAPRENDERSHAPE_H

#include "RenderShape.h"
#include <string>
#include <vector>

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

typedef struct Map{
    std::vector<std::vector<int>> map;
    int tileWidth;
    int tileHeight;
    int columns;
    int rows;
} Map_t;

class TileMapRenderShape : public RenderShape {
public:
    TileMapRenderShape(const std::string& imagePath, TileSet_t tileSet, Map_t map);

    // Rendershape overrides
    void applyTransform(const Transform &transform) override;
    RenderShapeType getType() override;

    // Getters/Setters
    [[nodiscard]] std::string imagePath() const;
    [[nodiscard]] const TileSet_t& tileSet() const;
    [[nodiscard]] const Map_t& map() const;
    [[nodiscard]] const Vector2& position() const;
    [[nodiscard]] const Vector2& scale() const;
    void setPixelScale(Vector2 scale);

private:
    std::string _imagePath;
    TileSet_t _tileSet;
    Vector2 _position;
    Vector2 _baseScale;
    Vector2 _scale;
    Map_t _map;
};


#endif //GOLFENGINE_TILEMAPRENDERSHAPE_H
