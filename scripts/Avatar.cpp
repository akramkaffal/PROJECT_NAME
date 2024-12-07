#include "Avatar.h"
#include <SDL_image.h>
#include <iostream>

Avatar::Avatar(int x, int y, int width, int height, SDL_Renderer* renderer, const std::string& texturePath)
    : rect{x, y, width, height}, speed(5), renderer(renderer), texture(nullptr) {
    // Load the texture from the specified file path
    SDL_Surface* surface = IMG_Load(texturePath.c_str());
    if (!surface) {
        std::cerr << "Failed to load avatar texture: " << IMG_GetError() << std::endl;
        return;
    }
    // Create a texture from the surface
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Failed to create avatar texture: " << SDL_GetError() << std::endl;
    } else {
        std::cout << "Avatar texture loaded successfully: " << texturePath << std::endl;
    }
}


// Handle keyboard input for movement
void Avatar::handleInput(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                rect.y -= speed;
            break;
            case SDLK_DOWN:
                rect.y += speed;
            break;
            default:
                break;
        }
    }
}

// Update avatar logic (e.g., constrain movement to screen bounds)
void Avatar::update() {
    const Uint8* kState = SDL_GetKeyboardState(nullptr);
    if(kState[SDL_SCANCODE_UP]){
        rect.y-=1;
    }
    if(kState[SDL_SCANCODE_DOWN]){
        rect.y+=1;
    }




    if (rect.y < 0) rect.y = 0; // Prevent going off the top
    if (rect.y + rect.h > 600) rect.y = 600 - rect.h; // Prevent going off the bottom
}

// Render the avatar
void Avatar::render() const {
    if (texture) {
        if (SDL_RenderCopy(renderer, texture, nullptr, &rect) != 0) {
                std::cerr << "Failed to render avatar texture: " << SDL_GetError() << std::endl;
        }
    } else {
    // render a fallback square
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
        SDL_RenderFillRect(renderer, &rect);
        }

    }


// Get the bounding box for collision detection
SDL_Rect& Avatar::getBounds() {
    return rect;
}
