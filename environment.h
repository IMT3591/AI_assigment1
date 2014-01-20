
/**
  \file   environment.h
  \brief  Header file for the environment
  \date   20140120 - Magnus Øverbø
**/

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
    ~Cell();
    bool  setNeighbor( int id, Cell *pointer );
    Cell* getNeighbor( int id );
    bool  updateAge();
    bool  resetAge(int)
    int   getAge();
    bool  updateDirty();
    void  setDirty();
    bool  getDirty();
}


