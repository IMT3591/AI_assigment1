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
int	 STEPS = 1000;
Cell *A = new Cell(false);
Cell *B = new Cell(false);

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


