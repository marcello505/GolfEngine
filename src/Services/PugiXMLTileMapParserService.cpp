//
// Created by conner on 12/6/2022.
//

#include "PugiXMLTileMapParserService.h"
#include <fstream>
#include <pugixml.hpp>
#include <sstream>

namespace GolfEngine::Services::TileMapParser {
    TileMapRenderShape PugiXMLTileMapParserService::loadMap(const std::string& mapPath) {
        pugi::xml_document doc;

        // Parse TileSet file
        std::string mapFile = readFile(mapPath);
        pugi::xml_parse_result xmlResult = doc.load_string(mapFile.c_str());

        if(!xmlResult)
            throw std::runtime_error("Unable to parse map file content to XML, from path: " + mapPath);

        // Map temp variables
        std::vector<std::vector<int>> map {};
        int tileWidth, tileHeight, columns, rows;
        std::string tileSetFileName;

        // Get map data
        auto mapObject = doc.child("map");
        columns = mapObject.attribute("width").as_int();
        rows = mapObject.attribute("height").as_int();
        tileWidth = mapObject.attribute("tilewidth").as_int();
        tileHeight = mapObject.attribute("tileheight").as_int();
        tileSetFileName = mapObject.child("tileset").attribute("source").as_string();

        // Fill map with all layer data
        for(auto& layer : mapObject.children("layer")){
            auto dataObject = layer.child("data");
            auto mapLayerString = dataObject.child_value();

            // Iterate every line
            uint8_t row = 0;
            std::istringstream mapStream;
            mapStream.str(mapLayerString);
            for(std::string line; std::getline(mapStream, line);){
                if(line.empty()) { continue;}
                // Add a row if current row does not exist
                if(row >= map.size())
                    map.emplace_back(std::vector<int>{});

                // Iterate every comma
                uint8_t column = 0;
                std::istringstream lineStream;
                lineStream.str(line);
                for(std::string tile; std::getline(lineStream, tile, ',');){
                    int tileValue = std::stoi(tile);
                    if(tileValue <= 0) { column++; continue; }

                    // Change tile value or create new entry
                    if(column >= map[row].size())
                        map[row].emplace_back(tileValue);
                    else
                        map[row][column] = tileValue;

                    column++;
                }
                row++;
            }
        }

        // Parse TileSet file
        std::string tileSetPath = R"(..\..\..\validation\US00_TileMap\res\)";
        tileSetPath += tileSetFileName;
        std::string tileSetFile = readFile(tileSetPath);
        xmlResult = doc.load_string(tileSetFile.c_str());

        if(!xmlResult)
            throw std::runtime_error("Unable to parse tile set file content to XML, from path: " + tileSetPath);

        // Tile set temp variables
        std::string tileSetImage = R"(..\..\..\validation\US00_TileMap\res\)";
        int tileSetWidth, tileSetHeight, tileSetColumns, imageWidth, imageHeight;
        std::vector<int> colliderTiles {};

        // Get tile set data
        auto tileSetObject {doc.child("tileset")};
        auto imageObject {tileSetObject.child("image")};

        tileSetWidth = tileSetObject.attribute("tilewidth").as_int();
        tileSetHeight = tileSetObject.attribute("tileheight").as_int();
        tileSetColumns = tileSetObject.attribute("columns").as_int();
        tileSetImage += imageObject.attribute("source").as_string();
        imageWidth = imageObject.attribute("width").as_int();
        imageHeight = imageObject.attribute("height").as_int();

        // Get collider tiles from tile set
        auto tiles {tileSetObject.children("tile")};
        for(auto& tile : tiles){
            int tileId {tile.attribute("id").as_int()};

            auto tileProperties {tile.child("properties").children("property")};
            for(auto& property : tileProperties){
                std::string propertyName {property.attribute("name").as_string()};
                if(propertyName == "collider"){
                    bool collider = property.attribute("value").as_bool();
                    if(collider)
                        colliderTiles.emplace_back(tileId);
                }
            }
        }

        // Create and return TileMapRenderShape
        return std::move(TileMapRenderShape{tileSetImage, TileSet_t{colliderTiles, tileSetWidth, tileSetHeight, tileSetColumns, imageWidth, imageHeight}, Map_t {map, tileWidth, tileHeight, columns, rows}});
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