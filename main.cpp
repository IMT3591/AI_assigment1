/**
  \file main.cpp
  \date 20140120 - Magnus Øverbø
  \brief Main driver for the agent and environment
**/

//  Include files
#include "stdhd.h"
#include "environment.h"
#include "dummyAgent.h"

//  Global variables
int	 	STEPS = 1;
char 	FNAME[] = "geo.mp";

//  Function declarations
void 	createMap();
void	displayMap();
Cell* findCell(int);

//Main function
int main( ){
	createMap();
	displayMap();
	return 0;
}

// FUNCTIONS
void  createMap(){
	char	tType;
	int		ttType;
	int		tLeft, tUp;
	int		tKey = 0;
	ifstream map( FNAME );
	while( !map.eof() && map >> tType >> tLeft >> tUp ){
		if( 		 tType == 'C' )	ttType = OPEN;
		else if( tType == 'W' ) ttType = WALL;
		else if( tType == 'O' ) ttType = OBSTACLE;

		tKey++;
		Cell* x = new Cell(tKey, false, ttType);
		x->setNeighbors( findCell(tLeft), findCell(0), findCell(tUp), findCell(0) );
	} 
}

Cell*	findCell(int id){
	if( id <= 0 )		return NULL;
	Cell *x;
	return x;
}

void displayMap(){
}


