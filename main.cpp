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
int	 STEPS = 3;
Cell *X = new Cell(false, WALL);
Cell *Y = new Cell(false, WALL);
Cell *A = new Cell(false, OPEN, X, NULL, NULL, NULL);
Cell *B = new Cell(false, OPEN, A, Y, NULL, NULL);

//  Function declarations
void update();

int main( ){
	
	for( int i=0; i<STEPS; i++){	
		A->updateAge();
		B->updateAge();
		A->display();
		B->display();
	}
	return 0;
}


