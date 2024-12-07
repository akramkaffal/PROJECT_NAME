//
// Created by Harvey on 25/11/2024.
//

#include "Menu.h"
#include "MenuOption.h"
//800 by 600
Menu::Menu(SDL_Renderer *renderer): renderer(renderer),
    start{100,50,600,200, renderer,"Start"},
    exit{100,350,600,200,renderer,"Exit"}{

    start.setActiveColour(0,255,0);


    exit.setActiveColour(255,0,0);
    gameStart= false;
    gameExit= false;
}

void Menu::update(bool press) {


    if(press){
        SDL_log('test');
    }


    if(press) {

        gameExit = exit.getMouseOver();
        gameStart=start.getMouseOver();

    }

    start.update();
    exit.update();


}

bool Menu::checkGameStart() {
    return  gameStart;
}
bool Menu::checkGameExit() {
    return gameExit;
}

void Menu::render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Clear screen with black
    SDL_RenderClear(renderer);
    //drawing basic options
    start.render();
    exit.render();

    //drawing lables over

    //play lable
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 0+375,0+125,0+375,50+125);
    SDL_RenderDrawLine(renderer, 0+375,0+125,50+375,25+125);
    SDL_RenderDrawLine(renderer, 50+375,25+125,0+375,50+125);

    //exit lable
    SDL_RenderDrawLine(renderer, 0+375,50+425,50+375,0+425);
    SDL_RenderDrawLine(renderer, 0+375,0+425,50+375,50+425);

    SDL_RenderPresent(renderer);


}
