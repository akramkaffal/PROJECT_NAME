//
// Created by Harvey on 02/12/2024.
//

#ifndef PROJECT_NAME_UI_H
#define PROJECT_NAME_UI_H
#include <SDL.h>

class UI {
public:
    UI(SDL_Renderer* renderer);
    ~UI() = default;
    void gameUpdate(int inputPlayerHP,int inputPlayerScore);
    void gameDraw();
    void menuDraw();

private:
    SDL_Renderer* renderer;
    int finalHP();
    void drawScore();
    void drawHP(int playerHP);
    int playerScore;
    int playerHP;
    void draw0(int x, int y);
    void draw1(int x, int y);
    void draw2(int x, int y);
    void draw3(int x, int y);
    void draw4(int x, int y);
    void draw5(int x, int y);
    void draw6(int x, int y);
    void draw7(int x, int y);
    void draw8(int x, int y);
    void draw9(int x, int y);
};


#endif //PROJECT_NAME_UI_H
