#ifndef SNAKE_H
#define SNAKE_H

#include "SDL2/SDL.h"
#include "Object.h"
#include <deque>

enum Direction { UP, RIGHT, DOWN, LEFT };

class Snake : public Object
{
    public:
        Snake();
        void grow();
        void move();
        void set_collision_state( bool state );
        bool get_collision_state() const;
        bool self_collide() const;
        //void set_frontX( int x );
        int get_frontX() const;
        //void set_frontY( int y );
        int get_frontY() const;
        int get_posX( int pos ) const;
        int get_posY( int pos ) const;
        void set_body_rect( int x, int y );
        Direction get_direction() const;
        void set_direction( Direction value );
        SDL_Rect* get_body_ptr();
        int length() const;
        ~Snake();
    private:
    	std::deque< SDL_Point > snakePos;
        SDL_Rect body;

        Direction direction;
        bool collided;

        void move_to_direction();
};

#endif // SNAKE_H
