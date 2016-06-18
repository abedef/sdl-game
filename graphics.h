#ifndef GRAPHICS_H
#define GRAPHICS_H

/* Graphics class
 * Holds all information dealing with graphics for the game.
 */

#include <map>
#include <string>

// Try to include as little as possible in header files
// Forward declare to let us use these types as pointers without including SDL.h
struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
    Graphics();
    ~Graphics();

    // Loads an image into the spriteSheets map if it doesn't already exist
    // As a result, each image will only ever be loaded once
    // Returns the image from the map regardless of whether it's just loaded
    SDL_Surface *loadImage(const std::string &filePath);

    // Draws a texture to a certain part of the screen
    void blitSurface(SDL_Texture *source,
            SDL_Rect *sourceRectangle,
            SDL_Rect *destinationRectangle);

    // Renders everything to the screen
    void flip();

    // Clears the screen
    void clear();

    // Returns the renderer
    SDL_Renderer *getRenderer() const;
private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    std::map<std::string, SDL_Surface *> spriteSheets;
};

#endif
