#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Avatar.h"
#include <vector>

#include "Hazard.h"
#include "Menu.h"
#include "UI.h"
#include "Background.h"

class Game {
public:
    Game(int screenWidth, int screenHeight, SDL_Renderer* renderer);
    ~Game() {
        for (auto& option : menuOptions) {
            delete option;
        }
        menuOptions.clear();
    }

    bool run(); // Main game loop function

private:
    void handleEvents();
    void update();
    void render() const;
    std::vector<Hazard*> hazards; //vector to store hazards
    void spawnHazard();
    std::vector<MenuOption*> menuOptions; // Hold menu options
    void setupMenu();                     // Initialize menu options
    void displayMenu();                   // Show and manage the menu
    Background* background;


    // Game state management
    enum GameState { MENU, RUNNING, GAME_OVER };
    GameState currentState;

    // Core properties
    SDL_Renderer* renderer;
    int screenWidth;
    int screenHeight;

    // Player properties
    int playerHealth;
    int playerScore;

    // Avatar
    Avatar* avatar;

    //menu
    Menu* menu;
    UI* ui;

    // Helper methods
    void startGame();
    void endGame();

    SDL_Texture* backgroundTexture; // Texture for the background

};

#endif
