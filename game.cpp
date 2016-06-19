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

    player = Player(graphics, 100, 100);
    level = Level("map_1", Vector2(100, 100), graphics);

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
        else if (input.isKeyHeld(SDL_SCANCODE_LEFT)) player.moveLeft();
        else if (input.isKeyHeld(SDL_SCANCODE_RIGHT)) player.moveRight();

        if (!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT)) player.stopMoving();

        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

        update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));

        LAST_UPDATE_TIME = CURRENT_TIME_MS;

        draw(graphics);
    }
}

void Game::draw(Graphics &graphics) {
    graphics.clear();

    level.draw(graphics);
    player.draw(graphics);

    graphics.flip();
}

void Game::update(float elapsedTime) {
    player.update(elapsedTime);
    level.update(elapsedTime);
}
