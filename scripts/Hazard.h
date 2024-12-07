#ifndef HAZARD_H
#define HAZARD_H
#include <SDL.h>
#include <string>

class Hazard {
public:
    Hazard(int x, int y, int width, int height, int speed, SDL_Renderer* renderer, const std::string& texturePath);
    ~Hazard();
    void update();          // Update position
    void render() const;    // Render the hazard
    bool isOffScreen() const; // Check if the hazard has left the screen
    SDL_Rect& getBounds(); // For collision detection

private:
    SDL_Rect rect; // Position and size of the hazard
    int speed;     // Movement speed
    SDL_Renderer* renderer; // Texture for the hazard
    SDL_Texture* texture; // Renderer for the hazard
};

#endif
