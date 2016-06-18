#include "input.h"

// Called at beginning of each frame to reset irrelevant keys
void Input::beginNewFrame() {
    pressedKeys.clear();
    releasedKeys.clear();
}

// Called when a key has been pressed
void Input::keyDownEvent(const SDL_Event &event) {
    pressedKeys[event.key.keysym.scancode] = true;
    heldKeys[event.key.keysym.scancode] = true;
}

// Called when a key is released
void Input::keyUpEvent(const SDL_Event &event) {
    releasedKeys[event.key.keysym.scancode] = true;
    heldKeys[event.key.keysym.scancode] = false;
}

// Check if a certain key was pressed during the current frame
bool Input::wasKeyPressed(SDL_Scancode key) {
    return pressedKeys[key];
}

// Check if a certian key was released during the current frame
bool Input::wasKeyReleased(SDL_Scancode key) {
    return releasedKeys[key];
}

// Check if a certain key is currently being held
bool Input::isKeyHeld(SDL_Scancode key) {
    return heldKeys[key];
}
