#ifndef GAME_H
#define GAME_H

#include "sprite.h"

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

    Sprite player;
};

#endif
