/*
   ****************************************
Creditos: Alver Lopez
   ****************************************
*/

#include "Snake.h"
#include "Config.h"


Snake::Snake()
{
    pos.x = COL_SIZE / 2;
    pos.y = ROW_SIZE / 2;

    body.x = 0;
    body.y = 0;
    body.w = IMAGE_WIDTH;
    body.h = IMAGE_HEIGHT;

    snakePos.push_front( pos );

    direction = RIGHT;

    collided = false;
}

Snake::~Snake()
{

}

void Snake::grow()
{
	move_to_direction();
	snakePos.push_front( pos );
}

void Snake::move()
{
	// Movemos todo el cuerpo de la serpiente excepto la cabeza
	for ( int i = snakePos.size() - 1; i > 0; --i )
	{
		snakePos[i].x = snakePos[i-1].x;
		snakePos[i].y = snakePos[i-1].y;
	}

	move_to_direction();

	snakePos.front() = pos;
}

// Movemos la cabeza de la serpiente
void Snake::move_to_direction()
{
	pos = snakePos.front();

	switch( direction )
	{
		case RIGHT:
			pos.x++;
		break;
		case LEFT:
			pos.x--;
		break;
		case UP:
			pos.y--;
		break;
		case DOWN:
			pos.y++;
		break;
	}
}

void Snake::set_collision_state( bool state )
{
	collided = state;
}

bool Snake::get_collision_state() const
{
	return collided;
}

int Snake::get_frontX() const
{
	return snakePos.front().x;
}

int Snake::get_frontY() const
{
	return snakePos.front().y;
}

int Snake::length() const
{
	return snakePos.size();
}

int Snake::get_posX( int pos ) const
{
	return snakePos[pos].x;
}

int Snake::get_posY( int pos ) const
{
	return snakePos[pos].y;
}

void Snake::set_body_rect( int x, int y )
{
	body.x = x;
	body.y = y;
}

SDL_Rect* Snake::get_body_ptr()
{
	return &body;
}

bool Snake::self_collide() const
{
	for ( int i = 1; i < snakePos.size(); ++i )
	{
		if ( ( snakePos.front().x == snakePos[i].x ) &&
			 ( snakePos.front().y == snakePos[i].y ) )
		{
			return true;
		}
	}

	return false;
}

Direction Snake::get_direction() const
{
	return direction;
}

void Snake::set_direction( Direction value )
{
	direction = value;
}
