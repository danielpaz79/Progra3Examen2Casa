#ifndef OBJECT_H
#define OBJECT_H

#include "SDL2/SDL.h"
#include "LTexture.h"
#include <fstream>
#include <cstdlib>


class Object
{
    public:
        Object();
        void set_posX( int x );
        int get_posX() const;
        void set_posY( int y );
        int get_posY() const;
        ~Object();

        LTexture texture;

    protected:
        SDL_Point pos;

};

#endif // OBJECT_H
