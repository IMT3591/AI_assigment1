
#include "dummyAgent.h"

/**
	\file		agent.cpp
	\date		20140122 - Magnus Øverbø
	\brief 	Functions for the agent class
**/

/**
	\brief 	Functions for the agent class
	\date		20140122 - Magnus Øverbø
	\param	
	\retval	
**/

Agent::Agent(){}

/**
	\brief 	
	\date		20140122 - Magnus Øverbø
	\param	
	\retval	
**/

Agent::Agent(Cell* tLocation){
	current = tLocation;
	memoryMap = tLocation;
	lastMove = 0;
	run = true;
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
	\param
	\retval
**/

bool Agent::move(){
	bool ret = false;
		//	Check if location is dirty and clean it
	if( current->getDirty() ){
		clean();
		ret = true;
		performance++;
		cout << "\nAction:\t\tCleaned cell";
	}else if( current->isSpace() ){
		if( lastMove == UP ){
			ret=true;
			performance--;
			swipeNumber++;
			if( swipeNumber%2 == 1){
				current=current->getNeighbour(LEFT);
				// Memorymap
				lastMove=LEFT;
				cout << "\nAction:\t\tMoved to the cell on the left";
			}else{
				current=current->getNeighbour(RIGHT);
				//Memorymap
				lastMove=RIGHT;
				cout << "\nAction:\t\tMoved to the cell on the right";
			}
		}else if( lastMove == DOWN || lastMove == LEFT || lastMove == RIGHT){
			current=current->getNeighbour(lastMove);
			//Memorymap
			ret=true;
			performance--;
			switch(lastMove){
				case DOWN: cout << "\nAction:\t\tMoved to the cell bellow"; break;
				case LEFT: cout << "\nAction:\t\tMoved to the cell on the left";break;
				case RIGHT: cout << "\nAction:\t\tMoved to the cell on the right";break;
			};
		}else {
			current=current->getNeighbour(LEFT);
			//Memorymap
			ret=true;
			performance--;
			lastMove=LEFT;
			cout << "\nAction:\t\tMoved to the cell on the left";
		}else if( lastMove==UP ){
			current=current->getNeighbour(DOWN);
			ret=true;
			performance--;
			lastMove=DOWN;
			cout << "\nAction:\t\tHitted the wall above";
		}else if( lastMove==RIGHT ){
			if(swipeNumber%2==0){
				current=current->getNeighbour(LEFT)->getNeighbour(UP);
				lastMove=UP;
			}else{
				current=*current->getNeighbour(LEFT);
				lastMove=LEFT;
			}
			ret=true;
			performance--;
			cout << "\nAction:\t\tHitted the right wall, running away";
		}else if( lastMove==LEFT ){
			if( swipeNumber%2==1){
				current=*current->getNeighbour(RIGHT)->getNeighbour(UP);
				lastMove=UP;
			}else{
				current=*current->getNeighbour(RIGHT);
				lastMove=RIGHT;
			}
			ret=true;
			performance--;
			cout << "\nAction:\t\tHitted the left wall, running away";
		}else if( lastMove==DOWN ){
			current=*current->getNeighbour(UP);
			lastMove = (swipeNumber%2==0) ? RIGHT:LEFT;
			ret=true;
			performance--;
			cout << "\nAction:\t\tHitted the bottom wall, running away";
		}
	}
	return ret;
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

#endif  // __AGENT_H_INCLUDED__ 
