#include "Background.h"
#include <SDL_image.h>
#include <iostream>

Background::Background(SDL_Renderer* renderer, const std::string& imagePath)
    : renderer(renderer), texture(nullptr) {
    // Load the image as a surface
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if (!surface) {
        std::cerr << "Failed to load background image: " << IMG_GetError() << std::endl;
    } else {
        // Create a texture from the surface
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface); // Free the surface after creating the texture

        if (!texture) {
            std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        }
    }
}

Background::~Background() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void Background::render() {
    if (texture) {
        // Render the texture to cover the entire screen
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    } else {
        std::cerr << "Error: Background texture is null" << std::endl;
    }
}
