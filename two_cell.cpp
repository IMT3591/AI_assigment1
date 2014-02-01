
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
	bender 	= new Agent( A );
	lastMove = LEFT;

	for( int i=0; i<STEPS; i++){
		pt = bender->getCurrent();
		//if( !A->getDirty() )	A->updateDirty();
		//if( !B->getDirty() )	B->updateDirty();

		if( bender->isRunning() ){
			if( pt->getDirty() ){
				bender->clean();
			}
			else if( lastMove == LEFT &&  pt->getNeighbor( LEFT ) != NULL ){
				bender->updateLocation( LEFT );
				bender->action("I'm moving to tho the left.");
			}
			else if( pt->getNeighbor( RIGHT ) != NULL ){
				lastMove = RIGHT;
				bender->updateLocation( lastMove );
				bender->action("I'm moving to tho the right.");
			}
			else{
				bender->shutDown();
				bender->action("Nothing more to do. I've been to the left and I've been to the right. I'm DOOOOOOONE, NO MORE CLEANING FOR ME.");
			}
		}
/*		else if( wait == 5 || pt->getDirty() ){
			lastMove = LEFT;
			bender->boot();
			wait = 0;
		}*/
		else{
			bender->action("No sucking, no moving until later.");
			++wait;
		}
		perf += calcPerfAward();
	}
	
	cout << "Performance:\t" << perf << "\n";
	bender->printPerf();

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

