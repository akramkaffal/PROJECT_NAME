//
// Created by Harvey on 25/11/2024.
//

#include "MenuOption.h"
using namespace std;

MenuOption::MenuOption(int x, int y, int width, int height, SDL_Renderer *renderer, const std::string& buttonText):
rect{x, y, width, height}, renderer(renderer), text(buttonText) {

    //sett deafualt colours
    setInactiveColour(255,255,255);
    setActiveColour(255,255,255);

}

void MenuOption::setActiveColour(int R, int G, int B) {
    activeColour[0]=R;
    activeColour[1]=G;
    activeColour[2]=B;
}

void MenuOption::setInactiveColour(int R, int G, int B) {
    inActiveColour[0]=R;
    inActiveColour[1]=G;
    inActiveColour[2]=B;
}

void MenuOption::update() {
    //needs to find out it if is being touched by cursor

    //get mouse position
    int mouseX,mouseY;
    SDL_GetMouseState(&mouseX,&mouseY);
    //check if in bounds
    if(rect.x<=mouseX&&mouseX<=rect.x+rect.w&&
        rect.y<=mouseY&&mouseY<=rect.y+rect.h){
        mouseOverButton= true;
        const Uint8* kState = SDL_GetKeyboardState(nullptr);

    }
    else{
        mouseOverButton= false;
    }

}

bool MenuOption::getMouseOver() {
    return mouseOverButton;
}

void MenuOption::render() const {
    //set colour
    if(mouseOverButton){
        SDL_SetRenderDrawColor(renderer, activeColour[0], activeColour[1], activeColour[2], 255);
    }
    else{
        SDL_SetRenderDrawColor(renderer, inActiveColour[0], inActiveColour[1], inActiveColour[2], 255);
    }


    //draw rect
    SDL_RenderFillRect(renderer, &rect);

}