
#ifndef __AGENT_H_INCLUDED__
#define __AGENT_H_INCLUDED__

#include "stdhd.h"
#include "environment.h"

/**
  \file   agent.h
  \brief  Header file for the agent
  \date   20140122 - Magnus Øverbø
**/

/** Global variables used in the Agent **/
	int INIT_PERFORMANCE = 0;	/*< The initial state of the performance measuerer */

/**
  \class  Agent
  \brief  The class for the agent that cleans the environment
  \date   20140122 - Magnus Øverbø
**/
class Agent{
  private:
	Cell* current;		/*< Pointer to the cell the agent located at */
	int lastMove;		/*< Direction where it is comming from*/
	Cell *memoryMap;	/*< Map pf the environment stored in memory*/
	bool run;		/*< Working state*/
	int performance;	/*< Performance counter for the agent */
	int swipeNumber;	/*< Number of swipes around the hole environment */

  public:
	Agent();
	Agent( Cell* tLocation);
	~Agent();
	bool move();
	bool clean();
};

#endif  // __AGENT_H_INCLUDED__

