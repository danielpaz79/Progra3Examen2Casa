#ifndef FOOD_H
#define FOOD_H

#include "Config.h"
#include "Map.h"
#include "Object.h"

class Food : public Object
{
    public:
        Food();
        void set_food( int* time_waiting, Map& myMap );
        void set_eaten_state( bool state );
        bool get_eaten_state() const;
        ~Food();

    private:
        bool eaten;
};

#endif // FOOD_H
