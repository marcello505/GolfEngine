//
// Created by conner on 12/6/2022.
//

#ifndef GOLFENGINE_TILEMAPPARSERSERVICE_H
#define GOLFENGINE_TILEMAPPARSERSERVICE_H

#include <filesystem>
#include <string>
#include "Scene/RenderShape/TileMapRenderShape.h"

class TileMapParserService {
public:
    /// Loads a map file
    /// \param mapPath Path to the map file
    /// \return TileMapRenderShape that holds all the info to render the map
    virtual TileMapRenderShape loadMap(const std::filesystem::path& mapPath) = 0;

    // Virtual Destructors
    virtual ~TileMapParserService() = default;
};

#endif //GOLFENGINE_TILEMAPPARSERSERVICE_H
