#include "sprite.h"
#include "graphics.h"
#include "globals.h"

Sprite::Sprite() {}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY) : x(posX), y(posY) {
    sourceRect.x = sourceX;
    sourceRect.y = sourceY;
    sourceRect.w = width;
    sourceRect.h = height;

    spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
    if (!spriteSheet) printf("Error: Unable to load image\n");
}

Sprite::~Sprite() {}

void Sprite::draw(Graphics &graphics, int x, int y) {
    SDL_Rect destinationRectangle = {
        x, y, sourceRect.w * globals::SPRITE_SCALE, sourceRect.h * globals::SPRITE_SCALE
    };
    graphics.blitSurface(spriteSheet, &sourceRect, &destinationRectangle);
}

void Sprite::update() {}
