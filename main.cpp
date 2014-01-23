/**
  \file main.cpp
  \date 20140120 - Magnus Øverbø
  \brief Main driver for the agent and environment
**/

//  Include files
#include "stdhd.h"
#include "dummyAgent.h"
#include "environment.h"

//  Global variables
int	 	STEPS = 1;
char 	FNAME[] = "geo.mp";
Cell*	START;

//  Function declarations
void 	createMap();
void	displayMap();
Cell* findCell(int);
int		retType(char*);

//Main function
int main( ){
	createMap();
	displayMap();
	return 0;
}

// FUNCTIONS
int retType(char tType){
	if( 		 tType == 'W' ) return WALL;
	else if( tType == 'O' ) return OBSTACLE;
	else										return OPEN;
}

void  createMap(){
	int		ttType, tLeft, tUp, tKey = 0;
	char	tType;
	ifstream map( FNAME );
	
	if( !map.eof() && map >> tType >> tLeft >> tUp ){
		ttType = retType( tType); 
		START = new Cell( ++tKey, false, ttType );
	}
	while( !map.eof() && map >> tType >> tLeft >> tUp ){
		ttType = retType( tType ); 
		Cell* x = new Cell( ++tKey, false, ttType );
		x->setNeighbors( findCell(tLeft), findCell(0), findCell(tUp), findCell(0) );
	} 
}

Cell*	findCell(int id){
	if( id <= 0 )		return NULL;
	Cell *x;
	x = START;
	return x;
}

void displayMap(){
}


