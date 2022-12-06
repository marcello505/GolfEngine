//
// Created by conner on 12/6/2022.
//

#include "TileMapRenderShape.h"

TileMapRenderShape::TileMapRenderShape(const std::string& imagePath, TileSet_t tileSet)
    : _imagePath{imagePath}, _tileSet(tileSet), _position{0,0}{
}

void TileMapRenderShape::applyTransform(const Transform &transform) {
    _position.x = transform.position.x;
    _position.y = transform.position.y;
}

RenderShapeType TileMapRenderShape::getType() {
    return RenderShapeType::TileMapRenderShape;
}

std::string TileMapRenderShape::imagePath() const {
    return _imagePath;
}

const TileSet& TileMapRenderShape::tileSet() const{
    return _tileSet;
}
