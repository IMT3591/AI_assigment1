/**
  \file main.cpp
  \date 20140120 - Magnus Øverbø
  \brief Main driver for the agent and environment
**/

//  Include files
#include "stdhd.h"
#include "environment.h"
#include "agent.h"

//  Global variables
int	 STEPS = 1;
Cell *X = new Cell(1, false, WALL);
Cell *Y = new Cell(2, false, WALL);
Cell *A = new Cell(3, false, OPEN);//, X, NULL, NULL, NULL);
Cell *B = new Cell(4, false, OPEN);//, A, Y, NULL, NULL);

//  Function declarations

int main( ){
	A->setNeighbors( X, B, NULL, NULL );
	B->setNeighbors( NULL, Y, NULL, NULL );

	for( int i=0; i<STEPS; i++){	
		X->display();
		A->display();
		B->display();
		Y->display();
	}
	return 0;
}


