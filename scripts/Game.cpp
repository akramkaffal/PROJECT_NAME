#include "Game.h"
#include <iostream>
#include "SDL_image.h"

// Constructor
Game::Game(int screenWidth, int screenHeight, SDL_Renderer* renderer)
    : screenWidth(screenWidth), screenHeight(screenHeight), renderer(renderer),
      currentState(MENU) , playerHealth(5), playerScore(0), avatar(nullptr), backgroundTexture(nullptr), ui(nullptr), background(nullptr) {ui = new UI(renderer);
    avatar = new Avatar(50, screenHeight / 2 - 25, 60, 60, renderer, "assets/avatar.png");
    setupMenu();

    // Initialize background
    background = new Background(renderer, "assets/background.jpg");
    if (!background) {
        std::cerr << "Error: Failed to initialize the background!" << std::endl;
    }


    // Load the background image
    SDL_Surface* surface = IMG_Load("assets/background.jpg");
    if (!surface) {
        std::cerr << "Failed to load background image: " << IMG_GetError() << std::endl;
    } else {
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface); // Free the surface after creating the texture
    }
}

void Game::setupMenu() {
    // Example: Add three menu options
    menuOptions.push_back(new MenuOption(100, 100, 200, 50, renderer, "Start Game")); // Option 1
    menuOptions.push_back(new MenuOption(100, 200, 200, 50, renderer, "Settings")); // Option 2
    menuOptions.push_back(new MenuOption(100, 300, 200, 50, renderer, "Exit")); // Option 3

    // Customize option colors
    menuOptions[0]->setInactiveColour(200, 200, 200); // Light grey
    menuOptions[0]->setActiveColour(255, 0, 0);      // Red when hovered

    menuOptions[1]->setInactiveColour(200, 200, 200);
    menuOptions[1]->setActiveColour(0, 255, 0);      // Green when hovered

    menuOptions[2]->setInactiveColour(200, 200, 200);
    menuOptions[2]->setActiveColour(0, 0, 255);      // Blue when hovered
}


// Main game loop function
bool Game::run() {
    std::cout << "Current state: " << currentState << std::endl;
    switch (currentState) {
        case MENU:
            displayMenu();
            break;
        case RUNNING:
            std::cout << "Game is running." << std::endl;
            handleEvents();
            update();
            render();
            break;
        case GAME_OVER:
            std::cout << "Game over. Cleaning up..." << std::endl;
            endGame();
            return false; // Return here to exit the game
    }

    // Add delay at the end of the loop to slow down the game
    SDL_Delay(5); // ~60 FPS (adjust value to make the game slower)
    return true; // Keep the game running
}

// Handle player input
void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            currentState = GAME_OVER;
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                currentState = MENU;
            }
        }
    }
}

// Update game logic
void Game::update() {
    static int hazardSpawnTimer = 0; // Timer to control spawning
    avatar->update();
    // Increment the timer
    hazardSpawnTimer++;
    // Spawn a hazard every 60 frames (about 1 second at 60 FPS)
    if (hazardSpawnTimer >= 60) {
        spawnHazard();
        hazardSpawnTimer = 0; // Reset the timer
    }

    // Update hazards
    for (auto it = hazards.begin(); it != hazards.end();) {
        (*it)->update();

        // Check for collisions with the avatar
        if (SDL_HasIntersection(&((*it)->getBounds()), &(avatar->getBounds()))) {
            playerHealth--; // Reduce health on collision
            delete *it;     // Remove hazard
            it = hazards.erase(it);
        }
        // Remove off-screen hazards
        else if ((*it)->isOffScreen()) {
            delete *it;
            it = hazards.erase(it);
        } else {
            ++it;
        }
    }

    // Spawn new hazards periodically
   // if (rand() % 100 < 5) { // 5% chance each frame
   //     spawnHazard();
   // }

    // Decrease health if playerHealth reaches zero
    if (playerHealth <= 0) {
        currentState = GAME_OVER;
    }

    playerScore++; // Increment score
    ui->gameUpdate(playerHealth,playerScore);

}


// Render the game
void Game::render() const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Clear screen with black
    SDL_RenderClear(renderer);
    background->render();
    avatar->render(); // Render the avatar

    // Render hazards
    for (const auto& hazard : hazards) {
        hazard->render();
    }

    ui->gameDraw();

    SDL_RenderPresent(renderer); // Present the updated screen

}


    // Placeholder for rendering game objects (player, hazards, etc.)

// Display the main menu
void Game::displayMenu() {
    bool showMenu = true;

    while (showMenu) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                currentState = GAME_OVER;
                showMenu = false;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                std::cout << "Mouse click at (" << event.button.x << ", " << event.button.y << ")" << std::endl;

                for (auto& option : menuOptions) {
                    if (option->getMouseOver()) {
                        std::cout << "Button clicked: " << option->getText() << std::endl;

                        if (option->getText() == "Start Game") {
                            currentState = RUNNING;
                            std::cout << "Transitioning to RUNNING state." << std::endl;
                            showMenu = false; // Exit the menu loop
                        } else if (option->getText() == "Exit") {
                            currentState = GAME_OVER;
                            showMenu = false; // Exit the menu loop
                        }
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (auto& option : menuOptions) {
            option->update();
            option->render();
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS
    }
}





// Start the game
void Game::startGame() {
    currentState = RUNNING;
    playerHealth = 3;
    playerScore = 0;
}

void Game::spawnHazard() {
    int y = rand() % (screenHeight - 50); // Random y position
    hazards.push_back(new Hazard(screenWidth, y, 50, 50, 5, renderer, "assets/hazard.png"));
}


// End the game and show the final score
void Game::endGame() {
    std::cout << "Game Over! Final Score: " << playerScore << std::endl;
    currentState = MENU;
}




