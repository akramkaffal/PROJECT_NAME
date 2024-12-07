//
// Created by Harvey on 02/12/2024.
//

#include "UI.h"
UI::UI(SDL_Renderer *renderer): renderer(renderer){
    playerHP=0;
    playerScore=0;
}

void UI::gameUpdate(int inputPlayerHP, int inputPlayerScore) {
    playerScore=inputPlayerScore;
    playerHP=inputPlayerHP;
}

void UI::gameDraw() {
    drawScore();
}

void UI::drawScore(){
    int x=5;
    int y=5;
    for(int i=0;i<playerHP;i++){
        SDL_Rect tempRec{x,y,30,30};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &tempRec);
        x+=35;
    }
};