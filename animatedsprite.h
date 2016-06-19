#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <map>
#include <string>
#include <vector>

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
protected:
    double timeToUpdate;
    bool currentAnimationOnce;
    std::string currentAnimation;

    // Adds an animation to the map of animations for the sprites
    void addAnimation(int frames, int x, int y, std::string name,
            int width, int height, Vector2 offset);

    // Resets all animations associated with this sprite
    void resetAnimations();

    // Stops the current animation
    void stopAnimation();

    // Changes the visibility of the animated sprite
    void setVisible(bool visible);

    // Logic that happens when an animation ends
    virtual void animationDone(std::string currentAnimation) = 0;

    // A required function that sets up all animations for sprites
    virtual void setupAnimations() = 0;
private:
    std::map<std::string, std::vector<SDL_Rect> > animations;
    std::map<std::string, Vector2> offsets;

    int frameIndex;
    double timeElapsed;
    bool visible;
};

#endif
