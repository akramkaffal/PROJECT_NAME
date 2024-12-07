//
// Created by Harvey on 25/11/2024.
//

#ifndef MENU_H
#define MENU_H

#include "MenuOption.h"
#include <SDL.h>

class Menu {
public:
    Menu(SDL_Renderer* renderer);
    ~Menu() = default;
    void update(bool press);
    void render();
    bool checkGameStart();
    bool checkGameExit();
private:

    SDL_Renderer* renderer;
    MenuOption start;
    MenuOption exit;
    bool gameExit;
    bool gameStart;
    int cursorX;
    int cursorY;
    bool containsCursor(SDL_Rect option);


};


#endif //PROJECT_NAME_MENU_H
