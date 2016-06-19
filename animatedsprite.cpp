#include "animatedsprite.h"
#include "graphics.h"

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::AnimatedSprite(Graphics &graphics, const std::string &filePath,
        int sourceX, int sourceY, int width, int height,
        float posX, float posY, float timeToUpdate) : Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY), frameIndex(0), timeToUpdate(timeToUpdate), visible(true), currentAnimationOnce(false), currentAnimation("") {}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset) {
    std::vector<SDL_Rect> rectangles;

    for (int i = 0; i < frames; ++i) {
        SDL_Rect newRect = { (i + x) * width, y, width, height };
        rectangles.push_back(newRect);
    }
    animations.insert(std::pair<std::string, std::vector<SDL_Rect> >(name, rectangles));
    offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::resetAnimations() {
    animations.clear();
    offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once) {
    currentAnimationOnce = once;
    if (currentAnimation != animation) {
        currentAnimation = animation;
        frameIndex = 0;
    }
}

void AnimatedSprite::setVisible(bool visible) {
    this->visible = visible;
}

void AnimatedSprite::stopAnimation() {
    frameIndex = 0;
    animationDone(currentAnimation);
}

void AnimatedSprite::update(int elapsedTime) {
    Sprite::update();

    timeElapsed += elapsedTime;
    if (timeElapsed > timeToUpdate) {
        timeElapsed -= timeToUpdate;
        if (frameIndex < animations[currentAnimation].size() - 1) {
            frameIndex++;
        } else {
            if (currentAnimationOnce) {
                setVisible(false);
            }

            frameIndex = 0;
            animationDone(currentAnimation);
        }
    }
}

void AnimatedSprite::draw(Graphics &graphics, int x, int y) {
    if (visible) {
        SDL_Rect destinationRectangle;
        destinationRectangle.x = x + offsets[currentAnimation].x;
        destinationRectangle.y = y + offsets[currentAnimation].y;
        destinationRectangle.w = sourceRect.w * globals::SPRITE_SCALE;
        destinationRectangle.h = sourceRect.h * globals::SPRITE_SCALE;

        SDL_Rect sourceRect = animations[currentAnimation][frameIndex];
        graphics.blitSurface(spriteSheet, &sourceRect, &destinationRectangle);
    }
}

// void AnimatedSprite::setupAnimations() {
//     addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
//     addAnimation(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
// }
