/*
   ****************************************
   Creditos: Alver Lopez
   ****************************************
*/

#include "Food.h"
#include <ctime>
#include <cstdlib>
#include <vector>

Food::Food()
{
    std::srand( time( 0 ) );
    eaten = false;
}

Food::~Food()
{

}

void Food::set_food( int* time_waiting, Map& myMap )
{
	std::vector< SDL_Point > availableSpace;

	SDL_Point point;

	int chosenSpace;

	if ( *time_waiting <= 0 || eaten )
	{
		for ( int i = 0; i < ROW_SIZE; ++i )
		{
			for ( int j = 0; j < COL_SIZE; ++j )
			{
				if ( myMap.get_symbol( j, i ) == EMPTY )
				{
					point.x = j;
					point.y = i;
					availableSpace.push_back( point );
				}
			}
		}

		chosenSpace = std::rand() % availableSpace.size();

		pos.x = availableSpace[ chosenSpace ].x;
		pos.y = availableSpace[ chosenSpace ].y;

		*time_waiting = std::rand() % ( ROW_SIZE * COL_SIZE ) + 1;

		eaten = false;
	}
}

void Food::set_eaten_state( bool state )
{
    eaten = state;
}

bool Food::get_eaten_state() const
{
    return eaten;
}
