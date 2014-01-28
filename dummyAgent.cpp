/**
	\file		agent.cpp
	\date		20140122 - Magnus Øverbø
	\brief 	Functions for the agent class
**/

#include "dummyAgent.h"

int INIT_PERFORMANCE = 0;
int INIT_STEPS = 1000;
/**
	\brief 	Constructor
	\date		20140122 - Magnus Øverbø
**/
Agent::Agent(){
	current 		= NULL;
	memoryMap 	= NULL;
	lastMove 		= -1;
	run 				= true;
	performance = INIT_PERFORMANCE;
	swipeNumber = 1;
	STEPS				= INIT_STEPS;
}

/**
	\brief 	
	\date		20140122 - Magnus Øverbø
**/
Agent::Agent(Cell* tLocation){
	current 		= tLocation;
	memoryMap 	= tLocation;
	lastMove 		= 0;
	run 				= true;
	performance = INIT_PERFORMANCE;
	swipeNumber = 1;
	STEPS				= INIT_STEPS;
}

/**
	\brief 	
	\date		20140122 - Magnus Øverbø
	\param	
	\retval	
**/
Agent::~Agent(){}

/**
	\brief 	Moves the agent to an adjacent cell or cleans the current cell

	If the cell is dirty, the cell is cleaned and a performance point is awarded.
	If the cell is clean, it will check if the cell on the

	\date		20140122 - Magnus Øverbø
**/
void Agent::move(){
	if( current->getDirty() ){		//	If current location is dirty, clean it
		clean();
		action("Cleaned the cell", 1);
	}
	// STOP
	else if( lastMove == UP && current == memoryMap ){
		cout << "\nAction:\tI've cleaned the room. It's siesta time... FOREVER";
	}
	else{													//If location is not dirty
		if( current->isSpace() ){		//If location isn't a wall or obstacle
			if( lastMove == UP ){			//If previous movement was UP
				swipeNumber++;					//Increment the swipenumber	
				if( swipeNumber%2 == 1){//Move left if odd swipenumber
					updateLocation( LEFT );
					action("Moved to the left", -1);
				}
				else{
					updateLocation( RIGHT );
					action("Moved to the right", -1);
				}
			}	// lastMove == UP
			//if previous movement was down, left or right
			else{
				updateLocation( lastMove );
				switch(lastMove){
					case DOWN: 	action( "Moved down", -1 );				break;
					case LEFT:	action( "Moved to the left", -1 );		break;
					case RIGHT: action( "Moved to the right", -1 );		break;
				};
			} //Lastmove == DOWN | LEFT | RIGHT
		}
		else if( lastMove==UP ){	// If current location is an obstacle or wall
			updateLocation( DOWN );
			action( "Hit the upper wall, running away", -1);
		}// lastMove == UP
		else if( lastMove==RIGHT ){
			if(swipeNumber%2==0){
				current=current->getNeighbor(LEFT)->getNeighbor(UP);
				lastMove=UP;
			}else		updateLocation( LEFT );
			action( "Hit the right wall, running away", -1);
		} // lastMove == RIGHT
		else if( lastMove==LEFT ){
			if( swipeNumber%2==1){
				current=current->getNeighbor(RIGHT)->getNeighbor(UP);
				lastMove=UP;
			}else	updateLocation( RIGHT );
			action( "Hit the left wall, running away", -1);
		} // LastMove == LEFT
		else if( lastMove==DOWN ){
			current=current->getNeighbor( UP );
			++swipeCurrent;
			lastMove = (swipeNumber%2==0) ? RIGHT:LEFT;
			action( "Hit the bottom wall, running away", -1);
		}// lastMove == DOWN
	}// end !is_space();
	current->setVisited();
} // end Function

/**
	\brief 	Sets the current location and updates the lastMove variable
	\date		2014012 - Magnus Øverbø
	\param	loc		Integer describing LEFT, RIGHT, UP or DOWN
**/
void Agent::updateLocation( int loc ){
	lastMove = loc;
	current = current->getNeighbor( loc );
}

/**
	\brief 	Updates the performance of the agent and prints out the action
	performed
	\date		2014012 - Magnus Øverbø
	\param	txt		Integer with +1, 0 or -1 as its value to inc, dec or do nothing
	\param	perf	Integer to add to current performance value
**/
void Agent::action(const char txt[], int perf){
	STEPS--; 
	performance += perf;
	cout << "\nAction:\t" << txt;
}

/**
	\brief 	Cleans the current cell
	\date		20140122 - Magnus Øverbø
	\retval	true	If the clel is clean
	\retval false	If the cell is still dirty
**/
bool Agent::clean(){
	current->setDirty( false );
	current->resetAge();
	if( !current->getDirty() )
		return true;
	return false;
}

int Agent::retLocID(){
	return current->retID();
}

void Agent::visit( Cell* cur ){
	if( STEPS == 0) return;
	Cell* l, *r, *u, *d;
	l = cur->getNeighbor( LEFT );
	r = cur->getNeighbor( RIGHT );
	u = cur->getNeighbor( UP );
	d = cur->getNeighbor( DOWN );
	if( cur->isSpace() && !cur->retVisited()){
		current = cur;
		cur->setVisited();
		if( cur->getDirty()  && STEPS != 0){
			action( "Cleaning cell, performance point awarded.", 1 );
			clean();
		}
		if( l != NULL && STEPS != 0){
			action( "Moving to the left, performance point withdrawn.", -1);
			visit( l );
		}
		if( r != NULL  && STEPS != 0){
			action( "Moving to the right, performance point withdrawn.", -1);
			visit( r );
		}
		if( u != NULL  && STEPS != 0){
			action( "Moving up, performance point withdrawn.", -1);
			visit( u );
		}
		if( d != NULL  && STEPS != 0){
			action( "Moving down, performance point withdrawn.", -1);
			visit( d );
		}
	}
	else if( cur->retVisited()  && STEPS != 0){
		current = cur;
		action( "Allready visited, going back.", -1);
		return;
	}
	else if( !cur->isSpace()  && STEPS != 0){
		action( "Hit the wall, retreat.", -1);
		return;
	}
}


void Agent::printPerf(){
	cout << performance;
}

void Agent::printSteps(){
	cout << STEPS;
}

int Agent::retSteps(){
	return STEPS;
}

Cell* Agent::getCurrent(){
	return current;
}
