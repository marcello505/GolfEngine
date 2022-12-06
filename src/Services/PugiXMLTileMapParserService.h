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
        PugiXMLTileMapParserService();
        TileMapRenderShape loadMap(const std::string& mapPath, const std::string& tileSetPath) override;
    private:
        std::string readFile(const std::string& path);
    };
}

#endif //GOLFENGINE_PUGIXMLTILEMAPPARSERSERVICE_H
