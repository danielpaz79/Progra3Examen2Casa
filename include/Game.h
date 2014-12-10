#ifndef GAME_H
#define GAME_H

#include <string>
#include <cstdlib>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "LTexture.h"
#include "Map.h"
#include "Snake.h"
#include "Food.h"

#include<iostream>
#include<fstream>

class Game
{
    public:
        Game();
        ~Game();
        int time_waiting;
        void execute();
        bool start();
        void think();
        void update();
        void update_2();
        void render();
       // void close();

    private:
    	bool success;
        bool quit;
        bool oneKeyPressed;
        std::string str_score;

    	SDL_Window* mWindow;
    	SDL_Renderer* mRenderer;
        SDL_Event event;
    	TTF_Font* mFont;

        SDL_Color textColor;

    	LTexture wall;
        LTexture textTexture_1;
        LTexture textTexture_2;
        LTexture textTexture_3;
        LTexture textTexture_4;
        LTexture scoreTexture;

    	Snake snake;
        Map myMap;
        Food food;

};

#endif // GAME_H
