#include <SDL2/SDL.h>

#include "game.h"
#include "graphics.h"
#include "input.h"

namespace {
    const int FPS = 50;
    const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    gameLoop();
}

Game::~Game() {
}

void Game::gameLoop() {
    Graphics graphics;
    Input input;
    SDL_Event event;

    player = Sprite(graphics, "content/sprites/MyChar.png", 0, 0, 16, 16, 100, 100);

    // Get the number of milliseconds since the library was initialized
    int LAST_UPDATE_TIME = SDL_GetTicks();

    // Start the game loop
    while (true) {
        input.beginNewFrame();

        if (SDL_PollEvent(&event)) {
            switch(event.type) {
            case SDL_KEYDOWN:
                if (!event.key.repeat) input.keyDownEvent(event);
                break;
            case SDL_KEYUP:
                input.keyUpEvent(event);
                break;
            case SDL_QUIT:
                return;
            }
        }

        if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) return;

        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

        update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));

        LAST_UPDATE_TIME = CURRENT_TIME_MS;

        draw(graphics);
    }
}

void Game::draw(Graphics &graphics) {
    graphics.clear();

    player.draw(graphics, 100, 100);

    graphics.flip();
}

void Game::update(float elapsedTime) {
}
