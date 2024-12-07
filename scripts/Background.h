#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL.h>
#include <string>

class Background {
private:
    SDL_Texture* texture;
    SDL_Renderer* renderer;

public:
    Background(SDL_Renderer* renderer, const std::string& imagePath);
    ~Background();

    void render();
};

#endif
