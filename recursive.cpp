
#include "stdhd.h"
#include <ctime>
#include "dummyAgent.h"
#include "environment.h"

//  Function declarations
void 	createMap();
void	displayMap();
Cell* findCell(int);
int		retType(char*);
//  Global variables
//char 		FNAME[] = "..\\geo.mp";
char 		FNAME[] = "geo.mp";
//char 		FNAME[] = "complex.mp";
int 		LAST_KEY;
Cell*		START;
List*		list;
Agent*	bender;
//Main function
int main( ){
	srand( time(0) );
	createMap();
	bender 	= new Agent( START->getNeighbor(RIGHT)->getNeighbor(DOWN) );
	
	//displayMap();
	while( bender->retSteps() > 1 ){
		bender->visit( bender->getCurrent(), -1, list );
	}
	//Final print
	displayMap();
	bender->printPerf();
	return 0;
}

// FUNCTIONS
/**
	\brief	Returns the int value of the TYPE in the geo.mp file.
	\date		20140124 - Magnus Øverbø
**/
int retType(char tType){
	if( 	 tType == 'W' ) return WALL;
	else if( tType == 'O' ) return OBSTACLE;
	else					return OPEN;
}

/**
  \brief	Creeates the map from the file geo.mp which holds the map

	the file format is [TYPE] [LEFT] [UP] where the TYPE is W, O C, and LEFT/UP is
	the key for the neighboring cell.  When these are set the existing node will
	automatically link back to the new node.
  \date		20140124 - Magnus Øverbø
**/
void  createMap(){
	int		ttType, tLeft, tUp, tKey = 0;
	bool	tDirt = false;
	char	tType;
	ifstream map( FNAME );
	
		// Set-up the initial node
	if( !map.eof() && map >> tType >> tLeft >> tUp ){
		ttType = retType( tType); 
		START = new Cell( ++tKey, false, ttType );
		list  = new List( START );
	}
	else cout << "Couldn't read the file, check it's location";
	while( !map.eof() && map >> tType >> tLeft >> tUp ){
		ttType = retType( tType );
		Cell* x = new Cell( ++tKey, tDirt, ttType );
		List* y = new List( x );
		y->n = list->n;
		list->n = y;
		x->setNeighbors( findCell(tLeft), findCell(0), findCell(tUp), findCell(0) );
		tType = WALL;		tLeft = 0;		tUp		= 0;
	}
	LAST_KEY = tKey;
}

/**
  \brief	Finds the cell by doing a depht first search of the list
  \date 	20140124 - Magnus Øverbø
**/
Cell*	findCell(int id){
	if( id <= 0 )		return NULL;
	Cell* ret = NULL;		List *x = list;
	while( x != NULL && !x->info->checkID( id ) ){
		x = x->n;
	}
	if( x->info->checkID(id) )
		ret = x->info;
	return ret;
}

/**
  \brief	Displays the map by going through keys made during generation one by
	one and printing their type
  \date 	20140124 - Magnus Øverbø
**/
void displayMap(){
	Cell *a;	//< Temporary holder for the retrieved cell
	cout << "\n";
	for( int i=1; i<= LAST_KEY; i++){
		a = findCell( i );
		if( a->getNeighbor(LEFT) == NULL ){	cout << '\n';}
		if ( i == bender->retLocID() )			{ cout << "H"; }
		else if( a->getDirty()   )  { cout << "D"; }
		else if( a->retVisited() )	{ cout << "B"; }
		else a->getType();
		cout << ' ';
	}
	cout << "\n";
}


/**
\brief Calculates current performance measure
**/
int calcPerfAward(){
	List* x = list; int award=0;
	while( x != NULL ){
		if( !x->info->getDirty() && x->info->retType() == OPEN )
			award++;
		x = x->n;	
	}
	return award;
}
