//
// Created by conner on 12/6/2022.
//

#ifndef GOLFENGINE_TILEMAPPARSERSERVICE_H
#define GOLFENGINE_TILEMAPPARSERSERVICE_H

#include <string>
#include "Scene/RenderShape/TileMapRenderShape.h"

class TileMapParserService {
public:
    virtual TileMapRenderShape loadMap(const std::string& mapPath) = 0;

    // Virtual Destructors
    virtual ~TileMapParserService() = default;
};

#endif //GOLFENGINE_TILEMAPPARSERSERVICE_H
