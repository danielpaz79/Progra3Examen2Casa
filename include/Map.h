#ifndef MAP_H
#define MAP_H

#include "Config.h"

class Map
{
    public:
        Map();
        void clear_map();
        void set_symbol( int x, int y, char symbol );
        char get_symbol( int x, int y ) const;
        ~Map();
    private:
        char pos[ROW_SIZE][COL_SIZE];

};

#endif // MAP_H
