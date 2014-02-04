/**
	\file		agent.cpp
	\date		20140122 - Magnus Øverbø
	\brief 	Functions for the agent class
**/

#include "dummyAgent.h"

int INIT_PERFORMANCE = 0;
int INIT_STEPS = 1000;
int STOP = 0;

Agent::Agent(){
	current 	= NULL;
	memoryMap = NULL;
	lastMove 	= -1;
	run 			= true;
	moves			= 0;
	cleans		= 0;
	swipeNumber = -1;
	STEPS			= INIT_STEPS;
	corner		= false;
	perf			= 0;
}

Agent::Agent(Cell* tLocation){
	current 	= tLocation;	//Sets the current location as provided
	memoryMap = tLocation;	//Sets the start of the memory map
	lastMove 	= 0;			//Sets run to true
	run 			= true;
	moves			= 0;
	cleans		= 0;
	swipeNumber = -1;
	STEPS			= INIT_STEPS;
	corner		= false;
	perf			= 0;
}

Agent::~Agent(){}

/**
	\brief 	Moves the agent to an adjacent cell, increases the counter and produces a message

	It will start from the bottom left corner and move to the right, then up 1, then left,
	the up 1, and to the right again. until it reaces the top and a side. Then it will go back down
	\date		20140122 - Adrian
**/
void Agent::move(){
	current->setVisited();
	if( swipeNumber >= 1 ){
		if( current->isSpace() ){		//If location isn't a wall or obstacle
			if( lastMove == UP ){			//If previous movement was UP
				swipeNumber++;					//Increment the swipenumber
				if( swipeNumber%2 == 1){//Move left if odd swipenumber
					updateLocation( LEFT );
					action("Moved to the left" );
				}
				else{
					updateLocation( RIGHT );
					action("Moved to the right" );
				}
			}	// lastMove == UP
			//if previous movement was down, left or right
			else {
				updateLocation( lastMove );
				switch(lastMove){
					case DOWN: 	action( "Moved down" );						break;
					case LEFT:	action( "Moved to the left" );		break;
					case RIGHT: action( "Moved to the right" );		break;
				};
			} //Lastmove == DOWN | LEFT | RIGHT
		}
		else if( lastMove==UP ){	// If current location is an obstacle or wall
			updateLocation( DOWN );
			action( "Hit the upper wall, running away" );
		}// lastMove == UP
		else if( lastMove==RIGHT ){
			if(swipeNumber%2==0){
				moves++;
				current = current->getNeighbor(LEFT)->getNeighbor(UP);
				lastMove=UP;
			}
			else updateLocation( LEFT );
			action( "Hit the right wall, running away" );
		} // lastMove == RIGHT
		else if( lastMove==LEFT ){
			if( swipeNumber%2==1){
				moves++;
				current=current->getNeighbor(RIGHT)->getNeighbor(UP);
				lastMove = UP;
			}
			else	updateLocation( RIGHT );
			action( "Hit the left wall, running away" );
		} // LastMove == LEFT
		else if( lastMove==DOWN ){
			updateLocation( UP );
			++swipeNumber;
			lastMove = (swipeNumber%2==0) ? RIGHT:LEFT;
			action( "Hit the bottom wall, running away" );
		}// lastMove == DOWN
	}// end !is_space();
} // end Function

