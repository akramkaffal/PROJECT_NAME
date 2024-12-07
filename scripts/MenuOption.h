//
// Created by Harvey on 25/11/2024.
//

#ifndef PROJECT_NAME_MENUOPTION_H
#define PROJECT_NAME_MENUOPTION_H

#include <SDL.h>
#include <string>

class MenuOption {
public:
    // Getter for the button text
    std::string getText() const {
        return text;
    }
    MenuOption(int x, int y, int width, int height, SDL_Renderer* renderer, const std::string& buttonText);
    ~MenuOption() = default;

    void setActiveColour(int R, int G, int B);
    void setInactiveColour(int R, int G, int B);


    SDL_Renderer* renderer;

    void update();
    void render() const;

    bool getMouseOver();

private:
    SDL_Rect rect;
    int inActiveColour[3];
    int activeColour[3];
    bool mouseOverButton;
    std::string text;


};


#endif //PROJECT_NAME_MENUOPTION_H
