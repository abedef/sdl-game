#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "globals.h"
#include "tile.h"

class Graphics;
struct SDL_Texture;
struct SDL_Rect;
struct Tileset;

class Level {
public:
    Level();
    Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
    ~Level();
    void update(int elapsedTime);
    void draw(Graphics &graphics);
private:
    std::string mapName;
    Vector2 spawnPoint;

    Vector2 size;
    Vector2 tilesize;

    SDL_Texture *backgroundTexture;

    std::vector<Tile> tileList;
    std::vector<Tileset> tilesets;

    // Private because we're only going to call this from within the class
    void loadMap(std::string mapName, Graphics &graphics);
};

struct Tileset {
    SDL_Texture *texture;
    int firstGid;

    Tileset() {
        firstGid = -1;
    }

    Tileset(SDL_Texture *texture, int firstGid) : texture(texture), firstGid(firstGid) {}
};

#endif
