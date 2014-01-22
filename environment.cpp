
#include "environment.h"

/**
  \file   environment.cpp
  \brief  All functions for the environment classes
  \date   20140120 - Magnus Øverbø
**/

/**
  \brief  Constructor
  \date   20140120 - Magnus Øverbø
**/
Cell::Cell(){
  dirty = false;
  age   = 0;
  /*
  up    = null;
  down  = null;
  left  = null;
  right = null;
  */
}

/**
  \brief  Constructor with set state for dirty
  \date   20140120 - Magnus Øverbø
**/
Cell::Cell( bool dirty ){
  dirty = dirty;
  age   = 0;
  /*
  up    = null;
  down  = null;
  left  = null;
  right = null;
  */
}

/**
  \brief Deconstructor
  \date   20140120 - Magnus Øverbø
**/
Cell::~Cell(){
}

/**
  \brief  Sets the neighbor as indicated by the parameter
  \date   20140120 - Magnus Øverbø
  \param  id      Integer that indicates which cell pointer to set
  \param  pointer Pointer to the Cell object to place
  \retval true    Returns true if nothing failed
  \retval false   Returns false if something failed
**/
bool  Cell::setNeighbor(int id, Cell *pointer){
  bool ret = false;
  if(pointer != NULL && id >= 1 && id <= 4){
    switch( id ){
      case DOWN: down  = pointer; ret = true; break;
      case UP: up    = pointer; ret = true; break;
      case LEFT: left  = pointer; ret = true; break;
      case RIGHT: right = pointer; ret = true; break;
    }
  }
  return ret;
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
    switch( id ){
      case DOWN1: ret = down;   break;
      case UP: ret = up;     break;
      case LEFT: ret = left;   break;
      case RIGHT: ret = right;  break;
    }
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

