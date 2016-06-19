#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "graphics.h"
#include "globals.h"

Graphics::Graphics() {
    SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Cavestory");
}

Graphics::~Graphics() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

SDL_Surface *Graphics::loadImage(const std::string &filePath) {
    if (spriteSheets.count(filePath) == 0) {
        spriteSheets[filePath] = IMG_Load(filePath.c_str());
    }

    return spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture *texture,
        SDL_Rect *sourceRectangle,
        SDL_Rect *destinationRectangle) {
    SDL_RenderCopy(renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip() {
    SDL_RenderPresent(renderer);
}

void Graphics::clear() {
    SDL_RenderClear(renderer);
}

SDL_Renderer *Graphics::getRenderer() const {
    return renderer;
}
