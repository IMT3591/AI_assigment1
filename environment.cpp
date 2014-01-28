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
  key		= -1;
	dirty = false;
	visited = false;
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
Cell::Cell( int tKey, bool tDirt, int tType){
	key		= tKey;
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
Cell::Cell( int tKey, bool tDirt, int tType, Cell* l, Cell* r, Cell* u, Cell* d){
	key		= tKey;
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
  \brief  Sets pointer of the adjacent cells if its not NULL
  \date   20140123 - Magnus Øverbø
	\param	Cell*	Left link
	\param	Cell*	Right link
	\param	Cell*	Up link
	\param	Cell*	Down link
**/
void Cell::setNeighbors(Cell* l, Cell* r, Cell* u, Cell* d){
	if( l != NULL )		setNeighbor(LEFT, 	l, this);
	if( r != NULL )		setNeighbor(RIGHT, 	r, this);
	if( u != NULL )		setNeighbor(UP, 		u, this);
	if( d != NULL )		setNeighbor(DOWN, 	d, this);
}

/**
  \brief  Sets pointer of the adjacent cell if its not NULL and calls the
	linkback function
  \date   20140123 - Magnus Øverbø
**/
void  Cell::setNeighbor(int id, Cell *pointer, Cell* cur){
	if( pointer != NULL && id >= LEFT && id <= DOWN){
		if( id == LEFT){
			left = pointer;
			left->setNeighbor(RIGHT, cur);
		}
		else if( id == RIGHT){
			right = pointer;
			right->setNeighbor(LEFT, cur);
		}
		else if( id == UP){
			up=pointer;
			up->setNeighbor(DOWN, cur);
		}
		else if( id == DOWN){
			down = pointer;	
			down->setNeighbor(UP, cur);
		}
  }
}

/**
  \brief  Sets the pointer of the adjacent cell 
  \date   20140123 - Magnus Øverbø
	\param	Cell* Pointer to the adjacent cell
	\param	int		Integer to state which link to set
**/
void  Cell::setNeighbor(int id, Cell *pointer){
	if( pointer != NULL && id >= LEFT && id <= DOWN){
		if( 		 id == LEFT){		left 	= pointer;		}
		else if( id == RIGHT){	right = pointer;		}
		else if( id == UP){			up		= pointer;		}
		else if( id == DOWN){		down	= pointer;		}
  }
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
  if( LEFT >= 0 && id <= DOWN ){
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
  \brief  Displays the information about the current and adjacent cells
  \date   20140120 - Magnus Øverbø
**/
void Cell::display(){
	getID();
	cout << " ("; getType(); cout << ")";
  cout << "\n---------------------------------------------------------------\n";
	//cout << "\n\tDirty:\t" << (( dirty ) ? "true" : "false" ); 
  //cout << "\tAge:\t"   << age << " since cleaned\t\t";
  //cout << "\n\tLeft:\t";
		if ( left  == NULL ) cout << "NONE\t";
		else{
				left->getID();
				cout << "("; left->getType(); cout << ")\t";
		}

  //cout << "\tRight:\t";
		if ( right  == NULL ) cout << "NONE\t";
		else{
				right->getID();
				cout << "("; right->getType(); cout << ")\t";
		}

  //cout << "\tAbove:\t";
		if ( up  == NULL ) cout << "NONE\t";
		else{
				up->getID();
				cout << " ("; up->getType(); cout << ")\t";
		}

  //cout << "\tBelow:\t";
		if ( down  == NULL ) cout << "NONE\t";
		else{
				down->getID();
				cout << "("; down->getType(); cout << ")\t";
		}
	cout << "\n\n";
}

// Prints the type of cell
void Cell::getType(){
	if( type == OPEN )
		cout << "S";
		//cout << "OPEN";
	else if( type == OBSTACLE )
		cout << "O";
		//cout << "Obstacle";
	else
		cout << "W";
		//cout << "Wall";
}

int Cell::retType(){
	return type;
}

/**
	\brief	Returns true of the cell is an open space
	\date		20140123 - Magnus Øverbø
**/
bool Cell::isSpace(){
	if( type == OPEN )
		return true;
	return false;
}

// Prints the ID of the cell
void Cell::getID(){
	cout << key;
}

/**
	\brief	Returns true of the id is an match
	\date		20140123 - Magnus Øverbø
**/
bool Cell::checkID( int id){
	if( key == id )	return true;
	return false;
}


int Cell::retID(){
	return key;
}

bool Cell::retVisited(){
	return visited;
}

void  Cell::setVisited(){
	visited = true;
}