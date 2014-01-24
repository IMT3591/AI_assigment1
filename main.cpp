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
int 	LAST_KEY;
Cell*	START;

struct List{
	Cell* info;
	List* n;
	List ( Cell* i){
		info = i;
		n = NULL;
	}
};

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
		tType = WALL;
		tLeft = 0;
		tUp		= 0;
	}
	LAST_KEY = tKey;
}


Cell*	findCell(int id){
	if( id <= 0 )		return NULL;
	Cell* ret;
	List *x = new List(START);
	List *y;
	while( !x->info->checkID( id ) ){
		if( x->info->getNeighbor(DOWN) != NULL ){
			y = x->n;
			x->n = new List( x->info->getNeighbor(DOWN) );
			x->n->n = y;
		}
		if( x->info->getNeighbor(RIGHT) != NULL ){
			y = x->n;
			x->n = new List( x->info->getNeighbor(RIGHT) );
			x->n->n = y;
		}
		x = x->n;
	}
	ret = x->info;
	delete x;
	return ret;
}

void displayMap(){
	Cell *a;
	for( int i=1; i<= LAST_KEY; i++){
		a = findCell( i );
		a->getType(); cout << ' ';
		if( a->getNeighbor(RIGHT) == NULL )
			cout << '\n';
	}
}

