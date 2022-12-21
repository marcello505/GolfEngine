//
// Created by conner on 12/6/2022.
//

#ifndef GOLFENGINE_TILEMAPPARSERSINGLETON_H
#define GOLFENGINE_TILEMAPPARSERSINGLETON_H

#include "../Abstracts/TileMapParserService.h"

namespace GolfEngine::Services::TileMapParser {
    /// Retrieves the global instance of the TileMapParser Service
    /// \return pointer reference to service
    TileMapParserService& getService();

    /// Checks whether there is an active global service
    /// \return true if there is an active global service
    bool hasService();

#ifdef GOLFENGINE_SINGLETON_PRIVATE
    void setService(TileMapParserService *service);
#endif
}

#endif //GOLFENGINE_TILEMAPPARSERSINGLETON_H
