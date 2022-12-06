//
// Created by conner on 12/6/2022.
//

#ifndef GOLFENGINE_TILEMAPPARSERSINGLETON_H
#define GOLFENGINE_TILEMAPPARSERSINGLETON_H

#include "../Abstracts/TileMapParserService.h"

namespace GolfEngine::Services::TileMapParser {
    TileMapParserService& getService();
    bool hasService();
    void setService(TileMapParserService *service);
}

#endif //GOLFENGINE_TILEMAPPARSERSINGLETON_H
