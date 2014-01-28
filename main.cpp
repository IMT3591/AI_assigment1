
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
int			STEPS = 1000;
char 		FNAME[] = "..\\geo.mp";
//char 		FNAME[] = "geo.mp";
int 		LAST_KEY;
Cell*		START;
Agent*	bender;

//Main function
int main( ){
	srand( time(0) );
	createMap();
	bender 	= new Agent( START );//START->getNeighbor(RIGHT)->getNeighbor(DOWN) );
	
		displayMap();
	for( int i=0; i<STEPS; i++){
		bender->move();
	}
	
	//	Recursive algorithm, it works but has a very low performance
	//bender->visit( bender->getCurrent() );
	
	cout << "Finished with: "; bender->printSteps(); cout << " left.\n";
	cout << "Performance: "; bender->printPerf(); cout << " points\n";
	displayMap();
	return 0;
}

// FUNCTIONS
/**
	\brief	Returns the int value of the TYPE in the geo.mp file.
	\date		20140124 - Magnus Øverbø
**/
int retType(char tType){
	if( 		 tType == 'W' ) return WALL;
	else if( tType == 'O' ) return OBSTACLE;
	else										return OPEN;
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
	
	if( !map.eof() && map >> tType >> tLeft >> tUp ){
		ttType = retType( tType); 
		START = new Cell( ++tKey, false, ttType );
	}
	else cout << "Couldn't read the file, check it's location";
	while( !map.eof() && map >> tType >> tLeft >> tUp ){
		ttType = retType( tType );
		//if(ttType == OPEN)
		//	tDirt = (( rand() % 2 ) ? true : false);
		//else tDirt = false;
		Cell* x = new Cell( ++tKey, tDirt, ttType );
		x->setNeighbors( findCell(tLeft), findCell(0), findCell(tUp), findCell(0) );
		tType = WALL;
		tLeft = 0;
		tUp		= 0;
	}
	LAST_KEY = tKey;
}


/**
  \brief	Finds the cell by doing a depht first search of the graph

	It creates a list/stack where the down and right neighbor of the cell is
	pushed on, then it will move to the next on the list and check its key, if
	found it will return the cell. It makes the assumption that the key exists
  \date 	20140124 - Magnus Øverbø
**/
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
		if ( i == bender->retLocID() )
			cout << "H";
		else if( a->retVisited() == true )
			cout << "B";
		else a->getType();
		cout << ' ';
		if( a->getNeighbor(RIGHT) == NULL )
			cout << '\n';
	}
}

