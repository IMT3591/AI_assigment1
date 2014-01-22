
#ifndef __AGENT_H_INCLUDED__
#define __AGENT_H_INCLUDED__

#include "stdhd.h"

/**
  \file   agent.h
  \brief  Header file for the agent
  \date   20140122 - Magnus Øverbø
**/

/** Global variables used in the Agent **/
int MAX_BAT = 1000; /*< Number of steps the battery can make */
int INIT_PERFORMANCE = 0; /*< The initial state of the performance measuerer */

/**
  \class  Agent
  \brief  The class for the agent that cleans the environment
  \date   20140122 - Magnus Øverbø
**/
class Agent{
  private:
		Cell* current;			/*< Pointer to the cell the agent located at */
		Cell*	charger;			/*< Pointer to the cell where the charger is located*/
		int		performance;	/*< Performance counter for the agent */
		int		battery;			/*< Battery info, for each action the battery is
													depleted by 1 */

  public:
    Agent();
    Agent( Cell* );
		Agent( Cell*, Cell*);
  	~Agent();
		bool move();
		bool checkForDirt();
		bool clean();
		//findCharger();
		//chargeBattery();
		//depleteBattery();
};

#endif  // __AGENT_H_INCLUDED__ 

