/**
	\file		agent.cpp
	\date		20140122 - Magnus Øverbø
	\brief 	Functions for the agent class
**/

#include "dummyAgent.h"

int INIT_PERFORMANCE = 0;

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
		cout << "\nAction:\tIve cleaned the room. It's siesta time... FOREVER";
	}
	//NO OPERATION BECAUSE THE CURRENT LOCATION HAS A GOOD CHANCE OF BECOMING
	//DIRTY AGAIN
	else if( current->getAge() >= 10 && !current->getDirty() ){
		cout << "\nAction:\tIt's siesta time. Until This spot becomes dirty again";
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
			else if( lastMove == DOWN || lastMove == LEFT || lastMove == RIGHT){
				updateLocation( lastMove );
				switch(lastMove){
					case DOWN: 	action( "Moved down", -1 );						break;
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
			}
			else		updateLocation( LEFT );
			action( "Hit the right wall, running away", -1);
		} // lastMove == RIGHT
		else if( lastMove==LEFT ){
			if( swipeNumber%2==1){
				current=current->getNeighbor(RIGHT)->getNeighbor(UP);
				lastMove=UP;
			}else{
				updateLocation( RIGHT );
			}
			action( "Hit the left wall, running away", -1);
		} // LastMove == LEFT
		
		else if( lastMove==DOWN ){
			current=current->getNeighbor( UP );
			lastMove = (swipeNumber%2==0) ? RIGHT:LEFT;
			action( "Hit the bottom wall, running away", -1);
		}// lastMove == DOWN
	}// end !is_space();
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

