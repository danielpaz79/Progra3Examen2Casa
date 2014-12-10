/*
   ****************************************
Creditos: Alver Lopez
   ****************************************
*/

#include "Map.h"

Map::Map()
{
    clear_map();
}

Map::~Map()
{

}

void Map::clear_map()
{
	for ( int i = 0; i < ROW_SIZE; ++i )
		for ( int j = 0; j < COL_SIZE; ++j )
			pos[i][j] = EMPTY;
}

void Map::set_symbol( int x, int y, char symbol )
{
	pos[y][x] = symbol;
}

char Map::get_symbol( int x, int y ) const
{
	return pos[y][x];
}
