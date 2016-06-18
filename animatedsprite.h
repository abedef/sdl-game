#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <map>
#include <string>

#include "sprite.h"
#include "globals.h"

class Graphics;

/* AnimatedSprite class
 * Holds logic for animating sprite
 */

class AnimatedSprite : public Sprite {
public:
    AnimatedSprite();
    AnimatedSprite(Graphics &graphics, const std::string &filePath,
            int sourceX, int sourceY, int width, int height,
            float posX, float posY, float timeToUpdate);

    // Plays the animation provided it isn't already playing
    void playAnimation(std::string animation, bool once = false);

    // Updates the animated sprite (timer)
    void update(int elapsedTime);

    // Draws the sprite to the screen
    void draw(Graphics &graphics, int x, int y);

    // A required function that sets up all animations for sprites
    virtual void setupAnimations();
private:
    std::map<std::string, std::vector<SDL_Rect>> animations;
};

#endif
