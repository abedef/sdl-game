#ifndef PLAYER_H
#define PLAYER_H

#include "animatedsprite.h"
#include "globals.h"

class Graphics;

class Player : public AnimatedSprite {
public:
    Player();
    Player(Graphics &graphics, float x, float y);
    void draw(Graphics &graphics);
    void update(float elapsedTime);

    // Moves the player left by -dx
    void moveLeft();

    // Moves the player right by dx
    void moveRight();

    // Stops moving the player
    void stopMoving();

    virtual void animationDone(std::string currentAnimation);
    virtual void setupAnimations();
private:
    float dx, dy;

    Direction facing;
};

#endif
