//
// Created by conner on 12/6/2022.
//

#include "TileMapRenderShape.h"

#include <utility>

TileMapRenderShape::TileMapRenderShape(const std::string& imagePath, TileSet_t tileSet, Map_t map)
    : _imagePath{imagePath}, _tileSet(std::move(tileSet)), _position{0,0}, _map{std::move(map)}{
}

void TileMapRenderShape::applyTransform(const Transform &transform) {
    _position.x = transform.position.x;
    _position.y = transform.position.y;
    _scale.x = _baseScale.x * transform.scale.x;
    _scale.y = _baseScale.y * transform.scale.y;
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

const Map_t& TileMapRenderShape::map() const {
    return _map;
}

const Vector2 &TileMapRenderShape::position() const {
    return _position;
}

void TileMapRenderShape::setPixelScale(Vector2 scale) {
    _baseScale = _scale = scale;
}

const Vector2 &TileMapRenderShape::scale() const {
    return _scale;
}
