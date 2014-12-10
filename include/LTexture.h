#ifndef LTEXTURE_H
#define LTEXTURE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include <fstream>
#include <cstdlib>

class LTexture
{
    public:
        LTexture();
        ~LTexture();
        bool loadFromFile( std::string path, SDL_Renderer* renderer, std::ofstream& mFile );
        bool loadFromRenderedText( std::string textTexture, SDL_Color textColor, TTF_Font* mFont, std::ofstream& mfile, SDL_Renderer* renderer );
        void free();
        void render( int x, int y, SDL_Renderer* renderer );
        int getWidth() const;
        int getHeight() const;

    private:
    	SDL_Texture *mTexture;
    	int mWidth;
    	int mHeight;
};

#endif // LTEXTURE_H
