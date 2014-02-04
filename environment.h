/**
  \file   environment.h
  \brief  Header file for the environment
  \date   20140120 - Magnus Øverbø
**/

#ifndef __ENVIRONMENT_H_INCLUDED__
#define __ENVIRONMENT_H_INCLUDED__

#include "stdhd.h"

/**	Global Variables	**/
enum DIRECTION{ LEFT, RIGHT, UP, DOWN };	/*< Enum giving the directions */
enum TYPE{ OPEN, WALL, OBSTACLE };				/*< Enum giving the type of cell */

/**
  \class  Cell
  \brief  The class for the cells that makes up the environment
  \date   20140120 - Magnus Øverbø
**/
class Cell{
  private:
    int		key;			/*< Integer indicating the ID of the cell */
	bool  dirty;    /*< Boolean value to indicate if the cell is dirty */
    int   age;      /*< Integer indicating time it's was last cleaning */
	int		type;			/*< Integer indicatiing the type of cell(Wall, object or
											open */
	bool	visited;
    Cell  *left,    /*< Pointer to the left neighbor cell */
          *right,   /*< Pointer to the right neighbor cell */ 
          *up,      /*< Pointer to the above neighbor cell */
          *down;    /*< Pointer to the below neighbor cell */

  public:
    Cell();
    Cell( int, bool, int );
    Cell( int, bool, int, Cell*, Cell*, Cell*, Cell* );
    ~Cell();
    
		Cell* getNeighbor( int );
    void  setNeighbors( Cell*, Cell*, Cell*, Cell* );
    void  setNeighbor( int, Cell* );
    void  setNeighbor( int, Cell*,  Cell* );
    
    int   getAge();
		bool  updateAge();
    bool  resetAge();
    
    bool  getDirty();
		bool  updateDirty();
    void  setDirty( bool );
    
		void  display();
		bool	isSpace();
		
		int		retType();
		void	getType();

		void	getID();
		int		retID();
		bool	checkID( int );

		bool	retVisited();
		void	setVisited();
		void	resetVisited();
};

#endif  // __ENVIRONMENT_H_INCLUDED__ 

