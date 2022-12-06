//
// Created by conner on 12/6/2022.
//

#include "PugiXMLTileMapParserService.h"
#include <fstream>
#include <pugixml.hpp>

namespace GolfEngine::Services::TileMapParser {

    PugiXMLTileMapParserService::PugiXMLTileMapParserService() {
    }

    TileMapRenderShape PugiXMLTileMapParserService::loadMap(const std::string &mapPath, const std::string &tileSetPath) {
        std::string tileSetFile = readFile(tileSetPath);
        std::string mapFile = readFile(mapPath);

        pugi::xml_document doc;
        pugi::xml_parse_result xmlResult = doc.load_string(tileSetFile.c_str());

        if(!xmlResult)
            throw std::runtime_error("Unable to parse tile set file content to XML from path: " + tileSetPath);

        // TileMapRenderShape temp variables
        std::string tileSetImage;
        int tileWidth, tileHeight, cols, imageWidth, imageHeight;

        // Get tile set data
        auto tileSetObject = doc.child("tileset");
        auto imageObject = tileSetObject.child("image");

        tileWidth = tileSetObject.attribute("tilewidth").as_int();
        tileHeight = tileSetObject.attribute("tileheight").as_int();
        cols = tileSetObject.attribute("columns").as_int();
        tileSetImage = imageObject.attribute("source").as_string();
        imageWidth = imageObject.attribute("width").as_int();
        imageHeight = imageObject.attribute("height").as_int();

        // Create and return TileMapRenderShape
        return std::move(TileMapRenderShape{tileSetImage, TileSet_t{tileWidth, tileHeight, cols, imageWidth, imageHeight}});
    }

    std::string PugiXMLTileMapParserService::readFile(const std::string& path) {
        std::string fileContent;
        std::string line;
        std::ifstream file {path};

        if (file.is_open())
        {
            while ( getline (file, line) )
            {
                fileContent.append(line + '\n');
            }
            file.close();
        }
        else
            throw std::runtime_error("Unable to open/load file: " + path + " in PugiXMLTileMapParserService");

        return fileContent;
    }


}