#include "Hazard.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
Hazard::Hazard(int x, int y, int width, int height, int speed, SDL_Renderer* renderer, const std::string& texturePath)
    : rect{x, y, width, height}, speed(speed), renderer(renderer) {
    SDL_Surface* surface = IMG_Load(texturePath.c_str());
    if (!surface) {
        std::cerr << "Failed to load hazard texture: " << IMG_GetError() << std::endl;
        return;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Failed to create hazard texture: " << SDL_GetError() << std::endl;
    }
    this->speed = 1;
}


// Update position
void Hazard::update() {
    rect.x -= speed; // Move left by speed
}

// Render the hazard
void Hazard::render() const {
    if (texture) {
        if (SDL_RenderCopy(renderer, texture, NULL, &rect) != 0) {
            std::cerr << "Failed to render hazard texture: " << SDL_GetError() << std::endl;
        }
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
        SDL_RenderFillRect(renderer, &rect);

    }
}



// Check if the hazard is off the screen
bool Hazard::isOffScreen() const {
    return rect.x + rect.w < 0; // Completely out of the left side
}

// Get the bounding box for collision detection
SDL_Rect& Hazard::getBounds() {
    return rect;
}
Hazard::~Hazard() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}