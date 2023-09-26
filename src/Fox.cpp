#include "Fox.h"
#include "World.h"

namespace world {
	namespace animals {


void  Fox::createNewborn(const int x, const int y) {
   Organism::createNewborn(x, y, new Fox(x, y));
}


//**************************************************
// Fox never moves to the field of stronger animal *
//**************************************************
void  Fox::moveX(const int direction) {
   //******************************************************************
   //* check if desired LEFT/RIGHT field is free from stronger animal *
   //******************************************************************
   if (world->isClearFromStronger(position.first + direction, position.second, this))
      Animal::moveX(direction);
   //************************************
   //* otherwise try opposite direction *
   //* **********************************
   else if (world->isClearFromStronger(position.first - direction, position.second, this))
      Animal::moveX(-direction);
   //*****************************************************************
   //* do the same check for UP/DOWN direction if still didn't moved *
   //*****************************************************************
   else if (world->isClearFromStronger(position.first, position.second + UP, this))
      Animal::moveY(UP);
   else if (world->isClearFromStronger(position.first, position.second + DOWN, this))
      Animal::moveY(DOWN);
}


//******************
//* same as above **
//******************
void  Fox::moveY(const int direction) {
   //******************************************************************
   //* check if desired UP/DOWN field is free from stronger animal *
   //******************************************************************
   if (world->isClearFromStronger(position.first, position.second + direction, this))
      Animal::moveY(direction);
   else if (world->isClearFromStronger(position.first, position.second - direction, this))
      Animal::moveY(-direction);
   //*****************************************************************
   //* do the same check for LEFT/RIGHT direction if still didn't moved *
   //*****************************************************************
   else if (world->isClearFromStronger(position.first, position.second + LEFT, this))
      Animal::moveX(LEFT);
   else if (world->isClearFromStronger(position.first, position.second + RIGHT, this))
      Animal::moveX(RIGHT);
}


	} //end of namespace animals
}  // end of namespace world
