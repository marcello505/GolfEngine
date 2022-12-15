//
// Created by conner on 12/6/2022.
//

#ifndef GOLFENGINE_PUGIXMLTILEMAPPARSERSERVICE_H
#define GOLFENGINE_PUGIXMLTILEMAPPARSERSERVICE_H

#include "Abstracts/TileMapParserService.h"
#include <memory>

namespace GolfEngine::Services::TileMapParser {
    class PugiXMLTileMapParserService : public TileMapParserService {
    public:
        /// Loads a .tmx map file created in Tiled
        /// \param mapPath Path to the map file
        /// \return TileMapRenderShape that holds all the info to render the map
        TileMapRenderShape loadMap(const std::filesystem::path& mapPath) override;
    private:
        std::string readFile(const std::filesystem::path& path);
    };
}

#endif //GOLFENGINE_PUGIXMLTILEMAPPARSERSERVICE_H
