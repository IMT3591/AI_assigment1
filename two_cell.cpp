
#include "stdhd.h"
#include <ctime>
#include "dummyAgent.h"
#include "environment.h"

//  Function declarations
int		calcPerfAward();

//  Global variables
int			STEPS = 1000;
Cell*		A, *B, *pt;
Agent*	bender;
int 		perf;
int			lastMove;
int			wait = 0;

//Main function
int main( ){
	srand( time(0) );
	A = new Cell(1, false, OPEN);
	B = new Cell(2, false, OPEN);
	B->setNeighbors(A, NULL, NULL, NULL );
	lastMove = LEFT;

	//bender 	= new Agent( A );
	bender 	= new Agent( B );
	
	//A->setDirty( true );
	//B->setDirty( true );

	for( int i=0; i<STEPS; i++){
		pt = bender->getCurrent();
		if( !A->getDirty() )	A->updateDirty();
		if( !B->getDirty() )	B->updateDirty();

		if( bender->isRunning() ){
			if( pt->getDirty() ){
				bender->clean();
			}
			else if( lastMove == LEFT &&  pt->getNeighbor( LEFT ) != NULL ){
				//bender->action("I'm moving to tho the left.");
				bender->updateLocation( LEFT );
			}
			else if( pt->getNeighbor( RIGHT ) != NULL ){
				lastMove = RIGHT;
				//bender->action("I'm moving to tho the right.");
				bender->updateLocation( lastMove );
			}
			else{
				//bender->action("I've covered all cells, now stopping.");
				bender->shutDown();
			}
		}
	 else if( wait == 3 || pt->getDirty() ){
		lastMove = LEFT;
		bender->boot();
		wait = 0;
		}
		else{
			//bender->action("No operation done.");
			++wait;
		}
		perf += calcPerfAward();
	}
	
	cout << "\n\nPerformance:\t" << perf << "\n";
	bender->printPerf();
	cout << "\n\n";
	return 0;
}

// FUNCTIONS

/**
\brief Calculates current performance measure
**/
int calcPerfAward(){
	int award = 0;
	if( !A->getDirty() ) ++award;
	if( !B->getDirty() ) ++award;
	return award;
}

