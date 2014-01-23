/**
  \file   environment.cpp
  \brief  All functions for the environment classes
  \date   20140120 - Magnus Øverbø
**/

#include "environment.h"

/**
  \brief  Constructor
  \date   20140120 - Magnus Øverbø
**/
Cell::Cell(){
  dirty = false;
  age   = 0;
  left  = NULL;
  right = NULL;
  up    = NULL;
  down  = NULL;
}

/**
  \brief  Constructor with set state for dirty
  \date   20140120 - Magnus Øverbø
**/
Cell::Cell( bool tDirt, int tType){
  dirty = tDirt;
	type	= tType;
  age   = 0;
  left  = NULL;
  right = NULL;
  up    = NULL;
  down  = NULL;
}

/**
  \brief  Constructor with set state for dirty
  \date   20140120 - Magnus Øverbø
**/
Cell::Cell( bool tDirt, int tType, Cell* l, Cell* r, Cell* u, Cell* d){
  dirty = tDirt;
	type	= tType;
  age   = 0;
  left  = NULL;
  right = NULL;
  up    = NULL;
  down  = NULL;
	setNeighbors( l, r, u, d );
}

/**
  \brief Deconstructor
**/
Cell::~Cell(){}

/**
  \brief  Sets the neighbor and the backlink
  \date   20140120 - Magnus Øverbø
**/
void  Cell::setNeighbor(int id, Cell *pointer, Cell* cur){
  if(pointer != NULL && id >= 1 && id <= 4){
		if( id == LEFT){
			left = pointer;
			left->setNeighbor(LEFT, cur);
		}
		else if( id == RIGHT){
			right = pointer;
			right->setNeighbor(RIGHT, cur);
		}
		else if( id == UP){
			up=pointer;
			up->setNeighbor(UP, cur);
		}
		else if( id == DOWN){
			down = pointer;	
			down->setNeighbor(DOWN, cur);
		}
  }
}

// Sets the pointer for the neighboring cell
void  Cell::setNeighbor(int id, Cell *pointer){
  if(pointer != NULL && id >= 1 && id <= 4){
		if( id == LEFT){
			left = pointer;
		}
		else if( id == RIGHT){
			right = pointer;
		}
		else if( id == UP){
			up=pointer;
		}
		else if( id == DOWN){
			down = pointer;	
		}
  }
}

void Cell::setNeighbors(Cell* l, Cell* r, Cell* u, Cell* d){
	if( l != NULL )		setNeighbor(LEFT, 	l, this);
	if( r != NULL )		setNeighbor(RIGHT, 	r, this);
	if( u != NULL )		setNeighbor(UP, 	u, this);
	if( d != NULL )		setNeighbor(DOWN, 	d, this);
}


/**
  \brief  Returns the neighbor as indicated by the parameter
  \date   20140120 - Magnus Øverbø
  \param  id   Integer that indicates which cell pointer to return 
  \retval Cell Returns the cell object as indicated by the parameter
  \retval NULL Returns the cell object with pointer to NULL if it fails
**/
Cell* Cell::getNeighbor( int id ){
  Cell* ret = NULL;
  if( id >= 1 && id <= 4 ){
		if( id == LEFT)				ret = left;
		else if( id == RIGHT)	ret = right;
		else if( id == UP)		ret = up;
		else if( id == DOWN)	ret = down;	
  }
  return ret;
}

/**
  \brief Updates the age since the cell was cleaned and creates a mess in the
  cell.

  \date   20140120 - Magnus Øverbø
  \retval false Returned if the dirty state wasn't updated or it failed
  \retval true  Returned if the dirty state was updated
**/
bool  Cell::updateAge(){
  ++age;
  if( age >= 5 && dirty == false ){
    return updateDirty();
  }
  return false;
}

/**
  \brief  Resets the age counter to 0
  \date   20140120 - Magnus Øverbø
  \retval true  Is returned if it succeeds
  \retval false Is returned if it fails
**/
bool  Cell::resetAge(){
  age = 0;
  return ((age == 0) ? true : false);
}

/**
  \brief  Returns the current age to the initiator
  \date   20140120 - Magnus Øverbø
**/
int   Cell::getAge(){
  return age;
}

/**
  \brief  Updates the dirty state of the cell if the condition is met
  \date   20140120 - Magnus Øverbø
  \retval true  Is returned if the dirty state was updated
  \retval false Is returned if the dirty state was not updated
**/
bool  Cell::updateDirty(){
  if( rand()%600 == 0 && dirty == false ){
    dirty = true;
    return true;
  }
  return false;
}

/**
  \brief  Sets the dirty state of the cell
  \date   20140120 - Magnus Øverbø
  \param  value Bool value to set the dirty state
**/
void  Cell::setDirty( bool value){
  if( value == true || value == false )
    dirty = value;
}

/**
  \brief  Returns the dirty state of the cell
  \date   20140120 - Magnus Øverbø
  \retval false   Returned if it is clean
  \retval true    Returned if it is dirty
**/
bool  Cell::getDirty(){
  return dirty;
}


/**
  \brief  Returns the dirty state of the cell
  \date   20140120 - Magnus Øverbø
**/
void Cell::display(){
  cout << "\nDirty:\t" << (( dirty ) ? "true" : "false" );
  cout << "\t\tAge:\t"   << age << " since cleaned";
  //cout << "\nAbove:\t" << (( up    == NULL ) ? "Void" : "Cell" );
  //cout << "\nBelow:\t" << (( down  == NULL ) ? "Void" : "Cell" );
  //cout << "\nLeft:\t"  << (( left  == NULL ) ? "Void" : "Cell" );
  //cout << "\nRight:\t" << (( right == NULL ) ? "Void" : "Cell" );
	//cout << "\n\n";
}

bool Cell::isSpace(){
	if( type == OPEN )
		return true;
	return false;
}

