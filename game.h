#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "level.h"

/* Game class
 * This class holds all of information for our main game loop
 */

class Graphics;

class Game {
public:
    Game();
    ~Game();
private:
    void gameLoop();
    void draw(Graphics &graphics);
    void update(float elapsedTime);

    Player player;

    Level level;
};

#endif
