/**
  \file   dummyAgent.h
  \brief  Header file for the agent
  \date   20140123 - Adrian
**/

#ifndef __DUMMYAGENT_H_INCLUDED__
#define __DUMMYAGENT_H_INCLUDED__

#include "stdhd.h"
#include "environment.h"

/** Global variables used in the Agent **/
/**
	\brief	Creates a stack/list with pointer to a cell.
	
	Used for searching the graph
	\date		20140124 - Magnus Øverbø
**/
struct List{
	Cell* info;
	List* n;
	List ( Cell* i){
		info = i;
		n = NULL;
	}
};


/**
  \class  Agent
  \brief  The class for the agent that cleans the environment
  \date   20140122 - Magnus Øverbø
**/
class Agent{
  private:
	Cell* current;			/*< Pointer to the cell the agent located at */
	int 	lastMove;			/*< Direction where it is comming from */
	Cell*	memoryMap;		/*< Map pf the environment stored in memory */
	bool 	run;					/*< Working state*/
	int		moves;	/*< Performance counter for the agent */
	int		cleans;
	int 	swipeNumber;	/*< Number of swipes around the hole environment */
	int		STEPS;
	bool	corner;
  
	public:
	Agent();
	Agent( Cell* );
	~Agent();
	void move();
	bool clean();
	void action( const char txt[] );
	void updateLocation( int );
	int	 retLocID();
	void visit( Cell*, int, List* );
	void printSteps();
	void printPerf();
	int	retSteps();
	Cell* getCurrent();
	void findCorner();
	bool foundCorner();
	void shutDown();
	void boot();
	bool isRunning();
};

#endif  // __AGENT_H_INCLUDED__

