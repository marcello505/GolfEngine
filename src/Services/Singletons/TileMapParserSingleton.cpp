//
// Created by conner on 12/6/2022.
//

#include "TileMapParserSingleton.h"
#include <memory>
#include <stdexcept>

namespace GolfEngine::Services::TileMapParser{
    std::unique_ptr<TileMapParserService> globalTileMapParserService {};

    TileMapParserService& getService() {
        if(globalTileMapParserService){
            return *globalTileMapParserService;
        }
        else{
            throw std::runtime_error("No Tile Map Parser Service initialized.");
        }
    }

    void setService(TileMapParserService* service){
        globalTileMapParserService.reset(service);
    }

    bool hasService(){
        return (bool)globalTileMapParserService;
    }
}