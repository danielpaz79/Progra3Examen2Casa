/*
   ****************************************
   Creditos: Alver Lopez
   ****************************************
*/

#include "Object.h"

Object::Object()
{
    pos.x = 0;
    pos.y = 0;
}

Object::~Object()
{

}

void Object::set_posX( int x )
{
    pos.x = x;
}

int Object::get_posX() const
{
    return pos.x;
}

void Object::set_posY( int y )
{
    pos.y = y;
}

int Object::get_posY() const
{
    return pos.y;
}