/**
	\brief 	Sets the current location and updates the lastMove variable
	\date		2014012 - Magnus Øverbø
	\param	loc		Integer describing LEFT, RIGHT, UP or DOWN
**/
void Agent::updateLocation( int loc ){
	moves++;
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
void Agent::action(const char txt[]){
	cout << "\nAction:\t" << txt;
	STEPS--;
}

/**
	\brief 	Cleans the current cell
	\date		20140122 - Magnus Øverbø
	\retval	true	If the clel is clean
	\retval false	If the cell is still dirty
**/
bool Agent::clean(){
	action( "Cleaning cell, performance point awarded." );
	cleans++;
	current->setDirty( false );
	current->resetAge();
	if( !current->getDirty() )		return true;
	return false;
}

/**
	\brief Returns the int value of the key for the current location
**/
int Agent::retLocID(){
	return current->retID();
}

/**
	\brief Recursive function to visit an arbitrary type of environment, very 
	poor performance and it has to mark the visited locations
**/
void Agent::visit( Cell* cur, int dir, List* env ){
	moves++;
	if( STEPS <= STOP ) return;
	
	List* a = env;
	while( a != NULL ){
		if(a->info->isSpace() && !a->info->getDirty() )
			a->info->updateAge();
		a = a->n;
	}

	Cell *l, *r, *u, *d;
	l = cur->getNeighbor( LEFT );		r = cur->getNeighbor( RIGHT );
	u = cur->getNeighbor( UP );			d = cur->getNeighbor( DOWN );

	//old aquaintance reset age and visited
	if( cur->getAge() >= 10 ){
		cur->resetVisited();
		cur->resetAge();
	}
	
	current = cur;
	if( STEPS > STOP && current->isSpace() && current->getDirty() ){
		clean();
		calcPerf( env );
	}
	
	if( STEPS > STOP && current->retVisited() ){
		moves++;
		action( "Allready visited, going back." );
		calcPerf( env );
		return;
	}

	//New cell set visited
	current->setVisited();
	//if wall opr obstacle
	if( STEPS > STOP && !current->isSpace() ){
		moves++;
		action( "Hit wall/object, going back." );
		calcPerf( env );
		return;
	}

	if( STEPS > STOP && current->isSpace() && 
			dir != LEFT && r != NULL ){
		action( "Moving RIGHT" );
		calcPerf( env );
		visit( r, RIGHT, env );
		current = cur;
	}
	if( STEPS > STOP && cur->getDirty() ){
		clean();
		calcPerf( env );
	}
	if( STEPS > STOP && current->isSpace() && 
			dir != RIGHT && l != NULL ){
		action( "Moving LEFT" );
		calcPerf( env );
		visit( l, LEFT, env );
		current = cur;
	}
	if( STEPS > STOP && cur->getDirty() ){
		clean();
		calcPerf( env );
	}
	if( STEPS > STOP && current->isSpace() && 
			dir != UP && d != NULL ){
		action( "Moving DOWN" );
		calcPerf( env );
		visit( d, DOWN, env );
		current = cur;
	}
	if( STEPS > STOP && cur->getDirty() ){
		clean();
		calcPerf( env );
	}
	if( STEPS > STOP && current->isSpace() && 
			dir != DOWN && u != NULL ){
		action( "Moving UP" );
		calcPerf( env );
		visit( u, UP, env );
		current = cur;
	}
	if( STEPS > STOP && cur->getDirty() ){
		clean();
		calcPerf( env );
	}
	cur->resetVisited();
	current = cur;

	if( STEPS > STOP ){
		action("Going back, where I came from.");
		calcPerf( env );
		moves++;
	}
	return;
}

/**
	\brief	Moves left and down untill it hits both walls or NULL. then it has
	found the bottom left corner.
**/
void Agent::findCorner(){
	if( swipeNumber == -1 ){
		if( current->isSpace() && current->getNeighbor(DOWN) != NULL) {
			updateLocation(DOWN);
			action( "Trying to find the starting point." );
		}
		else{
			if( !current->isSpace() )	updateLocation(UP);
			swipeNumber++;
			action( "Found bottom row, looking for the corner." );
		}
	}
	else if( swipeNumber == 0 ){
		if( current->isSpace() && current->getNeighbor(LEFT) != NULL ){
			updateLocation(LEFT);
			action( "Walking my way to the bottom left corener, nearly there" );
		}
		else{
			if( !current->isSpace() ) updateLocation(RIGHT);
			corner = true;
			swipeNumber++;
			action( "Found it! let's start cleaning" );
		}
	}
}

/**
	\brief Prints the performance data of the agent
**/
void Agent::printPerf(){
	cout << "Steps:\t\t"				<< STEPS	<< "\n";
	cout << "Movements:\t" 			<< moves	<< "\n";
	cout << "Cells cleaned:\t"	<< cleans << "\n";
	cout << "Internal Perf:\t"	<< perf		<< "\n";
}

/**
	\brief Prints the number of steps remaining
**/
void Agent::printSteps(){
	cout << STEPS;
}

/**
	\brief Returns the int value of STEPS
**/
int Agent::retSteps(){
	return STEPS;
}

/**
	\brief Returns the cell of current location
**/
Cell* Agent::getCurrent(){
	return current;
}

/**
	\brief Returns the status of wether the corner was found
**/
bool Agent::foundCorner(){
	return corner;
}

void Agent::shutDown(){
	run = false;
}

void Agent::boot(){
	run = true;
}

bool Agent::isRunning(){
	return run;
}

void Agent::calcPerf( List* env ){
	List* a = env;
	while( a != NULL ){
		if( a->info->isSpace() && !a->info->getDirty() )
			perf++;
		a = a->n;
	}
}
