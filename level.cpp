#include "level.h"
#include "graphics.h"
#include "globals.h"

#include "tinyxml2.h"

#include <SDL2/SDL.h>

#include <sstream>
#include <algorithm>
#include <cmath>

Level::Level() {}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics) : mapName(mapName), spawnPoint(spawnPoint), size(Vector2(0, 0)) {
    loadMap(mapName, graphics);
}

Level::~Level() {
}

void Level::loadMap(std::string mapName, Graphics &graphics) {

    // Parse the .tmx file
    tinyxml2::XMLDocument doc;
    std::stringstream ss;
    ss << "content/maps/" << mapName << ".tmx";
    doc.LoadFile(ss.str().c_str());

    // TODO add a check to make sure the file is loaded correctly

    tinyxml2::XMLElement *mapNode = doc.FirstChildElement("map");

    // Get and store the width and height of the whole map
    int width, height;
    mapNode->QueryIntAttribute("width", &width);
    mapNode->QueryIntAttribute("height", &height);
    size = Vector2(width, height);

    // Get and store the width and height of the map's tiles
    int tileWidth, tileHeight;
    mapNode->QueryIntAttribute("tilewidth", &tileWidth);
    mapNode->QueryIntAttribute("tileheight", &tileHeight);
    tilesize = Vector2(tileWidth, tileHeight);

    // Load the map's tileset(s)
    tinyxml2::XMLElement *pTileset = mapNode->FirstChildElement("tileset");
    while (pTileset) {
        int firstgid;
        const char *source = pTileset->FirstChildElement("image")->Attribute("source");
        char *path;
        std::stringstream ss;
        ss << "content/tilesets/" << source; // FIXME problematic path
        // FIXME map_1.tmx has an absolute path to the tilemap so idk
        pTileset->QueryIntAttribute("firstgid", &firstgid);
        SDL_Texture *tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ss.str()));
        tilesets.push_back(Tileset(tex, firstgid));

        pTileset = pTileset->NextSiblingElement("tileset");
    }

    // Load the layers
    tinyxml2::XMLElement *pLayer = mapNode->FirstChildElement("layer");

    // Loading the data element
    while (pLayer) {
        tinyxml2::XMLElement *pData = pLayer->FirstChildElement("data");

        // Loading the tile element
        while (pData) {
            tinyxml2::XMLElement *pTile = pData->FirstChildElement("tile");

            // Build each individual tile; if gid is 0, no tile should be drawn (continue to loop)
            int tileCounter = 0;
            while (pTile) {

                // Get the tileset for this specific gid
                if (pTile->IntAttribute("gid") != 0) {
                    int gid = pTile->IntAttribute("gid");
                    Tileset tls;
                    for (int i = 0; i < tilesets.size(); ++i) {
                        if (tilesets[i].firstGid <= gid) {
                            tls = tilesets.at(i);
                            break;
                        }
                    }

                    // The tileset was found
                    if (tls.firstGid != -1) {

                        // Get the position of the tile in the level
                        int tileX = (tileCounter % width) * tileWidth;
                        int tileY = (tileCounter / width) * tileHeight;

                        Vector2 finalTilePosition = Vector2(tileX, tileY);

                        // Calculate the position of the tile in the tileset
                        int tilesetWidth, tilesetHeight;
                        SDL_QueryTexture(tls.texture, NULL, NULL, &tilesetWidth, &tilesetHeight);

                        int tilesetX = ((gid % (tilesetWidth / tileWidth)) - 1) * tileWidth;
                        int tilesetY = (gid / (tilesetWidth / tileWidth)) * tileHeight;
                        Vector2 finalTilesetPosition = Vector2(tilesetX, tilesetY);

                        // Build the tile and add it to the level's tile list
                        Tile tile(tls.texture, Vector2(tileWidth, tileHeight), finalTilesetPosition, finalTilePosition);
                        tileList.push_back(tile);
                    }
                }

                tileCounter++;

                pTile = pTile->NextSiblingElement("tile");
            }

            pData = pData->NextSiblingElement("data");
        }

        pLayer = pLayer->NextSiblingElement("layer");
    }
}

void Level::update(int elapsedTime) {
}

void Level::draw(Graphics &graphics) {
    for (int i = 0; i < tileList.size(); ++i) {
        tileList.at(i).draw(graphics);
    }
}
