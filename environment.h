
#ifndef __ENVIRONMENT_H_INCLUDED__
#define __ENVIRONMENT_H_INCLUDED__

#include "stdhd.h"

/**
  \file   environment.h
  \brief  Header file for the environment
  \date   20140120 - Magnus Øverbø
**/

/**
 \Global Variables
**/
const enum DIRECTION{ LEFT, RIGHT, UP, DOWN };
const enum TYPE{ OPEN, WALL, OBSTACLE };

/**
  \class  Cell
  \brief  The class for the cells that makes up the environment
  \date   20140120 - Magnus Øverbø
**/
class Cell{
  private:
    bool  dirty;    /*< Boolean value to indicate if the cell is dirty */
    int   age;      /*< Integer indicating time it's was last cleaning */
    Cell  *left,    /*< Pointer to the left neighbor cell */
          *right,   /*< Pointer to the right neighbor cell */ 
          *up,      /*< Pointer to the above neighbor cell */
          *down;    /*< Pointer to the below neighbor cell */

  public:
    Cell();
    Cell( bool, int );
    Cell( bool, int, Cell*, Cell*, Cell*, Cell* );
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
};

#endif  // __ENVIRONMENT_H_INCLUDED__ 

